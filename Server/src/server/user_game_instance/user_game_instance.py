from pydantic import BaseModel
from server.user_game_instance.game_core.engine import Engine 

class UserGameInstance (BaseModel):

    engine : Engine = Engine()

    def process(self) -> None:
        self.engine.update()
        self.engine.render()
