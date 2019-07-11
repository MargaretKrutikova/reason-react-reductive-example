open AppStore;

[@react.component]
let make = () => {
  let state = Store.useSelector(state => state.text);
  let dispatch = Store.useDispatch();

  <div>
    <h2> {ReasonReact.string("Text: " ++ state)} </h2>
    <button onClick={_ => dispatch(TextAction(AppendA()))}>
      {ReasonReact.string("+A")}
    </button>
    <button onClick={_ => dispatch(TextAction(AppendB()))}>
      {ReasonReact.string("+B")}
    </button>
  </div>;
};
