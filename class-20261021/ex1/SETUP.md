# Exercise 1 setup

Read all three exercise slides in images/ and both supplied MFRC522 driver files.
The exercise requires RC522 card detection, then the card identifier sent to a
PC terminal over USART1. It does not require LCD output or writing card memory.

Implementation: create Ex1_RFID beside the original materials, reuse the existing
STM32F429ZIT6 startup/linker/CMSIS/HAL scaffold from Lab1_3_2, and add the matching
ST HAL SPI/UART sources. Keep the supplied driver originals intact. Configure
SPI4 PE2/PE5/PE6 with PE4 software chip select, USART1 PA9/PA10 at 115200 8N1,
and PG13/PG14 status LEDs. Keep the CubeMX configuration consistent with firmware.

Verification: import/build Debug and Release with bundled CubeIDE CLI; inspect
warnings, linked RFID/SPI/UART symbols, and ELF sizes. Check ST-LINK enumeration.
Only a subsequent flash and observed UART/card result can prove hardware operation.
Provide reproducible build, explicit flash, and serial-monitor commands plus wiring.
