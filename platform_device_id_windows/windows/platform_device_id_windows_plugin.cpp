#include "include/platform_device_id_windows/platform_device_id_windows_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <comdef.h>
#include <Wbemidl.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#pragma comment(lib, "wbemuuid.lib")

namespace {

// Reads Win32_ComputerSystemProduct.UUID directly through the WMI COM API.
//
// The previous implementation shelled out to `wmic csproduct get UUID`.
// Microsoft deprecated wmic.exe in 2021 and has been progressively removing
// it from Windows 11 (Feature-on-Demand since 22H2, off by default since
// 23H2/24H2, fully removed from 24H2/25H2 via the September 2026 cumulative
// update). On any machine where wmic.exe is gone, the old code silently got
// an empty stdout and returned an empty device id, which downstream made a
// perfectly stable machine look like a brand-new device. Talking to WMI
// directly has no dependency on that (or any other) external executable.
std::string GetSystemUuidViaWmi() {
  std::string result;

  HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);
  // S_OK: we own this initialization and must uninitialize it later.
  // S_FALSE / RPC_E_CHANGED_MODE: COM is already initialized on this thread
  // (by the Flutter engine, in whatever apartment model) and is usable as-is;
  // it is not ours to tear down.
  bool owns_com_init = (hres == S_OK);
  if (FAILED(hres) && hres != RPC_E_CHANGED_MODE) {
    return result;
  }

  // Only meaningful the first time it's called process-wide; a later call
  // (e.g. because the host already set its own security) returns
  // RPC_E_TOO_LATE, which is expected and safe to ignore.
  hres = CoInitializeSecurity(
      NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT,
      RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
  if (FAILED(hres) && hres != RPC_E_TOO_LATE) {
    if (owns_com_init) CoUninitialize();
    return result;
  }

  IWbemLocator *locator = NULL;
  hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
                           IID_IWbemLocator, (LPVOID *)&locator);
  if (FAILED(hres) || locator == NULL) {
    if (owns_com_init) CoUninitialize();
    return result;
  }

  IWbemServices *services = NULL;
  hres = locator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, 0, 0,
                                 0, &services);
  if (FAILED(hres) || services == NULL) {
    locator->Release();
    if (owns_com_init) CoUninitialize();
    return result;
  }

  hres = CoSetProxyBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE,
                            NULL, RPC_C_AUTHN_LEVEL_CALL,
                            RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
  if (FAILED(hres)) {
    services->Release();
    locator->Release();
    if (owns_com_init) CoUninitialize();
    return result;
  }

  IEnumWbemClassObject *enumerator = NULL;
  hres = services->ExecQuery(
      bstr_t("WQL"), bstr_t("SELECT UUID FROM Win32_ComputerSystemProduct"),
      WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &enumerator);
  if (FAILED(hres) || enumerator == NULL) {
    services->Release();
    locator->Release();
    if (owns_com_init) CoUninitialize();
    return result;
  }

  IWbemClassObject *class_object = NULL;
  ULONG returned = 0;
  // Bounded wait: this must never hang app startup if WMI is unresponsive.
  hres = enumerator->Next(5000, 1, &class_object, &returned);
  if (SUCCEEDED(hres) && returned != 0 && class_object != NULL) {
    VARIANT prop;
    VariantInit(&prop);
    if (SUCCEEDED(class_object->Get(L"UUID", 0, &prop, 0, 0)) &&
        prop.vt == VT_BSTR && prop.bstrVal != NULL) {
      _bstr_t bstr(prop.bstrVal);
      result = std::string(static_cast<const char *>(bstr));
    }
    VariantClear(&prop);
    class_object->Release();
  }

  enumerator->Release();
  services->Release();
  locator->Release();
  if (owns_com_init) CoUninitialize();

  return result;
}

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
  if (method_call.method_name().compare("getDeviceId") == 0) {
    result->Success(flutter::EncodableValue(GetSystemUuidViaWmi()));
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
