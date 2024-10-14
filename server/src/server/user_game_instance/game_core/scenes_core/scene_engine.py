from pydantic import BaseModel


class SceneEngine(BaseModel):
   
    def update_current_scene(self) -> None:
        pass

    def render_current_scene(self) -> None:
        pass
