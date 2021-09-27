#ifndef MATRIX44D_HPP
#define MATRIX44D_HPP

#include "Vector3D.hpp"

//Ligne colonne
#define m11 matrix[0]
#define m12 matrix[1]
#define m13 matrix[2]
#define m14 matrix[3]
#define m21 matrix[4]
#define m22 matrix[5]
#define m23 matrix[6]
#define m24 matrix[7]
#define m31 matrix[8]
#define m32 matrix[9]
#define m33 matrix[10]
#define m34 matrix[11]
#define m41 matrix[12]
#define m42 matrix[13]
#define m43 matrix[14]
#define m44 matrix[15]

namespace GE {
  class Matrix44D {
  public:
    double matrix[16];

    void loadIdentity() {
      m11 = m22 = m33 = m44 = 1.0;
      m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0; 
    }

    void loadOrthogonal(double r, double b) {
      m11 = 2.0 / r;
      m22 = 2.0 / -b;
      m33 = m41 = -1.0;
      m42 = m44 = 1.0;
      m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m43 = 0.0;
    }

    void loadPerspective(double r, double t, double nearCut, double farCut) {
      m11 = nearCut / r;
      m22 = nearCut / t;
      m33 = -(farCut + nearCut) /  (farCut - nearCut);
      m34 = -1.0;
      m43 = (-2.0 * farCut * nearCut) / (farCut - nearCut);
      m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m41 = m42 = m44 = 0.0;
    }

    void loadView(Vector3D side, Vector3D up, Vector3D front) {
      m11 = side.x;
      m21 = side.y;
      m31 = side.z;

      m12 = up.x;
      m22 = up.y;
      m32 = up.z;

      m13 = -front.x;
      m23 = -front.y;
      m33 = -front.z;

      m14 = m24 = m34 = m41 = m42 = m43 = 0;
      m44 = 1;
    }

    void loadXRotation(double angle) {
      m22 = m33 = cos(angle);
      m23 = -sin(angle);
      m32 = sin(angle);
      m12 = m13 = m21 = m31 = 0.0;
      m11 = 1.0;
    }

    void loadYRotation(double angle) {
      m11 = m33 = cos(angle);
      m13 = sin(angle);
      m31 = -sin(angle);
      m12 = m21 = m23 = m32 = 0.0;
      m22 = 1.0;
    }

    void loadZRotation(double angle) {
      m11 = m22 = cos(angle);
      m12 = -sin(angle);
      m21 = sin(angle);
      m13 = m23 = m31 = m32 = 0.0;
      m33 = 1.0;
    }

    Vector3D operator* (Vector3D v) {
      Vector3D r(
        (m11 * v.x) + (m12 * v.y) + (m13 * v.z),
        (m21 * v.x) + (m22 * v.y) + (m23 * v.z),
        (m31 * v.x) + (m32 * v.y) + (m33 * v.z) 
      );

      return r;
    }
  };
}

#endif