from __future__ import annotations
from pydantic import BaseModel
from server.user_game_instance.game_core.scenes_core.scene_engine import SceneEngine
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class Engine (BaseModel):
    
    scene_engine : SceneEngine = SceneEngine()

    def update(self, user_game_instance : UserGameInstance) -> None:
        user_game_instance.instructions_manager.instructions.clear()
        self.scene_engine.update_current_scene(user_game_instance) 

    def render(self, user_game_instance : UserGameInstance) -> None:
        self.scene_engine.render_current_scene(user_game_instance) 
