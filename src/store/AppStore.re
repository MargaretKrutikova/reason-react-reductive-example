open CounterReducer;
open TextReducer;

type appAction =
  | TextAction(textAction)
  | CounterAction(counterAction);

type appState = {
  counter: counterState,
  text: textState,
};

let appReducer = (state: appState, action: appAction) =>
  switch (action) {
  | TextAction(action) => {...state, text: textReducer(state.text, action)}
  | CounterAction(action) => {
      ...state,
      counter: counterReducer(state.counter, action),
    }
  };

let preloadedState: appState = {
  counter: counterInitialState,
  text: textInitialState,
};

let storeEnhancer =
  ReductiveDevTools.(
    Connectors.reductiveEnhancer(
      Extension.enhancerOptions(~name="ReductiveApp", ()),
    )
  );

let store =
  (storeEnhancer @@ Reductive.Store.create)(
    ~reducer=appReducer,
    ~preloadedState,
    (),
  );
