open CounterReducer;
open TextReducer;
open ColorDataReducer;

type appState = {
  counter: counterState,
  text: textState,
  colorData: colorDataState,
};

type Middleware.thunk(_) +=
  | TextAction(textAction)
  | CounterAction(counterAction)
  | ColorDataAction(colorDataAction);

let appReducer = (state: appState, action) =>
  switch (action) {
  | TextAction(action) => {...state, text: textReducer(state.text, action)}
  | CounterAction(action) => {
      ...state,
      counter: counterReducer(state.counter, action),
    }
  | ColorDataAction(action) => {
      ...state,
      colorData: colorDataReducer(state.colorData, action),
    }
  | _ => state
  };

type t = Reductive.Store.t(Middleware.thunk(appState), appState);

let createStore = (): t => {
  let baseUrl = "https://reqres.in/api/";

  let thunkMiddleware =
    Middleware.middleware(Api.createDataProvider(~baseUrl));

  let thunkEnhancer = (store, next) => thunkMiddleware(store) @@ next;

  let preloadedState: appState = {
    counter: counterInitialState,
    text: textInitialState,
    colorData: colorDataInitialState,
  };

  let storeEnhancer =
    ReductiveDevTools.(
      Connectors.reductiveEnhancer(
        Extension.enhancerOptions(~name="ReductiveApp", ()),
      )
    );

  let store: t =
    (storeEnhancer @@ Reductive.Store.create)(
      ~reducer=appReducer,
      ~preloadedState,
      ~enhancer=thunkEnhancer,
      (),
    );
  store;
};
