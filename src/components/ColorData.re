open AppStore;

let cotainerStyles = ReactDOMRe.Style.make(~height="180px", ());
let colorBoxStyles = color =>
  ReactDOMRe.Style.make(
    ~width="100px",
    ~height="100px",
    ~marginBottom="20px",
    ~marginTop="20px",
    ~backgroundColor=color,
    (),
  );

let fetchRandomColor = dispatch => {
  dispatch(Middleware.Thunk(ColorThunk.fetchRandomColor));
};

[@react.component]
let make = () => {
  let state = Store.useSelector(state => state.colorData);
  let dispatch = Store.useDispatch();

  <div style=cotainerStyles>
    <button onClick={_event => fetchRandomColor(dispatch)}>
      {ReasonReact.string("Refresh color")}
    </button>
    {state.loading
       ? <h3> {ReasonReact.string("Loading ...")} </h3>
       : <div>
           {switch (state.color) {
            | Some(colorInfo) =>
              <>
                <div style={colorBoxStyles(colorInfo.color)} />
                <h3>
                  {ReasonReact.string("Color name: " ++ colorInfo.name)}
                </h3>
              </>
            | None => <h3> {ReasonReact.string("No color loaded")} </h3>
            }}
         </div>}
  </div>;
};
