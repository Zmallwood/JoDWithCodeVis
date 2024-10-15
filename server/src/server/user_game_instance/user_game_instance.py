from pydantic import BaseModel
from server.user_game_instance.game_core.engine import Engine 
from server.user_game_instance.game_core.input.keyboard.keyboard_input import KeyboardInput
from server.user_game_instance.game_core.input.mouse.mouse_input import MouseInput 
from common.math_lib import (
    PointF
)
from server.user_game_instance.instructions.instructions_manager import InstructionsManager

class UserGameInstance (BaseModel):

    engine : Engine = Engine()
    keyboard_input : KeyboardInput = KeyboardInput()
    mouse_input : MouseInput = MouseInput()
    mouse_position : PointF = PointF()
    instructions_manager : InstructionsManager = InstructionsManager()

    def process(self) -> None:
        self.engine.update(self)
        self.engine.render(self)
