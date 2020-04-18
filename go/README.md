# platform_device_id

This Go package implements the host-side of the Flutter [platform_device_id](https://github.com/BestBurning/platform_device_id) plugin.

## Usage

Import as:

```go
import platform_device_id "github.com/BestBurning/platform_device_id/go"
```

Then add the following option to your go-flutter [application options](https://github.com/go-flutter-desktop/go-flutter/wiki/Plugin-info):

```go
flutter.AddPlugin(&platform_device_id.PlatformDeviceIdPlugin{}),
```
