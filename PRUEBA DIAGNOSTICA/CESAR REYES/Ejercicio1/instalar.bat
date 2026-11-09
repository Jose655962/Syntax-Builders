@echo off
echo ==========================================
echo  Instalacion de componentes - Ejercicio 1
echo ==========================================

echo.
echo [1/2] Instalando Python 3 con winget...
winget install -e --id Python.Python.3.12 --accept-package-agreements --accept-source-agreements

echo.
echo [2/2] Instalando MSYS2 con winget...
winget install -e --id MSYS2.MSYS2 --accept-package-agreements --accept-source-agreements

echo.
echo Instalando gcc dentro de MSYS2 (UCRT64)...
C:\msys64\usr\bin\bash.exe -lc "pacman -Syu --noconfirm"
C:\msys64\usr\bin\bash.exe -lc "pacman -S --needed --noconfirm mingw-w64-ucrt-x86_64-toolchain"

echo.
echo ==========================================
echo  Listo. Cierra y vuelve a abrir la terminal.
echo  Para compilar el codigo C usa MSYS2 UCRT64:
echo    gcc caballo.c -o caballo
echo    ./caballo
echo ==========================================
pause