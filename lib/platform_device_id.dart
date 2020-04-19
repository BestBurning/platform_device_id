import 'dart:async';
import 'dart:io';
import 'package:flutter/services.dart';
import 'package:device_info/device_info.dart';


class PlatformDeviceId {
  static const MethodChannel _channel =
      const MethodChannel('com.di1shaui.flutter/platform_device_id');

  static final DeviceInfoPlugin deviceInfoPlugin = DeviceInfoPlugin();


  static Future<String> get getDeviceId async {

    String deviceId;
    try {
      if (Platform.isAndroid) {
        AndroidDeviceInfo androidInfo = await deviceInfoPlugin.androidInfo;
        deviceId = androidInfo.androidId;
      } else if (Platform.isIOS) {
        IosDeviceInfo iosInfo = await deviceInfoPlugin.iosInfo;
        deviceId = iosInfo.identifierForVendor;
      } else {
        deviceId =  await _channel.invokeMethod('getDeviceId');
      }
    } on PlatformException {
      deviceId = '';
    }
    return deviceId;
  }
}
