/*
  Unittest for gob_shape2d
*/
#include "gtest/gtest.h"
#include <gob_shape2d.hpp>
#include <gob_line2d.hpp>
#include <gob_rect2d.hpp>
#include <gob_ellipse2d.hpp>
using namespace goblib;
#include <M5Stack.h>

using Pos2i = shape2d::Point<std::int32_t>;
using Pos2f = shape2d::Point<float>;
using Line2f = shape2d::LineSegment<float>;

namespace
{
void draw(std::vector<Pos2i>& v, std::uint16_t clr = TFT_WHITE)
{
    if(v.empty()) { return; }

    auto end = v.cend() - 1;
    for (auto it = v.cbegin(); it != end; ++it)
    {
        auto s = *it;
        auto e = *(it+1);
        M5.Lcd.drawLine(s.x(), s.y(), e.x(), e.y(), clr);
    }
}
//
}

TEST(Shape2d, Circle)
{
    using Circle2i = shape2d::Circle<int16_t>;

    Pos2i cpos(320/2, 240/2);
    Circle2i c(cpos, 10);
    std::vector<Pos2i> v;
    
    for(int i=1; i <=10; ++i)
    {
        c.setRadius(i*10);
        v.clear();
        for(int j=0; j <= 36; ++j)
        {
            v.emplace_back(c.pos(goblib::math::deg2rad(j * 10.f)));
        }
        draw(v, TFT_GREEN);
    }
}


TEST(Shape2d, Ellipse)
{
    using Ellipse2i = shape2d::Ellipse<int16_t>;

    Pos2i cpos(320/2, 240/2);
    Ellipse2i e(cpos, 100, 25);
    std::vector<Pos2i> v;

    #if 0
    for(int i=1; i <=10; ++i)
    {
        c.setRadius(i*4, i*8);
        v.clear();
        for(int j=0; j <= 36; ++j)
        {
            v.emplace_back(c.pos(goblib::math::deg2rad(j * 10.f)));
        }
        draw(v, TFT_PINK);
    }
    #endif

    
    for(int i=0; i < 36; ++i)
    {
        auto rot = goblib::math::deg2rad(i * 10.0f);
        e.setRotate(rot);

        v.clear();
        for(int j=0; j<=36; ++j)
        {
            v.emplace_back(e.pos(goblib::math::deg2rad(j * 10.f)));
        }
        draw(v, TFT_PINK);
    }
}
