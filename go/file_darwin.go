package platform_device_id

import (
	"fmt"
	"os/exec"
	"strings"

	"github.com/pkg/errors"
)

func getPlatformDeviceId() (deviceId string, err error) {
	arg := []string{"-c", "ioreg -l | grep IOPlatformUUID | awk 'NR==1{print $4}'"}
	cmd := exec.Command("bash", arg...)
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(string(out))
		return "", errors.Wrap(err, "failed to get deviceId")
	}
	deviceId = strings.ReplaceAll(string(out), "\"", "")
	return deviceId, nil
}
