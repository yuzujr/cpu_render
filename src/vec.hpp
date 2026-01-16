#ifndef VEC_HPP
#define VEC_HPP

#include <algorithm>
#include <cmath>
#include <cstddef>

// -------------------- vec<N> --------------------
template <std::size_t N>
struct vec {
    static_assert(N >= 2 && N <= 4);

    float x{}, y{}, z{}, w{};

    // index access (only [0..N-1] is valid)
    constexpr float& operator[](std::size_t i) {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else
            return w;
    }
    constexpr float operator[](std::size_t i) const {
        return const_cast<vec&>(*this)[i];
    }

    // ---- vector + vector ----
    constexpr vec& operator+=(const vec& rhs) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] += rhs[i];
        return *this;
    }
    friend constexpr vec operator+(vec lhs, const vec& rhs) {
        lhs += rhs;
        return lhs;
    }

    // ---- vector - vector ----
    constexpr vec& operator-=(const vec& rhs) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] -= rhs[i];
        return *this;
    }
    friend constexpr vec operator-(vec lhs, const vec& rhs) {
        lhs -= rhs;
        return lhs;
        return lhs;
    }
    friend constexpr vec operator-(vec v) {
        for (std::size_t i = 0; i < N; ++i) v[i] = -v[i];
        return v;
    }

    // ---- vector + scalar ----
    constexpr vec& operator+=(float s) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] += s;
        return *this;
    }
    friend constexpr vec operator+(vec v, float s) {
        v += s;
        return v;
    }
    friend constexpr vec operator+(float s, vec v) {
        v += s;
        return v;
    }

    // ---- vector - scalar ----
    constexpr vec& operator-=(float s) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] -= s;
        return *this;
    }
    friend constexpr vec operator-(vec v, float s) {
        v -= s;
        return v;
    }
    friend constexpr vec operator-(float s, vec v) {
        for (std::size_t i = 0; i < N; ++i) v[i] = s - v[i];
        return v;
    }

    // ---- vector * scalar ----
    constexpr vec& operator*=(float s) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] *= s;
        return *this;
    }
    friend constexpr vec operator*(vec v, float s) {
        v *= s;
        return v;
    }
    friend constexpr vec operator*(float s, vec v) {
        v *= s;
        return v;
    }

    // ---- vector / scalar ----
    constexpr vec& operator/=(float s) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] /= s;
        return *this;
    }
    friend constexpr vec operator/(vec v, float s) {
        v /= s;
        return v;
    }
};

using vec2 = vec<2>;
using vec3 = vec<3>;
using vec4 = vec<4>;

template <std::size_t N>
    requires(N >= 2)
constexpr vec2 xy(const vec<N>& t) {
    return vec2{t.x, t.y};
}

template <std::size_t N>
    requires(N >= 2)
constexpr vec2 yx(const vec<N>& t) {
    return vec2{t.y, t.x};
}

template <std::size_t N>
    requires(N >= 2)
constexpr vec3 xyy(const vec<N>& t) {
    return vec3{t.x, t.y, t.y};
}

template <std::size_t N>
    requires(N >= 3)
constexpr vec3 zxy(const vec<N>& t) {
    return vec3{t.z, t.x, t.y};
}

// -------------------- basic math --------------------
template <std::size_t N>
inline float dot(const vec<N>& a, const vec<N>& b) {
    float s = 0.0f;
    for (std::size_t i = 0; i < N; ++i) s += a[i] * b[i];
    return s;
}

template <std::size_t N>
inline float length(const vec<N>& v) {
    return std::sqrt(dot(v, v));
}

template <std::size_t N>
inline vec<N> normalize(vec<N> v) {
    float m = length(v);
    if (m > 0.0f) v /= m;
    return v;
}

template <std::size_t N, class F>
inline vec<N> map(vec<N> v, F&& op) {
    for (std::size_t i = 0; i < N; ++i) v[i] = static_cast<float>(op(v[i]));
    return v;
}

template <std::size_t N>
inline vec<N> sin(vec<N> v) {
    return map(v, [](float a) {
        return std::sin(a);
    });
}
template <std::size_t N>
inline vec<N> cos(vec<N> v) {
    return map(v, [](float a) {
        return std::cos(a);
    });
}
template <std::size_t N>
inline vec<N> tan(vec<N> v) {
    return map(v, [](float a) {
        return std::tan(a);
    });
}

template <std::size_t N>
inline vec<N> sinh(vec<N> v) {
    return map(v, [](float a) {
        return std::sinh(a);
    });
}
template <std::size_t N>
inline vec<N> cosh(vec<N> v) {
    return map(v, [](float a) {
        return std::cosh(a);
    });
}
template <std::size_t N>
inline vec<N> tanh(vec<N> v) {
    return map(v, [](float a) {
        return std::tanh(a);
    });
}

template <std::size_t N>
inline vec<N> exp(vec<N> v) {
    return map(v, [](float a) {
        return std::exp(a);
    });
}
template <std::size_t N>
inline vec<N> log(vec<N> v) {
    return map(v, [](float a) {
        return std::log(a);
    });
}
template <std::size_t N>
inline vec<N> sqrt(vec<N> v) {
    return map(v, [](float a) {
        return std::sqrt(a);
    });
}

template <std::size_t N>
inline vec<N> abs(vec<N> v) {
    return map(v, [](float a) {
        return std::fabs(a);
    });
}
template <std::size_t N>
inline vec<N> round(vec<N> v) {
    return map(v, [](float a) {
        return nearbyintf(a);
    });
}

template <std::size_t N>
inline vec<N> clamp(vec<N> v, float lo, float hi) {
    return map(v, [=](float a) {
        return std::clamp(a, lo, hi);
    });
}

#endif
