type textAction =
  | AppendA
  | AppendB;

type textState = string;

let textReducer = (state, action) =>
  switch (action) {
  | AppendA => state ++ "A"
  | AppendB => state ++ "B"
  };

let textInitialState: textState = "";
