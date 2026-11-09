import 'dart:async';

import 'package:flutter_web_plugins/flutter_web_plugins.dart';
import 'package:platform_device_id_platform_interface/platform_device_id_platform_interface.dart';
import 'package:web/web.dart';

/// Web implementation of platform_device_id.
///
/// `package:web` compiles for dart2js and dart2wasm. `dart:html` does not.
class PlatformDeviceIdWebPlugin extends PlatformDeviceIdPlatform {
  static void registerWith(Registrar registrar) {
    PlatformDeviceIdPlatform.instance = PlatformDeviceIdWebPlugin();
  }

  /// Returns the browser user agent.
  @override
  Future<String?> getDeviceId() async {
    return window.navigator.userAgent;
  }
}
