
#include "tests.hxx"
#include <consthash/cityhash128.hxx>
#include <cityhash/city.h>

typedef consthash::__detail::uint128_t uint128_t;

#define CH_DET_TEST_FUNC_WITH(FUNCNAME, WITH_WHAT) \
    TEST(city_utility, FUNCNAME) { WITH_WHAT(FUNCNAME); };

uint128 CityMurmur(const char *s, size_t len, uint128 seed);

template<class seed>
struct city_murmur_traits
{
    static constexpr uint128_t hash_ct(const char* str, size_t len)
    {
        return consthash::__detail::murmur::CityMurmur(str, len, CT2RT128(seed));
    }

    static uint128_t hash_rt(const char* str, size_t len)
    {
        return CityMurmur(str, len, CT2RT128(seed));
    }

    template<class ct_res>
	inline static void compare(uint128_t rt_res)
	{
		ASSERT_EQ(rt_res, (CT2RT128(ct_res)));
	}
};

#define TEST_CITYMURMUR_0(ID, SEED) \
    HASHER_TEST_ALL(city_murmur_ ## ID, CONCAT(city_murmur_traits<RT2CT128_T(SEED)>), RT2CT128_T)

#define TEST_CITYMURMUR(NULL_ARG, SEED, ID) \
    TEST_CITYMURMUR_0(ID, SEED)

FOR_EACH_128_BIT(, TEST_CITYMURMUR, __COUNTER__);



struct city128_traits
{
    static constexpr uint128_t hash_ct(const char* str, size_t len)
    {
        return consthash::city128(str, len);
    }

    static uint128_t hash_rt(const char* str, size_t len)
    {
        return CityHash128(str, len);
    }

    template<class ct_res>
	inline static void compare(uint128_t rt_res)
	{
		ASSERT_EQ(rt_res, (CT2RT128(ct_res)));
	}
};

HASHER_TEST_ALL_STD_TRAITS(city128, RT2CT128_T);



template<class seed>
struct city128_seed_traits
{
    static constexpr uint128_t hash_ct(const char* str, size_t len)
    {
        return consthash::city128_seed(str, len, CT2RT128(seed));
    }

    static uint128_t hash_rt(const char* str, size_t len)
    {
        return CityHash128WithSeed(str, len, CT2RT128(seed));
    }

    template<class ct_res>
	inline static void compare(uint128_t rt_res)
	{
		ASSERT_EQ(rt_res, (CT2RT128(ct_res)));
	}
};

#define TEST_CITY128_SEED_0(ID, SEED) \
    HASHER_TEST_ALL(city128_seed_##ID, CONCAT(city128_seed_traits<RT2CT128_T(SEED)>), RT2CT128_T)

#define TEST_CITY128_SEED(NULL_ARG, SEED, ID) \
    TEST_CITY128_SEED_0(ID, SEED)

FOR_EACH_128_BIT(, TEST_CITY128_SEED, __COUNTER__);
