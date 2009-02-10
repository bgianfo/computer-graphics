/*
** File:	vecmath.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _VECMATH_H_
#define _VECMATH_H_

#include <iostream>
#include <cmath>

using namespace std;

class Point3;

class Vector3 {
public:
  Vector3() : x(0), y(0), z(0) {}
  Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
  Vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  
  Vector3& operator=(const Vector3& a) {
    x = a.x; y = a.y; z = a.z;
    return *this;
  }

  double operator[](int n) const { return ((double *) this)[n]; }

  Vector3& operator+=(const Vector3& a) {
    x += a.x; y += a.y; z += a.z;
    return *this;
  }

  Vector3& operator-=(const Vector3& a) {
    x -= a.x; y -= a.y; z -= a.z;
    return *this;
  }

  Vector3& operator*=(double s) {
    x *= s; y *= s; z *= s;
    return *this;
  }

  Vector3 operator-() const {
    return Vector3(-x, -y, -z);
  }

  Vector3 operator+() const {
    return *this;
  }
  
  double length() const {
    return (double) sqrt(x * x + y * y + z * z);
  }

  double lengthSquared() const {
    return x * x + y * y + z * z;
  }

  void normalize() {
    double s = 1.0 / (double) sqrt(x * x + y * y + z * z);
    x *= s; y *= s; z *= s;
  }
  
  double x, y, z;
};

class Point3 {
public:
  Point3() : x(0), y(0), z(0) {}
  Point3(const Point3& p) : x(p.x), y(p.y), z(p.z) {}
  Point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  
  Point3& operator=(const Point3& a) {
    x = a.x; y = a.y; z = a.z;
    return *this;
  }
  
  double operator[](int n) const { return ((double *) this)[n]; }

  Point3& operator+=(const Vector3& v) {
    x += v.x; y += v.y; z += v.z;
    return *this;
  }

  Point3& operator-=(const Vector3& v) {
    x -= v.x; y -= v.y; z -= v.z;
    return *this;
  }

  Point3& operator*=(double s) {
    x *= s; y *= s; z *= s;
    return *this;
  }

  double distanceTo(const Point3& p) const {
    return (double) sqrt((p.x - x) * (p.x - x) +
                         (p.y - y) * (p.y - y) +
                         (p.z - z) * (p.z - z));
  }

  double distanceToSquared(const Point3& p) const {
    return ((p.x - x) * (p.x - x) +
            (p.y - y) * (p.y - y) +
            (p.z - z) * (p.z - z));
  }

  double distanceFromOrigin() const {
    return (double) sqrt(x * x + y * y + z * z);
  }

  double distanceFromOriginSquared() const {
    return x * x + y * y + z * z;
  }

  double x, y, z;
};



// **** Vector3 operators ****

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
  return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
  return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3 operator*(double s, const Vector3& v) {
  return Vector3(s * v.x, s * v.y, s * v.z);
}

inline Vector3 operator*(const Vector3& v, double s) {
  return Vector3(s * v.x, s * v.y, s * v.z);
}

// dot product
inline double operator*(const Vector3& a, const Vector3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// cross product
inline Vector3 operator^(const Vector3& a, const Vector3& b) {
  return Vector3(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

inline bool operator==(const Vector3& a, const Vector3& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const Vector3& a, const Vector3& b) {
  return a.x != b.x || a.y != b.y || a.z != b.z;
}

inline Vector3 operator/(const Vector3& v, double s) {
  double is = 1 / s;
  return Vector3(is * v.x, is * v.y, is * v.z);
}

inline ostream& operator<<(ostream& os, const Vector3& v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}


// **** Point3 operators ****

inline Vector3 operator-(const Point3& a, const Point3& b) {
  return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline bool operator==(const Point3& a, const Point3& b) {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const Point3& a, const Point3& b) {
  return a.x != b.x || a.y != b.y || a.z != b.z;
}

inline Point3 operator+(const Point3& p, const Vector3& v) {
  return Point3(p.x + v.x, p.y + v.y, p.z + v.z);
}

inline Point3 operator-(const Point3& p, const Vector3& v) {
  return Point3(p.x - v.x, p.y - v.y, p.z - v.z);
}

inline Point3 operator*(const Point3& p, double s) {
  return Point3(p.x * s, p.y * s, p.z * s);
}

inline Point3 operator*(double s, const Point3& p) {
  return Point3(p.x * s, p.y * s, p.z * s);
}

inline ostream& operator<<(ostream& os, const Point3& p) {
  os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
  return os;
}


#endif /* _VECMATH_H_ */
