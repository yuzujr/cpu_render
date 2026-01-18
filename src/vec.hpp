#ifndef VEC_HPP
#define VEC_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>

// -------------------- vec storage --------------------
template <std::size_t N>
struct vec_storage;

template <>
struct vec_storage<2> {
    float x{}, y{};
};

template <>
struct vec_storage<3> {
    float x{}, y{}, z{};
};

template <>
struct vec_storage<4> {
    float x{}, y{}, z{}, w{};
};

// -------------------- vec<N> --------------------
template <std::size_t N>
struct vec : vec_storage<N> {
    static_assert(N >= 2 && N <= 4);

    // constructors
    constexpr vec() = default;

    constexpr vec(float x, float y)
        requires(N == 2)
        : vec_storage<N>{x, y} {}

    constexpr vec(float x, float y, float z)
        requires(N == 3)
        : vec_storage<N>{x, y, z} {}

    constexpr vec(float x, float y, float z, float w)
        requires(N == 4)
        : vec_storage<N>{x, y, z, w} {}

    // index access (only [0..N-1] is valid)
    constexpr float& operator[](std::size_t i) {
        assert(i < N && "vec index out of bounds");
        if constexpr (N == 2) {
            return i == 0 ? this->x : this->y;
        } else if constexpr (N == 3) {
            return i == 0 ? this->x : (i == 1 ? this->y : this->z);
        } else {
            return i == 0 ? this->x
                          : (i == 1 ? this->y : (i == 2 ? this->z : this->w));
        }
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
    }
    friend constexpr vec operator-(vec v) {
        for (std::size_t i = 0; i < N; ++i) v[i] = -v[i];
        return v;
    }

    // ---- vector * vector ----
    constexpr vec& operator*=(const vec& rhs) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] *= rhs[i];
        return *this;
    }
    friend constexpr vec operator*(vec lhs, const vec& rhs) {
        lhs *= rhs;
        return lhs;
    }

    // ---- vector / vector ----
    constexpr vec& operator/=(const vec& rhs) {
        for (std::size_t i = 0; i < N; ++i) (*this)[i] /= rhs[i];
        return *this;
    }
    friend constexpr vec operator/(vec lhs, const vec& rhs) {
        lhs /= rhs;
        return lhs;
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

    // ---- swizzle functions ----
    constexpr vec<2> xy() const
        requires(N >= 2)
    {
        return vec<2>{this->x, this->y};
    }

    constexpr vec<2> yx() const
        requires(N >= 2)
    {
        return vec<2>{this->y, this->x};
    }

    constexpr vec<3> xyy() const
        requires(N >= 2)
    {
        return vec<3>{this->x, this->y, this->y};
    }

    constexpr vec<3> zxy() const
        requires(N >= 3)
    {
        return vec<3>{this->z, this->x, this->y};
    }

    constexpr vec<3> xyx() const
        requires(N >= 2)
    {
        return vec<3>{this->x, this->y, this->x};
    }

    constexpr vec<3> yzx() const
        requires(N >= 3)
    {
        return vec<3>{this->y, this->z, this->x};
    }

    constexpr vec<3> xyz() const
        requires(N >= 3)
    {
        return vec<3>{this->x, this->y, this->z};
    }
};

using vec2 = vec<2>;
using vec3 = vec<3>;
using vec4 = vec<4>;

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
inline vec<N> ceil(vec<N> v) {
    return map(v, [](float a) {
        return ceil(a);
    });
}
template <std::size_t N>
inline vec<N> clamp(vec<N> v, float lo, float hi) {
    return map(v, [=](float a) {
        return std::clamp(a, lo, hi);
    });
}

#endif
