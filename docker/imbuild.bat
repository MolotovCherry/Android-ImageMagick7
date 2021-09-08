@echo off

cd C:/data

if "%1"=="-r" (
  build-release
  goto End
)

if "%1"=="-d" (
  build-debug
  goto End
)

REM default option is to build release
build-release

:End
