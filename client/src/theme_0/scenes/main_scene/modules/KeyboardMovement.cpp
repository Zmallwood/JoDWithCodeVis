/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "KeyboardMovement.hpp"
#include "game/core/input/keyboard/KeyboardInput.hpp"
#include "game/core/core_game_objects/Player.hpp"

namespace JoD {
void KeyboardMovement::Update() {
    if (_<Player>().GetMovementTimerRef().HasTick()) {
        auto wIsPressed = _<KeyboardInput>().KeyIsPressed(SDLK_w);
        auto aIsPressed = _<KeyboardInput>().KeyIsPressed(SDLK_a);
        auto sIsPressed = _<KeyboardInput>().KeyIsPressed(SDLK_s);
        auto dIsPressed = _<KeyboardInput>().KeyIsPressed(SDLK_d);
        if (wIsPressed)
            _<Player>().MoveNorth();
        if (aIsPressed)
            _<Player>().MoveWest();
        if (sIsPressed)
            _<Player>().MoveSouth();
        if (dIsPressed)
            _<Player>().MoveEast();
    }
}
}
