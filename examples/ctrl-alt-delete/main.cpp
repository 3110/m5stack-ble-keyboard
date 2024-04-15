#include <M5Unified.h>

#include "M5BLEKeyboard.hpp"

M5BLEKeyboard keyboard;

#if defined(HAS_LED)
#define FASTLED_INTERNAL
#include <FastLED.h>

CRGB led[NUM_LEDS] = {
    CRGB::Black,
};

inline void showLED(const CRGB& color, size_t n_leds = NUM_LEDS) {
    for (size_t i = 0; i < n_leds; ++i) {
        led[i] = color;
    }
    FastLED.show();
}
#endif

bool onConnect(void) {
#if defined(HAS_LED)
    showLED(CRGB::Green);
#endif
    return true;
}

bool onDisconnect(void) {
#if defined(HAS_LED)
    showLED(CRGB::Red);
#endif
    return true;
}

void setup(void) {
    M5.begin();
    keyboard.begin(onConnect, onDisconnect);
#if defined(HAS_LED)
    FastLED.addLeds<WS2812, DATA_PIN, RGB_ORDER>(led, NUM_LEDS);
    FastLED.show();
    FastLED.setBrightness(20);
#endif
}

void loop(void) {
    M5.update();
    keyboard.update();
    if (M5.BtnA.wasClicked()) {
        M5_LOGI("Sending Ctrl+Alt+Delete...");
        keyboard.press(KEY_LEFT_CTRL);
        keyboard.press(KEY_LEFT_ALT);
        keyboard.press(KEY_DELETE);
        M5.delay(100);
        keyboard.releaseAll();
    }
    M5.delay(10);
}
