/*
** File:	color.h
** Authors:	Christopher Kulla, Reynold Bailey
** Contributors: J. Geigel, W. Carithers
*/

#ifndef _COLOR_H_
#define _COLOR_H_

class Color {
public:
  Color() : r(0.0), g(0.0), b(0.0) {}

  Color(const Color& c) : r(c.r), g(c.g), b(c.b) {}

  Color(double _r, double _g, double _b) : r(_r), g(_g), b(_b) {}

  Color& operator=(const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
  }

  Color& operator+=(const Color& c) {
    r += c.r; g += c.g; b += c.b;
    return *this;
  }

  Color& operator-=(const Color& c) {
    r -= c.r; g -= c.g; b -= c.b;
    return *this;
  }

  Color& operator*=(const Color& c) {
    r *= c.r; g *= c.g; b *= c.b;
    return *this;
  }

  Color& operator/=(const Color& c) {
    r /= c.r; g /= c.g; b /= c.b;
    return *this;
  }

  Color& operator*=(double s) {
    r *= s; g *= s; b *= s;
    return *this;
  }
  
  Color& operator/=(double s) {
    double is = 1.0 / s;
    r *= is; g *= is; b *= is;
    return *this;
  }

  Color operator-() const {
    return Color(-r, -g, -b);
  }

  Color operator+() const {
    return *this;
  }

  int toRGB() const {
    int red   = (int) (r * 255.0);
    int green = (int) (g * 255.0);
    int blue  = (int) (b * 255.0);

    if (red < 0)   red = 0;   else if (red > 255)   red = 255;
    if (green < 0) green = 0; else if (green > 255) green = 255;
    if (blue < 0)  blue = 0;  else if (blue > 255)  blue = 255;

    return (red << 16) | (green << 8) | blue;
  }

  double getMax() const {
    double max = (r > g) ? r : g;
    if (max < b)
      max = b;
    return max;
  }

  double getMin() const {
    double min = (r < g) ? r : g;
    if (min > b)
      min = b;
    return min;
  }

  double getAverage() const {
    return (r + g + b) / 3.0;
  }

  double r, g, b;
};

inline Color operator+(const Color& a, const Color& b) {
  return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

inline Color operator-(const Color& a, const Color& b) {
  return Color(a.r - b.r, a.g - b.g, a.b - b.b);
}

inline Color operator*(const Color& a, const Color& b) {
  return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

inline Color operator/(const Color& a, const Color& b) {
  return Color(a.r / b.r, a.g / b.g, a.b / b.b);
}

inline Color operator*(double s, const Color& c) {
  return Color(s * c.r, s * c.g, s * c.b);
}

inline Color operator*(const Color& c, double s) {
  return Color(s * c.r, s * c.g, s * c.b);
}

inline Color operator/(const Color& c, double s) {
  double is = 1.0 / s;
  return Color(is * c.r, is * c.g, is * c.b);
}

#endif
