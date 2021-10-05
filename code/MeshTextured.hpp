#ifndef MESHTEXTURED_HPP
#define MESHTEXTURED_HPP

#include <fstream>
#include <vector>
#include <iostream>

#include "Mesh.hpp"

using namespace std;

namespace GE {
  class MeshTextured : public Mesh{
  private:
    double* _normals;
    double* _textureCoords;
    unsigned int _textureID;

    inline void putDouble(vector<double> vectorDest, double tmpComp, ifstream* file, bool ignore = false) {
      *file >> tmpComp; vectorDest.push_back(tmpComp);
      if (ignore) {  (*file).ignore(1); }
    }

    inline void putInt(vector<double> vectorDest, int tmpComp, ifstream* file, bool ignore = false) {
      *file >> tmpComp; vectorDest.push_back(tmpComp);
      if (ignore) {  (*file).ignore(1); }
    }

  public:
    void load(const char* fileName) {
      vector<double> tmpVertices;
      vector<double> tmpNormals;
      vector<double> tmpTextures;
      vector<double> tmpFaces;
      ifstream file(fileName);
      string character;
      double tmpCompDouble;
      int tmpCompInt;

      while (!file.eof()) {
        file >> character;
        switch (character[0]) {
          case 'v':
            if (character.size() == 2) {
              switch (character[1]) {
                case 't': // vt (texture coord)
                  putDouble(tmpTextures, tmpCompDouble, &file);
                  putDouble(tmpTextures, tmpCompDouble, &file);
                  break;
                case 'n': // vn (vector normal)
                  putDouble(tmpNormals, tmpCompDouble, &file);
                  putDouble(tmpNormals, tmpCompDouble, &file);
                  putDouble(tmpNormals, tmpCompDouble, &file);
                  break;
              }
            }
            else { // v (vertex)
              putDouble(tmpVertices, tmpCompDouble, &file);
              putDouble(tmpVertices, tmpCompDouble, &file);
              putDouble(tmpVertices, tmpCompDouble, &file);
            }
            break;
            case 'f':
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file);
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file);
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file, true);
              putInt(tmpFaces, tmpCompInt, &file);
              break;
            default:
              while (character != "\n") { file >> character; }
              file >> character;
              break;
        }
      }
      _vertexCount = tmpVertices.size();

      _vertices[_vertexCount * 3];
      _normals[_vertexCount * 3];
      _textureCoords[_vertexCount * 2];
      int counter = 0;
      int index;

      for (int i = 0; i < tmpFaces.size(); i + 3) { //Sommets
        index = (tmpFaces[i] - 1) * 3;
        _vertices[counter] = tmpVertices[index]; counter++;
        _vertices[counter] = tmpVertices[index + 1]; counter++;
        _vertices[counter] = tmpVertices[index + 2]; counter++;
      }

      counter = 0;

      for (int i = 1; i < tmpFaces.size(); i + 3) {
        index = (tmpFaces[i] - 1) * 2;
        _textureCoords[counter] = tmpTextures[index]; counter++;
        _textureCoords[counter] = tmpTextures[index + 1]; counter++;
      }

      counter = 0;

      for (int i = 2; i < tmpFaces.size(); i + 3) {
        index = (tmpFaces[i] - 1) * 3;
        _normals[counter] = tmpNormals[index]; counter++;
        _normals[counter] = tmpNormals[index + 1]; counter++;
        _normals[counter] = tmpNormals[index + 2]; counter++;
      }
    }

    void draw () {
      glBindTexture(GL_TEXTURE_2D, _textureID);
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glVertexPointer(3, GL_DOUBLE, 0, _vertices);
      glNormalPointer(GL_DOUBLE, 0, _normals);
      glTexCoordPointer(2, GL_DOUBLE, 0, _textureCoords);
      glDrawArrays(GL_QUADS, 0, _vertexCount);
    }
  };
}

#endif