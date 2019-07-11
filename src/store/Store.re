let store = AppStore.createStore();

module StoreContext = {
  include Context.Make({
    type context = AppStore.t;
    let defaultValue = store;
  });
};

module Provider = {
  [@react.component]
  let make = (~children) => {
    <StoreContext.Provider value=store> children </StoreContext.Provider>;
  };
};

let useSelector = selector => {
  let storeFromContext = React.useContext(StoreContext.context);
  let (_, forceUpdate) = React.useReducer((s, _) => s + 1, 0);

  let latestSelectedModel =
    React.useRef(selector(Reductive.Store.getState(store)));

  React.useLayoutEffect1(
    () => {
      let checkForUpdates = () => {
        let newSelectedState = selector(Reductive.Store.getState(store));

        let hasStateChanged =
          newSelectedState !== React.Ref.current(latestSelectedModel);

        if (hasStateChanged) {
          React.Ref.setCurrent(latestSelectedModel, newSelectedState);
          forceUpdate();
        };
      };
      Some(Reductive.Store.subscribe(storeFromContext, checkForUpdates));
    },
    [|storeFromContext|],
  );

  React.Ref.current(latestSelectedModel);
};

let useDispatch = () => {
  let storeFromContext = React.useContext(StoreContext.context);
  Reductive.Store.dispatch(storeFromContext);
};
