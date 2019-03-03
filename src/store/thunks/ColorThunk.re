open AppStore;
open Api;

let fetchColorById =
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

let fetchRandomColor =
    (
      dispatch: Middleware.thunk(appState) => unit,
      state: appState,
      dataProvider: Api.dataProvider,
    ) => {
  // the api only has colors for ids from 1 to 12
  let randomId = Random.int(11) + 1;
  fetchColorById(randomId, dispatch, state, dataProvider);
};
