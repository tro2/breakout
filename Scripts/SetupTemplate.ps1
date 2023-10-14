#Requires -Version 3

# Set directory to solution root
$solutionDir = Join-Path -Path $PSScriptRoot -ChildPath ".."
Set-Location -Path $solutionDir

# Check if Breakout.sln exists and exit otherwise
if (-not(Test-Path -Path "Breakout.sln" -PathType Leaf)) {
	Write-Host "Fatal error: Breakout.sln not found"
	exit 1
}

# Check if BreakoutApp\ exists and exit otherwise
if (-not(Test-Path -Path "BreakoutApp" -PathType Container)) {
	Write-Host "Fatal error: BreakoutApp\ not found"
	exit 1
}

# Get BreakoutApp's project GUID
$currentGuid = "6dad8d3c-92b1-4267-b8df-37b72d942465"
$newGuid = New-Guid

# Get new project name
$newName = Read-Host "Please enter your new project name (must be a valid Visual Studio name, no spaces preferred)"
$newNameApp = $newName + "App"

# TODO: delete VS cache (fail if VS has lock on cache) and/or build folders?

# Temporary: Provide old and new GUIDs for manual find-and-replace
Write-Host "Old GUID: $currentGuid"
Write-Host "New GUID: $newGuid"

# Rename solution file
$newSolutionFileName = "$newName.sln"
Rename-Item -Path "Breakout.sln" -NewName "$newSolutionFileName"

# Rename project directory
$newProjectDirectoryName = "$newNameApp"
Rename-Item -Path "BreakoutApp" -NewName "$newProjectDirectoryName"

# Rename project files
Rename-Item -Path "$newProjectDirectoryName\BreakoutApp.vcxproj" -NewName "$newNameApp.vcxproj"
Rename-Item -Path "$newProjectDirectoryName\BreakoutApp.vcxproj.filters" -NewName "$newNameApp.vcxproj.filters"

if (Test-Path -Path "$newProjectDirectoryName\BreakoutApp.vcxproj.user") {
	Rename-Item -Path "$newProjectDirectoryName\BreakoutApp.vcxproj.user" -NewName "$newNameApp.vcxproj.user"
}

########################################################################################################################
########################################################################################################################
# TODO: Learn powershell to do this properly
########################################################################################################################
########################################################################################################################

# Why is this failing?

# Get-ChildItem -Exclude "Dependencies" |
# Get-ChildItem -Recurse *.* |
# ForEach-Object {
# 	Write-Host $_.fullname
# }

# Replace the old project name

# Get-ChildItem -Exclude "Dependencies\", ".git\" |
# ForEach-Object {
# 	Get-ChildItem -Recurse *.* |
# 	ForEach-Object {
# 		$a = $_.fullname;
# 		$content = Get-Content $a;
# 
# 		$content |
# 		ForEach-Object { $_ -replace "Breakout", "$newName" } | 
# 		set-content $a
# 	}
# }

# Replace the old guid

# Get-ChildItem -Recurse *.* -Exclude "Dependencies\*" |
# ForEach-Object {
# 	$a = $_.fullname;
# 	$content = Get-Content $a;
# 	
# 	if ($content.Contains("Breakout")) {
# 		$content |
# 		ForEach-Object { $_ -replace "$currentGuid", "$newName" } | 
# 		set-content $a
# 	}
# 	
# 	(Get-Content $a) |
# 	ForEach-Object { $_ -replace "$currentGuid", "$newGuid" } | 
# 	set-content $a
# }