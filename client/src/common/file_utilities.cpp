/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "file_utilities.hpp"

namespace JoD {
std::string GetFileExtension(std::string_view absPath) {
  auto extension = absPath.substr(absPath.find_last_of('.') + 1);
  return extension.data();
}

std::string GetFilenameNoExtension(std::string_view absPath) {
  auto nameWithExt =
    std::string(absPath.substr(absPath.find_last_of('/') + 1));
  auto fileName = nameWithExt.substr(0, nameWithExt.find_last_of('.'));
  return fileName;
}
}
