# platform_device_id

get device id from android、ios、windows、linux、mac

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
## Support Platform
 
- [x] Android
- [x] IOS
- [x] MacOS
- [x] Windows `go-flutter`
- [x] Linux
- [x] Web

## Todo

- [ ] Windows `flutter`


## Go-flutter for windows/macos/linux

see [here](https://github.com/BestBurning/platform_device_id/tree/master/go)
