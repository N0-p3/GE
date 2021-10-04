#ifndef MESH_HPP
#define MESH_HPP

#include <cstdlib>

namespace GE {
  class Mesh {
  protected:
    double* _vertices;
    size_t _vertexCount;

  public:
    virtual void load(const char* fileName) = 0;
    virtual void draw() = 0;
  };
}

#endif