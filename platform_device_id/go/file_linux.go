package platform_device_id

import (
	// "fmt"
	"os/exec"

	"github.com/pkg/errors"
)


func getPlatformDeviceId() (deviceId string, err error) {
	//dmidecode -s system-uuid
	arg := []string{"-s","system-uuid"}
	cmd := exec.Command("dmidecode", arg...)
	d, err := cmd.CombinedOutput()
	if err != nil {
		return "", errors.Wrap(err, "failed to get deviceId")
	}
	return string(d), nil
}
