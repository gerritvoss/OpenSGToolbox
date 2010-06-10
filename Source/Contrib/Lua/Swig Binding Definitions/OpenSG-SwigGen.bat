
echo off
:Location of swig.exe
:set SWIG_EXE_PATH=C:\Documents and Settings\David\My Documents\Work\swigwin-1.3.40\swig.exe
set SWIG_EXE_PATH=C:\Users\David\Documents\Work\swigwin-2.0.0\swig.exe

:Location of the swig interface file
set INTERFACE_FILE_PATH=C:\Users\David\Documents\Work\OpenSG-2.X\Toolbox\OpenSGToolbox\Source\Contrib\Lua\Swig Binding Definitions\OSGSystem.i

:Location of the output file to generate
set OUTPUT_FILE_PATH=C:\Users\David\Documents\Work\OpenSG-2.X\Toolbox\OpenSGToolbox\Source\Contrib\Lua\src\Bindings\OSG_wrap.cpp

"%SWIG_EXE_PATH%" -c++ -lua -o "%OUTPUT_FILE_PATH%" "%INTERFACE_FILE_PATH%"

pause

