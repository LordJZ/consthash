
#include "tests.hxx"
#include <consthash/crc32.hxx>

extern "C" uint32_t crc32(uint32_t crc, const void *buf, size_t size);

struct crc32_traits
{
    static constexpr uint32_t hash_ct(const char* str, size_t len)
    {
        return consthash::crc32(str, len);
    }

    template <size_t N>
    static constexpr uint32_t hash_ct(const char (&str)[N])
    {
        return consthash::crc32(str);
    }

    static constexpr uint32_t hash_ct(std::nullptr_t str)
    {
        return consthash::crc32(str);
    }

    static uint32_t hash_rt(const char* str, size_t len)
    {
        return crc32(0, str, len);
    }

    template<uint32_t ct_res>
	inline static void compare(uint32_t rt_res)
	{
		ASSERT_EQ(rt_res, ct_res);
	}
};

HASHER_TEST_ALL_STD_TRAITS(crc32, RT2CT_NULL);
