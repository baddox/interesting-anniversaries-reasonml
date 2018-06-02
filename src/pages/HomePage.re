type state = {
  birthday: option(Js.Date.t),
  beforeNow: int,
};

type action =
  | SetBirthday(option(Js.Date.t))
  | ShowMore;

let component = ReasonReact.reducerComponent("HomePage");

open Iterator;

let make = (~greeting, _children) => {
  ...component,
  initialState: () => {birthday: None, beforeNow: 0},
  reducer: (action, state) =>
    switch (action) {
    | SetBirthday(birthday) => ReasonReact.Update({...state, birthday})
    | ShowMore =>
      ReasonReact.Update({...state, beforeNow: state.beforeNow + 50})
    },
  render: self => {
    let now = Js.Date.make();
    let anniversaries =
      switch (self.state.birthday) {
      | Some(birthday) =>
        let anns: AnniversaryGenerator.anniversaryList =
          AnniversaryGenerator.get(birthday, now, self.state.beforeNow);
        let past = anns.past;
        let shownPast = anns.shownPast;
        let future = anns.future;
        <div className="Anniversaries">
          (
            Array.length(past) > 0 ?
              <button
                className="PreviousButton"
                onClick=(_e => self.send(ShowMore))>
                (ReasonReact.string("See previous anniversaries"))
              </button> :
              ReasonReact.null
          )
          (
            Array.length(shownPast) > 0 ?
              <AnniversaryList anniversaries=shownPast isPast=true /> :
              ReasonReact.null
          )
          <AnniversaryList anniversaries=future isPast=false />
        </div>;
      | None => ReasonReact.null
      };
    <div>
      <h2> (ReasonReact.string("What is your birthday?")) </h2>
      <DatePicker onDateChange=(date => self.send(SetBirthday(date))) />
      anniversaries
    </div>;
  },
};