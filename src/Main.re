[%bs.raw {|require('../../../src/Main.css')|}];

type route =
  | HomeRoute
  | AboutRoute
  | NoRoute;

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => HomeRoute
  | ["about"] => AboutRoute
  | _ => NoRoute
  };

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let component = ReasonReact.reducerComponent("Main");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: HomeRoute},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> mapUrlToRoute))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self =>
    <div className="Main">
      <div className="Row Header">
        <div className="MaxWidth">
          <h1> (ReasonReact.string("Interesting Anniversaries")) </h1>
        </div>
      </div>
      <div className="Row Main__routeHolder">
        <div className="MaxWidth">
          (
            switch (self.state.route) {
            | HomeRoute => <HomePage greeting="Hello!" />
            | AboutRoute => <AboutPage name="My name is Thomas Shaddox" />
            | NoRoute => <NotFoundPage />
            }
          )
        </div>
      </div>
      <div className="Row Footer">
        <div className="MaxWidth">
          <p>
            (
              ReasonReact.string(
                "Interesting Anniversaries is a recreational coding exercise by ",
              )
            )
            <a href="https://twitter.com/baddox">
              (ReasonReact.string("Thomas Shaddox"))
            </a>
            (ReasonReact.string("."))
          </p>
          <p>
            (
              ReasonReact.string("The source code and more information is on ")
            )
            <a
              href="https://github.com/baddox/interesting-anniversaries-reasonml">
              (ReasonReact.string("GitHub"))
            </a>
            (ReasonReact.string("."))
          </p>
        </div>
      </div>
    </div>,
};