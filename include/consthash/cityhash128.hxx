
#pragma once
#ifndef _CONSTHASH_CITYHASH128_HXX
#define _CONSTHASH_CITYHASH128_HXX

#include <consthash/cityhash_util.hxx>
#include <consthash/u128.hxx>

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {

constexpr uint128_t CityMurmur_ret(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return uint128_t(a ^ b, HashLen16(b, a));
}

constexpr uint128_t CityMurmur_tail(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return CityMurmur_ret(HashLen16(a, c), HashLen16(d, b), c, d);
}

constexpr uint128_t CityMurmur_br0_sub(const char* s, size_t len, uint64_t a, uint64_t b, uint64_t c) {
    return CityMurmur_tail(a, b, c, ShiftMix(a + (len >= 8 ? Fetch64(s) : c)));
}

constexpr uint128_t CityMurmur_br0(const char* s, size_t len, uint64_t a, uint64_t b) {
    return CityMurmur_br0_sub(s, len, ShiftMix(a * k1) * k1, b, b * k1 + HashLen0to16(s, len));
}

// Declaration
constexpr uint128_t CityMurmur_loop_body(const char* s, signed long l, uint64_t a, uint64_t b, uint64_t c, uint64_t d);

constexpr uint128_t CityMurmur_loop(const char* s, signed long l, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return l > 0 ? CityMurmur_loop_body(s, l, a, b, c, d) : CityMurmur_tail(a, b, c, d);
}

constexpr uint128_t CityMurmur_loop_body1(const char* s, signed long l, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return CityMurmur_loop(s + 16, l - 16, a, b ^ a, c, d ^ c);
}

constexpr uint128_t CityMurmur_loop_body(const char* s, signed long l, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return CityMurmur_loop_body1(s, l,
        (a ^ (ShiftMix(Fetch64(s) * k1) * k1)) * k1,
        b,
        (c ^ (ShiftMix(Fetch64(s + 8) * k1) * k1)) * k1,
        d);
}

constexpr uint128_t CityMurmur_br1_sub1(const char* s, signed long l, uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    return CityMurmur_loop_body(s, l, a + d, b, c, d);
}

constexpr uint128_t CityMurmur_br1_sub0(const char* s, size_t len, signed long l, uint64_t a, uint64_t b, uint64_t c) {
    return CityMurmur_br1_sub1(s, l, a, b, c, HashLen16(b + len, c + Fetch64(s + len - 16)));
}

constexpr uint128_t CityMurmur_br1(const char* s, size_t len, signed long l, uint64_t a, uint64_t b) {
    return CityMurmur_br1_sub0(s, len, l, a, b, HashLen16(Fetch64(s + len - 8) + k1, a));
}

constexpr uint128_t CityMurmur(const char *s, size_t len, uint128_t seed) {
    return len <= 16
        ? CityMurmur_br0(s, len, Uint128Low64(seed), Uint128High64(seed))
        : CityMurmur_br1(s, len, (signed long)len - 16, Uint128Low64(seed), Uint128High64(seed));
}

} // namespace __detail

CONSTHASH_NAMESPACE_END;

#endif // _CONSTHASH_CITYHASH64_HXX
