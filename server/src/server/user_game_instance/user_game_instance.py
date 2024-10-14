from pydantic import BaseModel
from server.user_game_instance.game_core.engine import Engine 

class UserGameInstance (BaseModel):

    engine : Engine = Engine()

    def process(self) -> None:
        print("Processing user game instance")
        self.engine.update()
        self.engine.render()
