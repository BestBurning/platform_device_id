// +build !darwin,!linux,!windows

package platform_device_id

import (
	"github.com/pkg/errors"
)

func getPlatformDeviceId() (deviceId string, err error) {
	return "", errors.New("platform unsupported")
}
