from __future__ import annotations
from server.user_game_instance.game_core.scenes_core.i_scene import IScene
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class IntroScene(IScene):
    
    def update_derived(self, user_game_instance : UserGameInstance) -> None:
        if user_game_instance.mouse_input.left_button.is_pressed:
            user_game_instance.engine.scene_engine.current_scene = "MainMenuScene"

    def render_derived(self, user_game_instance : UserGameInstance) -> None:
        user_game_instance.instructions_manager.instructions.append("DefaultSceneBackground,0.0f,0.0f,1.0f,1.0f")
        user_game_instance.instructions_manager.instructions.append("JoDLogo,0.3f,0.2f,0.4f,0.2f")
