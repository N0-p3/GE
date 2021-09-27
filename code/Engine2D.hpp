#ifndef ENGINE2D_HPP
#define ENGINE2D_HPP

#include "Engine.hpp"
#include "Event.hpp"
#include "Renderer.hpp"

namespace GE {
  class Engine2D : public Engine<Engine2D> {
  private:
    Renderer _renderer;

  public:
    void start() {
      bool isOpen = true;
      while (isOpen) {
        //TODO: Gestion des events
        while (Event::poll())
          switch (Event::getType()) {
            case SDL_QUIT:
              isOpen = false;
              break;
          }
        //TODO: Gestion des mises a jour
        //TODO: Gestion de l'affichage
        _renderer.refresh();
      }
    }
  };
}

#endif