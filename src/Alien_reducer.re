let alienSpeed = 0.3;

let nextX = (elapsedTime: float, a: Types.alien) : float =>
  a.x +. elapsedTime *. alienSpeed *. float_of_int(a.direction);

let isOnEdge = (newX: float, {width}: Types.alien) : (bool, bool) => (
  newX < 0.,
  newX +. width > Constants.width,
);

let alienStep = 70.;

let moveOnLeftEdge = (a: Types.alien) : Types.alien => {
  ...a,
  direction: 1,
  x: 0.,
  y: a.y +. alienStep,
};

let moveOnRightEdge = (a: Types.alien) : Types.alien => {
  ...a,
  direction: (-1),
  x: Constants.width -. a.width,
  y: a.y +. alienStep,
};

let moveAlien = (elapsedTime: float, a: Types.alien) : Types.alien => {
  let x = nextX(elapsedTime, a);
  switch (isOnEdge(x, a)) {
  | (false, false) => {...a, x}
  | (true, _) => moveOnLeftEdge(a)
  | (_, true) => moveOnRightEdge(a)
  };
};

let isStillInMap = (alien: Types.alien) => alien.y < Constants.height;

let moveAliens =
    (aliens: list(Types.alien), elapsedTime: float)
    : list(Types.alien) =>
  aliens |> List.map(moveAlien(elapsedTime)) |> List.filter(isStillInMap);

let reducer =
    (elapsedTime: float, state: Types.alienState, action: Actions.all)
    : Types.alienState =>
  switch (action) {
  | Tick => {...state, aliens: moveAliens(state.aliens, elapsedTime)}
  | _ => state
  };