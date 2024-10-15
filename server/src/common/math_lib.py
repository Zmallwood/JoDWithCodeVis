from pydantic import BaseModel

class PointF(BaseModel):
    x : float = 0.0
    y : float = 0.0
