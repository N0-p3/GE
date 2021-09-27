#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL2/SDL.h>

namespace GE {
  class Event {
  private:
    static SDL_Event _sdlEvent;

  public:
    static int poll() {
      return SDL_PollEvent(&_sdlEvent);
    }

    static unsigned int getType() {
      return _sdlEvent.type;
    }

    static char getKey() {
      return _sdlEvent.key.keysym.sym;
    }

    static SDL_Point getMouseMotion() {
      SDL_Point mouseRel;
      mouseRel.x = _sdlEvent.motion.xrel;
      mouseRel.y = _sdlEvent.motion.yrel;
      return mouseRel;
    }
		
  };
  SDL_Event Event::_sdlEvent = SDL_Event();
}

#endif
