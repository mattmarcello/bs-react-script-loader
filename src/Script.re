type element;

[@bs.val]
external createElement : string => element = "document.createElement";

[@bs.set] external setSrc : (element, string) => unit = "src";

[@bs.set] external setOnload : (element, unit => unit) => unit = "onload";

[@bs.set] external setOnerror : (element, unit => unit) => unit = "onerror";

[@bs.val]
external appendChild : element => element = "document.body.appendChild";

type observer = {
  onload: unit => unit,
  onerror: unit => unit,
};

type remote =
  | NotAsked
  | Loading
  | Success
  | Failure;

type state = {
  remote,
  id: int,
};

type action =
  | Initialize
  | CreateScript
  | Onload
  | Onerror
  | FlushOnload
  | FlushOnerror;

let component = ReasonReact.reducerComponent("Script");

let loadedScripts = ref(Belt.Set.String.empty);

let erroredScripts = ref(Belt.Set.String.empty);

let observers = ref(Belt.Map.String.empty);

let idCount = ref(0);

let make = (~url, children) => {
  ...component,
  initialState: () => {
    idCount := idCount^ + 1;
    {remote: NotAsked, id: idCount^};
  },
  didMount: self => self.send(Initialize),
  reducer: (action, state: state) =>
    switch (action) {
    | Initialize =>
      let loaded = Belt.Set.String.has(loadedScripts^, url);
      let errored = Belt.Set.String.has(erroredScripts^, url);
      let loading = Belt.Map.String.has(observers^, url);
      switch (loaded, errored, loading) {
      | (true, _, _) => ReasonReact.Update({...state, remote: Success})
      | (_, true, _) => ReasonReact.Update({...state, remote: Failure})
      | (_, _, true) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, remote: Loading},
          (
            self =>
              observers :=
                Belt.Map.String.set(
                  observers^,
                  url,
                  Belt.Map.String.get(observers^, url)
                  |> Belt.Option.getWithDefault(_, Belt.Map.Int.empty)
                  |> Belt.Map.Int.set(
                       _,
                       self.state.id,
                       {
                         onerror: () => self.send(Onerror),
                         onload: () => self.send(Onload),
                       },
                     ),
                )
          ),
        )
      | (false, false, false) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, remote: Loading},
          (
            self => {
              observers :=
                Belt.Map.String.set(
                  observers^,
                  url,
                  Belt.Map.String.get(observers^, url)
                  |> Belt.Option.getWithDefault(_, Belt.Map.Int.empty)
                  |> Belt.Map.Int.set(
                       _,
                       self.state.id,
                       {
                         onerror: () => self.send(Onerror),
                         onload: () => self.send(Onload),
                       },
                     ),
                );
              self.send(CreateScript);
            }
          ),
        )
      };
    | CreateScript =>
      ReasonReact.SideEffects(
        (
          self => {
            let script = createElement("script");
            setSrc(script, url);
            setOnload(
              script,
              () => {
                loadedScripts := Belt.Set.String.add(loadedScripts^, url);
                self.send(FlushOnload);
              },
            );
            setOnerror(
              script,
              () => {
                erroredScripts := Belt.Set.String.add(erroredScripts^, url);
                self.send(FlushOnerror);
              },
            );
            appendChild(script) |> ignore;
          }
        ),
      )
    | Onload => ReasonReact.Update({...state, remote: Success})
    | Onerror => ReasonReact.Update({...state, remote: Failure})
    | FlushOnload =>
      ReasonReact.SideEffects(
        (
          _self =>
            Belt.Map.String.get(observers^, url)
            |> Belt.Option.map(_, observers' =>
                 Belt.Map.Int.forEach(observers', (_id, observer) =>
                   observer.onload()
                 )
               )
            |> ignore
        ),
      )
    | FlushOnerror =>
      ReasonReact.SideEffects(
        (
          _self =>
            Belt.Map.String.get(observers^, url)
            |> Belt.Option.map(_, observers' =>
                 Belt.Map.Int.forEach(observers', (_id, observer) =>
                   observer.onerror()
                 )
               )
            |> ignore
        ),
      )
    },
  render: self => children(self.state.remote),
};
