/*
 * Copyright 2024 Andreas Åkerberg.
 */

#pragma once

namespace JoD {
 template <class T>
 T& _() {
  static T instance;
  return instance;
 }
}
