#include "include/platform_device_id_linux/platform_device_id_linux_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>


const char kChannelName[] = "com.di1shuai.flutter/platform_device_id";
const char kGetDeviceIdMethod[] = "getDeviceId";



#define PLATFORM_DEVICE_ID_LINUX_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), platform_device_id_linux_plugin_get_type(), \
                              PlatformDeviceIdLinuxPlugin))

struct _PlatformDeviceIdLinuxPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(PlatformDeviceIdLinuxPlugin, platform_device_id_linux_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void platform_device_id_linux_plugin_handle_method_call(
    PlatformDeviceIdLinuxPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, kGetDeviceIdMethod) == 0) {
    FILE *rstream = NULL;
    char buf[1024] = {0};
    rstream = popen("dmidecode -s system-uuid","r");
    fread(buf, sizeof(char), sizeof(buf), rstream);
    pclose(rstream);
    g_autofree gchar *deviceId = g_strdup_printf("%s", buf);
    g_autoptr(FlValue) result = fl_value_new_string(deviceId);
    response = FL_METHOD_RESPONSE(fl_method_success_response_new(result));
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void platform_device_id_linux_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(platform_device_id_linux_plugin_parent_class)->dispose(object);
}

static void platform_device_id_linux_plugin_class_init(PlatformDeviceIdLinuxPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = platform_device_id_linux_plugin_dispose;
}

static void platform_device_id_linux_plugin_init(PlatformDeviceIdLinuxPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  PlatformDeviceIdLinuxPlugin* plugin = PLATFORM_DEVICE_ID_LINUX_PLUGIN(user_data);
  platform_device_id_linux_plugin_handle_method_call(plugin, method_call);
}

void platform_device_id_linux_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  PlatformDeviceIdLinuxPlugin* plugin = PLATFORM_DEVICE_ID_LINUX_PLUGIN(
      g_object_new(platform_device_id_linux_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            kChannelName,
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
