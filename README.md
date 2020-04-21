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

`androidid` 

- IOS 

`identifierForVendor`


## Getting Started

a simple usage example:

```
import 'package:platform_device_id/platform_device_id.dart';

String deviceId = await PlatformDeviceId.getDeviceId;
```

## go-flutter for win/mac/linux

see [here](https://github.com/BestBurning/platform_device_id/tree/master/go)
