import 'dart:async';

import 'package:web/web.dart' as web;

import 'package:flutter_web_plugins/flutter_web_plugins.dart';
import 'package:platform_device_id_platform_interface/platform_device_id_platform_interface.dart';

/// A web implementation of the PlatformDeviceIdWeb plugin.
class PlatformDeviceIdWebPlugin extends PlatformDeviceIdPlatform {
  static void registerWith(Registrar registrar) =>
      PlatformDeviceIdPlatform.instance = PlatformDeviceIdWebPlugin();

  /// Returns a [String?] containing the ua of the web.
  @override
  Future<String?> getDeviceId() => Future.value(web.window.navigator.userAgent);
}
