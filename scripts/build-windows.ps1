param(
    [string]$VcpkgRoot = $env:VCPKG_ROOT
)

$ErrorActionPreference = "Stop"
$projectRoot = Split-Path -Parent $PSScriptRoot

if ([string]::IsNullOrWhiteSpace($VcpkgRoot)) {
    $vcpkgCommand = Get-Command vcpkg -ErrorAction SilentlyContinue
    if ($null -ne $vcpkgCommand) {
        $VcpkgRoot = Split-Path -Parent $vcpkgCommand.Source
    }
}

$vcpkg = if ([string]::IsNullOrWhiteSpace($VcpkgRoot)) { $null } else { Join-Path $VcpkgRoot "vcpkg.exe" }
$toolchain = if ([string]::IsNullOrWhiteSpace($VcpkgRoot)) { $null } else { Join-Path $VcpkgRoot "scripts\buildsystems\vcpkg.cmake" }
$cmakeCommand = Get-Command cmake -ErrorAction SilentlyContinue
$cmake = if ($null -ne $cmakeCommand) { $cmakeCommand.Source } else { $null }

if ([string]::IsNullOrWhiteSpace($VcpkgRoot) -or -not (Test-Path $vcpkg) -or -not (Test-Path $toolchain)) {
    throw "vcpkg was not found. Set VCPKG_ROOT, add vcpkg.exe to PATH, or pass -VcpkgRoot."
}
if ($null -eq $cmake) {
    throw "CMake was not found. Install CMake and add it to PATH."
}

Write-Host "Installing the required zlib package..."
& $vcpkg install zlib:x64-windows
if ($LASTEXITCODE -ne 0) {
    throw "vcpkg failed to install zlib."
}

$buildDir = Join-Path $projectRoot "build"
Write-Host "Configuring the Windows build..."
& $cmake -S $projectRoot -B $buildDir `
    -G "Visual Studio 17 2022" `
    -A x64 `
    "-DCMAKE_TOOLCHAIN_FILE=$toolchain" `
    "-DVCPKG_TARGET_TRIPLET=x64-windows"
if ($LASTEXITCODE -ne 0) {
    throw "CMake configuration failed."
}

Write-Host "Building mcserver..."
& $cmake --build $buildDir --target mcserver --config Release --parallel
if ($LASTEXITCODE -ne 0) {
    throw "The mcserver build failed."
}

Write-Host ""
Write-Host "Build complete. Start the server with:"
Write-Host "  .\scripts\run-windows.ps1"
