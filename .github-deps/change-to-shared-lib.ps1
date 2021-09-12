function Change-Setting {
    param( [string]$Name, [boolean]$Value )
    $script:content = $script:content -replace "$Name\s+:=\s+[a-zA-Z]+", ("$Name := " + $Value.ToString().ToLower())
}

$PRoot = Resolve-Path -Path "$PSScriptRoot\.."

$file = "$PRoot\Application.mk"
$content = Get-Content -Path "$file"


Change-Setting "STATIC_BUILD" $false
Change-Setting "BUILD_MAGICKPP" $true


Set-Content -Path $file -Value $content
