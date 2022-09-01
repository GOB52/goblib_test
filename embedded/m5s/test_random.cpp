/*
  Unittest for gob_random
*/
#include "gtest/gtest.h"
#include <gob_random.hpp>
using namespace goblib;
#include <gob_m5s_random.hpp>
#include <Arduino.h>

TEST(Random, Arduino)
{
    EXPECT_TRUE(goblib::template_helper::is_rng<goblib::m5s::arduino_engine>::value);

    Rng<goblib::m5s::arduino_engine> rng_ae; // hardware RNG
    goblib::m5s::arduino_engine ae;
    std::uniform_int_distribution<> d_int(-2,2);
    std::uniform_real_distribution<> d_real(0.0f, 0.00001f);

    //    printf("d_int %ld\n", d_int(ae));
    //    printf("rng %ld\n", rng_ae(-2,2));


    for(int i=0;i<10000;++i)
    {
        auto di = d_int(ae);
        auto df = d_real(ae);
        auto ri = rng_ae(-2,2);
        auto rf = rng_ae(0.0f, 0.00001f);
        EXPECT_GE(di, -2);
        EXPECT_LE(di,  2);
        EXPECT_GE(df, 0.0f);
        EXPECT_LE(df, 0.00001f);

        EXPECT_GE(ri, -2);
        EXPECT_LE(ri,  2);
        EXPECT_GE(rf, 0.0f);
        EXPECT_LE(rf, 0.00001f);
    }
}
