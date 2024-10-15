/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "login_attempter.hpp"
#include "game/core/net/server_connection.hpp"

namespace JoD {
bool LoginAttempter::AttemptLogin() {
  auto loginSuccessful = _<ServerConnection>().LoginUser(
    "adde",
    Hash("badde"));
  return loginSuccessful;
}
}
