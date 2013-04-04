
#include "tests.hxx"
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
