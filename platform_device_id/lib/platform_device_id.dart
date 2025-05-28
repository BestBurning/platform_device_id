import 'dart:async';
import 'dart:io';
import 'package:device_info_plus/device_info_plus.dart';
import 'package:flutter/services.dart';
import 'package:platform_device_id_platform_interface/platform_device_id_platform_interface.dart';
import 'package:flutter/foundation.dart' show kIsWeb;
import 'package:flutter_udid/flutter_udid.dart';
import 'package:shared_preferences/shared_preferences.dart';

/// Provides device id information.
class PlatformDeviceId {
  /// Provides device and operating system information.
  static final DeviceInfoPlugin deviceInfoPlugin = DeviceInfoPlugin();
  
  /// Key for storing the generated device ID in SharedPreferences
  static const String _deviceIdKey = 'platform_device_id_key';

  /// Information derived from `android`-`flutter_udid` or `ios`-`identifierForVendor`
  /// Falls back to SharedPreferences for persistence
  static Future<String?> get getDeviceId async {
    String? deviceId;
    try {
      if (kIsWeb) {
        deviceId = await PlatformDeviceIdPlatform.instance.getDeviceId();
      } else if (Platform.isAndroid) {
        // Use flutter_udid directly for Android instead of androidInfo.id
        try {
          deviceId = await FlutterUdid.udid;
        } catch (e) {
          print('Error getting Android UDID: $e');
          deviceId = null; // Will trigger the fallback logic below
        }
      } else if (Platform.isIOS) {
        IosDeviceInfo iosInfo = await deviceInfoPlugin.iosInfo;
        deviceId = iosInfo.identifierForVendor;
      } else {
        deviceId = await PlatformDeviceIdPlatform.instance.getDeviceId();
      }
      
      // If deviceId is null, empty, or consists only of whitespace, use fallback mechanisms
      if (deviceId == null || deviceId.trim().isEmpty) {
        // For non-Android platforms, try flutter_udid as first fallback
        if (!Platform.isAndroid) {
          try {
            deviceId = await FlutterUdid.udid;
          } catch (e) {
            print('Error getting UDID: $e');
          }
        }
        
        // If still empty, check SharedPreferences for a previously stored ID
        if (deviceId == null || deviceId.trim().isEmpty) {
          final prefs = await SharedPreferences.getInstance();
          deviceId = prefs.getString(_deviceIdKey);
          
          // If no ID in SharedPreferences, generate one using flutter_udid's consistentUdid
          // and store it for future use
          if (deviceId == null || deviceId.trim().isEmpty) {
            try {
              deviceId = await FlutterUdid.consistentUdid;
              // Store the generated ID for future use
              await prefs.setString(_deviceIdKey, deviceId ?? '');
            } catch (e) {
              print('Error getting consistent UDID: $e');
              // If all else fails, return an empty string
              deviceId = '';
            }
          }
        } else {
          // Store the flutter_udid value in SharedPreferences for future use
          final prefs = await SharedPreferences.getInstance();
          await prefs.setString(_deviceIdKey, deviceId);
        }
      }
    } on PlatformException {
      // Try flutter_udid as fallback for platform exception
      try {
        deviceId = await FlutterUdid.udid;
      } catch (e) {
        // If flutter_udid also fails, try to get from SharedPreferences
        final prefs = await SharedPreferences.getInstance();
        deviceId = prefs.getString(_deviceIdKey);
        
        // If still no ID, generate one
        if (deviceId == null || deviceId.trim().isEmpty) {
          try {
            deviceId = await FlutterUdid.consistentUdid;
            await prefs.setString(_deviceIdKey, deviceId ?? '');
          } catch (e) {
            deviceId = '';
          }
        }
      }
    }
    
    return deviceId;
  }
}
