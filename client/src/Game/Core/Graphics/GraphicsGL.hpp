#pragma once

namespace JoD {
class GraphicsGL {
  public:
    GraphicsGL();
    
    auto GetFogColorGround() const {
        return k_fogColorGround;
    }
    
    auto GetFogColorObjects() const {
        return k_fogColorObjects;
    }
    
  private:
    static constexpr bool k_cullFace {false};
    const ColorF k_fogColorGround {Colors::MildBlue};
    const ColorF k_fogColorObjects {Colors::MildBlue};
    const ColorF k_clearColor {Colors::MildBlue};
};
}
