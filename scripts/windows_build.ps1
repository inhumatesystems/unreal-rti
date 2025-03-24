#!/usr/bin/pwsh

$scriptpath = $MyInvocation.MyCommand.Path
$dir = Split-Path $scriptpath
Set-Location $dir\..

$env:Path = "c:\program files\git\bin;$env:Path"
$output = invoke-expression "bash.exe scripts\windows_build.sh" ; $output
if (Test-Path "Build\Binaries\Win64\UnrealEditor-InhumateRTI.dll") {
    Exit 0
} else {
    Exit 1
}
