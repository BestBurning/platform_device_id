package platform_device_id

import (
	"fmt"
	"os/exec"

	"github.com/pkg/errors"
)

func getPlatformDeviceId() (deviceId string, err error) {
	//wmic csproduct get UUID
	arg := []string{"csproduct", "get", "UUID"}
	cmd := exec.Command("wmic", arg...)
	d, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(string(d))
		return "", errors.Wrap(err, "failed to shutdown")
	}
	return string(d), nil

}
