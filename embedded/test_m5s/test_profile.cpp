/*
  Unittest for gob_profile on M5Stack
*/
#include <gtest/gtest.h>
#include <gob_profile.hpp>
#include <gob_m5s_thread.hpp>
#ifdef GOBLIB_ENABLE_PROFILE
using goblib::profile::MeasuringInstrument;
using goblib::profile::Ordinary;
#endif

TEST(Profile, M5Stack)
{
#ifdef GOBLIB_ENABLE_PROFILE
    do
    {
        MeasuringInstrument<goblib::m5s::esp_clock, std::chrono::seconds> mi_esp("esp_clock", false);
        goblib::m5s::this_thread::sleep_for(std::chrono::seconds(1)); // 1 sec.
        EXPECT_GE(mi_esp.elapsed().count(), std::chrono::seconds(1).count() ) << "esp_clock";
    }while(0);

    do
    {
        MeasuringInstrument<std::chrono::high_resolution_clock, std::chrono::nanoseconds> mi_high("high_resolution_clock", false);
        goblib::m5s::this_thread::sleep_for(std::chrono::microseconds(1)); // 1 usec.
        EXPECT_GE(mi_high.elapsed().count(), std::chrono::nanoseconds(1000).count() ) << "high_clock";

    }while(0);

    do
    {
        MeasuringInstrument<goblib::m5s::arduino_clock, std::chrono::milliseconds> mi_arduino("ardiono_clock", false);
        goblib::m5s::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10 msec
        EXPECT_GE(mi_arduino.elapsed().count(), std::chrono::milliseconds(10).count() ) << "arduino_clock";

    }while(0);
#endif
}
