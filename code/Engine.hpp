#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Singleton.hpp"

namespace GE {
  template <typename T>
  class Engine : public PC::Singleton<T> {
  protected:
    TTF_Font* _ttfFont;

  public:
    Engine() {
      SDL_Init(SDL_INIT_EVERYTHING);
      IMG_Init(IMG_INIT_PNG);
      TTF_Init();

      _ttfFont = TTF_OpenFont("../assets/fonts/TitilliumWeb-ExtraLight.ttf", 42);
    }

    ~Engine() {
      TTF_CloseFont(_ttfFont);
      TTF_Quit();
      IMG_Quit();
      SDL_Quit();
    }

    virtual void start() = 0;
  };
}

#endif