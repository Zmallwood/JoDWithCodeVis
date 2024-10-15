/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "game/game.hpp"

/*
 * \brief Entry point for the game client.
 */
int main(int argc, char * argv[]) {
  JoD::Game game;
  game.Start();
  return 0;
}
