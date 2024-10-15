from pydantic import BaseModel

class InstructionsManager(BaseModel):
    instructions : list[str] = []
