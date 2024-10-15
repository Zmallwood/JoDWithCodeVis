from pydantic import BaseModel
from server.user_game_instance.game_core.input.mouse.mouse_button import MouseButton
from server.user_game_instance.game_core.input.mouse.mouse_buttons import MouseButtons

class MouseInput(BaseModel):

    left_button : MouseButton = MouseButton()
    right_button : MouseButton = MouseButton()

    def RegisterMouseButtonPressed(self, button : MouseButtons):
        match button:
            case MouseButtons.LEFT:
                self.left_button.RegisterPressed() 
            case MouseButtons.RIGHT:
                self.right_button.RegisterPressed() 

    def RegisterMouseButtonReleased(self, button : MouseButtons):
        match button:
            case MouseButtons.LEFT:
                self.left_button.RegisterReleased() 
            case MouseButtons.RIGHT:
                self.right_button.RegisterReleased()
