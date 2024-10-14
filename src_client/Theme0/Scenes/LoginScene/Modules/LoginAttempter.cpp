/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "LoginAttempter.hpp"
#include "Game/Core/Net/ServerConnection.hpp"

namespace JoD {
bool LoginAttempter::AttemptLogin() {
    _<ServerConnection>().EnsureConnected();
    auto loginSuccessful = _<ServerConnection>().LoginUser("adde", Hash("badde"));
    return loginSuccessful;
}
}
