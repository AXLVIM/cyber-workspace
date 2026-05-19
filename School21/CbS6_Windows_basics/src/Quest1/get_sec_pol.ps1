# Check if running as Administrator
if (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "Restarting as Administrator..." -ForegroundColor Yellow
    Start-Process powershell.exe "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"" -Verb RunAs
    exit
}

Write-Host "Exporting security policy to secpol.txt ..." -ForegroundColor Green
$tempFile = [System.IO.Path]::GetTempFileName()
secedit /export /cfg $tempFile /areas SECURITYPOLICY | Out-Null
Get-Content $tempFile | Out-File -FilePath "secpol.txt" -Encoding UTF8
Remove-Item $tempFile
Write-Host "Done! Check secpol.txt in the current folder." -ForegroundColor Green