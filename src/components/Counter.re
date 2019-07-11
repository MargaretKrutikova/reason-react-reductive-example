open AppStore;

module CounterProvider = {
  let make =
    StoreProvider.createMake(~name="CounterProvider", ~lense=s => s.counter);
};

module CounterComponent = {
  let component = ReasonReact.statelessComponentWithRetainedProps("Counter");
  let make = (~state, ~dispatch, ~text: string, _children) => {
    ...component,
    ReasonReact.retainedProps: state,
    render: _self =>
      <div>
        <h1> {ReasonReact.string(text)} </h1>
        <h2> {ReasonReact.string("Counter: " ++ string_of_int(state))} </h2>
        <button onClick={_ => dispatch(CounterAction(Increment()))}>
          {ReasonReact.string("++")}
        </button>
        <button onClick={_ => dispatch(CounterAction(Decrement()))}>
          {ReasonReact.string("--")}
        </button>
      </div>,
  };
};

let make = (~text, children) =>
  CounterProvider.make(~component=CounterComponent.make(~text), children);
