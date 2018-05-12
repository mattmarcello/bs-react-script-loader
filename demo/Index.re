ReactDOMRe.renderToElementWithId(
  <Script url="https://www.gstatic.com/charts/loader.js">
    ...(
         remote =>
           switch (remote) {
           | Script.NotAsked => ReasonReact.string("not asked")
           | Script.Loading => ReasonReact.string("loading")
           | Script.Success => ReasonReact.string("success")
           | Script.Failure => ReasonReact.string("failure")
           }
       )
  </Script>,
  "index1",
);
ReactDOMRe.renderToElementWithId(
  <Script url="https://www.gstatic.com/charts/loader.js">
    ...(
         remote =>
           switch (remote) {
           | Script.NotAsked => ReasonReact.string("not asked")
           | Script.Loading => ReasonReact.string("loading asked")
           | Script.Success => ReasonReact.string("success")
           | Script.Failure => ReasonReact.string("failure")
           }
       )
  </Script>,
  "index2",
);
ReactDOMRe.renderToElementWithId(
  <Script url="https://www.gstatic.asdfasdfcom/charts/loader.js">
    ...(
         remote =>
           switch (remote) {
           | Script.NotAsked => ReasonReact.string("not asked")
           | Script.Loading => ReasonReact.string("loading asked")
           | Script.Success => ReasonReact.string("success")
           | Script.Failure => ReasonReact.string("failure")
           }
       )
  </Script>,
  "index3",
);
ReactDOMRe.renderToElementWithId(
  <Script url="https://www.gstatic.asdfasdfcom/charts/loader.js">
    ...(
         remote =>
           switch (remote) {
           | Script.NotAsked => ReasonReact.string("not asked")
           | Script.Loading => ReasonReact.string("loading asked")
           | Script.Success => ReasonReact.string("success")
           | Script.Failure => ReasonReact.string("failure")
           }
       )
  </Script>,
  "index4",
);
ReactDOMRe.renderToElementWithId(
  <Script url="https://www.gstatic.asdfasdfcom/charts/loader.js">
    ...(
         remote =>
           switch (remote) {
           | Script.NotAsked => ReasonReact.string("not asked")
           | Script.Loading => ReasonReact.string("loading asked")
           | Script.Success => ReasonReact.string("success")
           | Script.Failure => ReasonReact.string("failure")
           }
       )
  </Script>,
  "index3",
);
