/*
  main.cpp
*/
#include <gtest/gtest.h>

#include <M5stack.h>
#ifdef min
# undef min
#endif

#include <gob_m5s_sd.hpp>
#if __has_include (<esp_idf_version.h>)
#include <esp_idf_version.h>
#else // esp_idf_version.h has been introduced in Arduino 1.0.5 (ESP-IDF3.3)
#define ESP_IDF_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))
#define ESP_IDF_VERSION ESP_IDF_VERSION_VAL(3,2,0)
#endif
#include <gob_version.hpp>
#include <gob_m5s_version.hpp>

static void test()
{
    M5.Lcd.fillRect( 0,0,32,240, RUN_ALL_TESTS() ? TFT_RED : TFT_GREEN );
}

void setup()
{
    M5.begin(true /* LCD */, false /* SD */ , true /* Serial */);
    Wire.begin();
    while(!Serial) { delay(10); }
    SdFat& sd = goblib::m5s::SD::instance().sd();
    while(!sd.begin((unsigned)TFCARD_CS_PIN, SD_SCK_MHZ(25))) { delay(10); }

    /*
    printf("M5 begin\n");
    printf("Running setup() from %s\n", __FILE__);

    printf("CPP %ld\n", __cplusplus);
    printf("ESP-IDF Version %d.%d.%d\n",
           (ESP_IDF_VERSION>>16) & 0xFF, (ESP_IDF_VERSION>>8)&0xFF, ESP_IDF_VERSION & 0xFF);
    printf("goblib %s:%08xH\n", GOBLIB_VERSION_STRING, GOBLIB_VERSION_VALUE);
    printf("goblib_m5s %s:%08xH\n", GOBLIB_M5S_VERSION_STRING, GOBLIB_M5S_VERSION_VALUE);
    printf("Free heap pre test: %u\n", esp_get_free_heap_size());
    */

    ::testing::InitGoogleTest();
}
    
void loop()
{
    test();
    delay(1000 * 5);
}

#error "MAIN TEST"
