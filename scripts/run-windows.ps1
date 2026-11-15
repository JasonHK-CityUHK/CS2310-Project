param(
    [int]$Port = 25565
)

$ErrorActionPreference = "Stop"
$projectRoot = Split-Path -Parent $PSScriptRoot
$executable = Join-Path $projectRoot "build\src\Release\mcserver.exe"
$dataRoot = Join-Path $projectRoot "build\share\mcserver"

if (-not (Test-Path $executable)) {
    throw "The server executable was not found. Run .\scripts\build-windows.ps1 first."
}
if (-not (Test-Path $dataRoot)) {
    throw "Generated Minecraft data was not found at '$dataRoot'. Run the build first."
}

$env:MCSERVER_DATA_DIR = $dataRoot
& $executable $Port
exit $LASTEXITCODE
