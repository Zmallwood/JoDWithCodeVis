#include "Game.hpp"
#include "Core/Engine.hpp"

namespace JoD {
void Game::Start() {
    _<Engine>().Run();
}
}
