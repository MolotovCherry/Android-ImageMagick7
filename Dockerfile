FROM mcr.microsoft.com/powershell:lts-nanoserver-2004

ENV NDK=android-ndk-r23
ENV NDK_PLATFORM=windows
ENV NDK_FILE=$NDK-$NDK_PLATFORM.zip
ENV POWERSHELL_TELEMETRY_OPTOUT=1
ENV PATH="C:/Program Files/PowerShell;C:/ndk/$NDK;C:/data;$PATH"

ADD https://dl.google.com/android/repository/$NDK_FILE .

# extract ndk zip
RUN pwsh.exe -Command Expand-Archive -Path %NDK_FILE% -DestinationPath ndk
RUN del /F %NDK_FILE%

VOLUME C:/data

COPY docker/imbuild.bat C:/
ENTRYPOINT imbuild
