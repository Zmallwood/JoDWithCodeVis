/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "dev_utilities.hpp"

namespace JoD {
std::string CodeLocation(
  std::source_location location) {
  return "Code location: '" + std::string(location.function_name()) + "'\n";
}
}
