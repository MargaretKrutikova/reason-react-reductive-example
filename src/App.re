type state = {helloCount: int};

type action =
  | Update;

let component = ReasonReact.reducerComponent("App");

let mainStyles = ReactDOMRe.Style.make(~maxWidth="600px", ());
let wrapperStyles =
  ReactDOMRe.Style.make(
    ~paddingBottom="20px",
    ~marginBottom="20px",
    ~borderBottom="1px solid #ccc",
    (),
  );

let make = _children => {
  ...component,
  initialState: () => {helloCount: 0},
  reducer: (action, state) =>
    switch (action) {
    | Update => ReasonReact.Update({helloCount: state.helloCount + 1})
    },
  render: self =>
    <main style=mainStyles>
      <div style=wrapperStyles> <ColorData /> </div>
      <div style=wrapperStyles>
        <button onClick={_event => self.send(Update)}>
          {ReasonReact.string("Hello")}
        </button>
        <Counter
          text={"Hello " ++ string_of_int(self.state.helloCount) ++ " times"}
        />
      </div>
      <Text />
    </main>,
};
