/*
 * Copyright 2024 Andreas Åkerberg.
 */
#include "engine.hpp"
#include "common/mouse_utilities.hpp"
#include "graphics/graphics.hpp"
#include "input/keyboard/keyboard_input.hpp"
#include "input/mouse/mouse_input.hpp"
#include "scenes_core/scene_engine.hpp"
#include "fps_counter/fps_counter.hpp"
#include "cursor/cursor.hpp"
#include "graphics/rendering/image_rendering/image_renderer.hpp"
#include "graphics/rendering/text_rendering/text_renderer.hpp"
#include "graphics/rendering/ground_rendering/ground_renderer.hpp"
#include "configuration/game_properties.hpp"
#include "game/core/instructions/instructions_manager.hpp"
#include "game/core/net/server_connection.hpp"
#include "game/core/assets/models/model_bank.hpp"

namespace JoD {
Engine::Engine() {
  SDL_Init(SDL_INIT_EVERYTHING);
  _<Graphics>();
  _<ModelBank>().LoadModels();
  _<ServerConnection>().EnsureConnected();
  _<InstructionsManager>();
}

void Engine::Initialize() const {
  srand(time(nullptr));
  _<SceneEngine>().InitializeScenes();
  _<SceneEngine>().GoToScene("IntroScene");
  _<GameProperties>().SetWorldAreaSize({140, 100});
}

void Engine::ResetInputState() const {
  _<KeyboardInput>().Reset();
  _<MouseInput>().Reset();
}

void Engine::Run() {
  try {
    Initialize();
    while (m_running) {
      _<Cursor>().Reset();
      PollEvents();
      _<SceneEngine>().UpdateCurrentScene();
      _<FPSCounter>().Update();
      _<Graphics>().ClearCanvas();
      _<SceneEngine>().RenderCurrentScene();
      _<FPSCounter>().Render();
      _<Cursor>().Render();
      _<ServerConnection>().Update();
      _<InstructionsManager>().PerformInstructions();
      _<Graphics>().PresentCanvas();
    }
  }
  catch (const std::runtime_error& e) {
    std::cout <<
      "Exception of \"runtime error\" type occured in Engine::Run():\n\""
              <<
      e.what() << "\"\n";
  }
  catch (const std::invalid_argument& e) {
    std::cout <<
      "Exception of \"invalid argument\" type occured in Engine::Run():\n\""
              <<
      e.what() << "\"\n";
  }
  catch (const std::exception& e) {
    std::cout <<
      "Exception of unhandled type occured in Engine::Run():\n\"" <<
      e.what() <<
      "\"\n";
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
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
        _<ServerConnection>().SendMessage("LeftMouseButtonPressed");
        break;
      case SDL_BUTTON_RIGHT:
        _<ServerConnection>().SendMessage("RightMouseButtonPressed");
        break;
      }
      _<MouseInput>().RegisterButtonPressed(event.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      switch (event.button.button) {
      case SDL_BUTTON_LEFT:
        _<ServerConnection>().SendMessage("LeftMouseButtonReleased");
        break;
      case SDL_BUTTON_RIGHT:
        _<ServerConnection>().SendMessage("RightMouseButtonReleased");
        break;
      }
      _<MouseInput>().RegisterButtonReleased(event.button.button);
      break;
    case SDL_MOUSEMOTION: {
      auto mousePosition = GetMousePosition();
      _<ServerConnection>().SendMessage(
        "MouseMove\n" +
        std::to_string(mousePosition.x) + "\n" +
        std::to_string(mousePosition.y));
      _<MouseInput>().RegisterMouseMoved(
        {event.motion.xrel,
         event.motion.yrel});
      break;
    }
    case SDL_TEXTINPUT:
      _<KeyboardInput>().AppendTextInput(event.text.text);
      break;
    case SDL_MOUSEWHEEL:
      _<MouseInput>().RegisterMouseWheelScrolled(event.wheel.y);
      break;
    }
  }
}

Size Engine::GetWorldAreaSize() const {
  return _<GameProperties>().GetWorldAreaSize();
}

RID Engine::AllocateNewImage() const {
  return _<ImageRenderer>().AllocateNewImage();
}

void Engine::DrawImage(RID rid, int imageNameHash, const BoxF &area,
                       ColorF color, bool repeatTexture,
                       SizeF textureFillAmount,
                       bool noPixelEffect) const {
  _<ImageRenderer>().DrawImage(
    rid, imageNameHash, area, color, repeatTexture,
    textureFillAmount, noPixelEffect);
}

void Engine::DrawImage(RID rid, std::string_view imageName, const BoxF &area,
                       ColorF color, bool repeatTexture,
                       SizeF textureFillAmount,
                       bool noPixelEffect) const {
  _<ImageRenderer>().DrawImage(
    rid, imageName, area, color,repeatTexture,
    textureFillAmount, noPixelEffect);
}

RID Engine::AllocateNewString() const {
  return _<TextRenderer>().AllocateNewString();
}

void Engine::DrawString(int id,
                        std::string_view text,
                        Point2F position,
                        ColorF color,
                        bool centerAlign,
                        FontSizes fontSize) const {
  _<TextRenderer>().DrawString(
    id, text, position, color, centerAlign,
    fontSize);
}

RID Engine::AllocateNewTile() const {
  return _<GroundRenderer>().AllocateNewTile();
}

void Engine::SetCursorStyle(CursorStyles newStyle) const {
  _<Cursor>().SetCursorStyle(newStyle);
}

bool Engine::AnyMouseButtonisPressed() const {
  return _<MouseInput>().AnyMouseButtonIsPressed();
}

bool Engine::AnyKeyIsPressed() const {
  return _<KeyboardInput>().AnyKeyIsPressed();
}

GLuint Engine::GetImage(int imageNameHash) const {
  return _<Graphics>().GetImage(imageNameHash);
}

GLuint Engine::GetImage(std::string_view imageName) const {
  return _<Graphics>().GetImage(imageName);
}

void Engine::CreateBlankImage(std::string uniqueImageName) const {
  _<Graphics>().CreateBlankImage(uniqueImageName);
}
}
