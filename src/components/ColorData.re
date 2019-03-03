open AppStore;

module ColorDataProvider = {
  let make =
    StoreProvider.createMake(~name="ColorDataProvider", ~lense=s =>
      s.colorData
    );
};

let colorBoxStyles = color =>
  ReactDOMRe.Style.make(
    ~width="100px",
    ~height="100px",
    ~marginBottom="20px",
    ~marginTop="20px",
    ~backgroundColor=color,
    (),
  );

module ColorDataComponent = {
  let component =
    ReasonReact.statelessComponentWithRetainedProps("ColorData");
  let make = (~state: ColorDataReducer.colorDataState, ~dispatch, _children) => {
    let fetchColor = id => {
      dispatch(Middleware.Thunk(ColorThunk.fetchData(id)));
    };
    let fetchRandomColor = () => {
      let randomId = Random.int(11) + 1;
      fetchColor(randomId);
    };
    {
      ...component,
      ReasonReact.retainedProps: state,
      didMount: _self => {
        fetchColor(1);
      },
      render: _self =>
        <>
          <button onClick={_event => fetchRandomColor()}>
            {ReasonReact.string("Refresh color")}
          </button>
          {state.loading ?
             <h3> {ReasonReact.string("Loading ...")} </h3> :
             <div>
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
        </>,
    };
  };
};

let make = children =>
  ColorDataProvider.make(~component=ColorDataComponent.make, children);
