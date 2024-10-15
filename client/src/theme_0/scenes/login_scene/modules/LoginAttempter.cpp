#include "LoginAttempter.hpp"
#include "game/core/net/ServerConnection.hpp"

namespace JoD {
bool LoginAttempter::AttemptLogin() {
    auto loginSuccessful = _<ServerConnection>().LoginUser(
        "adde",
        Hash("badde"));
    return loginSuccessful;
}
}
