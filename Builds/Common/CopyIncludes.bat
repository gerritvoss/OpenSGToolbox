echo off

::Make the include directories
mkdir %1\include
mkdir %1\include\OpenSG
mkdir %1\include\OpenSG\%2

::Copy the .h and .inl files into the include directory
FOR /F "tokens=*" %%G IN ('dir ..\..\src\*.h /S /B') DO copy "%%G" %1\include\OpenSG\%2\. /Y
FOR /F "tokens=*" %%G IN ('dir ..\..\src\*.inl /S /B') DO copy "%%G" %1\include\OpenSG\%2\. /Y


::Run the sed script on the .h and .inl files to point the library specific includes to the correct library
FOR /F "tokens=*" %%G IN ('dir %1\include\OpenSG\%2\*.h /B') DO (
..\..\..\External\GnuWin32\bin\sed -f ..\..\..\Builds\Common\SedConvertIncludes %1\include\OpenSG\%2\%%G > %1\include\OpenSG\%2\%%G.temp
del %1\include\OpenSG\%2\%%G
move %1\include\OpenSG\%2\%%G.temp %1\include\OpenSG\%2\%%G
)

FOR /F "tokens=*" %%G IN ('dir %1\include\OpenSG\%2\*.inl /B') DO (
..\..\..\External\GnuWin32\bin\sed -f ..\..\..\Builds\Common\SedConvertIncludes %1\include\OpenSG\%2\%%G > %1\include\OpenSG\%2\%%G.temp
del %1\include\OpenSG\%2\%%G
move %1\include\OpenSG\%2\%%G.temp %1\include\OpenSG\%2\%%G
)


