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
    unsigned int textureID;

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

      for (int i = 0; i < tmpFaces.size(); i++) {

        int comp = (i + 1) % 3;

        switch (comp) {
        case 1: // sommet
          _vertices[0] = tmpVertices[0];
          _vertices[1] = tmpVertices[1];
          _vertices[2] = tmpVertices[2];
          break;
        case 2: // texture

          break;
        case 0: // normal
          
          break;
        }
      }
    }

    void draw () {

    }
  };
}

#endif