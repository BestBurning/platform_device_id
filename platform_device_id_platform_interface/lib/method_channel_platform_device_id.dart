import 'dart:async';

import 'package:flutter/services.dart';

import 'platform_device_id_platform_interface.dart';

const MethodChannel _channel = MethodChannel('com.di1shuai.flutter/platform_device_id');

class MethodChannelPlatformDeviceId extends PlatformDeviceIdPlatform{

  @override
  Future<String?> getDeviceId(){
    return _channel.invokeMethod<String?>('getDeviceId');
  }

}