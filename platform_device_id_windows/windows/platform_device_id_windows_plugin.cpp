#include "include/platform_device_id_windows/platform_device_id_windows_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <memory>
#include <sstream>

namespace {

class PlatformDeviceIdWindowsPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  PlatformDeviceIdWindowsPlugin();

  virtual ~PlatformDeviceIdWindowsPlugin();

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

// static
void PlatformDeviceIdWindowsPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "com.di1shuai.flutter/platform_device_id",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<PlatformDeviceIdWindowsPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

PlatformDeviceIdWindowsPlugin::PlatformDeviceIdWindowsPlugin() {}

PlatformDeviceIdWindowsPlugin::~PlatformDeviceIdWindowsPlugin() {}

void PlatformDeviceIdWindowsPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  FILE *rstream;
  std::string deviceId;
  std::string deviceIdResult;
  char buf[1024] = {0};

  if (method_call.method_name().compare("getDeviceId") == 0) {
    rstream = _popen("wmic csproduct get UUID","r");
    fread(buf, sizeof(char), sizeof(buf), rstream);
    _pclose(rstream);
    deviceIdResult = buf;
    std::size_t pos = deviceIdResult.find("\n");
    deviceId = deviceIdResult.substr(pos+1);
    result->Success(flutter::EncodableValue(deviceId));
  } else {
    result->NotImplemented();
  }
}

}  // namespace

void PlatformDeviceIdWindowsPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  PlatformDeviceIdWindowsPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
