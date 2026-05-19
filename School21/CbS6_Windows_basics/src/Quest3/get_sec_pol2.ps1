<#
.SYNOPSIS
    Exports complete Windows security policy (all areas) to secpol.txt
.NOTES
    Must be run as Administrator.
#>

# Check for admin rights
if (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "Restarting as Administrator..." -ForegroundColor Yellow
    Start-Process powershell.exe "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"" -Verb RunAs
    exit
}

Write-Host "Exporting complete security policy to secpol.txt ..." -ForegroundColor Green

$tempFile = [System.IO.Path]::GetTempFileName()

# Export ALL areas (no filter)
secedit /export /cfg $tempFile | Out-Null

# Save to secpol.txt in current directory
Get-Content $tempFile | Out-File -FilePath "secpol.txt" -Encoding UTF8

Remove-Item $tempFile

Write-Host "Done! Check secpol.txt in the current folder." -ForegroundColor Green
Read-Host "Press Enter to exit"