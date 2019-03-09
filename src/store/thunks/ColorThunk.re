open AppStore;
open Api;

let fetchColorById =
    (
      colorId: int,
      dispatch: action('state) => unit,
      _state: appState,
      dataProvider: Api.dataProvider,
    ) => {
  dispatch(`ColorDataAction(ColorDataReducer.Fetch));

  Js.Promise.(
    dataProvider.fetchColorData(colorId)
    |> then_(result =>
         switch (result) {
         | Success(colorInfo) =>
           dispatch(`ColorDataAction(Success(colorInfo))) |> resolve
         | Error => dispatch(`ColorDataAction(Failure)) |> resolve
         }
       )
  )
  |> ignore;
};

let fetchRandomColor =
    (
      dispatch: action('state) => unit,
      state: appState,
      dataProvider: Api.dataProvider,
    ) => {
  let randomId = Random.int(11) + 1;
  fetchColorById(randomId, dispatch, state, dataProvider);
};
