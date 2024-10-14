/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class GameProperties {
  public:
    auto GetWorldAreaSize() const {
        return m_worldAreaSize;
    }
    
    void SetWorldAreaSize(Size value) {
        m_worldAreaSize = value;
    }
    
  private:
    Size m_worldAreaSize {100, 100};
};
}
