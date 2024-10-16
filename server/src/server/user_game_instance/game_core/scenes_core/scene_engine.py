from __future__ import annotations
from pydantic import BaseModel
from server.user_game_instance.theme_0.scenes.intro_scene.intro_scene import IntroScene
from server.user_game_instance.theme_0.scenes.main_menu_scene.main_menu_scene import MainMenuScene 
from server.user_game_instance.theme_0.scenes.login_scene.login_scene import LoginScene 
from server.user_game_instance.theme_0.scenes.world_generation_scene.world_generation_scene import WorldGenerationScene 
from server.user_game_instance.theme_0.scenes.main_scene.main_scene import MainScene 
from typing import TYPE_CHECKING
if TYPE_CHECKING:
    from server.user_game_instance.user_game_instance import UserGameInstance

class SceneEngine(BaseModel):

    scenes : dict = {}
    current_scene : str = ""

    def __init__(self) -> None:
        super().__init__()
        
        self.scenes["IntroScene"] = IntroScene()
        self.scenes["MainMenuScene"] = MainMenuScene()
        self.scenes["LoginScene"] = LoginScene()
        self.scenes["WorldGenerationScene"] = WorldGenerationScene()
        self.scenes["MainScene"] = MainScene()

        self.current_scene = "IntroScene"
   
    def update_current_scene(self, user_game_instance : UserGameInstance) -> None:
        if self.current_scene in self.scenes:
            self.scenes[self.current_scene].update(user_game_instance)

    def render_current_scene(self, user_game_instance: UserGameInstance) -> None:
        if self.current_scene in self.scenes:
            self.scenes[self.current_scene].render(user_game_instance)


