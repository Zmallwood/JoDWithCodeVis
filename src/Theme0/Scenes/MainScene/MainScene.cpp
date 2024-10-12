/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "MainScene.hpp"
#include "Modules/WorldViewModule/WorldView.hpp"

namespace JoD {
void MainScene::UpdateDerived() {
    _<WorldView>().Update();
}

void MainScene::RenderDerived() {
    _<WorldView>().Render();
}
}
