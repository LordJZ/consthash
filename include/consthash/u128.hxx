
#pragma once
#ifndef _CONSTHASH_U128_HXX
#define _CONSTHASH_U128_HXX

#include <cstdint>
#include <utility>
#include <consthash/common.hxx>

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {;

template<uint64_t _Lo, uint64_t _Hi>
struct ctu128_t
{
    static constexpr uint64_t lo = _Lo;
    static constexpr uint64_t hi = _Hi;
};

typedef std::pair<uint64_t, uint64_t> rtu128_t;

#define RT2CT128_T(RT) consthash::__detail::ctu128_t<RT.first, RT.second>

template<>
struct ensure<rtu128_t>
{
    template<class T>
    static constexpr void ct() { }
};

}; // namespace __detail

CONSTHASH_NAMESPACE_END;

#endif
