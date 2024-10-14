#include "LoginAttempter.hpp"
#include "Game/Core/Net/ServerConnection.hpp"

namespace JoD {
bool LoginAttempter::AttemptLogin() {
    auto loginSuccessful = _<ServerConnection>().LoginUser(
        "adde",
        Hash("badde"));
    return loginSuccessful;
}
}
