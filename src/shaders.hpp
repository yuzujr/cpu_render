#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <vector>

#include "vec.hpp"

struct RenderCtx {
    int w = 0;
    int h = 0;
    int frames = 0;
};

// buf is empty, fill with ctx.w * ctx.h RGB pixels.
// frame is used to calculate time.

inline void shader1(const RenderCtx& ctx, int frame,
                    std::vector<unsigned char>& buf) {
    for (int y = 0; y < ctx.h; ++y) {
        for (int x = 0; x < ctx.w; ++x) {
            // Iterator, raymarch depth and step distance
            float i{};
            float z{};
            float d{};

            // Raymarch sample point
            vec3 p;
            vec4 O;

            vec2 I = {(float)x, (float)y};
            vec2 Res = {(float)ctx.w, (float)ctx.h};
            vec2 I2 = I + I;
            vec3 baseDir = normalize(vec3(I2.x, I2.y, 0) - xyy(Res));
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
                    p += zxy(sin(round(p) + d * 3.));
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

inline void shader2(const RenderCtx& ctx, int frame,
                    std::vector<unsigned char>& buf) {
    for (int y = 0; y < ctx.h; ++y) {
        for (int x = 0; x < ctx.w; ++x) {
            vec2 FC = {(float)x, (float)y};
            vec2 Res = {(float)ctx.w, (float)ctx.h};
            float t = (float)frame / ctx.frames;
            vec4 O;
            vec2 p = (xy(FC) * 2.f - Res) / Res.y * 2e1f;
            O = tanh(vec4(1, 1, 2, 1) /
                     length(p * .2f + tan(yx(sin(p += t * 10.0)) + p)));
            buf.push_back(nearbyintf(O.x * 255));
            buf.push_back(nearbyintf(O.y * 255));
            buf.push_back(nearbyintf(O.z * 255));
        }
    }
}

inline void shader3(const RenderCtx& ctx, int frame,
                    std::vector<unsigned char>& buf) {
    for (int y = 0; y < ctx.h; ++y) {
        for (int x = 0; x < ctx.w; ++x) {
            // Raymarch depth
            float z{};
            // Step distance
            float d{};
            // Raymarch iterator
            float i{};
            // output
            vec4 O;
            vec2 iResolution{(float)ctx.w, (float)ctx.h};
            vec2 I{(float)x, (float)y};
            vec2 I2 = I + I;
            float iTime = (float)frame / ctx.frames;
            // Clear fragColor and raymarch 20 steps
            for (O *= i; i++ < 2e1;) {
                // Sample point (from ray direction)
                vec3 p =
                    z * normalize(vec3(I2.x, I2.y, 0) - xyx(iResolution)) + .1f;

                // Polar coordinates and additional transformations
                p = vec3(std::atan2(p.y / .2, p.x) * 2., p.z / 3.,
                         length(xy(p)) - 5. - z * .2);

                // Apply turbulence and refraction effect
                for (d = 0.; d++ < 7.;)
                    p += sin(yzx(p) * d + iTime + .3 * i) / d;

                // Distance to cylinder and waves with refraction
                vec3 tmp = .4f * cos(p) - .4f;
                z += d = length(vec4(tmp.x, tmp.y, tmp.z, p.z));

                // Coloring and brightness
                O += (1. + cos(p.x + i * .4 + z + vec4(6, 1, 2, 0))) / d;
            }
            // Tanh tonemap
            O = tanh(O * O / 4e2);
            buf.push_back(nearbyintf(O.x * 255));
            buf.push_back(nearbyintf(O.y * 255));
            buf.push_back(nearbyintf(O.z * 255));            
        }
    }
}

#endif
