echo off

set SED_CONVERT_INCLUDES_FILE=ConvertIncludes.sed

::Make the include directories
if not exist %1\include mkdir %1\include
if not exist %1\include\OpenSG mkdir %1\include\OpenSG
if not exist %1\include\OpenSG\%2 mkdir %1\include\OpenSG\%2

::Copy the .h and .inl files into the include directory
"%~dp0\..\..\External\GnuWin32\bin\sed" s-REPLACE-%2- "%~dp0\..\..\Builds\Common\ConvertIncludesTemplate.sed" > %SED_CONVERT_INCLUDES_FILE%
FOR /F "tokens=*" %%G IN ('dir ..\..\src\*.h ..\..\src\*.inl /S /B') DO (
    xcopy "%%G" %1\include\OpenSG\%2\. /D /L | FIND "0 File(s)" > Temp.txt
    
    if ERRORLEVEL 1 (
        call "%~dp0\CopyIfNotEmpty.bat" "%~f1\include\OpenSG\%2\" "%%G" %SED_CONVERT_INCLUDES_FILE%
    )
)
if exist %SED_CONVERT_INCLUDES_FILE% del %SED_CONVERT_INCLUDES_FILE%
echo Finished Installing Include Files

