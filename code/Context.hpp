#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Window.hpp"

namespace GE {
  class Context : public Window {
  private:
    SDL_GLContext _glContext;

  public:
    Context(const int &resX = 640, const int &resY = 480, const char *title = "You forgot to give me a title", const int &posX = 0, const int &posY = 0, const unsigned int &windowFlags = 0, const unsigned int &rendFlags = 0) : Window(title, posX, posY, resX, resY, windowFlags | SDL_WINDOW_OPENGL) {
      this->_glContext = SDL_GL_CreateContext(_window);
    }

    ~Context() {
      SDL_GL_DeleteContext(_glContext);
    }

    void refresh(){
      SDL_GL_SwapWindow(_window);
    }
  };
}

#endif
