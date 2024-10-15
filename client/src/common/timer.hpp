/*
 * Copyright 2024 Andreas Åkerberg.
 */
#pragma once

namespace JoD {
class Timer {
public:
  Timer(float& tickSpeed);
  
  bool HasTick();
  
private:
  int m_ticksLastUpdate {0};
  float& m_tickSpeed;
};
}
