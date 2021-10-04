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
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      //Textures
      unsigned int crateTextureID;
      glGenTextures(1, &crateTextureID); //ajouter une texture
      glBindTexture(GL_TEXTURE_2D, crateTextureID); //mettre la texture a cette addresse comme active
      
      SDL_Surface* sdlSurface = IMG_Load("../assets/res/crate.png"); //charger une image
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
      int fontWitdth = sdlSurface -> w, fontHeight = sdlSurface -> h;
      SDL_FreeSurface(sdlSurface);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      
      unsigned int fontTextureID;
      glGenTextures(1, &fontTextureID); //ajouter une texture
      glBindTexture(GL_TEXTURE_2D, fontTextureID); //mettre la texture a cette addresse comme active
      
      sdlSurface = TTF_RenderText_Blended(_ttfFont, "T'ES LAID :D", {255, 255, 255, 255}); //charger un ttf
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sdlSurface->w, sdlSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdlSurface->pixels);
      SDL_FreeSurface(sdlSurface);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      

      Matrix44D orthoProjection;
      Matrix44D perspectProjection;
      SDL_Point windowSize = _glContext.getSize();

      Matrix44D mRX, mRY, mRZ;

      size_t vertexCount = 24;
      double vertices[72] = { -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0, -1.0,  1.0,  1.0, -1.0,  1.0,  1.0,  1.0, -1.0, -1.0,  1.0, -1.0, -1.0, -1.0,  1.0, -1.0, -1.0,  1.0, -1.0,  1.0, -1.0,  1.0, -1.0, -1.0,  1.0,  1.0, -1.0, -1.0,  1.0, -1.0, -1.0, -1.0, 1.0,  1.0, -1.0,  1.0,  1.0,  1.0,  1.0, -1.0,  1.0,  1.0, -1.0, -1.0 };
      double normals[72] = { 0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0, 0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0, 0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0, 0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, -1.0,  0.0,  0.0, 1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0,  1.0,  0.0,  0.0 };
      double textureCoords[48] = { 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0 };

      
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _cam.update();
       
        //TODO: Gestion de l'affichage

        //Mode 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(orthoProjection.matrix);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glBindTexture(GL_TEXTURE_2D, fontTextureID); //mettre la texture a cette addresse comme active
        glBegin(GL_QUADS);
          glTexCoord2d(0.0, 0.0); glVertex3d(0.0, 0.0, 0.0);
          glTexCoord2d(1.0, 0.0); glVertex3d((double) fontWitdth, 0.0, 0.0);
          glTexCoord2d(1.0, 1.0); glVertex3d((double) fontWitdth, (double)fontHeight, 0.0);
          glTexCoord2d(0.0, 1.0); glVertex3d(0.0, (double) fontHeight, 0.0);
        glEnd();

        //Mode 3D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixd(perspectProjection.matrix);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _cam.applyView();
        glBindTexture(GL_TEXTURE_2D, crateTextureID); //mettre la texture a cette addresse comme active
        
        //Dire a OpenGL que on va lui passer nos vertexes, normales et coordonner de texture en array
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_DOUBLE, 0, vertices);
        glNormalPointer(GL_DOUBLE, 0, normals);
        glTexCoordPointer(2, GL_DOUBLE, 0, textureCoords);

        glDrawArrays(GL_QUADS, 0, vertexCount);

        _glContext.refresh();
      }
    }
  };
}

#endif