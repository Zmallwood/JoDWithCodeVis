from __future__ import annotations
from pydantic import BaseModel
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class IScene(BaseModel):
    
    def update(self, user_game_instance : UserGameInstance) -> None:
        self.update_derived(user_game_instance)

    def render(self, user_game_instance : UserGameInstance) -> None:
        self.render_derived(user_game_instance)

    def update_derived(self, user_game_instance : UserGameInstance) -> None:
        raise NotImplementedError()

    def render_derived(self, user_game_instance : UserGameInstance) -> None:
        raise NotImplementedError()
