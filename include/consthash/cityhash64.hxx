
#pragma once
#ifndef _CONSTHASH_CITYHASH64_HXX
#define _CONSTHASH_CITYHASH64_HXX

#include <consthash/cityhash_util.hxx>

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {

// Declaration
constexpr uint64_t city64impl_loop(const char *s, size_t len, uint64_t x, uint64_t y, uint64_t z, uint128_t v, uint128_t w);

constexpr uint64_t city64impl_loop_body2(const char *s, size_t len, uint64_t x, uint64_t y, uint64_t z, uint128_t v, uint128_t w) {
    return city64impl_loop(s + 64, len - 64, z, y, x,
        WeakHashLen32WithSeeds(s, v.second * k1, x + w.first),
        WeakHashLen32WithSeeds(s + 32, z + w.second, y + Fetch64(s + 16)));
}

constexpr uint64_t city64impl_loop_body1(const char *s, size_t len, uint64_t x, uint64_t y, uint64_t z, uint128_t v, uint128_t w) {
    return city64impl_loop_body2(s, len,
        (Rotate(x + y + v.first + Fetch64(s + 8), 37) * k1) ^ w.second,
        (Rotate(y + v.second + Fetch64(s + 48), 42) * k1) + v.first + Fetch64(s + 40),
        Rotate(z + w.first, 33) * k1,
        v, w);
}

constexpr uint64_t city64impl_loop(const char *s, size_t len, uint64_t x, uint64_t y, uint64_t z, uint128_t v, uint128_t w) {
    return len == 0 ? HashLen16(HashLen16(v.first, w.first) + ShiftMix(y) * k1 + z,
                   HashLen16(v.second, w.second) + x) : city64impl_loop_body1(s, len, x, y, z, v, w);
}

constexpr uint64_t city64impl_sub2(const char *s, size_t len, uint64_t x, uint64_t y, uint64_t z) {
    return city64impl_loop(s, (len - 1) & ~static_cast<size_t>(63),
        x * k1 + Fetch64(s), y, z,
        WeakHashLen32WithSeeds(s + len - 64, len, z),
        WeakHashLen32WithSeeds(s + len - 32, y + k1, x));
}

constexpr uint64_t city64impl_sub1(const char *s, size_t len) {
    return city64impl_sub2(s, len,
        Fetch64(s + len - 40),
        Fetch64(s + len - 16) + Fetch64(s + len - 56),
        HashLen16(Fetch64(s + len - 48) + len, Fetch64(s + len - 24)));
}

constexpr uint64_t city64impl(const char *s, size_t len)
{
    return
        len <= 32 ? (len <= 16 ? HashLen0to16(s, len) : HashLen17to32(s, len)) :
        len <= 64 ? HashLen33to64(s, len) : city64impl_sub1(s, len);
}

constexpr uint64_t city64_seeds_impl(const char *s, size_t len,
                                       uint64_t seed0, uint64_t seed1) {
  return HashLen16(city64impl(s, len) - seed0, seed1);
}

constexpr uint64_t city64_seed_impl(const char *s, size_t len, uint64_t seed) {
  return city64_seeds_impl(s, len, k2, seed);
}

} // namespace __detail

// Hash function for a byte array.
constexpr uint64_t city64(const char *buf, size_t len)
{
    return __detail::city64impl(buf, len);
}

// Hash function for a byte array.  For convenience, a 64-bit seed is also
// hashed into the result.
constexpr uint64_t city64_seed(const char *buf, size_t len, uint64_t seed)
{
    return __detail::city64_seed_impl(buf, len, seed);
}

// Hash function for a byte array.  For convenience, two seeds are also
// hashed into the result.
constexpr uint64_t city64_seeds(const char *buf, size_t len, uint64_t seed0, uint64_t seed1)
{
    return __detail::city64_seeds_impl(buf, len, seed0, seed1);
}

CONSTHASH_NAMESPACE_END;

#endif // _CONSTHASH_CITYHASH64_HXX
