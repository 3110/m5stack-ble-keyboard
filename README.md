# M5Stack用BLEキーボードライブラリ

[ESP32 BLE Keyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard)をM5Stackシリーズで使うためのライブラリです。

## 既知の問題

- ペアリング前に`BleKeyboard::isConnected()`がたまに`true`を返すため，`M5BLEKeyboard::update()`の中で接続・切断を繰り返す。
