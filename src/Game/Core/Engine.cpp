#include "Engine.hpp"
#include "Graphics/Graphics.hpp"
#include "Input/Keyboard/KeyboardInput.hpp"
#include "Input/Mouse/MouseInput.hpp"
#include "ScenesCore/SceneManager.hpp"
#include "FPSCounter/FPSCounter.hpp"
#include "Cursor/Cursor.hpp"

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
}
