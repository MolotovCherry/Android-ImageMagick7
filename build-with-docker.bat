@echo off
setlocal enabledelayedexpansion

docker build %~dp0 --tag cherryleafroad/imbuild

for /f "delims=" %i in ('"docker volume inspect imbuild 2>NUL"') DO set imvolume=%i

if "!imvolume!"=="[]" (
  docker volume create imbuild
)

rd /s /q %~dp0\jniLibs >NUL 2>NUL
mkdir jniLibs\arm64-v8a

docker run --rm -v %~dp0:C:/data cherryleafroad/imbuild %1
