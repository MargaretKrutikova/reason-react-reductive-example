open Types;

type colorDataAction =
  | Fetch
  | Success(colorInfo)
  | Failure;

type colorDataState = {
  loading: bool,
  error: bool,
  color: option(colorInfo),
};

let colorDataReducer = (state, action) =>
  switch (action) {
  | Fetch => {...state, loading: true, error: false}
  | Success(color) => {color: Some(color), loading: false, error: false}
  | Failure => {...state, loading: false, error: true}
  };

let colorDataInitialState: colorDataState = {
  loading: false,
  error: false,
  color: None,
};
