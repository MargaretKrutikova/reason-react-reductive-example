open CounterReducer;
open TextReducer;
open ColorDataReducer;

type appState = {
  counter: counterState,
  text: textState,
  colorData: colorDataState,
};

type action('state) = [ 
  Middleware.thunk('state)
  | `TextAction(textAction)
  | `CounterAction(counterAction)
  | `ColorDataAction(colorDataAction)
];

let appReducer = (state: appState, action: action('state)) =>
  switch (action) {
  | `TextAction(action) => {...state, text: textReducer(state.text, action)}
  | `CounterAction(action) => {
      ...state,
      counter: counterReducer(state.counter, action),
    }
  | `ColorDataAction(action) => {
      ...state,
      colorData: colorDataReducer(state.colorData, action),
    }
  | _ => state
  };

type appStore = Reductive.Store.t(Middleware.thunk(appState), appState);

let createStore = (dataProvider: Api.dataProvider): appStore => {
  let thunkMiddleware = Middleware.middleware(dataProvider);

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

  let store: appStore =
    (storeEnhancer @@ Reductive.Store.create)(
      ~reducer=Obj.magic(appReducer),
      ~preloadedState,
      ~enhancer=Obj.magic(thunkEnhancer),
      (),
    );
  store;
};
