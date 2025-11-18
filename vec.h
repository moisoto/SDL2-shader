#ifndef _MATH_H
#include <math.h>
#endif

// Equivalent to vec4 from GLSL
struct vec4 {
    float x, y, z, w;
    vec4(float x = 0, float y = 0, float z = 0, float w = 0): x(x), y(y), z(z), w(w) {}
};

// Equivalent to vec2 from GLSL
struct vec2 {
    float x, y;
    vec2(float x = 0, float y = 0): x(x), y(y) {}
    vec2 yx()   const { return vec2(y, x); }
    vec4 xyyx() const { return vec4(x, y, y, x); }
};

// Operator overloading for vec2
vec2 operator *(const vec2 &a, float s) { return vec2(a.x*s, a.y*s); }
vec2 operator +(const vec2 &a, float s) { return vec2(a.x+s, a.y+s); }
vec2 operator *(float s, const vec2 &a) { return a*s; }
vec2 operator -(const vec2 &a, const vec2 &b) { return vec2(a.x-b.x, a.y-b.y); }
vec2 operator +(const vec2 &a, const vec2 &b) { return vec2(a.x+b.x, a.y+b.y); }
vec2 operator *(const vec2 &a, const vec2 &b) { return vec2(a.x*b.x, a.y*b.y); }
vec2 operator /(const vec2 &a, float s) { return vec2(a.x/s, a.y/s); }
float dot(const vec2 &a, const vec2 &b) { return a.x*b.x + a.y*b.y; }
vec2 abs(const vec2 &a) { return vec2(fabsf(a.x), fabsf(a.y)); }
vec2 &operator +=(vec2 &a, const vec2 &b) { a = a + b; return a; }
vec2 &operator +=(vec2 &a, float s) { a = a + s; return a; }
vec2 cos(const vec2 &a) { return vec2(cosf(a.x), cosf(a.y)); }

// Operator overloading for vec4
vec4 sin(const vec4 &a) { return vec4(sinf(a.x), sinf(a.y), sinf(a.z), sinf(a.w)); }
vec4 exp(const vec4 &a) { return vec4(expf(a.x), expf(a.y), expf(a.z), expf(a.w)); }
vec4 tanh(const vec4 &a) { return vec4(tanhf(a.x), tanhf(a.y), tanhf(a.z), tanhf(a.w)); }
vec4 operator +(const vec4 &a, float s) { return vec4(a.x+s, a.y+s, a.z+s, a.w+s); }
vec4 operator *(const vec4 &a, float s) { return vec4(a.x*s, a.y*s, a.z*s, a.w*s); }
vec4 operator *(float s, const vec4 &a) { return a*s; }
vec4 operator +(const vec4 &a, const vec4 &b) { return vec4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w); }
vec4 &operator +=(vec4 &a, const vec4 &b) { a = a + b; return a; }
vec4 operator -(float s, const vec4 &a) { return vec4(s-a.x, s-a.y, s-a.z, s-a.w); }
vec4 operator /(const vec4 &a, const vec4 &b) { return vec4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w); }
