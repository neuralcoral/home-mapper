# Hexapod Firmware

This directory contains the C++ firmware for the hexapod robot.

The build system is fully hermetic and powered by **Bazel**. This means you do not need to install `avr-gcc` or configure C++ toolchains on your host machine to compile the code. Bazel will automatically download a strictly versioned compiler, the Arduino Core, and required libraries (like Servo) to ensure the firmware builds identically on any machine.

## Prerequisites

While the compiler is handled automatically by Bazel, you need a few host tools to convert the compiled binary and flash it over USB to the robot.

**Ubuntu / Debian:**
```bash
sudo apt-get update
sudo apt-get install avrdude binutils-avr picocom
```

**macOS (via Homebrew):**
```bash
brew tap osx-cross/avr
brew install avrdude avr-binutils picocom
```

*Note: `binutils-avr` provides the `avr-objcopy` command used to convert the raw ELF binary into a flashable HEX file.*

## Building the Firmware

To compile the firmware and generate the `.hex` file, run the following command from the root of the repository:

```bash
bazel build //firmware/src:hex --config=avr
```

**What this does:**
1. Downloads the hermetic `avr-gcc` toolchain (if not already cached).
2. Compiles the Arduino Core and Servo libraries.
3. Compiles the hexapod kinematics and main loop.
4. Links the `.elf` binary and converts it into `hexapod.hex`.

The final flashable file will be located at:  
`bazel-bin/firmware/src/hexapod.hex`

## Flashing to the Robot

1. Connect the hexapod's microcontroller to your computer via USB.
2. Identify your USB port.
    - On Linux, it is usually `/dev/ttyUSB0` or `/dev/ttyACM0`.
    - On macOS, it is usually `/dev/cu.usbserial-*` or `/dev/cu.usbmodem*`.
3. Use `avrdude` to upload the firmware:

```bash
avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:bazel-bin/firmware/src/hexapod.hex:i
```

### Flashing Troubleshooting (Linux)
If you get a "Permission Denied" error when trying to upload, your user likely doesn't have access to the serial ports. Add yourself to the `dialout` group:
```bash
sudo usermod -a -G dialout $USER
```
*(You will need to log out and log back in for this to take effect).*

---

## Serial Monitoring

To review the serial monitor first identify your USB port the robot is connected to:
* **Linux:** `ls /dev/ttyUSB*` or `ls /dev/ttyACM*`
* **Mac:** Usually `/dev/cu.usbserial-0001` or `/dev/cu.usbmodem14101` (Run `ls /dev/cu.*` to find the exact name)

### Option 1: picocom (Recommended)
This is lightweight and easy to use. Assuming a baud rate of `115200` and port `/dev/ttyUSB0`:

**Linux:**
```bash
picocom -b 115200 /dev/ttyUSB0
```

**macOS:**
```bash
picocom -b 115200 /dev/cu.usbserial-0001
```

**To exit picocom:** Press `Ctrl+A`, then `Ctrl+X`.

### Option 2: screen (Built-in on macOS/most Linux)
If you don't want to install `picocom`, you can use `screen`:

**Linux:**
```bash
screen /dev/ttyUSB0 115200
```

**macOS:**
```bash
screen /dev/cu.usbserial-0001 115200
```
**To exit screen:** Press `Ctrl+A`, then `K`, and type `y` to confirm.


## Word of Caution

You cannot flash the robot while monitoring. Always exit before attempting to flash.

---

### MCU Notes
The default target for this build is the **ATmega328p** (Arduino Uno/Nano). If you swap the brain to an Arduino Mega (ATmega2560), you will need to update the `-mmcu` flags in `firmware/toolchain/avr_toolchain_config.bzl` and change the `-p` flag in the `avrdude` command above to `atmega2560`.