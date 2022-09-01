/*
  Unittest for gob_easing
*/
#include "gtest/gtest.h"
#include <gob_easing.hpp>
#include <M5Stack.h>
#include "helper.hpp"

using namespace goblib::easing;

namespace
{
constexpr std::int16_t WIDTH = 256;
constexpr std::int16_t HEIGHT = 120;
constexpr std::int16_t dx = (320 - WIDTH) / 2;
constexpr std::int16_t dy = (240 - HEIGHT) / 2;

void drawGraph(std::vector<std::int16_t>& v, std::uint16_t clr = TFT_WHITE)
{
    if(v.empty()) { return; }

    std::int16_t i = 0;
    auto end = v.cend() - 1;
    for (auto it = v.cbegin(); it != end; ++it, ++i)
    {
        M5.Lcd.drawLine(dx + i, dy + HEIGHT - *it, dx + i + 1, dy + HEIGHT - *(it+1), clr);
    }
}
//
}

template<class E> void easing(std::uint16_t clr = TFT_WHITE)
{
    //    printf("%s:%s\n", __func__, helper::TypeName<E>());

    E e;
    std::vector<std::int16_t> v;
    e.start(0, HEIGHT, WIDTH);
    while(e.busy())
    {
        e.pump();
        v.push_back(e.value());
    }
    EXPECT_EQ(v.back(), HEIGHT);
    drawGraph(v, clr);
}


TEST(Easing, M5Stack)
{
    M5.Lcd.drawRect(dx, dy, WIDTH, HEIGHT, TFT_WHITE);

    easing< EaseLerp<std::int16_t> >();

    easing< EaseInQuad<std::int16_t> >(RED);
    easing< EaseOutQuad<std::int16_t> >(BLUE);
    easing< EaseInOutQuad<std::int16_t> >(YELLOW);

    easing< EaseInCubic<std::int16_t> >(RED);
    easing< EaseOutCubic<std::int16_t> >(BLUE);
    easing< EaseInOutCubic<std::int16_t> >(YELLOW);

    easing< EaseInQuart<std::int16_t> >(RED);
    easing< EaseOutQuart<std::int16_t> >(BLUE);
    easing< EaseInOutQuart<std::int16_t> >(YELLOW);

    easing< EaseInQuint<std::int16_t> >(RED);
    easing< EaseOutQuint<std::int16_t> >(BLUE);
    easing< EaseInOutQuint<std::int16_t> >(YELLOW);

    easing< EaseInSine<std::int16_t> >(RED);
    easing< EaseOutSine<std::int16_t> >(BLUE);
    easing< EaseInOutSine<std::int16_t> >(YELLOW);

    easing< EaseInExpo<std::int16_t> >(RED);
    easing< EaseOutExpo<std::int16_t> >(BLUE);
    easing< EaseInOutExpo<std::int16_t> >(YELLOW);

    easing< EaseInCirc<std::int16_t> >(RED);
    easing< EaseOutCirc<std::int16_t> >(BLUE);
    easing< EaseInOutCirc<std::int16_t> >(YELLOW);

    easing< EaseInBack<std::int16_t> >(RED);
    easing< EaseOutBack<std::int16_t> >(BLUE);
    easing< EaseInOutBack<std::int16_t> >(YELLOW);

    easing< EaseInElastic<std::int16_t> >(RED);
    easing< EaseOutElastic<std::int16_t> >(BLUE);
    easing< EaseInOutElastic<std::int16_t> >(YELLOW);

    easing< EaseInBounce<std::int16_t> >(RED);
    easing< EaseOutBounce<std::int16_t> >(BLUE);
    easing< EaseInOutBounce<std::int16_t> >(YELLOW);
}
