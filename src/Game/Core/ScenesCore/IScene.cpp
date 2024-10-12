#include "IScene.hpp"

namespace JoD {
void IScene::Update() {
    UpdateDerived();
}

void IScene::Render() {
    RenderDerived();
}
}
