
#pragma once
#ifndef _CONSTHASH_CITYHASH128_HXX
#define _CONSTHASH_CITYHASH128_HXX

#include <consthash/cityhash_util.hxx>
#include <consthash/u128.hxx>

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {

namespace murmur {

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

}; // namespace murmur

constexpr uint128_t CityHash128WithSeed_ge128_sub1(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
  return uint128_t(HashLen16(x + v.second, w.second) + y,
                 HashLen16(x + w.second, y + v.second));
}

// Declaration
constexpr uint128_t CityHash128WithSeed_loop2(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z,
    size_t tail_done);

constexpr uint128_t CityHash128WithSeed_loop2sub2(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z,
    size_t tail_done)
{
    return CityHash128WithSeed_loop2(s, len, seed, uint128_t(v.first * k0, v.second), w, x, y, z, tail_done);
}

constexpr uint128_t CityHash128WithSeed_loop2sub(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z,
    size_t tail_done)
{
    return CityHash128WithSeed_loop2sub2(s, len, seed,
        WeakHashLen32WithSeeds(s + len - tail_done, z + w.second + Fetch64(s + len - tail_done), v.second),
        w,
        x * k0 + w.first,
        y,
        z + w.second - v.first + Fetch64(s + len - tail_done),
        tail_done);
}

constexpr uint128_t CityHash128WithSeed_loop2(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z,
    size_t tail_done)
{
    return tail_done < len ? CityHash128WithSeed_loop2sub(s, len, seed,
        v,
        uint128_t(w.first + Fetch64(s + len - (tail_done+32) + 16), w.second + v.first),
        x, Rotate(x + y, 42) * k0 + v.second, z,
        tail_done + 32)
        : CityHash128WithSeed_ge128_sub1(s, len, seed, v, w, HashLen16(x, v.first), HashLen16(y + z, w.first), z);
}

constexpr uint128_t CityHash128WithSeed_ge128_sub0(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
  return CityHash128WithSeed_loop2(s, len, seed,
    uint128_t(v.first * k0, v.second),
    uint128_t(w.first * 9, w.second),
    x + Rotate(v.first + z, 49) * k0,
    y * k0 + Rotate(w.second, 37),
    z * k0 + Rotate(w.first, 27),
    0);
}

// Declaration
constexpr uint128_t CityHash128WithSeed_loop1body(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z);

constexpr uint128_t CityHash128WithSeed_loop1body2(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
    return len >= 128 ? CityHash128WithSeed_loop1body(s, len, seed, v, w, x, y, z)
        : CityHash128WithSeed_ge128_sub0(s, len, seed, v, w, x, y, z);
}

constexpr uint128_t CityHash128WithSeed_loop1body1(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
    return CityHash128WithSeed_loop1body2(s + 128, len - 128, seed,
        WeakHashLen32WithSeeds(s + 64, v.second * k1, ((Rotate(z + y + v.first + Fetch64(s + 64 + 8), 37) * k1) ^ w.second) + w.first),
        WeakHashLen32WithSeeds(s + 64 + 32, (Rotate(x + w.first, 33) * k1) + w.second, (Rotate(y + v.second + Fetch64(s + 64 + 48), 42) * k1 + v.first + Fetch64(s + 64 + 40)) + Fetch64(s + 64 + 16)),
        Rotate(x + w.first, 33) * k1,
        Rotate(y + v.second + Fetch64(s + 64 + 48), 42) * k1 + v.first + Fetch64(s + 64 + 40),
        (Rotate(z + y + v.first + Fetch64(s + 64 + 8), 37) * k1) ^ w.second);
}

constexpr uint128_t CityHash128WithSeed_loop1body(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
    return CityHash128WithSeed_loop1body1(s, len, seed,
        WeakHashLen32WithSeeds(s, v.second * k1, ((Rotate(x + y + v.first + Fetch64(s + 8), 37) * k1) ^ w.second) + w.first),
        WeakHashLen32WithSeeds(s + 32, (Rotate(z + w.first, 33) * k1) + w.second, (Rotate(y + v.second + Fetch64(s + 48), 42) * k1 + v.first + Fetch64(s + 40)) + Fetch64(s + 16)),
        (Rotate(x + y + v.first + Fetch64(s + 8), 37) * k1) ^ w.second,
        Rotate(y + v.second + Fetch64(s + 48), 42) * k1 + v.first + Fetch64(s + 40),
        Rotate(z + w.first, 33) * k1);
}

constexpr uint128_t CityHash128WithSeed_ge128(
    const char *s, size_t len, uint128_t seed,
    uint128_t v, uint128_t w, uint64_t x, uint64_t y, uint64_t z)
{
    return CityHash128WithSeed_loop1body(s, len, seed,
        uint128_t(v.first, Rotate(v.first, 42) * k1 + Fetch64(s + 8)), w,
        x, y, z);
}

constexpr uint128_t CityHash128WithSeed(const char *s, size_t len, uint128_t seed)
{
  return len < 128 ? murmur::CityMurmur(s, len, seed)
    : CityHash128WithSeed_ge128(s, len, seed,
        uint128_t(Rotate(Uint128High64(seed) ^ k1, 49) * k1 + Fetch64(s), 0),
        uint128_t(Rotate(Uint128High64(seed) + len * k1, 35) * k1 + Uint128Low64(seed), Rotate(Uint128Low64(seed) + Fetch64(s + 88), 53) * k1),
        Uint128Low64(seed), Uint128High64(seed), len * k1);
}

constexpr uint128_t CityHash128(const char *s, size_t len) {
  return len >= 16 ?
      CityHash128WithSeed(s + 16, len - 16,
                          uint128_t(Fetch64(s), Fetch64(s + 8) + k0)) :
      CityHash128WithSeed(s, len, uint128_t(k0, k1));
}

}; // namespace __detail

typedef __detail::uint128_t uint128_t;

constexpr uint128_t city128(const char *s, size_t len) {
    return __detail::CityHash128(s, len);
}

constexpr uint128_t city128_seed(const char *s, size_t len, uint128_t seed) {
    return __detail::CityHash128WithSeed(s, len, seed);
}

CONSTHASH_NAMESPACE_END;

#endif // _CONSTHASH_CITYHASH64_HXX
