type state = {helloCount: int};

type action =
  | Update;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {helloCount: 0},
  reducer: (action, state) =>
    switch (action) {
    | Update => ReasonReact.Update({helloCount: state.helloCount + 1})
    },
  render: self =>
    <div>
      <button onClick={_event => self.send(Update)}>
        {ReasonReact.string("Hello")}
      </button>
      <Counter
        text={"Hello " ++ string_of_int(self.state.helloCount) ++ " times"}
      />
      <Text />
    </div>,
};
