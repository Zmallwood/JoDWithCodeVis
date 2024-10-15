/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "Game.hpp"
#include "core/Engine.hpp"

namespace JoD {
void Game::Start() const {
  _<Engine>().Run();
}
}
