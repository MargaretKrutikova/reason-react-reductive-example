type thunk('state) = ..;

type thunkFunc('state) =
  (thunk('state) => unit, 'state, Api.dataProvider) => unit;

type thunk('state) +=
  | Thunk(thunkFunc('state));

let middleware = (dataProvider: Api.dataProvider, store, next, action) =>
  switch (action) {
  | Thunk(func) =>
    func(
      Reductive.Store.dispatch(store),
      Reductive.Store.getState(store),
      dataProvider,
    )
  | _ => next(action)
  };
