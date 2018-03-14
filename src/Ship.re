let onKeyDown = (keyCode: string) : unit =>
  switch (keyCode) {
  | "ArrowLeft" => Store.dispatch(Actions.GoLeft)
  | "ArrowRight" => Store.dispatch(Actions.GoRight)
  | _ => ()
  };

let render = (canvasContext: Types.canvasContext, state: Types.shipState) =>
  switch (state.potentialShipSprite) {
  | Some(image) => Image.draw(canvasContext, image, ~x=state.x, ~y=state.y)
  | None => ()
  };