let mainStyles = ReactDOMRe.Style.make(~maxWidth="600px", ());
let wrapperStyles =
  ReactDOMRe.Style.make(
    ~paddingBottom="20px",
    ~marginBottom="20px",
    ~borderBottom="1px solid #ccc",
    (),
  );

[@react.component]
let make = () => {
  <main style=mainStyles>
    <div style=wrapperStyles> <ColorData /> </div>
    <div style=wrapperStyles> <Counter /> </div>
    <Text />
  </main>;
};
