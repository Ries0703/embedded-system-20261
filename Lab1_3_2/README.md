# Lab 1, exercise 3.2 — work in progress

Partners: Trần Anh Dũng (20226031) and Maier Benedikt Quirin.

## Current working state

This is a separate STM32F429 project. The latest firmware enables segments a, b and c (the digit 7) and alternates the two displays every 500 ms. Both displays were reported working in this test during the lab session. The build log records zero errors and zero warnings. No new hardware test was performed when making this archive.

This is a slow wiring test, not the finished multiplexed number display. Displaying 25, button B1 incrementing the number, and simultaneous operation of the eight individual LEDs have NOT been completed. Wiring for segment d was instructed, but its completion was not confirmed. One display was reported to have a faulty middle segment g.

## Open on macOS

Install the macOS version of STM32CubeIDE compatible with your Mac. Extract this entire folder first. In CubeIDE choose File > Import > General > Existing Projects into Workspace, select the STM32CubeIDE subdirectory, select Lab1_3_2, and finish. Leave Copy projects into workspace unchecked. Build the Debug configuration so the IDE generates fresh local Makefiles. Create a new ST-LINK debug configuration locally for Debug/Lab1_3_2.elf.

The STM32CubeIDE directory contains portable project metadata, linker scripts, startup assembly, and syscalls/sysmem source files: it is NOT the Windows IDE installer. Keep it. Prebuilt output and machine-specific launch settings are excluded. Windows build/flash success does not establish macOS build or hardware success.

## Files

- Core/Src/main.c: current three-segment wiring test and GPIO initialization.
- Core/Src/stm32f4xx_it.c: inherited sample interrupt handlers; B1 increment is not implemented.
- Core/Src/7seg.c and Core/Inc/7seg.h: instructor-supplied full digit driver, not yet called by the current test. They are not yet listed as linked source resources in the Eclipse project; add 7seg.c to the build when integrating it.
- Drivers/: CMSIS and STM32 HAL sources/headers.
- Lab1_3_2.ioc: copied project configuration. GPIO changes made manually in main.c are not necessarily reflected here. Do not regenerate code without checking and preserving them.
- docs/build-windows.log: historical successful build log; may contain Windows paths.
- WIRING.md: planned layout and confirmed wiring-test scope.

No photos or video are included: photos shared in chat are not available as local image files in this project.
