param([ValidateSet('Debug', 'Release')][string]$Configuration = 'Debug')
$ErrorActionPreference = 'Stop'
$workspaceRoot = (Resolve-Path (Join-Path $PSScriptRoot '../../..')).Path
$ideRoot = Join-Path $workspaceRoot 'STM32CubeIDE_2.2.0/STM32CubeIDE'
$headless = Join-Path $ideRoot 'headless-build.bat'
if (!(Test-Path -LiteralPath $headless)) { throw "CubeIDE not found: $headless" }
$buildWorkspace = Join-Path $workspaceRoot '.stm32-ex1-workspace'
$logDir = Join-Path $PSScriptRoot 'docs'
New-Item -ItemType Directory -Force -Path $logDir | Out-Null
$logFile = Join-Path $logDir "build-$Configuration.log"
& $headless -data $buildWorkspace -import (Join-Path $PSScriptRoot 'STM32CubeIDE') -cleanBuild "Ex1_RFID/$Configuration" 2>&1 | Tee-Object -FilePath $logFile
$buildExitCode = $LASTEXITCODE
if ($buildExitCode -ne 0) { throw "CubeIDE exited with $buildExitCode. See $logFile" }
$logText = Get-Content -LiteralPath $logFile -Raw
$elf = Join-Path $PSScriptRoot "STM32CubeIDE/$Configuration/Ex1_RFID.elf"
if (!(Test-Path -LiteralPath $elf) -or $logText -notmatch '0 errors') {
    throw "Build did not report success. See $logFile"
}
Write-Host "Firmware: $elf"
