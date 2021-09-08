@echo off
setlocal enabledelayedexpansion

for /f "delims=" %%i in ('docker images -q cherryleafroad/imbuild') DO set imbuild=%%i

if [!imbuild!]==[] (
  set /p choice="Download(d) or build(b) image? [dB]: "
  
  if "!choice!"=="d" (
    docker pull cherryleafroad/imbuild
    goto continue
  ) else (
    if "!choice!"=="b" (
      docker build %~dp0 --tag cherryleafroad/imbuild
      goto continue
    )
  )
  
  docker build %~dp0 --tag cherryleafroad/imbuild
)

:continue

for /f "delims=" %i in ('"docker volume inspect imbuild 2>NUL"') DO set imvolume=%i

if "!imvolume!"=="[]" (
  docker volume create imbuild
)

rd /s /q %~dp0\jniLibs >NUL 2>NUL
mkdir jniLibs\arm64-v8a

docker run --rm -v %~dp0:C:/data cherryleafroad/imbuild %1
