type counterAction =
  | Increment
  | Decrement;

type counterState = int;

let counterReducer = (state, action) =>
  switch (action) {
  | Increment => state + 1
  | Decrement => state - 1
  };

let counterInitialState: counterState = 0;
