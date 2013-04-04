
#include "tests.hxx"
#include <cityhash/city.h>

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
