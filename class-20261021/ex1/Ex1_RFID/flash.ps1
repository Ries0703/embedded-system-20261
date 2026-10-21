param([ValidateSet('Debug', 'Release')][string]$Configuration = 'Debug')
$ErrorActionPreference = 'Stop'
$workspaceRoot = (Resolve-Path (Join-Path $PSScriptRoot '../../..')).Path
$plugins = Join-Path $workspaceRoot 'STM32CubeIDE_2.2.0/STM32CubeIDE/plugins'
$programmer = Get-ChildItem "$plugins/*cubeprogrammer*/tools/bin/STM32_Programmer_CLI.exe" | Select-Object -First 1
if (!$programmer) { throw 'Bundled STM32CubeProgrammer not found.' }
$elf = Join-Path $PSScriptRoot "STM32CubeIDE/$Configuration/Ex1_RFID.elf"
if (!(Test-Path -LiteralPath $elf)) { throw 'Build this configuration first with build.ps1.' }
# Explicit invocation writes the connected target; normal build never flashes.
& $programmer.FullName -c port=SWD -d $elf -v -rst
if ($LASTEXITCODE -ne 0) { throw "Flash/verification failed ($LASTEXITCODE)." }
