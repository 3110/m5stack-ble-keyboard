#include "M5BLEKeyboard.hpp"

const char* M5BLEKeyboard::DEVICE_NAME = "M5 BLE Keyboard";
const char* M5BLEKeyboard::MANUFACTURER = "M5Stack";

M5BLEKeyboard::M5BLEKeyboard(const char* name, const char* manufacturer)
    : _keyboard(name, manufacturer),
      _connected(false),
      _on_connect(nullptr),
      _on_disconnect(nullptr) {
}

M5BLEKeyboard::~M5BLEKeyboard(void) {
}

bool M5BLEKeyboard::begin(std::function<bool(void)> onConnect,
                          std::function<bool(void)> onDisconnect) {
    M5.begin();
    this->_keyboard.begin();
    this->_on_connect = onConnect;
    this->_on_disconnect = onDisconnect;
    return true;
}

bool M5BLEKeyboard::update(void) {
    M5.update();
    if (this->_keyboard.isConnected()) {
        if (!this->_connected) {
            this->_connected = true;
            M5_LOGI("BLE Connected");
            if (this->_on_connect) {
                return this->_on_connect();
            }
        }
    } else {
        if (this->_connected) {
            this->_connected = false;
            M5_LOGI("BLE Disconnected");
            if (this->_on_disconnect) {
                return this->_on_disconnect();
            }
        }
    }
    return true;
}

bool M5BLEKeyboard::end(void) {
    this->_keyboard.end();
    return true;
}

bool M5BLEKeyboard::press(uint8_t k) {
    return this->_keyboard.press(k) == 1;
}

bool M5BLEKeyboard::release(uint8_t k) {
    return this->_keyboard.release(k) == 1;
}

bool M5BLEKeyboard::releaseAll(void) {
    this->_keyboard.releaseAll();
    return true;
}

bool M5BLEKeyboard::write(uint8_t c) {
    return this->_keyboard.write(c) == 1;
}

bool M5BLEKeyboard::write(const char* str, size_t len) {
    const size_t s =
        this->_keyboard.write(reinterpret_cast<const uint8_t*>(str), len);
    return s == len;
}

bool M5BLEKeyboard::write(const String& str) {
    return write(str.c_str(), str.length());
}

bool M5BLEKeyboard::isConnected(void) {
    return this->_keyboard.isConnected();
}
