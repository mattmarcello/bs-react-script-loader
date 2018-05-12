# bs-react-script-loader

Script loader for reason-react.


# usage 

```
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
  </Script>
```


## Run Demo

```sh
yarn
yarn start
# in another tab
yarn run webpack
```
After you see the webpack compilation succeed (the `npm run webpack` step), open up `demo/index.html` (**no server needed!**).


