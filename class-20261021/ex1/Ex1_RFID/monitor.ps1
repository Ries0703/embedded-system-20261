param([Parameter(Mandatory = $true)][string]$Port)
$ErrorActionPreference = 'Stop'
$serial = [System.IO.Ports.SerialPort]::new($Port, 115200, [System.IO.Ports.Parity]::None, 8, [System.IO.Ports.StopBits]::One)
$serial.Handshake = [System.IO.Ports.Handshake]::None
$serial.ReadTimeout = 500
try {
    $serial.Open()
    Write-Host "Listening on $Port at 115200 8N1. Press RESET on the board for the startup banner. Ctrl+C to stop."
    while ($true) {
        try { Write-Host ($serial.ReadLine().TrimEnd("`r")) }
        catch [System.TimeoutException] { }
    }
} finally {
    if ($serial.IsOpen) { $serial.Close() }
    $serial.Dispose()
}
