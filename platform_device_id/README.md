# platform_device_id

get device id from android、ios、windows、linux、mac、web

## Description

- Windows 

`BIOS UUID` e.g. `99A4D301-53F5-11CB-8CA0-9CA39A9E1F01`
- Linux 

`BIOS UUID` e.g. `32a70060-2a39-437e-88e2-d68e6154de9f`
- Mac 

`IOPlatformUUID` e.g. `02662E79-E342-521C-98EA-D4C18B61FEF3`

- Android 

`AndroidId` e.g. `9774d56d682e549c`

- IOS 

`IdentifierForVendor` e.g. `9C287922-EE26-4501-94B5-DDE6F83E1475`

- Web

`UserAgent` e.g. `Mozilla/5.0 (Macintosh; Intel Mac OS X 11_2_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.114 Safari/537.36`

## Getting Started

a simple usage example:

```dart
import 'package:platform_device_id/platform_device_id.dart';

String? deviceId = await PlatformDeviceId.getDeviceId;
```
## Plugins Info

| Plugin | Pub | Points | Popularity | Likes |
|--------|-----|--------|------------|-------|
| [platform_device_id](./platform_device_id/) | [![pub package](https://img.shields.io/pub/v/platform_device_id.svg)](https://pub.dev/packages/platform_device_id) | [![pub points](https://badges.bar/platform_device_id/pub%20points)](https://pub.dev/packages/platform_device_id/score) |  [![popularity](https://badges.bar/platform_device_id/popularity)](https://pub.dev/packages/platform_device_id/score) | [![likes](https://badges.bar/platform_device_id/likes)](https://pub.dev/packages/platform_device_id/score) |
| [platform_device_id_macos](./platform_device_id_macos/) | [![pub package](https://img.shields.io/pub/v/platform_device_id_macos.svg)](https://pub.dev/packages/platform_device_id_macos) | [![pub points](https://badges.bar/platform_device_id_macos/pub%20points)](https://pub.dev/packages/platform_device_id_macos/score) |  [![popularity](https://badges.bar/platform_device_id_macos/popularity)](https://pub.dev/packages/platform_device_id_macos/score) | [![likes](https://badges.bar/platform_device_id_macos/likes)](https://pub.dev/packages/platform_device_id_macos/score) |
| [platform_device_id_linux](./platform_device_id_linux/) | [![pub package](https://img.shields.io/pub/v/platform_device_id_linux.svg)](https://pub.dev/packages/platform_device_id_linux) | [![pub points](https://badges.bar/platform_device_id_linux/pub%20points)](https://pub.dev/packages/platform_device_id_linux/score) |  [![popularity](https://badges.bar/platform_device_id_linux/popularity)](https://pub.dev/packages/platform_device_id_linux/score) | [![likes](https://badges.bar/platform_device_id_linux/likes)](https://pub.dev/packages/platform_device_id_linux/score) |
| [platform_device_id_windows](./platform_device_id_windows/) | [![pub package](https://img.shields.io/pub/v/platform_device_id_windows.svg)](https://pub.dev/packages/platform_device_id_windows) | [![pub points](https://badges.bar/platform_device_id_windows/pub%20points)](https://pub.dev/packages/platform_device_id_windows/score) |  [![popularity](https://badges.bar/platform_device_id_windows/popularity)](https://pub.dev/packages/platform_device_id_windows/score) | [![likes](https://badges.bar/platform_device_id_windows/likes)](https://pub.dev/packages/platform_device_id_windows/score) |
| [platform_device_id_web](./platform_device_id_web/) | [![pub package](https://img.shields.io/pub/v/platform_device_id_web.svg)](https://pub.dev/packages/platform_device_id_web) | [![pub points](https://badges.bar/platform_device_id_web/pub%20points)](https://pub.dev/packages/platform_device_id_web/score) |  [![popularity](https://badges.bar/platform_device_id_web/popularity)](https://pub.dev/packages/platform_device_id_web/score) | [![likes](https://badges.bar/platform_device_id_web/likes)](https://pub.dev/packages/platform_device_id_web/score) |



## Go-flutter for windows/macos/linux

see [here](https://github.com/BestBurning/platform_device_id/tree/master/platform_device_id/go)
