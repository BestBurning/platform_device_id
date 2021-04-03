import 'dart:async';

import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'method_channel_platform_device_id.dart';

/// The interface that implementations of platform_device_id must implement.
///
/// Platform implementations should extend this class rather than implement it as `platform_device_id`
/// does not consider newly added methods to be breaking changes. Extending this class
/// (using `extends`) ensures that the subclass will get the default implementation, while
/// platform implementations that `implements` this interface will be broken by newly added
/// [UrlLauncherPlatform] methods.
abstract class PlatformDeviceIdPlatform extends PlatformInterface {
  /// Constructs a UrlLauncherPlatform.
  PlatformDeviceIdPlatform() : super(token: _token);

  static final Object _token = Object();

  static PlatformDeviceIdPlatform _instance = MethodChannelPlatformDeviceId();

  /// The default instance of [PlatformDeviceIdPlatform] to use.
  ///
  /// Defaults to [MethodChannelPlatformDeviceId].
  static PlatformDeviceIdPlatform get instance => _instance;

  /// Platform-specific plugins should set this with their own platform-specific
  /// class that extends [MethodChannelPlatformDeviceId] when they register themselves.
  static set instance(PlatformDeviceIdPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  /// Get the platform device id - [String]
  Future<String?> getDeviceId() {
    throw UnimplementedError('getDeviceId() has not been implemented.');
  }
}
