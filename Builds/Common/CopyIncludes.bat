echo off

set COPYIED_FILES_TXT=CopiedFiles.txt
set SED_CONVERT_INCLUDES_FILE=ConvertIncludes.sed

::Make the include directories
if not exist %1\include mkdir %1\include
if not exist %1\include\OpenSG mkdir %1\include\OpenSG
if not exist %1\include\OpenSG\%2 mkdir %1\include\OpenSG\%2

::Copy the .h and .inl files into the include directory
if exist %COPYIED_FILES_TXT% del %COPYIED_FILES_TXT%
FOR /F "tokens=*" %%G IN ('dir ..\..\src\*.h ..\..\src\*.inl /S /B') DO (
    :Copy the file only if the src has modified date newer than the destination
    xcopy "%%G" %1\include\OpenSG\%2\. /D /Y | FIND /V "File(s) copied">Temp.txt
    :If the File was copied then print the destination folder to the COPYIED_FILES_TXT File
    call "%~dp0\CopyIfNotEmpty.bat" Temp.txt "%~f1\include\OpenSG\%2\" "%%G" %COPYIED_FILES_TXT%
)

if exist %COPYIED_FILES_TXT% (
    ::Run the sed script on the .h and .inl files to point the library specific includes to the correct library
    "%~dp0\..\..\External\GnuWin32\bin\sed" s-REPLACE-%2- "%~dp0\..\..\Builds\Common\ConvertIncludesTemplate.sed" > %SED_CONVERT_INCLUDES_FILE%
    FOR /F "tokens=*" %%G IN (%COPYIED_FILES_TXT%) DO (
        "%~dp0\..\..\External\GnuWin32\bin\sed" -f "%SED_CONVERT_INCLUDES_FILE%" "%%G" > "%%G.temp"
        del "%%G"
        move "%%G.temp" "%%G"
        echo Copied changed file: "%%G"
    )
    if exist %COPYIED_FILES_TXT% del %COPYIED_FILES_TXT%
    if exist %SED_CONVERT_INCLUDES_FILE% del %SED_CONVERT_INCLUDES_FILE%
)


