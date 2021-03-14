package platform_device_id

import (
	flutter "github.com/go-flutter-desktop/go-flutter"
	"github.com/go-flutter-desktop/go-flutter/plugin"
)

const channelName = "com.di1shuai.flutter/platform_device_id"

const (
	methodGetDeviceId   = "getDeviceId"
)

// PlatformDeviceIdPlugin implements flutter.Plugin and handles method.
type PlatformDeviceIdPlugin struct{}

var _ flutter.Plugin = &PlatformDeviceIdPlugin{} // compile-time type check

// InitPlugin initializes the plugin.
func (p *PlatformDeviceIdPlugin) InitPlugin(messenger plugin.BinaryMessenger) error {
	channel := plugin.NewMethodChannel(messenger, channelName, plugin.StandardMethodCodec{})
	channel.HandleFunc(methodGetDeviceId, p.getDeviceId)
	return nil
}

func (p *PlatformDeviceIdPlugin) getDeviceId(arguments interface{}) (reply interface{}, err error) {
	deviceId, err := getPlatformDeviceId()
	if err != nil {
		return nil, err
	}
	return deviceId,nil
}
