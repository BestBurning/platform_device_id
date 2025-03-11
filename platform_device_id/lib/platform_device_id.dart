import 'dart:async';
import 'dart:io';
import 'package:flutter/services.dart';
import 'package:device_info_plus/device_info_plus.dart';
import 'package:platform_device_id_platform_interface/platform_device_id_platform_interface.dart';
import 'package:flutter/foundation.dart' show kIsWeb;

/// Provides device id information.
class PlatformDeviceId {
  /// Provides device and operating system information.
  static final DeviceInfoPlugin deviceInfoPlugin = DeviceInfoPlugin();

  /// Information derived from `android`-`androidId` or `ios`-`identifierForVendor`
  static Future<String?> get getDeviceId async {
    try {
      if (kIsWeb) {
        return PlatformDeviceIdPlatform.instance.getDeviceId();
      } else if (Platform.isAndroid) {
        final androidInfo = await deviceInfoPlugin.androidInfo;

        return androidInfo.id;
      } else if (Platform.isIOS) {
        final iosInfo = await deviceInfoPlugin.iosInfo;

        return iosInfo.identifierForVendor;
      } else {
        return await PlatformDeviceIdPlatform.instance.getDeviceId();
      }
    } on PlatformException {
      return '';
    }
  }
}
