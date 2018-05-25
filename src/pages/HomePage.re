type state = {birthday: option(Js.Date.t)};

type action =
  | SetBirthday(option(Js.Date.t));

let component = ReasonReact.reducerComponent("HomePage");

let make = (~greeting, _children) => {
  ...component,
  initialState: () => {birthday: None},
  reducer: (action, state) =>
    switch (action) {
    | SetBirthday(birthday) => ReasonReact.Update({...state, birthday})
    },
  render: self => {
    let now = Js.Date.make();
    /* let birthday = Js.Date.makeWithYMD(1987.0, 7.0, 5.0, ()); */
    let anniversaries =
      switch (self.state.birthday) {
      | Some(birthday) =>
        let dates = AnniversaryGenerator.generate(birthday, now);
        <div className="Anniversaries">
          <ul>
            (
              dates
              |> List.map((ann: Anniversary.t) =>
                   <li>
                     (ReasonReact.string("On "))
                     (
                       ReasonReact.string(
                         DateFns.format("MMMM D, YYYY", ann.date),
                       )
                     )
                     (ReasonReact.string(" you will be "))
                     (
                       ReasonReact.string(
                         CommaNumber.commaNumber(ann.number.value),
                       )
                     )
                     (ReasonReact.string(" "))
                     (
                       ReasonReact.string(
                         switch (ann.number.description) {
                         | Some(description) => {j|($description) |j}
                         | None => ""
                         },
                       )
                     )
                     (ReasonReact.string(ann.units))
                     (ReasonReact.string(" old!"))
                   </li>
                 )
              |> Array.of_list
              |> ReasonReact.array
            )
          </ul>
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