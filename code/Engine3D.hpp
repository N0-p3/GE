#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include "Engine.hpp"
#include "Event.hpp"
#include "EventDispatcher.hpp"
#include "Context.hpp"
#include "Matrix44d.hpp"
#include "Vector3D.hpp"
#include "CameraFP.hpp"
#include "Observer_Observable.hpp"

namespace GE
{
  class Engine3D : public Engine<Engine3D>
  {
  private:
    Context _glContext;
    CameraFP _cam = CameraFP();
    EventDispatcher _eventDispatcher;

  public:

    Engine3D() : _glContext(1280, 720, "Title") {
      //_eventDispatcher.bind(SDL_KEYDOWN, &_cam);
      //_eventDispatcher.bind(SDL_KEYUP, &_cam);
      //_eventDispatcher.bind(SDL_MOUSEMOTION, &_cam);
    }

    ~Engine3D() {
      //_eventDispatcher.unbind(SDL_KEYDOWN, &_cam);
      //_eventDispatcher.unbind(SDL_KEYUP, &_cam);
      //_eventDispatcher.unbind(SDL_MOUSEMOTION, &_cam);
    }

    void start() {
      glEnable(GL_TEXTURE_2D);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);

      //Textures
      unsigned int textureID;
      glGenTextures(1, &textureID); //ajouter une texture
      glBindTexture(GL_TEXTURE_2D, textureID); //mettre la texture a cette addresse comme active
      SDL_Surface *sdlSurface = IMG_Load("../res/crate.png"); //charger une image
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
      SDL_FreeSurface(sdlSurface);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      Matrix44D orthoProjection;
      Matrix44D perspectProjection;
      SDL_Point windowSize = _glContext.getSize();

      Vector3D v1(-1.0, 1.0, 1.0), v2(1.0, 1.0, 1.0), v3(1.0, -1.0, 1.0), v4(-1.0, -1.0, 1.0), v5(-1.0, 1.0, -1.0), v6(1.0, 1.0, -1.0), v7(1.0, -1.0, -1.0),v8(-1.0, -1.0, -1.0),
       vnFront(0.0, 0.0, 1.0), vnTop(0.0, 1.0, 0.0), vnRight(1.0, 0.0, 0.0), vnLeft(-1.0, 0.0, 0.0), vnDown(0.0, -1.0, 0.0), vnBack(0.0, 0.0, -1.0);
      Matrix44D mRX, mRY, mRZ;
      mRX.loadXRotation(0.05);
      mRY.loadYRotation(0.03);
      mRZ.loadZRotation(0.01);

      double r = tan(45.0 * 3.14159265 / 180.0) * 1.0;
      double t = ((double)windowSize.y / (double)windowSize.x) * r;

      orthoProjection.loadOrthogonal(windowSize.x, windowSize.y);
      perspectProjection.loadPerspective(r, t, 1.0, 100.0);
      bool isOpen = true;
      _glContext.centerMouse();

      while (isOpen) {
        //TODO: Gestion des events
        while (Event::poll()) {
          switch (Event::getType()) {
            case SDL_QUIT:
              isOpen = false;
              break;

            default:
              _eventDispatcher.dispatch();
              break;
          }
        }

        //TODO: Gestion des mises a jour

        
        v1 = mRX * v1;
        v2 = mRX * v2; 
        v3 = mRX * v3; 
        v4 = mRX * v4; 
        v5 = mRX * v5; 
        v6 = mRX * v6; 
        v7 = mRX * v7; 
        v8 = mRX * v8; 

        v1 = mRY * v1;
        v2 = mRY * v2; 
        v3 = mRY * v3; 
        v4 = mRY * v4; 
        v5 = mRY * v5; 
        v6 = mRY * v6; 
        v7 = mRY * v7; 
        v8 = mRY * v8; 

        v1 = mRZ * v1;
        v2 = mRZ * v2; 
        v3 = mRZ * v3; 
        v4 = mRZ * v4; 
        v5 = mRZ * v5; 
        v6 = mRZ * v6; 
        v7 = mRZ * v7; 
        v8 = mRZ * v8; 

        vnFront = mRX * vnFront;
        vnFront = mRY * vnFront;
        vnFront = mRZ * vnFront;

        vnTop = mRX * vnTop;
        vnTop = mRY * vnTop;
        vnTop = mRZ * vnTop;

        vnRight = mRX * vnRight;
        vnRight = mRY * vnRight;
        vnRight = mRZ * vnRight;

        vnLeft = mRX * vnLeft;
        vnLeft = mRY * vnLeft;
        vnLeft = mRZ * vnLeft;

        vnDown = mRX * vnDown;
        vnDown = mRY * vnDown;
        vnDown = mRZ * vnDown;

        vnBack = mRX * vnBack;
        vnBack = mRY * vnBack;
        vnBack = mRZ * vnBack;
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _cam.update();
        _cam.applyView();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspectProjection.matrix);

        //TODO: Gestion de l'affichage
        glBegin(GL_QUADS);
          glNormal3d(vnFront.x, vnFront.y, vnFront.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v1.x, v1.y, v1.z); //F
          glTexCoord2d(1.0, 0.0); glVertex3d(v2.x, v2.y, v2.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v3.x, v3.y, v3.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v4.x, v4.y, v4.z);

          glNormal3d(vnTop.x, vnTop.y, vnTop.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v5.x, v5.y, v5.z); //T
          glTexCoord2d(1.0, 0.0); glVertex3d(v6.x, v6.y, v6.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v2.x, v2.y, v2.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v1.x, v1.y, v1.z);

          glNormal3d(vnRight.x, vnRight.y, vnRight.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v2.x, v2.y, v2.z); //R
          glTexCoord2d(1.0, 0.0); glVertex3d(v6.x, v6.y, v6.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v3.x, v3.y, v3.z);

          glNormal3d(vnLeft.x, vnLeft.y, vnLeft.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v5.x, v5.y, v5.z); //L
          glTexCoord2d(1.0, 0.0); glVertex3d(v1.x, v1.y, v1.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v4.x, v4.y, v4.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);

          glNormal3d(vnDown.x, vnDown.y, vnDown.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v4.x, v4.y, v4.z); //D
          glTexCoord2d(1.0, 0.0); glVertex3d(v3.x, v3.y, v3.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);

          glNormal3d(vnBack.x, vnBack.y, vnBack.z);
          glTexCoord2d(0.0, 0.0); glVertex3d(v6.x, v6.y, v6.z); //B
          glTexCoord2d(1.0, 0.0); glVertex3d(v5.x, v5.y, v5.z);
          glTexCoord2d(1.0, 1.0); glVertex3d(v8.x, v8.y, v8.z);
          glTexCoord2d(0.0, 1.0); glVertex3d(v7.x, v7.y, v7.z);
        glEnd();
        _glContext.refresh();
      }
    }
  };
}

#endif