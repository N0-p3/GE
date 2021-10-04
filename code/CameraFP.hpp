#ifndef CAMERAFP_HPP
#define CAMERAFP_HPP

#define keyW _keys[0]
#define keyA _keys[1]
#define keyS _keys[2]
#define keyD _keys[3]
#define keySpace _keys[4]
#define keyC _keys[5]

#include "Camera3D.hpp"

#include <cmath>

namespace GE {
  class CameraFP : public Camera3D {
  private:
    double _sens;
    double _camYAngle; //Used to limit the Rotation of the camera to 89 degrees up and down

  public:
    CameraFP(double sensitivity = 0.01) {
      _sens = sensitivity;
      _camYAngle = M_PI_2;
    }

    void RotateView(double angleX, double angleY) {
      Matrix44D mRX, mRY;

      double angleMoveTotalY = _camYAngle + angleY;
      if (angleMoveTotalY < M_PI && angleMoveTotalY > 0.0)
        mRX.loadXRotation(-angleY);
      
      mRY.loadYRotation(-angleX);

      Vector3D front = (mRX * (_target - _position).GetNormalized());
      front = mRY * front;

      _target = _position + front;
      
      Vector3D up = (0.0, 1.0, 0.0);
      Vector3D side = (front % up).GetNormalized();
      up = (side % front).GetNormalized();

      _view.loadView(side, up, front);
    }

    void receiveNotification() {
      switch (Event::getType()) {
        case SDL_KEYDOWN:
          switch (Event::getKey()) {
            case SDLK_w:
              keyW = true;
              break;
            case SDLK_a:
              keyA = true;
              break;
            case SDLK_s:
              keyS = true;
              break;
            case SDLK_d:
              keyD = true;
              break;
            case SDLK_SPACE:
              keySpace = true;
              break;
            case SDLK_c:
              keyC = true;
              break;
          }
          break;
        case SDL_KEYUP:
          switch (Event::getKey()) {
            case SDLK_w:
              keyW = false;
              break;
            case SDLK_a:
              keyA = false;
              break;
            case SDLK_s:
              keyS = false;
              break;
            case SDLK_d:
              keyD = false;
              break;
            case SDLK_SPACE:
              keySpace = false;
              break;
            case SDLK_c:
              keyC = false;
              break;
          }
          case SDL_MOUSEMOTION:
            SDL_Point mouseRelMovement = Event::getMouseMotion();
            RotateView(mouseRelMovement.x * _sens, mouseRelMovement.y * _sens);
            break;
          break;
      }
    }

    void update() {
      if (keyW) _position.z -= 0.1;
        if (keyA) _position.x -= 0.1;
        if (keyS) _position.z += 0.1;
        if (keyD) _position.x += 0.1;
        if (keySpace) _position.y += 0.1;
        if (keyC) _position.y -= 0.1;
    }
  };  
}

#endif