open AppStore;
open Api;

let fetchData =
    (
      colorId: int,
      dispatch: Middleware.thunk(appState) => unit,
      _state: appState,
      dataProvider: Api.dataProvider,
    ) => {
  dispatch(ColorDataAction(Fetch));

  Js.Promise.(
    dataProvider.fetchColorData(colorId)
    |> then_(result =>
         switch (result) {
         | Success(colorInfo) =>
           dispatch(ColorDataAction(Success(colorInfo))) |> resolve
         | Error => dispatch(ColorDataAction(Failure)) |> resolve
         }
       )
  )
  |> ignore;
};
