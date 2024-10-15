from pydantic import BaseModel

class KeyboardInput(BaseModel):

    def RegisterKeyPress(self, key) -> None:
        pass

    def RegisterKeyRelease(self, key) -> None:
        pass
