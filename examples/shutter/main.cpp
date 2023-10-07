#include "M5BLEKeyboard.hpp"

M5BLEKeyboard keyboard;

#if defined(ARDUINO_M5STACK_ATOM) || defined(ARDUINO_M5STACK_ATOMS3_LITE)
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
#if defined(ARDUINO_M5STACK_ATOM) || defined(ARDUINO_M5STACK_ATOMS3_LITE)
    showLED(CRGB::Green);
#endif
    return true;
}

bool onDisconnect(void) {
#if defined(ARDUINO_M5STACK_ATOM) || defined(ARDUINO_M5STACK_ATOMS3_LITE)
    showLED(CRGB::Red);
#endif
    return true;
}

void setup(void) {
    keyboard.begin(onConnect, onDisconnect);
#if defined(ARDUINO_M5STACK_ATOM) || defined(ARDUINO_M5STACK_ATOMS3_LITE)
    FastLED.addLeds<WS2812, DATA_PIN, RGB_ORDER>(led, NUM_LEDS);
    FastLED.show();
    FastLED.setBrightness(20);
#endif
}

void loop(void) {
    keyboard.update();
    if (M5.BtnA.wasClicked()) {
        keyboard.write(KEY_MEDIA_VOLUME_UP);
    }
    M5.delay(10);
}
