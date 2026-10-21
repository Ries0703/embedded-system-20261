# Exercise 2 — STM32F429 Discovery onboard gyroscope

Uses the supplied L3GD20 library to read the onboard gyroscope through SPI5 and
send calibrated angular rates X/Y/Z over USART1 at 115200 baud, 8N1. LED3 (green,
PG13) is on when X > 0; LED4 (red, PG14) is on when Y > 0. Each LED is off otherwise.
These follow the task's stated requirements rather than the example's simultaneous
three-axis condition and five-second blinking loop.

## Hardware and running

No added sensor or jumpers are required: the gyroscope is soldered onto the board.
Ex1's RC522 can remain connected to SPI4 while this project uses SPI5. The Ex2
firmware holds the RC522's PE4 chip select high and does not configure its SPI bus.
It also holds the LCD's PC2 chip select high because the LCD shares SPI5 with the
gyroscope. Change jumper wiring only with USB/power disconnected.

Connect the top ST-LINK Mini-USB port with a data cable. After reset, keep the
board flat and still while 2,000 samples are collected for calibration. Allow
several tens of seconds and wait for **Calibration complete**, then rotate the board about
its different axes. A stationary tilt is not a continuous angular rate: readings
should return near zero when rotation stops. Small offsets/noise can flicker the
LEDs at rest because the task explicitly uses a threshold of zero.

Open the ST-LINK serial port in a terminal at **115200 baud, 8 data bits, no parity,
1 stop bit, no flow control**. On this Windows workstation it was COM8 for Ex1;
check the current port rather than assuming that number. On macOS look under
`/dev/cu.*`. Open only one serial terminal at a time. Press RESET after opening
the terminal if you missed the calibration/startup messages.

Typical format (illustration, not a measured result):

```text
Ex2 onboard gyroscope / SPI5 / USART1 115200 8N1
WHO_AM_I=0xD3. Keep board STILL during calibration.
Calibrating... keep board still.
Calibration complete. Rotate board to change X/Y/Z (deg/s).
X = 0.000, Y = -0.070, Z = 0.140 deg/s
```

## Build and flash

Install the appropriate STM32CubeIDE for your OS and import the `STM32CubeIDE`
subfolder as existing project `Ex2_Gyro`. Keep **Copy projects into workspace**
unchecked. Select Debug or Release and use **Project > Build Project**. Create a
local ST-LINK debug configuration for `Debug/Ex2_Gyro.elf` (or Release ELF), launch
it, and resume execution when stopped at main. Alternatively use STM32CubeProgrammer
to program and verify the ELF, then reset/run the board.

Flashing replaces the currently running firmware; building alone does not. Build
logs, binaries and Windows PowerShell/batch helpers stay ignored by Git. Keep this
entire project folder together, including Core and Drivers. See the root README
for shared setup and the serial settings above for displaying readings.

## Source and configuration

- STM32F429ZIT6 at 180 MHz using its onboard 8 MHz HSE crystal.
- SPI5 master, full duplex, 8-bit MSB first, mode 0, software NSS, prescaler 16:
  PF7 SCK, PF8 MISO, PF9 MOSI, PC1 active-low gyroscope select.
- USART1 PA9 TX / PA10 RX at 115200 8N1.
- Sensor configuration, calibration, offsets, sensitivity and original angle APIs
  come from the supplied library, whose attribution is retained in both files.
- The integration copy adds only `get_Rate_X/Y/Z()` to expose the existing
  calibrated rate variables and `L3GD20_IsCalibrated()` to report readiness.
  Original `get_Angle_X/Y/Z()` functions remain available, but the application
  prints rates in degrees/second to match the assignment.
- The original library uses one call to read and a second to process a sample.
  The application calls it twice per fresh XYZ sample, approximately every 3 ms.
  UART output is throttled to ten lines per second without a long blinking delay.
- No external interrupt is required. The application polls STATUS_REG for fresh
  data, checks WHO_AM_I at startup and reports SPI transfer failures.
- `Ex2_Gyro.ioc` records the matching pin/clock configuration; CubeMX regeneration
  has not been verified. Back up source before regenerating and compare changes.
- `gyro_x_dps`, `gyro_y_dps`, `gyro_z_dps`, `gyro_id`, `gyro_calibrated`,
  `gyro_samples`, `spi_errors`, `uart_errors` are available for debugger inspection.

The library was supplied as L3GD20 code adapted for this board. The board's
I3G4250D is an angular-rate sensor with a compatible register interface. Sensor
reference: [ST I3G4250D datasheet](https://www.st.com/resource/en/datasheet/i3g4250d.pdf).

Debug and Release builds, flash verification and real serial readings were
verified on this Windows workstation; see [verification evidence](docs/VERIFICATION.md).
Physical LED behavior and response to deliberate rotation have not yet been
observed by the user. macOS builds are not yet verified.
