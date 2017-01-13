
#pragma once
#ifndef _CONSTHASH_CITYHASH32_HXX
#define _CONSTHASH_CITYHASH32_HXX

#include <consthash/cityhash_util.hxx>

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {

constexpr uint32_t Hash32Len13to24(const char *s, size_t len) {
  return fmix(
    Mur(
        Fetch32(s + len - 4),
        Mur(
            Fetch32(s),
            Mur(
                Fetch32(s + (len >> 1)),
                Mur(
                    Fetch32(s + len - 8),
                    Mur(
                        Fetch32(s + 4),
                        Mur(
                            Fetch32(s - 4 + (len >> 1)),
                            len))))))
    );
}

// Declaration
constexpr uint32_t Hash32Len0to4_loop(const char *s, size_t len, uint32_t b, uint32_t c, size_t i);

constexpr uint32_t Hash32Len0to4_loop_sub(const char *s, size_t len, uint32_t b, uint32_t c, size_t i) {
    return Hash32Len0to4_loop(s, len, b, c ^ b, i + 1);
}

constexpr uint32_t Hash32Len0to4_loop(const char *s, size_t len, uint32_t b, uint32_t c, size_t i) {
    return i < len ? Hash32Len0to4_loop_sub(s, len, b * c1 + s[i], c, i) : fmix(Mur(b, Mur(len, c)));
}

constexpr uint32_t Hash32Len0to4(const char *s, size_t len) {
  return Hash32Len0to4_loop(s, len, 0, 9, 0);
}

constexpr uint32_t Hash32Len5to12(const char *s, size_t len) {
  return fmix(Mur(Fetch32(s + ((len >> 1) & 4)) + 9, Mur(len * 5 + Fetch32(s + len - 4), Mur(len + Fetch32(s), len * 5))));
}

// Declaration
constexpr uint32_t city32impl_loop_body(const char* s, size_t len, uint32_t f, uint32_t g, uint32_t h, size_t iters);

constexpr uint32_t city32impl_loop(const char* s, size_t len, uint32_t f, uint32_t g, uint32_t h, size_t iters) {
    return iters != 0 ? city32impl_loop_body(s, len, f, g, h, iters)
        : Rotate32(Rotate32(Rotate32(Rotate32(h + Rotate32(Rotate32(g, 11) * c1, 17) * c1, 19) * 5 + 0xe6546b64, 17) * c1 +
            Rotate32(Rotate32(f, 11) * c1, 17) * c1, 19) * 5 + 0xe6546b64, 17) * c1;
}

constexpr uint32_t city32impl_loop_body1(const char* s, size_t len, uint32_t f, uint32_t g, uint32_t h, size_t iters,
                                         uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4) {
    return city32impl_loop(s + 20, len,
        swap_bytes_32((Rotate32(g + a2, 18) * 5 + 0xe6546b64) ^ a4) * 5,
        swap_bytes_32((Rotate32((Rotate32(h ^ a0, 18) * 5 + 0xe6546b64) ^ (a3 + a1), 19) * 5 + 0xe6546b64) + a4 * 5),
        Rotate32(f + a1, 19) * c1 + a0,
        iters - 1);
}

constexpr uint32_t city32impl_loop_body(const char* s, size_t len, uint32_t f, uint32_t g, uint32_t h, size_t iters) {
    return city32impl_loop_body1(s, len, f, g, h, iters,
        Rotate32(Fetch32(s) * c1, 17) * c2,
        Fetch32(s + 4),
        Rotate32(Fetch32(s + 8) * c1, 17) * c2,
        Rotate32(Fetch32(s + 12) * c1, 17) * c2,
        Fetch32(s + 16));
}

constexpr uint32_t city32impl_sub(const char* s, size_t len) {
  return city32impl_loop_body(s, len,
    Rotate32(c1 * len + Rotate32(Fetch32(s + len - 20) * c1, 17) * c2, 19) * 5 + 0xe6546b64,
    Rotate32((Rotate32(c1 * len ^ Rotate32(Fetch32(s + len - 8) * c1, 17) * c2, 19) * 5 + 0xe6546b64) ^ Rotate32(Fetch32(s + len - 12) * c1, 17) * c2, 19) * 5 + 0xe6546b64,
    Rotate32((Rotate32(len ^ Rotate32(Fetch32(s + len - 4) * c1, 17) * c2, 19) * 5 + 0xe6546b64) ^ Rotate32(Fetch32(s + len - 16) * c1, 17) * c2, 19) * 5 + 0xe6546b64,
    (len - 1) / 20);
}

constexpr uint32_t city32impl(const char* s, size_t len) {
    return len <= 24 ? (len <= 12 ?
        (len <= 4 ? Hash32Len0to4(s, len) : Hash32Len5to12(s, len)) :
        Hash32Len13to24(s, len)) : city32impl_sub(s, len);
}

}; // namespace __detail

constexpr uint32_t city32(const char* s, size_t len) {
    return __detail::city32impl(s, len);
}

constexpr uint32_t city32(const char* s) {
	return __detail::city32impl(s, __detail::str_len(s));
}

CONSTHASH_NAMESPACE_END;

#endif // _CONSTHASH_CITYHASH32_HXX
