open AppStore;

[@react.component]
let make = () => {
  let state = Store.useSelector(state => state.counter);
  let dispatch = Store.useDispatch();

  <div>
    <h2> {ReasonReact.string("Counter: " ++ string_of_int(state))} </h2>
    <button onClick={_ => dispatch(CounterAction(Increment()))}>
      {ReasonReact.string("++")}
    </button>
    <button onClick={_ => dispatch(CounterAction(Decrement()))}>
      {ReasonReact.string("--")}
    </button>
  </div>;
};
