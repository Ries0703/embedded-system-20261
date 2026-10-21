# Exercise 1 — STM32F429 Discovery + RC522

This implements the three supplied exercise slides: initialize the RC522 using
the instructor's driver, detect a card, and send its four-byte identifier to the
PC over USART1. The LCD is not used in this exercise.

## Wire the reader

Disconnect USB/power while wiring. Use the labels printed on the boards, including
the correct pin of each two-row STM32 header. The reader's SDA pin is SPI chip
select in this project; it is not an I2C connection.

| RC522 label | STM32 board label | Purpose |
| --- | --- | --- |
| SDA / SS | PE4 | Software chip select |
| SCK | PE2 | SPI4 clock |
| MOSI | PE6 | STM32 to reader |
| MISO | PE5 | Reader to STM32 |
| IRQ | Leave disconnected | Polling driver |
| GND | GND | Common ground |
| RST | 3V | Hold reset inactive, as specified in supplied driver |
| 3.3V | 3V | Reader supply — use 3.3 V, never 5 V |

You need seven jumper connections; both RST and 3.3V need 3V. Use two available
3V header contacts or split the 3V supply with a breadboard. Follow printed labels
rather than assuming the RC522 header is oriented like a web photo.

Connect a data-capable Mini-USB cable to the **top ST-LINK USB connector** near
the buttons, not the bottom USB USER connector. Keep both CN4 ST-LINK jumpers
installed for programming the onboard STM32. The photo shows MB1075E: this board
revision provides USART1 PA9/PA10 through ST-LINK's virtual COM port (SB11/SB15).
Normally no separate USB-to-serial adapter is needed.

## Open and build

In STM32CubeIDE: **File > Import > General > Existing Projects into Workspace**,
select this project's `STM32CubeIDE` subfolder, select `Ex1_RFID`, and finish.
Leave **Copy projects into workspace** unchecked because sources are linked from
the parent folder. Keep the entire Ex1_RFID folder together.

From PowerShell in this folder:

```powershell
.\build.ps1
.\build.ps1 -Configuration Release
```

Scripts locate the bundled IDE relative to the school workspace. They use a
separate `.stm32-ex1-workspace` and save logs in `docs/`. Close any IDE opened on
that same headless workspace before running the script. A normal build does not
write to the board.

## Flash and view card IDs

After connecting the wired board, run:

```powershell
.\flash.ps1
[System.IO.Ports.SerialPort]::GetPortNames()
.\monitor.ps1 -Port COM8
```

Replace COM8 with the actual **STMicroelectronics STLink Virtual COM Port** in
Device Manager. The Bluetooth COM ports are unrelated. `flash.ps1` explicitly
programs and verifies the connected target and then resets it. It uses the Debug
ELF by default; use `-Configuration Release` for the Release build.

Alternatively use Hercules, Serial tab: **115200 baud, 8 data bits, no parity,
1 stop bit, no handshake**. Only one terminal may open the COM port at a time.
Press the black RESET button after opening the terminal to see the startup banner.

Expected output (illustrative UID, not a measured card):

```text
Welcome! Ex1 RC522 / SPI4 / USART1 115200 8N1
RC522 VersionReg: 0x92
RFID Card Not Found!
RFID Card Found!
Reading from card: 12 34 56 78 (BCC 08)
```

Bring a supplied 13.56 MHz RFID card/key fob close to the reader antenna. Move it
away and present it again to demonstrate both cases. The green LED blinks while
polling; the red LED indicates a detection or an unresponsive reader. The original
driver requests idle cards and sends HALT after checking; continuously holding a
card in place need not produce a new ID every poll.

## Configuration and source

- MCU: STM32F429ZIT6, Cortex-M4F, 2 MB flash, hard-float ABI.
- Clock: onboard 8 MHz HSE crystal -> 180 MHz CPU; APB1 45 MHz, APB2 90 MHz.
- SPI4: mode 0, MSB first, 8 bits, software NSS, prescaler 64 (1.40625 MHz).
- USART1: PA9 TX / PA10 RX, 115200 8N1, polling transmit with a 100 ms timeout.
- `Core/Src/main.c`: initialization, diagnostics, polling and UID output.
- `Core/Src/stm32f4xx_hal_msp.c`: SPI/UART peripheral clocks and pin alternate functions.
- `Core/Src/tm_stm32f4_mfrc522.c`: instructor driver integration copy.
- `Ex1_RFID.ioc`: peripheral/pin configuration matching this setup. It was prepared
  as a configuration snapshot; CubeMX regeneration has not been verified. Back up
  sources before regenerating and review custom driver links and application code.
- `build.ps1`, `flash.ps1`, `monitor.ps1`: CLI build, explicit programming and terminal.

The original driver files one directory above remain unchanged. In the integration
copy, register transfers query `HAL_SPI_GetState` directly instead of assigning
SPI-state enum values into a HAL-status enum variable. This removes four compiler
enum-comparison warnings without changing the transfer sequence. The application
uses a 16-byte receive buffer because the driver may copy up to MFRC522_MAX_LEN;
the slide's five-byte buffer is smaller than that maximum. The output separates
the four UID bytes from the fifth XOR check byte (BCC).

The supplied driver implements single-level anticollision for four-byte UIDs.
Full seven-/ten-byte UID cascade handling and authenticated card memory access
are outside this setup. Card memory is not written.

## Troubleshooting and proof limits

- No ST-LINK: check the top USB port, USB data cable, board power and ST-LINK driver.
- No COM port: inspect Device Manager and the ST-LINK VCP driver; do not select a
  Bluetooth COM port. For a modified board, check SB11/SB15 against the board manual.
- `VersionReg` 00/FF: firmware retries once per second; check 3V, common GND, RST,
  SDA/PE4 and the three SPI wires. Other versions may occur on compatible modules.
- Good reader version but no detection: check card type/distance and try the
  supplied RFID card/fob. Present one card at a time.
- No serial banner: check terminal settings and press RESET. The debugger can watch
  `rfid_version`, `last_card_id`, `cards_found` and `uart_errors` in the Debug build.

Build success proves compilation/linking only. Flash verification and actual RFID
output require the physical board/reader and are recorded separately in
`docs/VERIFICATION.md`.

## Sources and licensing

Assignment: the three images and two instructor driver files in the parent folder.
The TM MFRC522 files retain Tilen Majerle's GPLv3-or-later notice and TrungNL's HAL
adaptation attribution. Preserve these notices when sharing the project.

CMSIS, startup/linker support and the existing HAL scaffold were copied from this
workspace's Lab1_3_2 without modifying that project. Missing SPI/UART .c/.h files
come from [ST's STM32F4 HAL driver v1.8.5](https://github.com/STMicroelectronics/stm32f4xx-hal-driver/tree/v1.8.5),
matching the existing HAL 1.8.5 version. Vendor license files remain in Drivers/.

Hardware references: [ST UM1670 board manual](https://www.st.com/resource/en/user_manual/DM00093903-.pdf)
(VCP section 7.3.3), [NXP MFRC522 datasheet](https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf).
