/*
  Unittest for templates
 */
#include <gtest/gtest.h>
#include <gob_template_helper.hpp>
using namespace goblib::template_helper;
#include "gob_math.hpp"
#include <gob_m5s_clock.hpp>
#include <chrono>
#include <array>

TEST(Template, M5Stack))
{
    auto b = goblib::template_helper::is_clock<goblib::m5s::arduino_clock>::value;
    EXPECT_TRUE(b);
    b = goblib::template_helper::is_clock<goblib::m5s::esp_clock>::value;
    EXPECT_TRUE(b);
}
