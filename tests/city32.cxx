
#include "tests.hxx"
#include <consthash/cityhash32.hxx>
#include <cityhash/city.h>

#define CH_DET_TEST_FUNC_WITH(FUNCNAME, WITH_WHAT) \
    TEST(city_utility, FUNCNAME) { WITH_WHAT(FUNCNAME); };

uint32_t Hash32Len0to4(const char *s, size_t len);
uint32_t Hash32Len5to12(const char *s, size_t len);
uint32_t Hash32Len13to24(const char *s, size_t len);

struct Hash32Len0to4_traits
{
    static constexpr uint32_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::Hash32Len0to4(str, len);
    }

    static uint32_t hash_rt(const char* str, size_t len)
    {
        return Hash32Len0to4(str, len);
    }

    template<uint32_t ct_res>
	inline static void compare(uint32_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_0to4(Hash32Len0to4, Hash32Len0to4_traits, RT2CT_NULL);

struct Hash32Len5to12_traits
{
    static constexpr uint32_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::Hash32Len5to12(str, len);
    }

    static uint32_t hash_rt(const char* str, size_t len)
    {
        return Hash32Len5to12(str, len);
    }

    template<uint32_t ct_res>
	inline static void compare(uint32_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_5to12(Hash32Len5to12, Hash32Len5to12_traits, RT2CT_NULL);

struct Hash32Len13to24_traits
{
    static constexpr uint32_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::Hash32Len13to24(str, len);
    }

    static uint32_t hash_rt(const char* str, size_t len)
    {
        return Hash32Len13to24(str, len);
    }

    template<uint32_t ct_res>
	inline static void compare(uint32_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_13to24(Hash32Len13to24, Hash32Len13to24_traits, RT2CT_NULL);

struct city32_traits
{
    static constexpr uint32_t hash_ct(const char* str, size_t len)
    {
        return consthash::city32(str, len);
    }

    static uint32_t hash_rt(const char* str, size_t len)
    {
        return CityHash32(str, len);
    }

    template<uint32_t ct_res>
	inline static void compare(uint32_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_ALL_STD_TRAITS(city32, RT2CT_NULL);
