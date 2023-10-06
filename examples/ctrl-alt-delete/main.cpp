#include "M5BLEKeyboard.hpp"

M5BLEKeyboard keyboard;

#if defined(ARDUINO_M5STACK_ATOM)
#define FASTLED_INTERNAL
#include <FastLED.h>

CRGB led[NUM_LEDS] = {
    0,
};
#endif

bool onConnect(void) {
#if defined(ARDUINO_M5STACK_ATOM)
    for (int i = 0; i < NUM_LEDS; ++i) {
        led[i] = CRGB::Green;
    }
    FastLED.show();
#endif
    return true;
}

bool onDisconnect(void) {
#if defined(ARDUINO_M5STACK_ATOM)
    for (int i = 0; i < NUM_LEDS; ++i) {
        led[i] = CRGB::Red;
    }
    FastLED.show();
#endif
    return true;
}

void setup(void) {
    keyboard.begin(onConnect, onDisconnect);
#if defined(ARDUINO_M5STACK_ATOM)
    FastLED.addLeds<WS2812, GPIO_NUM_27, GRB>(led, NUM_LEDS);
    FastLED.show();
    FastLED.setBrightness(20);
#endif
}

void loop(void) {
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
