#include "MainMenuScene.hpp"
#include "Game/Core/Graphics/Rendering/ImageRendering/ImageRenderer.hpp"

namespace JoD {
MainMenuScene::MainMenuScene() {
    m_ridBackground = _<ImageRenderer>().NewImage();
    m_ridLogo = _<ImageRenderer>().NewImage();
}

void MainMenuScene::UpdateDerived() {}

void MainMenuScene::RenderDerived() {
    auto areaBackground = BoxF{0.0f, 0.0f, 1.0f, 1.0f};
    _<ImageRenderer>().DrawImage(
        m_ridBackground, "DefaultSceneBackground",
        areaBackground);
    
    auto areaLogo = BoxF {0.4, 0.15f, 0.2f, 0.1f};
    _<ImageRenderer>().DrawImage(m_ridLogo, "JoDLogo", areaLogo);
}
}
