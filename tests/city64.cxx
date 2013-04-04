
#include "tests.hxx"
#include <consthash/cityhash64.hxx>
#include <cityhash/city.h>

struct city64_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::city64(str, len);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return CityHash64(str, len);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_ALL_STD_TRAITS(city64, RT2CT_NULL);

template<uint64_t seed>
struct city64_seed_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::city64_seed(str, len, seed);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return CityHash64WithSeed(str, len, seed);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

#define TEST_CITY64_SEED(NULL_ARG, SEED) \
    HASHER_TEST_ALL(city64_seed_##SEED, city64_seed_traits<SEED>, RT2CT_NULL)

FOR_EACH_64_BIT(, TEST_CITY64_SEED);

template<uint64_t seed0, uint64_t seed1>
struct city64_seeds_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::city64_seeds(str, len, seed0, seed1);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return CityHash64WithSeeds(str, len, seed0, seed1);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

#define TEST_CITY64_SEEDS(NULL_ARG, SEED1, SEED0) \
    HASHER_TEST_ALL(city64_seeds_##SEED0##_##SEED1, CONCAT(city64_seeds_traits<SEED0, SEED1>), RT2CT_NULL)

#define TEST_CITY64_SEEDS_0(NULL_ARG, SEED0) \
    FOR_EACH_64_BIT(, TEST_CITY64_SEEDS, SEED0)

FOR_EACH_64_BIT_2(, TEST_CITY64_SEEDS_0);
