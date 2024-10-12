/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "Engine.hpp"
#include "Graphics/Graphics.hpp"
#include "Input/Keyboard/KeyboardInput.hpp"
#include "Input/Mouse/MouseInput.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "FPSCounter/FPSCounter.hpp"
#include "Cursor/Cursor.hpp"
#include "Graphics/Rendering/ImageRendering/ImageRenderer.hpp"
#include "Graphics/Rendering/TextRendering/TextRenderer.hpp"

namespace JoD {
void Engine::Run() {
    SDL_Init(SDL_INIT_EVERYTHING);
    _<Graphics>();
    while (m_running) {
        _<Cursor>().Reset();
        PollEvents();
        _<SceneManager>().UpdateCurrentScene();
        _<FPSCounter>().Update();
        _<Graphics>().ClearCanvas();
        _<SceneManager>().RenderCurrentScene();
        _<FPSCounter>().Render();
        _<Cursor>().Render();
        _<Graphics>().PresentCanvas();
    }
}

void Engine::PollEvents() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_KEYDOWN:
            _<KeyboardInput>().RegisterKeyPress(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            _<KeyboardInput>().RegisterKeyRelease(event.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            _<MouseInput>().RegisterButtonPressed(event.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            _<MouseInput>().RegisterButtonReleased(event.button.button);
            break;
        }
    }
}

RID Engine::NewImage() {
    return _<ImageRenderer>().NewImage();
}

void Engine::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                       ColorF color, bool repeatTexture,
                       SizeF textureFillAmount,
                       bool noPixelEffect) {
    _<ImageRenderer>().DrawImage(
        rid, imageNameHash, area, color, repeatTexture,
        textureFillAmount, noPixelEffect);
}

void Engine::DrawImage(RID rid, std::string_view imageName, const BoxF &area,
                       ColorF color, bool repeatTexture,
                       SizeF textureFillAmount,
                       bool noPixelEffect) {
    _<ImageRenderer>().DrawImage(
        rid, imageName, area, color,repeatTexture,
        textureFillAmount, noPixelEffect);
}

int Engine::NewString() {
    return _<TextRenderer>().NewString();
}

void Engine::DrawString(int id,
                        std::string_view text,
                        Point2F position,
                        ColorF color,
                        bool centerAlign,
                        FontSizes fontSize) {
    _<TextRenderer>().DrawString(
        id, text, position, color, centerAlign,
        fontSize);
}

}
