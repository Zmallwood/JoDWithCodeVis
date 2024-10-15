from pydantic import BaseModel
from server.user_game_instance.theme_0.scenes.intro_scene.intro_scene import IntroScene
from server.user_game_instance.theme_0.scenes.main_menu_scene.main_menu_scene import MainMenuScene 
from server.user_game_instance.theme_0.scenes.login_scene.login_scene import LoginScene 
from server.user_game_instance.theme_0.scenes.world_generation_scene.world_generation_scene import WorldGenerationScene 
from server.user_game_instance.theme_0.scenes.main_scene.main_scene import MainScene 

class SceneEngine(BaseModel):

    scenes : dict = {}
    current_scene : str = ""

    def __init__(self) -> None:
        super().__init__()
        
        self.scenes["IntroScene"] = IntroScene()
        self.scenes["MainMenuScene"] = IntroScene()
        self.scenes["LoginScene"] = IntroScene()
        self.scenes["WorldGenerationScene"] = IntroScene()
        self.scenes["MainScene"] = IntroScene()

        self.current_scene = "IntroScene"
   
    def update_current_scene(self) -> None:
        if self.current_scene in self.scenes:
            self.scenes[self.current_scene].update()

    def render_current_scene(self) -> None:
        if self.current_scene in self.scenes:
            self.scenes[self.current_scene].render()


