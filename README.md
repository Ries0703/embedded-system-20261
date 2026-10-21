# Embedded systems coursework

Shared STM32F429 Discovery coursework for Windows, macOS and Linux. The repository
contains source, project configuration, assignment slides, wiring notes and reports.
Install development tools separately for your operating system.

## Projects and materials

| Folder | Contents / status |
| --- | --- |
| `Lab1_3_1/` | Existing Lab 1 firmware, assignment and report materials. CubeIDE project name: `Lab1_20252`. |
| `Lab1_3_2/` | Seven-segment wiring test; full exercise remains incomplete. Read its README and WIRING first. |
| `IrRemoteControl/` | Instructor/sample IR project extracted from the original ZIP; not claimed as a completed exercise. |
| `class-20261021/ex1/Ex1_RFID/` | RC522 project; built and demonstrated reading a card over USART1 during the 2026-10-21 session. |
| `class-20261021/ex2/Ex2_Gyro/` | Onboard gyroscope project using the supplied library; angular rates over USART1 and sign-controlled LEDs. |
| `class-20261021/ex3/images/` | LCD assignment slides; implementation/library not included yet. |
| `lectures/` | Lecture PDFs and text notes. |
| `hand-in/`, `report-assets/` | Existing reports, video-link text and report illustrations; generated ZIPs excluded. |

## Open a project on any OS

1. Install the Eclipse-based [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
   package compatible with your OS and CPU architecture. The local Windows setup
   used CubeIDE 2.2.0; macOS builds have not been tested here. These are Eclipse
   `.project`/`.cproject` projects, not CMake projects for the VS Code extension.
2. Clone or copy the whole repository. Create a separate CubeIDE workspace outside
   the checkout so IDE state stays local.
3. In CubeIDE select **File > Import > General > Existing Projects into Workspace**.
   Select the chosen project's `STM32CubeIDE` subfolder and finish. Leave
   **Copy projects into workspace** unchecked: sources are linked from its parent.
4. Build **Debug** or **Release**. CubeIDE generates local Makefiles and output for
   your installed compiler. Do not reuse somebody else's generated Makefiles.
5. Create your own **STM32 C/C++ Application / ST-LINK** debug configuration for the
   project's freshly built ELF. Probe identifiers and host tool paths stay local.

The project layout and import workflow follow [ST's CubeIDE user guide](https://www.st.com/resource/en/user_manual/dm00629856-stm32cubeide-user-guide-stmicroelectronics.pdf).
Keep each `STM32CubeIDE/` project subfolder: it contains portable startup assembly,
linker scripts and project metadata. Only the root `STM32CubeIDE_2.2.0/` folder is
the installed Windows tool suite, which is excluded.

`Core/`, `Drivers/`, `.ioc`, `.project`, `.cproject`, startup `.s` and linker `.ld`
files are tracked. In particular, **Drivers contains required STM32 HAL/CMSIS C
source and headers**, not just host USB drivers. Each project retains its vendor
license notices. No single new license replaces the licenses of supplied code.

The generated sources are sufficient to import/build; code regeneration is a
separate operation. Install STM32CubeMX and the package named by the `.ioc`
(currently STM32Cube FW_F4 V1.28.3) if you need regeneration. Existing lab GPIO
changes may not match the `.ioc`, and the Ex1 `.ioc` is an unverified configuration
snapshot: back up changes and compare generated code before replacing anything.

## macOS serial output

Connect the board's top **ST-LINK Mini-USB** port with a data cable. For the RFID
project, keep all seven reader connections described in its README.

Find the ST-LINK serial device using:

```sh
ls /dev/cu.*
```

Use a serial terminal at **115200 baud, 8 data bits, no parity, 1 stop bit, no flow
control**. macOS device names usually look like `/dev/cu.usbmodem...`; `COM8` in
Windows examples is not a portable device name. Open one terminal at a time and
press RESET to see the startup banner. The terminal displays output from whatever
firmware is currently flashed; building a project alone does not change firmware.

Windows PowerShell/batch helpers stay local and are ignored by Git. Use your own
CubeIDE installation and serial terminal on each OS; no Windows helper script is
required for any project to build or flash.

## What Git excludes

- Installed IDEs/toolchains, Windows ST-LINK USB drivers and executable libraries.
- Generated firmware, objects, build folders, maps, logs and coverage files.
- Eclipse workspace/settings caches and machine-specific debug launch files.
- ZIPs and other archives: the IR project is tracked unpacked; submission/handoff
  archives can be recreated locally from source when needed.
- OS/editor temporary files and local environment configuration.

PDFs, DOCX reports, PNG/JPG slides and SVG illustrations remain tracked because
they are portable course materials. “No binaries” here means no compiled tools or
firmware, not removal of assignment documents and images. Ignoring files does not
delete the local IDE, drivers, archives or build output.

Text uses LF across platforms through `.gitattributes`; Windows `.bat`/`.cmd`
files use CRLF. Edit source and build configuration, then commit those changes.
Do not force-add ignored build output or copied tool installations.

## Local Git repository

The repository starts on branch `main`. No remote is required for local commits.
When a shared remote is ready, add its URL and push:

```sh
git remote add origin <repository-url>
git push -u origin main
```

Build success on Windows does not prove a macOS build or a hardware result. Each
group member should build locally and verify their own board connection.

For this initial repository setup, all four projects were imported and built in
both Debug and Release from a fresh export containing only Git-staged files.
All eight configurations built successfully on Windows. The supplied IR sample
emitted one Release warning that `code` in `irda.c` may be used uninitialized;
that sample code was preserved unchanged. The other clean builds had no warnings.
