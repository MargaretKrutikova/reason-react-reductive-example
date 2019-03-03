open Types;
open Decode;

type fetchColorResult =
  | Success(colorInfo)
  | Error;

type dataProvider = {fetchColorData: int => Js.Promise.t(fetchColorResult)};

let createDataProvider = (~baseUrl: string): dataProvider => {
  let fetchColorData = (colorId: int) =>
    Js.Promise.(
      Axios.get(baseUrl ++ "unknown/" ++ string_of_int(colorId))
      |> then_(response =>
           Success(response##data |> decodeColorResponse) |> resolve
         )
      |> catch(_ => Error |> resolve)
    );

  {fetchColorData: fetchColorData};
};

let createFakeDataProvider = (): dataProvider => {
  {
    fetchColorData: (colorId: int) =>
      Js.Promise.resolve(Success({id: 1, color: "#000", name: "black"})),
  };
};
