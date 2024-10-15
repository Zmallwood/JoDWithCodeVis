/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "game.hpp"
#include "core/engine.hpp"

namespace JoD {
void Game::Start() const {
  _<Engine>().Run();
}
}
