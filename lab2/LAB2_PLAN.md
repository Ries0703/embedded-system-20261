# Lab 2 completion and recording plan

> **For agentic workers:** Use `superpowers:executing-plans` when implementation is requested. Follow the checkboxes and record each working exercise immediately.

**Goal:** Complete the required STM32 exercises and save four checked demonstration videos before class ends at **16:45 on 30 October 2026 (Asia/Bangkok)**.

**Architecture:** One project, `Lab2_Peripherals`, contains exercises 3.6, 3.7 and 3.8 together. A separate project, `Lab2_AccessControl`, contains exercise 3.9. Reuse the existing RFID scaffold and supplied libraries; keep the original materials and earlier labs intact.

**Tech stack:** STM32F429 Discovery, STM32CubeIDE 2.2.0, STM32 HAL, DS1307, SH1106, RC522, I2C3, SPI4, USART1, Hercules/serial terminal.

## Read first: what actually needs submitting

Sources reviewed: `LAB_INSTRUCTION.md`, both seven-page lab PDFs, the 14-page DS1307 datasheet, the 19-page AT24C32 datasheet, all six supplied C/header files, and the workspace's general submission instructions and existing project/tool setup. PDF diagrams and the image-only RFID code were inspected as well.

| Part | Required outcome | Evidence/submission |
| --- | --- | --- |
| 3.1 | Explain shared I2C operation, required module connections and both IC addresses | Answers in individual report |
| 3.2–3.5 | Understand modules, wire circuit, configure clock/peripherals | Working circuit, wiring notes/photo and configuration supporting later exercises |
| 3.6 | Implement parameterized `SetTime()` and `GetTime()`; set correct time once, continuously read it | Added code explained in PDF; UART demonstration video |
| 3.7 | Continuously display the DS1307 date/time on SH1106 | Same project as 3.6; added code explained; OLED demonstration video |
| 3.8 | Read an RFID tag and display **all five returned bytes** on SH1106 | Same project as 3.6/3.7; added code explained; RFID/OLED demonstration video |
| 3.9 | Card presence LED, allowed/rejected decisions, timestamped RAM log, UART card configuration and log viewing | Separate project; added code/protocol explained; complete access-control demonstration video |

- [ ] Individual **PDF** report: name, student ID, partner and required declaration; 3.1 answers; explanations of added code for 3.6–3.9; video links and observed results.
- [ ] Source ZIP with **both complete, importable projects**, required HAL/library sources and IDE metadata. Exclude tool installation, caches and generated build folders.
- [ ] Four clearly named video links, one per required exercise. **Student ID card visibly appears in every video.** Check sharing permissions.
- [ ] Submit using each student's own assignment/account, even when working as a pair.

The announcement says **PDF** repeatedly; the English note's isolated “.docx” wording conflicts with that. Submit PDF. Due date in the supplied instructions: **13 November 2026, 23:59**; assignment closes **21 November, 02:00**. These are copied from the local announcement, not checked against live Teams.

## Schedule: protect recording time

These are target checkpoints, not measured implementation durations. Record immediately after each part works; do not wait for all code to be finished.

| Time today | Work | Must leave this block with |
| --- | --- | --- |
| 13:30–13:50 | Board detection, checked wiring, project scaffold and I2C address probe | ST-LINK and serial working; RTC/OLED acknowledge |
| 13:50–14:15 | 3.6 RTC | `Lab2_3_6_RTC.mp4` saved and played back |
| 14:15–14:35 | 3.7 OLED clock | `Lab2_3_7_OLED_Clock.mp4` saved and played back |
| 14:35–14:55 | 3.8 RFID display | `Lab2_3_8_RFID_OLED.mp4` saved and played back; real card codes noted |
| 14:55–15:50 | Separate 3.9 project: presence, authorization, UART, logs | Full flow tested, ready for filming |
| 15:50–16:15 | Record 3.9, replay all four videos, copy off phone | `Lab2_3_9_Access_Control.mp4` and three earlier clips readable locally |
| 16:15–16:45 | Retakes, wiring photos, source/evidence backup | All board-dependent evidence secured before leaving |

At a missed checkpoint: save current sources/logs, identify the single failing layer, and drop display polish or extra features. Never skip a required behavior or claim it worked. Spend at most 10 minutes on one unexplained hardware symptom before checking wiring/module/pin mapping with the TA. Reserve the last 30 minutes for evidence; write and format the report after class.

## Verified workspace setup and remaining gaps

Verified on this workstation during the review:

- CubeIDE installation: `../STM32CubeIDE_2.2.0/STM32CubeIDE/`; configuration reports version 2.2.0. Headless build launcher and Make executable exist.
- Bundled `arm-none-eabi-gcc.exe --version` runs: GCC **14.3.1**.
- Bundled `STM32_Programmer_CLI.exe --version` runs: CubeProgrammer **2.23.0**.
- Existing Ex1 RFID and Ex2 gyro Debug/Release ELFs exist. `arm-none-eabi-size` successfully reads both Debug ELFs. These are earlier exercises, **not Lab 2 firmware**.
- Reusable source: `../class-20261021/ex1/Ex1_RFID/`, including SPI4, USART1, LEDs, linked project layout and an integrated MFRC522 driver.
- Ex1 has I2C disabled and lacks I2C HAL source files. Matching-named I2C HAL `.c/.h` files are already under `../IrRemoteControl/Drivers/STM32F4xx_HAL_Driver/`; compare HAL version before copying them into new projects.
- Supplied OLED code already references `hi2c3`. Its header's PB6/PB7 pin comment describes a different platform; use the lab's PA8/PC9 instead.
- Last device probe returned **No ST-Link detected** and no serial ports. User confirms the board/modules/ID are available; USB detection still requires verification.
- No Hercules executable was found inside this workspace. Existing local PowerShell serial helpers can display output; 3.9 also needs an interactive transmit/receive terminal. Check the installed Hercules shortcut/location at the setup checkpoint; use a bidirectional serial terminal if it is absent.

No new Lab 2 project has been compiled, flashed, demonstrated or filmed at this planning stage.

## Task 1: Checked hardware and buildable Lab 2 foundation

- `depends_on:` none
- `blocks:` Tasks 2–5
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` Original projects remain intact; new project builds; connection status and actual address probe are recorded.

**New project:** `Lab2_Peripherals/`, starting from the Ex1 source scaffold. Rename `.project`, `.cproject` project/configuration references, ELF target and `.ioc` consistently; use a fresh local build workspace. Retain startup, linker scripts, vendor licenses and required HAL/CMSIS sources.

**Files to configure:** `Core/Src/main.c`, `Core/Src/stm32f4xx_hal_msp.c`, `Core/Inc/stm32f4xx_hal_conf.h`, the `.ioc`, and project build metadata. Add matching I2C HAL source/header files to `Drivers/STM32F4xx_HAL_Driver/`.

- [ ] Disconnect power while wiring. Follow printed labels, including OLED SDA/SCL order.
- [ ] **Get the teacher/TA's circuit check before first power-up**, as required by the English PDF p.3. Current announcement explicitly says the external **100 µF capacitor is not needed**.
- [ ] Verify backup power arrangement: Vietnamese PDF says BAT → 3V; English version omits it. Inspect the actual battery/module with the TA before connecting BAT. A BAT supply derived only from the board cannot preserve time when board power is removed.
- [ ] Check I2C pull-up voltage: supplied Tiny RTC schematic has SDA/SCL pull-ups to module VCC (5V). Have the TA confirm a compatible shared-bus arrangement with the 3.3V OLED; use suitable level translation or corrected pull-ups when required by the actual modules. Do not assume the OLED tolerates 5V signals.

| Module signal | STM32 connection |
| --- | --- |
| All module GNDs | Common GND |
| Tiny RTC VCC | 5V |
| OLED VCC | 3V |
| RTC + OLED SCL | PA8 / I2C3 SCL |
| RTC + OLED SDA | PC9 / I2C3 SDA |
| RC522 VCC and RST | 3V |
| RC522 SDA/SS | PE4 GPIO output, initially HIGH |
| RC522 SCK / MISO / MOSI | PE2 / PE5 / PE6, SPI4 |
| RC522 IRQ | Unconnected; polling |
| LED3 / LED4 | Onboard PG13 green / PG14 red |
| USART1 TX / RX | PA9 / PA10; ST-LINK VCP where supported by the actual board |

- [ ] Configure 180 MHz CPU; I2C3 PA8/PC9 AF4 open-drain at **100 kHz**; SPI4 mode 0; USART1 **115200, 8N1, no flow control**. Keep I2C standard mode despite the PDF screenshot showing 400 kHz: DS1307 datasheet pp.3/10 allows only 100 kHz.
- [ ] Enable `HAL_I2C_MODULE_ENABLED`; add `I2C_HandleTypeDef hi2c3`, peripheral/GPIO clock setup and `MX_I2C3_Init()`.
- [ ] Enumerate ST-LINK and current serial port; do not reuse old COM8 blindly. Open only one serial client at a time.
- [ ] Compile the new project with headless CubeIDE or IDE. Flash the **new project's** ELF with verification once implementation/board work begins; read its startup banner.
- [ ] Probe I2C once at startup, with bounded timeouts: RTC expected `0x68`, OLED library defaults to `0x3C`, EEPROM expected `0x50` from the supplied A0/A1/A2-to-GND schematic. Record actual results; EEPROM address variants can be `0x50`–`0x57`, OLED variants can differ.

Tool commands from repository root (PowerShell; read-only inspection):

```powershell
$plugins = 'STM32CubeIDE_2.2.0/STM32CubeIDE/plugins'
$programmer = Get-ChildItem "$plugins/*cubeprogrammer*/tools/bin/STM32_Programmer_CLI.exe" | Select-Object -First 1
& $programmer.FullName -l st-link
[System.IO.Ports.SerialPort]::GetPortNames()
```

New project build command:

```powershell
& './STM32CubeIDE_2.2.0/STM32CubeIDE/headless-build.bat' -data './.stm32-lab2-workspace' -import './lab2/Lab2_Peripherals/STM32CubeIDE' -cleanBuild 'Lab2_Peripherals/Debug'
```

Pass condition: zero compile/link errors, freshly generated target ELF; programmer later reports download verification and the board emits the expected banner. Tool existence or an old ELF alone does not satisfy this.

## Task 2: Exercise 3.6 — correct RTC functions and first video

- `depends_on:` Task 1
- `blocks:` Tasks 3–5
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` Shared project reads correct ticking time; video 3.6 is saved and checked.

**Create:** `Lab2_Peripherals/Core/Inc/ds1307.h`, `Core/Src/ds1307.c`. **Modify:** `Core/Src/main.c` to initialize once and print readings every 500 ms using HAL tick scheduling.

API and register conversion:

```c
typedef struct {
    uint8_t sec, min, hour, weekday, day, month, year;
} Time; /* year: 00..99 means 2000..2099; weekday: 1..7 */
HAL_StatusTypeDef SetTime(const Time *time);
HAL_StatusTypeDef GetTime(Time *time);
static uint8_t to_bcd(uint8_t v) { return ((v / 10) << 4) | (v % 10); }
static uint8_t from_bcd(uint8_t v) { return (v >> 4) * 10 + (v & 15); }
/* HAL device address for BOTH read/write APIs: (0x68 << 1). */
```

- [ ] Validate ranges and calendar dates before writing; weekday is **1–7**, not the example's 0. `SetTime()` encodes seven registers explicitly, selects 24-hour mode and clears seconds CH bit. Never write an ordinary decimal struct straight into BCD registers.
- [ ] `GetTime()` reads seven registers in one transaction; masks control bits; decodes BCD and handles 12-hour AM/PM or explicitly rejects unsupported/invalid data. Return HAL error/timeout to caller; show an error instead of stale time. Check stopped oscillator separately.
- [ ] Use an explicit one-shot setup action to set current local time, then leave normal startup read-only. Later expose `TIME SET` through UART. No unconditional time setting on boot or inside the loop.
- [ ] Meaningful checks: decimal 59 encodes as `0x59`; 23:59:59 reads correctly; weekday 0 and 31 February are rejected; minutes advance correctly at :59; a reset does not restore a hard-coded time.
- [ ] **Record 3.6 now:** show student ID, board and live terminal date/time ticking for at least 10 seconds. Reset the MCU and show continued time without running the set action again. This demonstrates reset behavior; full power-loss retention requires independent VBAT and is a separate check.
- [ ] Save/play `Lab2_3_6_RTC.mp4`; save matching source revision and real terminal capture.

## Task 3: Exercise 3.7 — OLED clock and second video

- `depends_on:` Task 2
- `blocks:` Tasks 4–5
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` RTC/UART remain usable; OLED continuously shows date/time; video 3.7 is saved and checked.

**Add:** supplied `SH1106.c`/`fonts.c` to `Lab2_Peripherals/Core/Src/`, corresponding headers to `Core/Inc/`. Preserve attribution. **Modify:** `main.c`; integration copy of `SH1106.c` as necessary for the actual bus.

- [ ] Initialize OLED only after I2C3 initialization; check `SH1106_Init()` return value. Probe failure must not stall indefinitely.
- [ ] Change OLED transfer timeout to at least **50 ms** at 100 kHz: one page transfer contains 129 bytes and takes over 11 ms before software overhead; supplied 10 ms timeout is too short. Reduce the supplied 20-second readiness timeout to a bounded diagnostic check. Track transfer failures in the integration copy.
- [ ] Draw date and time using `Font_7x10` or a layout that fits 128×64; clear old text before redraw and call `SH1106_UpdateScreen()`. Refresh about once a second while polling UART/card state between updates.
- [ ] Verify OLED time matches UART and seconds advance. If shifted/clipped, verify actual display/controller and page column settings before modifying the driver.
- [ ] **Record 3.7 now:** student ID, readable OLED date/time advancing over at least 10 seconds; include terminal comparison in the same clip when readable.
- [ ] Save/play `Lab2_3_7_OLED_Clock.mp4`; retain matching source.

## Task 4: Exercise 3.8 — RFID bytes and third video

- `depends_on:` Task 3
- `blocks:` Task 5
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` One shared project fulfills 3.6–3.8; actual tags identified; video 3.8 is saved and checked.

**Add/reuse:** `tm_stm32f4_mfrc522.c/.h` in `Lab2_Peripherals/Core/Src/` and `Core/Inc/`; use the earlier integration corrections after comparing with the supplied files. **Modify:** `main.c` for five-byte OLED formatting.

- [ ] Allocate receive buffer `uint8_t card[MFRC522_MAX_LEN]`, not the PDF's five-byte buffer: the driver's transport can copy up to 16 bytes.
- [ ] Probe reader VersionReg; report `00`/`FF` as wiring/device trouble before testing card detection.
- [ ] Print **five bytes** as `%02X %02X %02X %02X %02X` on OLED using the small font. The supplied four-byte-UID path returns four UID bytes plus XOR/BCC byte; explain that distinction in the report. It does not implement full long-UID cascade handling.
- [ ] Keep RTC and OLED functions in this same project; do not submit three separate peripheral projects. Retain serial date/time while displaying card data on OLED.
- [ ] Present/remove/re-present each supplied card/fob. Note the real five-byte codes for 3.9. If only one compatible tag is available, the same tag can demonstrate rejection before authorization and acceptance after UART enrollment.
- [ ] **Record 3.8 now:** student ID, no-card state, card presentation, all five bytes legible on OLED, removal/re-presentation; show the second tag too when available.
- [ ] Save/play `Lab2_3_8_RFID_OLED.mp4`; retain the tested shared-project ELF/source before moving to 3.9.

## Task 5: Exercise 3.9 — independent access controller and fourth video

- `depends_on:` Task 4
- `blocks:` Task 6
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` Separate project demonstrates every 3.9 behavior; fourth video is saved and checked; shared peripheral project remains available.

**Create:** `Lab2_AccessControl/` from the working peripheral project, with distinct Eclipse/project/build identities. New application units under `Core/`: `access_control.c/.h` (whitelist, state and 100-record RAM ring), `uart_commands.c/.h` (line parser), plus reused RTC/OLED/RFID sources. Add USART1 receive interrupt handler in `stm32f4xx_it.c` and enable its IRQ in `stm32f4xx_hal_msp.c`.

**Chosen behavior and protocol** (design decisions to implement; not extra assignment requirements):

- Poll one card about every 100 ms. Use a wake-up request (`PICC_REQALL`, 0x52) followed by anticollision and HALT so a held card remains detectable. The supplied `Check()` uses idle request plus HALT, which is unsuitable as a direct physical-presence test.
- State transitions: absent → new tag: LED3 ON, compare five-byte code; allowed → LED4 ON, OLED `Welcome`, append one timestamp/code record; denied → LED4 OFF, OLED `Rejected`, no opening record. Same held tag produces no repeated log records. New different code is a new presentation. Three consecutive no-tag responses clear presence and both LEDs. Reader faults force locked/error state rather than fabricated absence/success.
- On removal, return to clock/ready display. LED4 stays on only while an authorized tag is present; this closes the simulated door on removal.
- A valid RTC reading is required before granting an opening, so every opening has a real timestamp. RTC fault displays an error, leaves LED4 off and records no invented time.
- Store at most **100** successful-opening records in MCU RAM. On entry 101 overwrite the oldest and retain chronological output. Logs clear on reset. Whitelist holds up to **10** codes in RAM and starts empty; explicitly enroll the demo tag after boot. No EEPROM persistence is required.
- UART receives into a bounded ring via interrupt; main loop parses lines. Accept CR, LF and CRLF; discard an overlong line completely and return `ERR LINE_TOO_LONG`. Never perform OLED/I2C work or long responses inside the interrupt. Stream log output in bounded chunks so polling/LED removal still works.

| Command, terminated by Enter | Response/behavior |
| --- | --- |
| `HELP` | Command syntax |
| `TIME GET` | Current decoded RTC date/time or explicit RTC error |
| `TIME SET 2026-10-30 14:00:00` | Validate date, derive weekday, set once; `OK` or `ERR` (example only; use actual local time) |
| `CARD LAST` | Last successfully read five-byte code or `ERR NO_CARD` |
| `ALLOW ADD 1122334444` | Add exact five-byte hexadecimal code, validate BCC, reject malformed code/full list; duplicate returns `OK ALREADY_ALLOWED` |
| `ALLOW DEL 1122334444` | Remove code; absent code returns `ERR NOT_FOUND` |
| `ALLOW LIST` | All allowed codes; empty list is explicit |
| `LOG LIST` | Count and chronological sequence/date/time/five-byte-code rows; explicit empty result and end marker |
| `LOG CLEAR` | Clear records; acknowledge |
| Unknown or malformed command | `ERR` with syntax; no state change |

Example card bytes above are illustrative, not observed hardware codes. `0x11 ^ 0x22 ^ 0x33 ^ 0x44 == 0x44`.

- [ ] Implement presence transitions and verify held card leaves LED3 continuously on. Check removal turns it off within roughly 300 ms plus one display refresh/transfer interval.
- [ ] Verify allowed/rejected decisions, a second allowlist entry, delete/re-enroll, and one record per presentation. Authorization changes while a tag is held must not silently unlock; apply changes on next presentation, except deleting its permission immediately relocks it.
- [ ] Verify received commands at 115200 without losing characters during OLED refresh/log dump; malformed/overlong lines cause no partial command execution.
- [ ] Meaningful logic checks: `held_tag_logs_once`, `rejected_tag_never_unlocks`, `removal_locks_door`, `log_101_keeps_latest_100_in_order`, `malformed_allow_leaves_list_unchanged`, `rtc_failure_does_not_unlock`. Host tests can exercise logic/overflow quickly; do not insert fake hardware events or synthetic logs into the filmed firmware session.
- [ ] Build and flash **Lab2_AccessControl**, verify download and startup; close any old serial monitor before opening Hercules.
- [ ] **Record 3.9 in one coherent clip:** ID and exercise identification → `HELP`, `TIME GET`, empty allowlist/log → present an unenrolled tag (`Rejected`, LED3 ON, LED4 OFF) → remove (LED3 OFF) → `CARD LAST`, enroll that real code via UART, `ALLOW LIST` → present again (`Welcome`, both LEDs ON) → hold for several seconds (no repeated log) → remove (both OFF) → `LOG LIST` shows one correct timestamp/code → re-present/remove and list again (second record) → delete code and show rejection again. With two tags, also show an unlisted second tag and adding it without recompiling.
- [ ] Save/play `Lab2_3_9_Access_Control.mp4`; confirm commands, LEDs and OLED are legible. The 100-record limit needs logic evidence, not 101 manual swipes unless the instructor asks for that demonstration.

## Task 6: Evidence audit and submission completion

- `depends_on:` Tasks 2–5
- `blocks:` final submission
- `closure_depends_on:` none
- `standalone_closable:` yes
- `post_task_invariants:` Every claimed result has actual evidence; the two-project ZIP and individual PDF match the videos.

**Create after experiments:** `Report_Lab2.md` and exported PDF, `hand-in/` source ZIP and video-link file, `evidence/` actual serial captures/wiring photos and video filenames. Keep raw videos outside Git and ensure cloud links work for the instructor.

- [ ] Before 16:15: play every clip; verify student ID in **each**, focus/readability, all cases, saved file size/duration and a second copy off the recording device. A recording still only on a phone is not the final backup.
- [ ] Take one clear wiring photo showing module labels and board pin connections; save real card codes and terminal log outputs with the corresponding project version.
- [ ] 3.1 report answers: both ICs can share the same bus because addresses differ; master addresses one device per transaction while RTC keeps time independently. Power is VCC/GND with VBAT backup; basic I2C signals are SDA/SCL. DS1307 seven-bit address `0x68` (wire bytes D0/D1); AT24C32 `0x50 | A2A1A0`, `0x50` for the supplied grounded-address schematic (wire bytes A0/A1). Confirm the actual module with the probe. DS/SQW are unnecessary for this assignment's time reading.
- [ ] Explain the added BCD/RTC functions, OLED update path, five-byte RFID display, presence state, allowlist, UART protocol and 100-entry RAM log. Cite supplied libraries and distinguish instructor code from added code.
- [ ] ZIP contains `Lab2_Peripherals/` and `Lab2_AccessControl/` with complete sources and metadata. Check archive integrity and import/build from an extracted copy using the bundled toolchain; no tool binaries are required inside the ZIP.
- [ ] Export report as PDF and check name/ID/declaration, required exercise sections, code explanation, figures and working video links. Keep the editable source separately.
- [ ] Upload the four videos; test view permissions; submit PDF, source ZIP and links before the announcement's due time.

## Scope guardrails

No EEPROM logger, DS18B20 temperature driver, real lock actuator, cloud service, GUI, extra display animation or elaborate enrollment system is requested. AT24C32 is needed for the 3.1 analysis/address explanation; 3.9 explicitly asks for RAM logs. Focus class time on hardware behavior and evidence.
