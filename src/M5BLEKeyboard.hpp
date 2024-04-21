#pragma once

#include <BleKeyboard.h>

#include <functional>

class M5BLEKeyboard {
public:
    static const char* DEVICE_NAME;
    static const char* MANUFACTURER;

    M5BLEKeyboard(const char* name = DEVICE_NAME,
                  const char* manufacturer = MANUFACTURER);
    virtual ~M5BLEKeyboard(void);

    virtual bool begin(std::function<bool(void)> onConnected = nullptr,
                       std::function<bool(void)> onDisconnected = nullptr);
    virtual bool update(void);
    virtual bool end(void);

    virtual bool press(uint8_t k);
    virtual bool press(const MediaKeyReport k);
    virtual bool release(uint8_t k);
    virtual bool release(const MediaKeyReport k);
    virtual bool releaseAll(void);
    virtual bool write(uint8_t c);
    virtual bool write(const MediaKeyReport c);
    virtual bool write(const char* str, size_t len);
    virtual bool write(const String& str);

    virtual bool isConnected(void);

protected:
    BleKeyboard _keyboard;

private:
    bool _connected;
    std::function<bool(void)> _on_connect;
    std::function<bool(void)> _on_disconnect;
};
