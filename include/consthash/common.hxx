
#pragma once
#ifndef _CONSTHASH_COMMON_HXX
#define _CONSTHASH_COMMON_HXX

#include <cstdint>

#ifndef CONSTHASH_NAMESPACE_BEGIN
#  define CONSTHASH_NAMESPACE_BEGIN namespace consthash {
#endif

#ifndef CONSTHASH_NAMESPACE_END
#  define CONSTHASH_NAMESPACE_END }
#endif

CONSTHASH_NAMESPACE_BEGIN;

namespace __detail {;

template<class T>
struct ensure
{
    template<T value>
    static constexpr void ct() { }
};

constexpr size_t str_len(const char* const str)
{
	return *str ? (1 + str_len(str + 1)) : 0;
}

}; // namespace __detail

CONSTHASH_NAMESPACE_END;

#endif
