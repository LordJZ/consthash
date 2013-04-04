
#include <cityhash/city.h>
#include <consthash/cityhash_util.hxx>
#include "tests.hxx"

#ifdef _MSC_VER

#include <stdlib.h>
#define bswap_32(x) _byteswap_ulong(x)
#define bswap_64(x) _byteswap_uint64(x)

#elif defined(__APPLE__)

// Mac OS X / Darwin features
#include <libkern/OSByteOrder.h>
#define bswap_32(x) OSSwapInt32(x)
#define bswap_64(x) OSSwapInt64(x)

#else

#include <byteswap.h>

#endif

#define CH_DET_TEST_FUNC_WITH(FUNCNAME, WITH_WHAT) \
    TEST(city_utility, FUNCNAME) { WITH_WHAT(FUNCNAME); };

uint64_t swap_bytes_64(uint64_t value)
{
    return bswap_64(value);
}

uint32_t swap_bytes_32(uint32_t value)
{
    return bswap_32(value);
}

uint32_t fmix(uint32_t h);
uint32 Rotate32(uint32 val, int shift);
uint64_t Rotate(uint64_t val, int shift);
uint64 ShiftMix(uint64 val);
uint64 HashLen16(uint64 u, uint64 v);
uint64 HashLen16(uint64 u, uint64 v, uint64 mul);
uint32_t Mur(uint32_t a, uint32_t h);
std::pair<uint64_t, uint64_t> WeakHashLen32WithSeeds(
    uint64_t w, uint64_t x, uint64_t y, uint64_t z, uint64_t a, uint64_t b);
uint64 HashLen0to16(const char *s, size_t len);
uint64 HashLen17to32(const char *s, size_t len);
uint64 HashLen33to64(const char *s, size_t len);
uint64 Fetch64(const char *p);
uint32 Fetch32(const char *p);

CH_DET_TEST_FUNC_WITH(swap_bytes_32, CH_DET_TEST_FUNC_32);
CH_DET_TEST_FUNC_WITH(swap_bytes_64, CH_DET_TEST_FUNC_64);

CH_DET_TEST_FUNC_WITH(Uint128Low64, CH_DET_TEST_FUNC_128);
CH_DET_TEST_FUNC_WITH(Uint128High64, CH_DET_TEST_FUNC_128);

CH_DET_TEST_FUNC_WITH(Hash128to64, CH_DET_TEST_FUNC_128);
CH_DET_TEST_FUNC_WITH(fmix, CH_DET_TEST_FUNC_32);

CH_DET_TEST_FUNC_WITH(Rotate32, CH_DET_TEST_FUNC_32_5);
CH_DET_TEST_FUNC_WITH(Rotate, CH_DET_TEST_FUNC_64_6);
CH_DET_TEST_FUNC_WITH(ShiftMix, CH_DET_TEST_FUNC_64);

TEST(city_utility, HashLen16_2) { CH_DET_TEST_FUNC_64_64(HashLen16); };
TEST(city_utility, HashLen16_3) { CH_DET_TEST_FUNC_64_64_64(HashLen16); };

CH_DET_TEST_FUNC_WITH(Mur, CH_DET_TEST_FUNC_32_32);

CONSTHASH_NAMESPACE_BEGIN;
namespace __detail {;

constexpr uint64_t Fetch64_wrapper(const char* s, size_t len)
{
    return len < sizeof(uint64_t) ? 0 : Fetch64(s);
}

constexpr uint32_t Fetch32_wrapper(const char* s, size_t len)
{
    return len < sizeof(uint32_t) ? 0 : Fetch32(s);
}

}; // namespace __detail
CONSTHASH_NAMESPACE_END;

uint64_t Fetch64_wrapper(const char* s, size_t len)
{
    if (len < sizeof(uint64_t))
        return 0;

    return Fetch64(s);
}

uint32_t Fetch32_wrapper(const char* s, size_t len)
{
    if (len < sizeof(uint32_t))
        return 0;

    return Fetch32(s);
}

CH_DET_TEST_FUNC_WITH(Fetch64_wrapper, CH_DET_TEST_FUNC_STRS);
CH_DET_TEST_FUNC_WITH(Fetch32_wrapper, CH_DET_TEST_FUNC_STRS);

#undef RT2CT_CURRENT
#define RT2CT_CURRENT(x) RT2CT128_T(x)
CH_DET_TEST_FUNC_WITH(WeakHashLen32WithSeeds, CH_DET_TEST_FUNC_64_64_64_64_64_64);
#undef RT2CT_CURRENT
#define RT2CT_CURRENT(x) RT2CT_NULL(x)

struct HashLen0to16_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::HashLen0to16(str, len);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return HashLen0to16(str, len);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_0to16(HashLen0to16, HashLen0to16_traits, RT2CT_NULL);

struct HashLen17to32_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::HashLen17to32(str, len);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return HashLen17to32(str, len);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_17to32(HashLen17to32, HashLen17to32_traits, RT2CT_NULL);

struct HashLen33to64_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::HashLen33to64(str, len);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return HashLen33to64(str, len);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_33to64(HashLen33to64, HashLen33to64_traits, RT2CT_NULL);
