from pydantic import BaseModel

class IScene(BaseModel):
    
    def update(self) -> None:
        self.update_derived()

    def render(self) -> None:
        self.render_derived()

    def update_derived(self) -> None:
        raise NotImplementedError()

    def render_derived(self) -> None:
        raise NotImplementedError()
