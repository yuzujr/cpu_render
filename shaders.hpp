#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <vector>
#include "math.hpp"

struct RenderCtx {
  int w = 0;
  int h = 0;
  int frames = 0;
  vec3 iResolution;
};

inline void shader1(const RenderCtx& ctx, int frame, std::vector<unsigned char> &buf) {
  for (int y = 0; y < ctx.h; ++y) {
    for (int x = 0; x < ctx.w; ++x) {
      // Iterator, raymarch depth and step distance
      float i{};
      float z{};
      float d{};

      // Raymarch sample point
      vec3 p{};
      vec4 O{};

      vec2 I = {(float)x, (float)y};
      vec3 baseDir = normalize(vec3(I + I, 0) - ctx.iResolution.xyy());
      float iTime = (float)frame / ctx.frames;

      // Clear fragColor and raymarch 77 steps
      for (O *= i; i++ < 77;) {
        // Slowly step forward using the distance to a distorted z-plane
        z += d = std::abs(p.z / 30.f + .2f);
        // Add color (attenuating with distance to surface)
        O += vec4(z, z, 9, 1) / d;
        // Compute the next sample point
        p = z * baseDir;
        // Shift diagonally
        p.x += iTime;
        p.y += iTime;

        // Use blocky "turbulence" for the distortion
        // https://mini.gmshaders.com/p/turbulence
        for (d = 0; d++ < 9;) {
          p += sin(round(p) + d * 3.).zxy();
        }
      }

      // Tanh tonemapping
      // https://mini.gmshaders.com/p/func-tanh
      O = tanh(O / 8e4f);
      buf.push_back(nearbyintf(O.x * 255));
      buf.push_back(nearbyintf(O.y * 255));
      buf.push_back(nearbyintf(O.z * 255));
    }
  }
}

#endif
