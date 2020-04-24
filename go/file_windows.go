package platform_device_id

import (
	"fmt"
	"os/exec"
	"strings"

	"github.com/pkg/errors"
)

func getPlatformDeviceId() (deviceId string, err error) {
	//wmic csproduct get UUID
	arg := []string{"csproduct", "get", "UUID"}
	cmd := exec.Command("wmic", arg...)
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(string(out))
		return "", errors.Wrap(err, "failed to get deviceId")
	}
	deviceId =  strings.Split(string(out),"\n")[1]
	return deviceId , nil

}
