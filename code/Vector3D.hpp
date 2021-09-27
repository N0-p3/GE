#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>

using namespace std;
namespace GE {
  class Vector3D {
  public:
    double x, y, z;

    ///\param x Composante x du Vector3D.
    ///\param y Composante y du Vector3D.
    ///\param z Composante z du Vector3D.
    Vector3D(double x = 1.0, double y = 1.0, double z = 1.0) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    ///\brief Fait une copie d'un Vector3D déjà existant.
    ///\param v Vector3D dont une copie doit être faite.
    Vector3D(const Vector3D &v) {
      this->x = v.x;
      this->y = v.y;
      this->z = v.z;
    }

    ///\brief Calcule et retourne la norme de "this".
    ///\return Retourne la norme de "this".
    double GetNorm() {
      return sqrt((x * x) + (y * y) + (z * z));
    }

    ///\brief Normalise "this".
    void Normalize() {
      double n = GetNorm();

      x /= n;
      y /= n;
      z /= n;
    }

    ///\brief Calcule et retourne une version "normaliser" (de norme 1) de "this".
    ///\return Retourne une version "normaliser" (de norme 1) de "this".
    Vector3D GetNormalized() {
      Vector3D v = Vector3D(*this);
      double n = v.GetNorm();

      v.x /= n;
      v.y /= n;
      v.z /= n;

      return v;
    }

    ///\brief Calcule et retourne la somme de "this" et du Vector3D "v".
    ///\param v Deuxième paramêtre Vector3D dans l'équation d'une somme entre "this" et "v".
    ///\return Retourne un Vector3D ayant la somme des composantes de "this" et du Vector3D "v" comme composantes.
    Vector3D operator+(Vector3D v) {
      return Vector3D(x + v.x, y + v.y, z + v.z);
    }

    ///\brief Calcule et retourne la différence de "this" et du Vector3D "v".
    ///\param v Deuxième paramêtre Vector3D dans l'équation d'une différence entre "this" et "v".
    ///\return Retourne un Vector3D ayant la différence des composantes de "this" et du Vector3D "v" comme composantes.
    Vector3D operator-(Vector3D v) {
      return Vector3D(x - v.x, y - v.y, z - v.z);
    }

    ///\brief Calcule et retourne le produit scalaire de "this" et du Vector3D "v".
    ///\param v Deuxième paramêtre Vector3D dans l'équation d'un produit scalaire entre "this" et "v".
    ///\return Retourne le produit scalaire de "this" et du Vector3D "v".
    double operator*(Vector3D v) {
      return ((x * v.x) + (y * v.y) + (z * v.z));
    }

    ///\brief Calcule et retourne "this" multiplier par le Vector3D "v". Chaque composantes de "this" seront multiplier par le Vector3D "v".
    ///\param v Deuxième paramêtre double dans l'équation d'une multiplication par un scalaire entre "this" et "v".
    ///\return Retourne "this" multiplier par le Vector3D "v". Chaque composantes de "this" seront multiplier par le Vector3D "v".
    Vector3D operator*(double v) {
      return Vector3D(x * v, y * v, z * v);
    }

    ///\brief Calcule et retourne le produit vectoriel de "this" et du Vector3D "v".
    ///\param v Deuxième paramêtre Vector3D dans l'équation d'un produit vectoriel entre "this" et "v".
    ///\return Retourne le produit vectoriel de "this" et du Vector3D "v".
    Vector3D operator%(Vector3D v) {
      return Vector3D((y * v.z) - (v.y * z), (z * v.x) - (v.z * x), (x * v.y) - (v.x * y));
    }

    ///\brief Calcule et retourne la mesure de l'angle entre "this" et le Vector3D "v".
    ///\param v Deuxième paramêtre Vector3D dans le calcul entre l'angle de "this" et "v".
    ///\return Retourne la mesure de l'angle entre "this" et le Vector3D "v".
    double GetAngle(Vector3D v) {
      double ps = *this * v; //VALEUR AU BOUT DU POINTEURS
      double n1 = GetNorm();
      double n2 = v.GetNorm();
      return acos(ps / (n1 * n2));
    }
  };
}
#endif