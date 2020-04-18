import 'dart:async';

import 'package:flutter/services.dart';

class PlatformDeviceId {
  static const MethodChannel _channel =
      const MethodChannel('com.di1shaui.flutter/platform_device_id');

  static Future<String> get getDeviceId async {
    final String deviceId = await _channel.invokeMethod('getDeviceId');
    return deviceId;
  }
}
