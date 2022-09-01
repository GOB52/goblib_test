/*
  Unittest for gob_profile
*/
#include <gtest/gtest.h>
#include <gob_profile.hpp>
#include <thread>

#ifdef GOBLIB_ENABLE_PROFILE
using goblib::profile::MeasuringInstrument;
using goblib::profile::Ordinary;
#endif

TEST(Profile, Basic)
{
#ifdef GOBLIB_ENABLE_PROFILE
    constexpr const char tag32[] = "01234567890123456789012345678901234"; 
    constexpr const char tag31[] = "0123456789012345678901234567890"; // 31 char +'\0

    EXPECT_EQ(Ordinary::TAG_SIZE, goblib::size(tag31));

    Ordinary block_0(tag32, false);
    EXPECT_TRUE(std::strcmp(block_0.tag(), tag31) == 0);

    {
        Ordinary block_1("elapsed time of this block", false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        EXPECT_GE(block_1.elapsed().count(), std::chrono::milliseconds(10).count() );
    }
    
    do
    {
        MeasuringInstrument<std::chrono::system_clock,std::chrono::seconds> m_sys("system_clock", false);
#if defined(ESP32)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        EXPECT_GE(m_sys.elapsed().count(),  std::chrono::millseconds(1000).count() );
#else
        std::this_thread::sleep_for(std::chrono::seconds(1));
        EXPECT_GE(m_sys.elapsed().count(),  std::chrono::seconds(1).count() );
#endif

    }while(0);

    do
    {
        MeasuringInstrument<std::chrono::high_resolution_clock, std::chrono::nanoseconds> m_high("high_resolution_clock", false);
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // 1 usec.
        EXPECT_GE(m_high.elapsed().count(),  std::chrono::nanoseconds(1000).count() );

    }while(0);

    do
    {
        MeasuringInstrument<std::chrono::steady_clock, std::chrono::milliseconds> m_steady("steady_clock", false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10 msec
        EXPECT_GE(m_steady.elapsed().count(), std::chrono::milliseconds(10).count() );

    }while(0);
#endif
}
