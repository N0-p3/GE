#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace GE {
	class Window {
	protected:
	  SDL_Window* _window;
	public:
	  Window(const char *title, const int &posX, const int &posY, const int &resX, const int &resY, const int &flags) {
	    this->_window = SDL_CreateWindow(title, posX, posY, resX, resY, flags);
	  }

	  ~Window() {
	    SDL_DestroyWindow(_window);
	  }

	  void setTitle(const char *title) {
	    SDL_SetWindowTitle(_window, title);
	  }

	  SDL_Point getSize() {
	    SDL_Point size;
	    SDL_GetWindowSize(_window, &size.x, &size.y);
	    return size;
	  }

		void centerMouse() {
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}

	  virtual void refresh() = 0;
	};
}

#endif
