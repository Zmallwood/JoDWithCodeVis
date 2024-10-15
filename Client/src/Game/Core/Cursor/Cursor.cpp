/*
 * Copyright 2024 Andreas Åkerberg.
 */

#include "Cursor.hpp"
#include "Game/Core/Engine.hpp"

namespace JoD {
Cursor::Cursor() {
    SDL_ShowCursor(0);
    m_ridCursorImage = _<Engine>().AllocateNewImage();
}

void Cursor::Render() const {
    if (!m_visibleThisFrame)
        return;
    auto mousePosition= GetMousePosition();
    auto usedCursorSize= SizeF{k_cursorSize,
                               ConvertWidthToHeight(k_cursorSize)};
    auto usedCursorPosition= mousePosition.Translate(
        -usedCursorSize.width / 2.0f, -usedCursorSize.height / 2.0f);
    auto bounds = BoxF{
        usedCursorPosition.x, usedCursorPosition.y,
        usedCursorSize.width, usedCursorSize.height};
    std::string imageName;
    switch (m_cursorStyle) {
    case JoD::CursorStyles::Hovering:
        imageName= "CursorHovering";
        break;
    case CursorStyles::Rotating:
        imageName= "CursorRotating";
        break;
    case CursorStyles::Normal:
    default:
        imageName= "CursorNormal";
    }
    _<Engine>().DrawImage(m_ridCursorImage, imageName, bounds);
}

void Cursor::Reset() {
    m_cursorStyle= CursorStyles::Normal;
    m_visibleThisFrame = true;
}

void Cursor::HideThisFrame() {
    m_visibleThisFrame = false;
}
}
