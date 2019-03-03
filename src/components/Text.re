open AppStore;

module TextProvider = {
  let make =
    Reductive.Lense.createMake(
      ~name="TextProvider",
      ~lense=(s: appState) => s.text,
      store,
    );
};

module TextComponent = {
  let component = ReasonReact.statelessComponentWithRetainedProps("Text");
  let make = (~state: string, ~dispatch, _children) => {
    ...component,
    ReasonReact.retainedProps: state,
    render: _self =>
      <div>
        <h2> {ReasonReact.string("Text: " ++ state)} </h2>
        <button onClick={_ => dispatch(AppStore.TextAction(AppendA))}>
          {ReasonReact.string("+A")}
        </button>
        <button onClick={_ => dispatch(AppStore.TextAction(AppendB))}>
          {ReasonReact.string("+B")}
        </button>
      </div>,
  };
};

let make = children =>
  TextProvider.make(~component=TextComponent.make, children);
