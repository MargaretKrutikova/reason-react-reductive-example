open Json.Decode;
open Types;

let decodeColorInfo = (json): colorInfo => {
  {
    id: json |> field("id", int),
    color: json |> field("color", string),
    name: json |> field("name", string),
  };
};

let decodeColorResponse = (json): colorInfo => {
  let response = {data: json |> field("data", decodeColorInfo)};
  response.data
};
