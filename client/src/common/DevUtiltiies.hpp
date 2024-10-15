/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
std::string CodeLocation(
    std::source_location location = std::source_location::current());
}
