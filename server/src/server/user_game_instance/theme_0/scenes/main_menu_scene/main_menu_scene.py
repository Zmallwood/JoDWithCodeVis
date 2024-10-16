from __future__ import annotations
from server.user_game_instance.game_core.scenes_core.i_scene import IScene
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class MainMenuScene(IScene):
    
    def update_derived(self, user_game_instance : UserGameInstance) -> None:
        pass

    def render_derived(self, user_game_instance : UserGameInstance) -> None:
        user_game_instance.instructions_manager.instructions.append("DefaultSceneBackground,0.0f,0.0f,1.0f,1.0f")
        user_game_instance.instructions_manager.instructions.append("JoDLogo,0.4f,0.2f,0.2f,0.1f")
