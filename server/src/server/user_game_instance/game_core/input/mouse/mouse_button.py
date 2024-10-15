from pydantic import BaseModel

class MouseButton(BaseModel):

    is_pressed : bool = False

    def RegisterPressed(self) -> None:
        self.is_pressed = True

    def RegisterReleased(self) -> None:
        self.is_pressed = False
