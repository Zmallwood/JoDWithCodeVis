/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Game.hpp"
#include "Core/Engine.hpp"

namespace JoD {
void Game::Start() const {
    _<Engine>().Initialize();
    _<Engine>().Run();
}
}
