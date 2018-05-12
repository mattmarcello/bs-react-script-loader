# bs-react-script-loader

A script loader for reason-react.

A debt is owed to: https://github.com/blueberryapps/react-load-script

## usage 

All you can do is pass a `url`. 


```
  /* script is only loaded once */
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

## installation

```sh
npm install --save bs-react-script-loader
```

Then add `bs-react-script-loader` to `bs-dependencies` in your `bsconfig.json`:
```js
{
  ...
  "bs-dependencies": ["bs-react-script-loader"]
}
```


## demo

```sh
yarn
yarn start
# in another tab
yarn run webpack
```
After you see the webpack compilation succeed (the `npm run webpack` step), open up `demo/index.html` (**no server needed!**).


