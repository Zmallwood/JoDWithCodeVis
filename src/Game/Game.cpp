/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Game.hpp"
#include "Core/Engine.hpp"
#include "Core/Configuration/GameProperties.hpp"

namespace JoD {
void Game::Start() {
    _<Engine>().InitializeScenes();
    _<GameProperties>().SetWorldAreaSize({140, 100});
    _<Engine>().Run();
}
}
