from __future__ import annotations
from server.user_game_instance.game_core.scenes_core.i_scene import IScene
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class MainScene(IScene):
    
    def update_derived(self, user_game_instance : UserGameInstance) -> None:
        pass

    def render_derived(self, user_game_instance : UserGameInstance) -> None:
        pass
