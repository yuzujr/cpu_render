#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

struct vec2 {
  float x = 0;
  float y = 0;

  vec2() = default;

  vec2(float x, float y) {
    this->x = x;
    this->y = y;
  }

  vec2 operator+(vec2 v) const {
    vec2 tmp = *this;
    tmp += v;
    return tmp;
  }
  vec2 &operator+=(vec2 v) {
    x += v.x;
    y += v.y;
    return *this;
  }
};

struct vec3 {
  float x = 0;
  float y = 0;
  float z = 0;

  vec3() = default;

  vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  vec3(vec2 v2, float f) {
    x = v2.x;
    y = v2.y;
    z = f;
  }

  vec3 operator-(vec3 v) const {
    vec3 tmp = *this;
    tmp -= v;
    return tmp;
  }
  vec3 &operator-=(vec3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  vec3 operator+(vec3 v) const {
    vec3 tmp = *this;
    tmp += v;
    return tmp;
  }
  vec3 &operator+=(vec3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  vec3 operator+(float i) const {
    vec3 tmp = *this;
    tmp += i;
    return tmp;
  }
  vec3 &operator+=(float i) {
    x += i;
    y += i;
    z += i;
    return *this;
  }
  vec3 operator*(float i) const {
    vec3 tmp = *this;
    tmp *= i;
    return tmp;
  }
  vec3 &operator*=(float i) {
    x *= i;
    y *= i;
    z *= i;
    return *this;
  }

  vec3 zxy() const { return vec3{z, x, y}; }
  vec3 xyy() const { return vec3{x, y, y}; }
};

struct vec4 {
  float x = 0;
  float y = 0;
  float z = 0;
  float w = 0;

  vec4() = default;

  vec4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  vec4 operator+(float i) const {
    vec4 tmp = *this;
    tmp += i;
    return tmp;
  }
  vec4 &operator+=(float i) {
    x += i;
    y += i;
    z += i;
    w += i;
    return *this;
  }
  vec4 operator+(vec4 v) const {
    vec4 tmp = *this;
    tmp += v;
    return tmp;
  }
  vec4 &operator+=(vec4 v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  vec4 operator*(float i) const {
    vec4 tmp = *this;
    tmp *= i;
    return tmp;
  }
  vec4 &operator*=(float i) {
    x *= i;
    y *= i;
    z *= i;
    w *= i;
    return *this;
  }
  vec4 operator/(float i) const {
    vec4 tmp = *this;
    tmp /= i;
    return tmp;
  }
  vec4 &operator/=(float i) {
    x /= i;
    y /= i;
    z /= i;
    w /= i;
    return *this;
  }
};

inline vec3 operator*(float f, vec3 v) { return vec3{v.x * f, v.y * f, v.z * f}; }

inline vec3 normalize(vec3 v) {
  float magnitude = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  if (magnitude > 0) {
    v.x /= magnitude;
    v.y /= magnitude;
    v.z /= magnitude;
  }
  return v;
}

inline vec3 round(vec3 v) {
  v.x = nearbyintf(v.x);
  v.y = nearbyintf(v.y);
  v.z = nearbyintf(v.z);
  return v;
}

inline vec3 sin(vec3 v) {
  v.x = std::sin(v.x);
  v.y = std::sin(v.y);
  v.z = std::sin(v.z);
  return v;
}

inline vec4 tanh(vec4 v) {
  v.x = std::tanh(v.x);
  v.y = std::tanh(v.y);
  v.z = std::tanh(v.z);
  v.w = std::tanh(v.w);
  return v;
}

#endif
