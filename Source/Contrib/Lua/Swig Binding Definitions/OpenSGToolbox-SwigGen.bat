
echo off
:Location of swig.exe
:set SWIG_EXE_PATH=C:\Program Files (x86)\swigwin-2.0.0\swig.exe
set SWIG_EXE_PATH=C:\Program Files (x86)\swigwin-2.0.0\swig.exe

:Location of the swig interface file
set INTERFACE_FILE_PATH=C:\Users\danielg\Documents\OpenSGToolbox\Source\Contrib\Lua\Swig Binding Definitions\OSGToolbox.i

:Location of the output file to generate
set OUTPUT_FILE_PATH=C:\Users\danielg\Documents\OpenSGToolbox\Source\Contrib\Lua\ToolboxBindings\src\Bindings\OSGToolbox_wrap.cpp

"%SWIG_EXE_PATH%" -c++ -lua -o "%OUTPUT_FILE_PATH%" "%INTERFACE_FILE_PATH%"

pause

