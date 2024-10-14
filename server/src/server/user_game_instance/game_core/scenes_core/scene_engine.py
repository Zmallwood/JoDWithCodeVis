from pydantic import BaseModel


class SceneEngine(BaseModel):

    scenes : dict = {}
    current_scene : str = ""

    def __init__(self) -> None:
        super().__init__()
   
    def update_current_scene(self) -> None:
        pass

    def render_current_scene(self) -> None:
        pass


