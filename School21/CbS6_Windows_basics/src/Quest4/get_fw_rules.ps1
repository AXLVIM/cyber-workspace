# get_fw_rules.ps1
# Exports only the firewall rules created for Task 4

$ruleNames = @("Block_http_conn", "Allow_rdp_conn", "Block_ftp_conn", "Block_ping_conn")

$result = Get-NetFirewallRule | Where-Object { $ruleNames -contains $_.DisplayName } | ForEach-Object {
    $rule = $_
    $portFilter = Get-NetFirewallPortFilter -AssociatedNetFirewallRule $rule
    [PSCustomObject]@{
        Name         = $rule.DisplayName
        Enabled      = $rule.Enabled
        Protocol     = $portFilter.Protocol
        LocalPort    = ($portFilter.LocalPort -join ',')
        RemotePort   = ($portFilter.RemotePort -join ',')
        Action       = $rule.Action
        Profile      = $rule.Profile
    }
}

$result | Format-Table -AutoSize | Out-File -FilePath "result.txt" -Encoding UTF8

Write-Host "Firewall rules exported to result.txt" -ForegroundColor Green