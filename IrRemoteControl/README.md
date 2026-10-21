# IR remote control sample

Portable source extracted from the workspace's original `IrRemoteControl.zip`.
The archive remains local and ignored by Git. Firmware source and vendor libraries
were preserved; generated Debug output, local IDE settings and launch files were
not extracted.

Import the `STM32CubeIDE` subfolder as an existing Eclipse project named
`IrRemoteControl`, leaving **Copy projects into workspace** unchecked. Keep this
whole folder together because the project links to `Core/` and `Drivers/`.

This is supplied sample code, not a claim that the IR assignment is complete or
that it has been tested on a physical board or macOS. Consult the Lab 1 assignment
for required hardware, pin wiring and expected behavior before flashing it.

The initial repository setup verified Debug and Release builds from the tracked
files on Windows. Release emitted an existing warning in `irda.c` that `code` may
be used uninitialized. No firmware behavior was changed to suppress that warning.
