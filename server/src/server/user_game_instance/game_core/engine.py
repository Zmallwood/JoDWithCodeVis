from pydantic import BaseModel
from server.user_game_instance.game_core.scenes_core.scene_engine import SceneEngine


class Engine (BaseModel):
    
    scene_engine : SceneEngine = SceneEngine()

    def update(self) -> None:
       self.scene_engine.update_current_scene() 

    def render(self) -> None:
       self.scene_engine.render_current_scene() 
