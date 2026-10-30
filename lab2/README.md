# Lab 2 — STM32 serial peripherals and RFID access control

Student: Trần Anh Dũng — 20226031. Partner: Maier Benedikt Quirin — 20260015S.

## Projects

- `Lab2_Peripherals/`: one cumulative project for exercises 3.6, 3.7 and 3.8. Reads DS1307, displays date/time and the five returned RFID bytes on SH1106, and prints time/card events over UART.
- `Lab2_AccessControl/`: separate exercise 3.9 project. Adds card authorization, LED3/LED4 state, up to 100 timestamped RAM opening records and UART configuration/query commands.
- `tests/`: native C checks for the RTC conversion, presence state, allowlist and log ring. The HAL header here is a host-test stub, not firmware HAL.

## Import and build

Install the Eclipse-based STM32CubeIDE for your OS. Import each project's `STM32CubeIDE/` directory using **File > Import > Existing Projects into Workspace**, leaving **Copy projects into workspace** unchecked. The complete project folder must remain together: Eclipse linked sources refer to its sibling `Core/` and `Drivers/` directories.

Build Debug or Release. Create a local STM32/ST-LINK launch configuration for the newly built ELF, program with verification, and run. The supplied `.ioc` files are configuration snapshots; source builds have been tested, but CubeMX regeneration has not. Back up custom source and compare regenerated output before replacing it.

The source ZIP intentionally excludes the installed IDE, Windows helpers, debug launch settings, generated Makefiles, objects, ELFs, reports and videos. Required HAL/CMSIS source, startup assembly, linker scripts, project metadata and vendor license files are included.

## Wiring

All grounds are common. Power off while wiring. The lab's TA checked the assembled circuit and shared-bus arrangement before powering.

| Module | Connection |
|---|---|
| Tiny RTC | VCC→5V, GND→GND, SCL→PA8, SDA→PC9 |
| SH1106 | VCC→3V, GND→GND, SCL→PA8, SDA→PC9 |
| RC522 | 3.3V/RST→3V; GND→GND; SDA/SS→PE4; SCK→PE2; MISO→PE5; MOSI→PE6; IRQ unused |
| LED3 / LED4 | Onboard PG13 green / PG14 red |

RTC/OLED share I2C3 at 100 kHz; SPI4 is mode 0. The RTC's matching pins on opposite headers can serve as shared SCL/SDA/GND contacts. Follow printed labels rather than inferring a header pin from its physical row. Check actual I2C pull-ups/voltage compatibility before reproducing this with different modules. The external 100 µF capacitor is not required by the current announcement.

The lab coin cell was removed and BAT left unconnected. The RTC loses its initialized time after main power is removed; set it once after reconnecting. A bare CR2032 must not be charged by a Tiny RTC charging circuit. Resetting only the MCU while RTC power remains present does not require resetting the time.

## UART

Use the ST-LINK virtual COM port at **115200 baud, 8N1, no flow control**, with one terminal open at a time. Port names vary by host. Commands are case-sensitive; terminate with CR, LF or CRLF. The board generates decisions/logs; a PC serial terminal only sends commands and displays replies.

Both projects support `HELP`, `SCAN`, `RFID INIT`, `CARD LAST`, `TIME GET`, and `TIME SET YYYY-MM-DD HH:MM:SS`. Use actual local time. Time is never unconditionally set at boot.

Exercise 3.9 also supports:

```text
STATUS
ALLOW ADD B3C08F34C8
ALLOW DEL B3C08F34C8
ALLOW LIST
LOG LIST
LOG CLEAR
```

`B3C08F34C8` is the actual tested card's four UID bytes plus BCC; replace it with the code from your own card. The supplied reader path handles four-byte UIDs plus BCC, not full long-UID cascade handling.

The allowlist holds ten codes and starts empty. Presenting an unlisted card shows Rejected (green on, red off). Enroll it through UART, remove it and present again: Welcome and both LEDs on. A held card produces one log. Removal turns both LEDs off. Deleting an allowed held card relocks immediately.

Logs contain sequence, date/time and five-byte code; maximum 100 entries, oldest overwritten on overflow. `LOG LIST` has BEGIN/END markers and prints a snapshot in chronological order. `LOG CLEAR` resets logs/sequence but preserves permissions. Both logs and permissions are RAM-only and clear on MCU reset. RTC/read errors keep the simulated door locked.

## Host checks

On Linux or WSL with GCC and sanitizer support:

```sh
bash tests/run.sh
```

This compiles actual application C modules, using a HAL stub only for RTC register transfers. It checks BCD/calendar/error handling, held-card/removal transitions, invalid/duplicate/full allowlist handling, authorization with/without valid time, and the 101st append retaining the latest 100 records.

Source attributions and vendor notices remain in the supplied driver files. Consult the individual report for the added application code and experimental results.
