#include "Game/Core/ScenesCore/IScene.hpp"

namespace JoD {
class MainScene : public IScene {
  protected:
    void UpdateDerived() override;
    
    void RenderDerived() override;
};
}
