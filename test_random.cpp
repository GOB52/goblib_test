/*
  Unittest for gob_random
*/
#include "gtest/gtest.h"
#include <gob_random.hpp>
using namespace goblib;

TEST(Random, Basic)
{
    constexpr std::uint32_t seed = 52;

    EXPECT_TRUE(goblib::template_helper::is_rng<std::mt19937>::value);
    EXPECT_FALSE(goblib::template_helper::is_rng<std::vector<int>>::value);
    EXPECT_TRUE(goblib::template_helper::is_rng<std::ranlux24>::value);
    
    std::ranlux24 lux24(seed);
    std::uniform_int_distribution<> d_int(-100, +100);
    std::uniform_real_distribution<> d_real(-123.f, +123.f);
    Rng<std::ranlux24> rng_lux24(seed); // using same seed.

    EXPECT_EQ(d_int(lux24), rng_lux24(-100,100));
    EXPECT_FLOAT_EQ(d_real(lux24), rng_lux24(-123.f, 123.f));
    EXPECT_EQ(d_int(lux24), rng_lux24(-100,100));
    EXPECT_EQ(d_int(lux24), rng_lux24(-100,100));
    EXPECT_FLOAT_EQ(d_real(lux24), rng_lux24(-123.f, 123.f));
    EXPECT_FLOAT_EQ(d_real(lux24), rng_lux24(-123.f, 123.f));
    EXPECT_EQ(lux24(), rng_lux24());
    
    lux24.discard(100);
    rng_lux24.discard(99);
    EXPECT_NE(lux24(), rng_lux24());
    rng_lux24.discard(1);
    EXPECT_EQ(d_int(lux24), rng_lux24(-100,100));
}
