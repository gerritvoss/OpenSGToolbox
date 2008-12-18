
echo off
     "%~dp0\..\..\External\GnuWin32\bin\sed" -f "%~f3" "%~f2" > "%~f1\%~nx2"
     echo Copied "%~f2"

