# Exercise 1 verification

Evidence from this Windows workstation during the 2026-10-21 session:

- Bundled STM32CubeIDE 2.2.0 built Debug and Release with **0 errors, 0 warnings**.
- STM32CubeProgrammer detected the STM32F429 Discovery, programmed the Debug ELF
  and reported **Download verified successfully**.
- USART1 output was received through the ST-LINK virtual serial port, COM8,
  at 115200 baud, 8N1.
- Initial card detection failed while only the four SPI wires were connected.
  After adding reader GND, 3.3V and RST-to-3V connections, the firmware repeatedly
  printed a real card identifier:

```text
RFID Card Found!
Reading from card: 33 D6 15 35 (BCC C5)
```

The final startup reported VersionReg 0xB2. The earlier 0x90 value with missing
power/reset connections was not reliable proof of reader communication. The
successful repeated UID output is the functional evidence.

These are historical session results. COM8 is a Windows-local port name; macOS
builds, another board and another host require separate verification. Generated
ELFs and raw build logs are local artifacts excluded from Git.
