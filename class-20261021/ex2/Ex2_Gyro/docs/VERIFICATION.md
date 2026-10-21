# Ex2 verification — 2026-10-21

- STM32CubeIDE 2.2.0 Debug and Release builds: 0 errors, 0 warnings.
- Debug ELF flashed to the connected STM32F429 Discovery. STM32CubeProgrammer
  reported **Download verified successfully**, then reset the MCU.
- ST-LINK USART1 serial output received on COM8 at 115200 8N1.
- Onboard gyroscope detected with WHO_AM_I **0xD3**.
- Calibration messages appeared at startup. Following calibration, repeated
  three-axis readings were received, including:

```text
X = -0.210, Y = -0.350, Z = 0.210 deg/s
X = -0.140, Y = 0.350, Z = 0.770 deg/s
X = 0.210, Y = -0.700, Z = 0.350 deg/s
```

The supplied driver's 2,000-sample calibration took longer than six seconds in
this run; keep the board still until its completion message rather than using a
fixed six-second countdown. Near-zero readings include sensor noise and residual
offset; these values alone do not demonstrate an intentional rotation.

LED3/LED4 are configured to follow the X/Y sign independently. Physical LED
observation and a deliberate rotation demonstration remain to be done by the
user. Build logs/ELFs are ignored local output; macOS is not verified.
