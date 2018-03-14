let removeKilledBy =
    (shot: Types.shot, aliens: list(Types.alien))
    : list(Types.alien) =>
  List.filter(
    (alien: Types.alien) =>
      ! (
        shot.x < alien.x
        +. alien.width
        && shot.x
        +. shot.width > alien.x
        && shot.y < alien.y
        +. alien.height
        && shot.height
        +. shot.y > alien.y
      ),
    aliens
  );

let findNotCollided =
    (aliens: list(Types.alien), shots: list(Types.shot))
    : (list(Types.alien), list(Types.shot)) => {
  let initValue = (aliens, []);
  shots
  |> List.fold_left(
       ((remainingAliens, remainingShots), shot) => {
         let newRemainingAliens = remainingAliens |> removeKilledBy(shot);
         let isShotHitAlien =
           List.length(newRemainingAliens) < List.length(remainingAliens);
         let newRemainingShot =
           isShotHitAlien ? remainingShots : remainingShots @ [shot];
         (newRemainingAliens, newRemainingShot);
       },
       initValue
     );
};