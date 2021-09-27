#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Window.hpp"

namespace GE {
	class Renderer : public Window {
	private:
	  SDL_Renderer* _sdlRend;
		
	public:
	  Renderer(const int &resX = 640, const int &resY = 480, const char *title = "You forgot to give me a title", const int &posX = 0, const int &posY = 0, const unsigned int &windowFlags = 0, const unsigned int &rendFlags = 0) : Window(title, posX, posY, resX, resY, windowFlags) {
	    this->_sdlRend = SDL_CreateRenderer(_window, -1, rendFlags);
	  }

	  ~Renderer() {
	    SDL_DestroyRenderer(_sdlRend);
	  }

	  void refresh() {
	    SDL_RenderPresent(_sdlRend);
	  }
	};
}

#endif
