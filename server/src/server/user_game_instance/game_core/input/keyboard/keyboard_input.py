from pydantic import BaseModel

class KeyboardInput(BaseModel):

    pressed_keys : set = set()

    def RegisterKeyPress(self, key) -> None:
        self.pressed_keys.add(key) 

    def RegisterKeyRelease(self, key) -> None:
        self.pressed_keys.remove(key)
