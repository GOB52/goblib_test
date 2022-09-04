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

/*
  ESP32 std::this_thread::sleep_for does not meet specifications!
  function returns earlier than the specified time.

  see also https://en.cppreference.com/w/cpp/thread/sleep_for
  Blocks the execution of the current thread for at least the specified sleep_duration.

  So this test will be skipped.
*/
#if !defined(ESP32)
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
        MeasuringInstrument<std::chrono::system_clock,std::chrono::seconds> mi_sys("system_clock", false);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        EXPECT_GE(mi_sys.elapsed().count(),  std::chrono::seconds(1).count() );
    }while(0);

    do
    {
        MeasuringInstrument<std::chrono::high_resolution_clock, std::chrono::nanoseconds> mi_high("high_resolution_clock", false);
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // 1 usec.
        EXPECT_GE(mi_high.elapsed().count(),  std::chrono::nanoseconds(1000).count() );

    }while(0);

    do
    {
        MeasuringInstrument<std::chrono::steady_clock, std::chrono::milliseconds> mi_steady("steady_clock", false);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10 msec
        EXPECT_GE(mi_steady.elapsed().count(), std::chrono::milliseconds(10).count() );

    }while(0);
#endif
}
#endif
