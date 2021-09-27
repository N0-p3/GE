#ifndef CAMERA3D_HPP
#define CAMERA3D_HPP

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

#include "Event.hpp"
#include "Matrix44d.hpp"
#include "Vector3D.hpp"
#include "Observer_Observable.hpp"

using namespace GE;

namespace GE {
  class Camera3D : public PC::Observer {
  protected:
    Vector3D _target;
    Vector3D _position;
    Vector3D _up;
    Matrix44D _view;
    bool _keys[6];

  public:
    //NORMALIZED VECTORS ONLY
    Camera3D() {
      _position = Vector3D(0.0, 0.0, 3.0);
      _target = Vector3D(0.0, 0.0, 0.0);
      _up = Vector3D(0.0, 1.0, 0.0);
      _view.loadIdentity();
    }

    void applyView() {
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glMultMatrixd(_view.matrix);
      glTranslated(-_position.x, -_position.y, -_position.z); //Translating the camera
    }

    virtual void receiveNotification() = 0;
  };
}

#endif