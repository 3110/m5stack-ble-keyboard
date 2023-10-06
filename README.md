# M5Stack用BLEキーボードライブラリ

[ESP32 BLE Keyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard)をM5Stackシリーズで使うためのライブラリです。各機種ごとに公式から提供されているライブラリは使用せず，[M5Unified](https://github.com/m5stack/M5Unified)を使用しています。

## サンプルプログラム

サンプルプログラムを書き込んだM5Stackを起動すると，「M5 BLE Keyboard」という名前のBluetoothデバイスとして検出可能になりますので，デバイスを追加してペアリングしてください。
### CTRL+ALT+DELETEを送信する（`examples/ctrl-alt-delete`）

ボタンAを押すとCTRL+ALT+DELETEを送信します。

## 既知の問題

- ペアリング前に`BleKeyboard::isConnected()`がたまに`true`を返すため，`M5BLEKeyboard::update()`の中で接続・切断を繰り返しているように見えます。
