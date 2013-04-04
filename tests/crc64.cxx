
#include "tests.hxx"
#include <consthash/crc64.hxx>

extern "C" uint64_t crc64(uint64_t crc, const void *buf, size_t size);

struct crc64_traits
{
    static constexpr uint64_t hash_ct(const char* str, size_t len)
    {
        return consthash::crc64(str, len);
    }

    static uint64_t hash_rt(const char* str, size_t len)
    {
        return crc64(0, str, len);
    }

    template<uint64_t ct_res>
	inline static void compare(uint64_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_ALL_STD_TRAITS(crc64, RT2CT_NULL);
