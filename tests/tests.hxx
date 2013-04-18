
#pragma once
#ifndef _TESTS_HXX
#define _TESTS_HXX

#include <cstddef>
#include <type_traits>
//#include <cstdio>
#include <consthash/common.hxx>
#include <gtest/gtest.h>

// Standard traits declaration
// has the following static interface:
//  constexpr rt_type hash_ct(const char*, size_t)
//  rt_type hash_ct(const char*, size_t)
//  template<ct_type> void compare(rt_type)

// Default macro to convert an instance of rt_type to ct_type.
#define RT2CT_NULL(x) x

#define RT2CT_CURRENT(x) RT2CT_NULL(x)

#define CONCAT(...) __VA_ARGS__

#define _HASHER_TEST_SINGLE(SUBNAME, STR, LEN, NAME, TRAITS, RT2CT) \
    TEST(NAME, SUBNAME) \
    { \
        typedef TRAITS traits; \
        auto constexpr ct_res = traits::hash_ct(STR, LEN); \
        traits::compare<RT2CT(ct_res)>(traits::hash_rt(STR, LEN)); \
    }

#define FOR_EACH_STR_0to4(DO, ...) \
    DO(empty_string,    NULL, 0, ##__VA_ARGS__); \
    DO(null_char,       "\0", 1, ##__VA_ARGS__); \
    DO(0xFF,            "\xFF", 1, ##__VA_ARGS__); \
    DO(1,               "1", 1, ##__VA_ARGS__); \
    DO(12,              "12", 2, ##__VA_ARGS__); \
    DO(123,             "123", 3, ##__VA_ARGS__); \
    DO(0xFFFFFFFF,      "\xFF\xFF\xFF\xFF", 4, ##__VA_ARGS__); \
    DO(four,            "four", 4, ##__VA_ARGS__)

#define FOR_EACH_STR_5to8(DO, ...) \
    DO(null_teminated,  "woot\0", 5, ##__VA_ARGS__); \
    DO(sixlen,          "sixlen", 6, ##__VA_ARGS__); \
    DO(0xFF_23456_0xFF, "\xFF 345 \xFF", 7, ##__VA_ARGS__); \
    DO(eight,           "- eight!", 8, ##__VA_ARGS__)

#define FOR_EACH_STR_9to12(DO, ...) \
    DO(123456789,       "123456789", 9, ##__VA_ARGS__); \
    DO(twelve_chars,    "0123456789AB", 12, ##__VA_ARGS__)

#define FOR_EACH_STR_13to16(DO, ...) \
    DO(thirteen_chars,  "0123456789AB\xFF", 13, ##__VA_ARGS__); \
    DO(fourteen_chars,  "\xFF_123456789ABC", 14, ##__VA_ARGS__); \
    DO(null_char_16,    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16, ##__VA_ARGS__); \
    DO(0123456789ABCDEF,"0123456789ABCDEF", 16, ##__VA_ARGS__)

#define FOR_EACH_STR_17to24(DO, ...) \
    DO(17byte,          "0123456789ABCDEF\0", 17, ##__VA_ARGS__); \
    DO(19byte,          "\xFF 23456789ABCDEF\0\0\0", 19, ##__VA_ARGS__); \
    DO(24chars,         "here's twenty-four chars", 24, ##__VA_ARGS__)

#define FOR_EACH_STR_25to32(DO, ...) \
    DO(25chars,         "here's twenty-five chars!", 25, ##__VA_ARGS__); \
    DO(26chars,         "\xFF here's twenty-six chars!", 26, ##__VA_ARGS__); \
    DO(32byte,          "0123456789ABCDEF0123456789ABCDEF", 32, ##__VA_ARGS__)

#define FOR_EACH_STR_33to64(DO, ...) \
    DO(33byte,          "0123456789ABCDEF0123456789ABCDEF\0", 33, ##__VA_ARGS__); \
    DO(35byte,          "0123456789ABCDEF0123456789ABCDEF\0\0\0", 35, ##__VA_ARGS__); \
    DO(64byte,          "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF", 64, ##__VA_ARGS__)

#define FOR_EACH_STR_65(DO, ...) \
    DO(128bytes, "At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos do", 128, ##__VA_ARGS__); \
    DO(144bytes, "At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas mo", 144, ##__VA_ARGS__); \
    DO(many1, "At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio.", 353, ##__VA_ARGS__); \
    DO(many2, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 446, ##__VA_ARGS__); \
    DO(many3, "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.", 370, ##__VA_ARGS__); \
    DO(many_zeros, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 230, ##__VA_ARGS__); \
    DO(many4, "Maecenas euismod odio ut erat euismod vel luctus turpis interdum. Sed lobortis nisl vel tortor aliquam in viverra nunc ultrices. Proin ut diam purus. Curabitur dapibus nunc vel enim dignissim nec semper elit mollis. Sed ante dolor, commodo quis placerat vitae, varius non lorem. Ut ut pulvinar purus.", 300, ##__VA_ARGS__)

/* COMBOS */

#define FOR_EACH_STR_0to16(DO, ...) \
    FOR_EACH_STR_0to4(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_5to8(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_9to12(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_13to16(DO, ##__VA_ARGS__)

#define FOR_EACH_STR_5to12(DO, ...) \
    FOR_EACH_STR_5to8(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_9to12(DO, ##__VA_ARGS__); \

#define FOR_EACH_STR_17to32(DO, ...) \
    FOR_EACH_STR_17to24(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_25to32(DO, ##__VA_ARGS__)

#define FOR_EACH_STR_13to24(DO, ...) \
    FOR_EACH_STR_13to16(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_17to24(DO, ##__VA_ARGS__)

#define FOR_EACH_STR(DO, ...) \
    FOR_EACH_STR_0to16(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_17to32(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_33to64(DO, ##__VA_ARGS__); \
    FOR_EACH_STR_65(DO, ##__VA_ARGS__)

#define HASHER_TEST_0to4(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_0to4(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_5to12(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_5to12(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_13to24(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_13to24(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_0to16(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_0to16(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_17to32(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_17to32(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_33to64(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_33to64(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_65(NAME, TRAITS, RT2CT) \
    FOR_EACH_STR_65(_HASHER_TEST_SINGLE, NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_ALL(NAME, TRAITS, RT2CT) \
	HASHER_TEST_0to16(NAME, CONCAT(TRAITS), RT2CT); \
	HASHER_TEST_17to32(NAME, CONCAT(TRAITS), RT2CT); \
	HASHER_TEST_33to64(NAME, CONCAT(TRAITS), RT2CT); \
	HASHER_TEST_65(NAME, CONCAT(TRAITS), RT2CT)

#define HASHER_TEST_ALL_STD_TRAITS(NAME, RT2CT) \
    HASHER_TEST_ALL(NAME, NAME ## _traits, RT2CT)


#define CH_DET consthash::__detail::

#define CH_DET_TEST_FUNC(FUNCNAME, ...) \
    do { \
        auto constexpr ct_value = CH_DET FUNCNAME(__VA_ARGS__); \
        auto rt_value = FUNCNAME(__VA_ARGS__); \
        CH_DET ensure<typename std::remove_const<decltype(ct_value)>::type>::ct<RT2CT_CURRENT(ct_value)>(); \
        ASSERT_EQ(rt_value, ct_value); \
    } while (0)

#define FOR_EACH_5_BIT(ARG, DO, ...) \
    DO(ARG, 0, ##__VA_ARGS__); \
    DO(ARG, 1, ##__VA_ARGS__); \
    DO(ARG, 2, ##__VA_ARGS__); \
    DO(ARG, 3, ##__VA_ARGS__); \
    DO(ARG, 10, ##__VA_ARGS__); \
    DO(ARG, 12, ##__VA_ARGS__); \
    DO(ARG, 16, ##__VA_ARGS__); \
    DO(ARG, 20, ##__VA_ARGS__); \
    DO(ARG, 24, ##__VA_ARGS__); \
    DO(ARG, 26, ##__VA_ARGS__); \
    DO(ARG, 30, ##__VA_ARGS__); \
    DO(ARG, 31, ##__VA_ARGS__)

#define FOR_EACH_6_BIT(ARG, DO, ...) \
    DO(ARG, 0, ##__VA_ARGS__); \
    DO(ARG, 1, ##__VA_ARGS__); \
    DO(ARG, 2, ##__VA_ARGS__); \
    DO(ARG, 3, ##__VA_ARGS__); \
    DO(ARG, 7, ##__VA_ARGS__); \
    DO(ARG, 12, ##__VA_ARGS__); \
    DO(ARG, 16, ##__VA_ARGS__); \
    DO(ARG, 20, ##__VA_ARGS__); \
    DO(ARG, 24, ##__VA_ARGS__); \
    DO(ARG, 26, ##__VA_ARGS__); \
    DO(ARG, 31, ##__VA_ARGS__); \
    DO(ARG, 32, ##__VA_ARGS__); \
    DO(ARG, 33, ##__VA_ARGS__); \
    DO(ARG, 41, ##__VA_ARGS__); \
    DO(ARG, 42, ##__VA_ARGS__); \
    DO(ARG, 43, ##__VA_ARGS__); \
    DO(ARG, 48, ##__VA_ARGS__); \
    DO(ARG, 49, ##__VA_ARGS__); \
    DO(ARG, 50, ##__VA_ARGS__); \
    DO(ARG, 60, ##__VA_ARGS__); \
    DO(ARG, 61, ##__VA_ARGS__); \
    DO(ARG, 62, ##__VA_ARGS__); \
    DO(ARG, 63, ##__VA_ARGS__)

#define FOR_EACH_32_BIT(ARG, DO, ...) \
    DO(ARG, 0U, ##__VA_ARGS__); \
    DO(ARG, 1U, ##__VA_ARGS__); \
    DO(ARG, 0x01234567U, ##__VA_ARGS__); \
    DO(ARG, 0xcc9e2d51U, ##__VA_ARGS__); \
    DO(ARG, 0x1b873593U, ##__VA_ARGS__); \
    DO(ARG, 0x85ebca6bU, ##__VA_ARGS__); \
    DO(ARG, 0xc2b2ae35U, ##__VA_ARGS__)

#define FOR_EACH_32_BIT_2(ARG, DO, ...) \
    DO(ARG, 0U, ##__VA_ARGS__); \
    DO(ARG, 0xc2b2ae35U, ##__VA_ARGS__)

#define FOR_EACH_64_BIT(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); DO(ARG, 1ULL, ##__VA_ARGS__); \
    DO(ARG, 0xFFFFFFFFFFFFFFFFULL, ##__VA_ARGS__); DO(ARG, 0xc3a5c85c97cb3127ULL, ##__VA_ARGS__); \
    DO(ARG, 0xb492b66fbe98f273ULL, ##__VA_ARGS__); DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_64_BIT_2(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); \
    DO(ARG, 0xFFFFFFFFFFFFFFFFULL, ##__VA_ARGS__); \
    DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_64_BIT_3(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); \
    DO(ARG, 0xFFFFFFFFFFFFFFFFULL, ##__VA_ARGS__); \
    DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_64_BIT_4(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); \
    DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_64_BIT_5(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); \
    DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_64_BIT_6(ARG, DO, ...) \
    DO(ARG, 0ULL, ##__VA_ARGS__); \
    DO(ARG, 0x9ae16a3b2f90404fULL, ##__VA_ARGS__)

#define FOR_EACH_128_BIT(ARG, DO, ...) \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0ULL, 0ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(1ULL, 1ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(1ULL, 0ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0ULL, 1ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0xFFFFFFFFFFFFFFFFULL, 0ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0ULL, 0xFFFFFFFFFFFFFFFFULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0xc3a5c85c97cb3127ULL, 0xb492b66fbe98f273ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0ULL, 0xc3a5c85c97cb3127ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0xb492b66fbe98f273ULL, 0ULL)), ##__VA_ARGS__); \
    DO(ARG, CONCAT(consthash::__detail::rtu128_t(0x9ae16a3b2f90404fULL, 1ULL)), ##__VA_ARGS__)

#define HASHER_TEST_TO_CH_DET_FUNC_CONVERTER(STR_NAME, STR, STR_LEN, FUNCNAME, ...) \
    CH_DET_TEST_FUNC(FUNCNAME, STR, STR_LEN, ##__VA_ARGS__);

#define CH_DET_TEST_FUNC_5(FUNCNAME, ...) \
    FOR_EACH_5_BIT(FUNCNAME, CH_DET_TEST_FUNC, ##__VA_ARGS__)
    
#define CH_DET_TEST_FUNC_6(FUNCNAME, ...) \
    FOR_EACH_6_BIT(FUNCNAME, CH_DET_TEST_FUNC, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_32(FUNCNAME, ...) \
    FOR_EACH_32_BIT(FUNCNAME, CH_DET_TEST_FUNC, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_32_5(FUNCNAME, ...) \
    FOR_EACH_5_BIT(FUNCNAME, CH_DET_TEST_FUNC_32, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_32_32(FUNCNAME, ...) \
    FOR_EACH_32_BIT_2(FUNCNAME, CH_DET_TEST_FUNC_32, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT(FUNCNAME, CH_DET_TEST_FUNC, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_6(FUNCNAME, ...) \
    FOR_EACH_6_BIT(FUNCNAME, CH_DET_TEST_FUNC_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT_2(FUNCNAME, CH_DET_TEST_FUNC_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_64_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT_3(FUNCNAME, CH_DET_TEST_FUNC_64_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_64_64_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT_4(FUNCNAME, CH_DET_TEST_FUNC_64_64_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_64_64_64_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT_5(FUNCNAME, CH_DET_TEST_FUNC_64_64_64_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_64_64_64_64_64_64(FUNCNAME, ...) \
    FOR_EACH_64_BIT_6(FUNCNAME, CH_DET_TEST_FUNC_64_64_64_64_64, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_128(FUNCNAME, ...) \
    FOR_EACH_128_BIT(FUNCNAME, CH_DET_TEST_FUNC, ##__VA_ARGS__)

#define CH_DET_TEST_FUNC_STRS(FUNCNAME, ...) \
    FOR_EACH_STR(HASHER_TEST_TO_CH_DET_FUNC_CONVERTER, FUNCNAME, ##__VA_ARGS__)

#endif
