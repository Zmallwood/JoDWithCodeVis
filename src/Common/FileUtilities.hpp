/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
std::string GetFileExtension(std::string_view absPath);

std::string GetFilenameNoExtension(std::string_view absPath);
}
