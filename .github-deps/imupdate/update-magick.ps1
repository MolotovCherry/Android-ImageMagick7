# Update imagemagick to a new version

# current path to 
$PRoot = Resolve-Path -Path "$PSScriptRoot\..\.."
$ImPath = Resolve-Path -Path "$PRoot\ImageMagick-*"
$TmpPath = "$PRoot\tmp"
$version = ""

# check if we need a version update first
$matched = Split-Path -Leaf -Path $ImPath | foreach-object {$_ -match "ImageMagick-(.*)"}
if ($matched) {
    $version = $Matches[1]
}

Write-Host Searching for latest version...`n

# get latest tag
$tag = (git ls-remote --tags --refs --sort="v:refname" https://github.com/ImageMagick/ImageMagick "*.*.*-*" | Select-Object -Last 1).substring(51)

Write-Host Found latest version: $tag

# updates only go up ^, so -ne basically means we're outdated
if ($version -ne $tag) {
    Write-Host Updating $version -> $tag`n
} else {
    Write-Host Local version $version is the same as remote $tag
    Write-Host No update needed!
    Exit 1
}

Write-Host Cloning latest imagemagick...`n

Set-Location -Path "$PRoot"

# clone the latest changes (yes, overkill on the null, because the messages just wouldn't go away)
git clone --quiet --depth 1 -b $tag https://github.com/ImageMagick/ImageMagick "$TmpPath" 2>&1 | Out-Null

Set-Location -Path "$TmpPath"

#
# Remove all extra cruft
#
Write-Host Removing extraneous content...`n

# before we delete, we need some version data from it for writing the new version
$content = Get-Content -Path "$TmpPath\configure"

$package_lib_version = (Select-String -InputObject $content -Pattern "PACKAGE_LIB_VERSION=([^\s]+)").Matches.Groups[1]
$magick_lib_version_text = (Select-String -InputObject $content -Pattern "PACKAGE_BASE_VERSION=([^\s]+)").Matches.Groups[1]

$magick_library_current = (Select-String -InputObject $content -Pattern "MAGICK_LIBRARY_CURRENT=([^\s]+)").Matches.Groups[1]
$magick_library_revision = (Select-String -InputObject $content -Pattern "MAGICK_LIBRARY_REVISION=([^\s]+)").Matches.Groups[1]
$magick_library_age = (Select-String -InputObject $content -Pattern "MAGICK_LIBRARY_AGE=([^\s]+)").Matches.Groups[1]
$magick_lib_version_number = "$magick_library_current,$magick_library_age,$magick_library_revision"

$package_version_addendum = (Select-String -InputObject $content -Pattern "PACKAGE_VERSION_ADDENDUM=([^\s]+)").Matches.Groups[1]
$magick_library_current_min = [int]$magick_library_current.Value - [int]$magick_library_age.Value

$magickpp_lib_version_text = (Select-String -InputObject $content -Pattern "PACKAGE_BASE_VERSION=([^\s]+)").Matches.Groups[1]
$magickpp_library_current = (Select-String -InputObject $content -Pattern "MAGICKPP_LIBRARY_CURRENT=([^\s]+)").Matches.Groups[1]
$magickpp_library_revision = (Select-String -InputObject $content -Pattern "MAGICKPP_LIBRARY_REVISION=([^\s]+)").Matches.Groups[1]
$magickpp_library_age = (Select-String -InputObject $content -Pattern "MAGICKPP_LIBRARY_AGE=([^\s]+)").Matches.Groups[1]
$magickpp_library_version_info = "${magickpp_library_current}:${magickpp_library_revision}:${magickpp_library_age}"
$magickpp_library_current_min = [int]$magickpp_library_current.Value - [int]$magickpp_library_age.Value

$magick_release_date = (Select-String -InputObject $content -Pattern "PACKAGE_RELEASE_DATE=([^\s]+)").Matches.Groups[1]

$content = Get-Content -Path "$TmpPath\MagickCore\version.h.in"
$magick_copyright = (Select-String -InputObject $content -Pattern "#define MagickCopyright  `"([^`"]+)`"").Matches.Groups[1]

# remove all immediate files
Get-ChildItem -File | Foreach-Object {Remove-Item $_.FullName}

$DelDirs = @(
    ".git", ".github", "api_examples", "app-image", "config",
    "images", "m4", "Magick++", "PerlMagick", "scripts", "tests",
    "www", "MagickWand\tests"
)

$ExcludeFileTypes = @(
    "*.c", ".h"
)

ForEach ($d in $DelDirs) {
    Remove-Item -Path "$TmpPath\$d" -Force -Recurse
}

# remove all non c or non h files
$items = Get-ChildItem -File -Path "$TmpPath" -Exclude "*.c","*.h" -Recurse
ForEach ($i in $items) {
    Remove-Item -Path "$i" -Force
}

Write-Host Writing new mk files...`n

$coders = Get-ChildItem -File -Recurse -Path "$TmpPath\coders" -Include "*.c"
$filters = Get-ChildItem -File -Recurse -Path "$TmpPath\filters" -Include "*.c"
$magickCore = Get-ChildItem -File -Recurse -Path "$TmpPath\MagickCore" -Include "*.c"
$magickWand = Get-ChildItem -File -Recurse -Path "$TmpPath\MagickWand" -Include "*.c"

$magickCoreText = ""
$magickWandText = ""


ForEach ($coder in $coders) {
    $file = [System.IO.Path]::GetFileName($coder)
    $magickCoreText += "    `$(IMAGE_MAGICK)/coders/$file \`r`n"
}
ForEach ($filter in $filters) {
    $file = [System.IO.Path]::GetFileName($filter)
    $magickCoreText += "    `$(IMAGE_MAGICK)/filters/$file \`r`n"
}
ForEach ($core in $magickCore) {
    $file = [System.IO.Path]::GetFileName($core)
    $magickCoreText += "    `$(IMAGE_MAGICK)/MagickCore/$file \`r`n"
}
ForEach ($wand in $magickWand) {
    $file = [System.IO.Path]::GetFileName($wand)
    $magickWandText += "    `$(IMAGE_MAGICK)/MagickWand/$file \`r`n"
}


$file = "$PSScriptRoot\mk\libmagickcore-7.mk"
$destination = "$PRoot\make\libmagickcore-7.mk"
(Get-Content $file) -replace '<!MAGICKCORE!>', $magickCoreText | Set-Content $destination

$file = "$PSScriptRoot\mk\libmagickwand-7.mk"
$destination = "$PRoot\make\libmagickwand-7.mk"
(Get-Content $file) -replace '<!MAGICKWAND!>', $magickWandText | Set-Content $destination

$file = "$PRoot\Android.mk"
(Get-Content $file) -replace 'ImageMagick-(.*)', "ImageMagick-$tag" | Set-Content $file

Write-Host Updating imagemagick source files...`n

Copy-Item -Path "$ImPath\configs" -Destination "$TmpPath\configs" -Recurse

# move old directory to new version
$newIm = "$PRoot\ImageMagick-$tag"

git mv "$ImPath" "$newIm"

Set-Location -Path "$newIm"

Get-ChildItem -Path "$newIm" | Foreach-Object {Remove-Item $_.FullName -Recurse}

Copy-Item -Path "$TmpPath\*" -Destination "$newIm" -Recurse

Remove-Item -Path "$TmpPath" -Force -Recurse

# now update version files
$file = "$newIm\configs\arm64\MagickCore\magick-baseconfig.h"
$content = Get-Content -Path $file | foreach-object {$_ -replace "$version", "$tag" }
$content | Set-Content $file

$file = "$newIm\configs\arm64\MagickCore\version.h"
$content = Get-Content -Path $file

$content = $content -replace "#define MagickCopyright\s+`"[^`"]+`"", "#define MagickCopyright  `"$magick_copyright`""
$content = $content -replace "#define MagickLibVersion\s+[^\s]+", "#define MagickLibVersion  $package_lib_version"
$content = $content -replace "#define MagickLibVersionText\s+[^\s]+", "#define MagickLibVersionText  `"$magick_lib_version_text`""
$content = $content -replace "#define MagickLibVersionNumber\s+[^\s]+", "#define MagickLibVersionNumber  $magick_lib_version_number"
$content = $content -replace "#define MagickLibAddendum\s+[^\s]+", "#define MagickLibAddendum  `"$package_version_addendum`""
$content = $content -replace "#define MagickLibInterface\s+[^\s]+", "#define MagickLibInterface  $magick_library_current"
$content = $content -replace "#define MagickLibMinInterface\s+[^\s]+", "#define MagickLibMinInterface  $magick_library_current_min"
$content = $content -replace "#define MagickppLibVersionText\s+[^\s]+", "#define MagickppLibVersionText  `"$magickpp_lib_version_text`""
$content = $content -replace "#define MagickppLibVersionNumber\s+[^\s]+", "#define MagickppLibVersionNumber  $magickpp_library_version_info"
$content = $content -replace "#define MagickppLibAddendum\s+[^\s]+", "#define MagickppLibAddendum  `"$package_version_addendum`""
$content = $content -replace "#define MagickppLibInterface\s+[^\s]+", "#define MagickppLibInterface  $magickpp_library_current"
$content = $content -replace "#define MagickppLibMinInterface\s+[^\s]+", "#define MagickppLibMinInterface  $magickpp_library_current_min"
$content = $content -replace "#define MagickReleaseDate\s+[^\s]+", "#define MagickReleaseDate  `"$magick_release_date`""
$content | Set-Content $file

Write-Host Update done!

return "$version -> $tag"
