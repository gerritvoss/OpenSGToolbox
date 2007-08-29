echo off

pushd .
cd %~p1
"%~d0%~p0..\External\fcdCompile\Windows\fcdCompile.exe" -b -f "%~n1%~x1"

"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpFC.sed" "OSG%~n1.h" > "OSG%~n1.h.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpFC.sed" "OSG%~n1Base.h" > "OSG%~n1Base.h.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpFC.sed" "OSG%~n1Fields.h" > "OSG%~n1Fields.h.temp"

del "OSG%~n1.h"
move "OSG%~n1.h.temp" "OSG%~n1.h"
del "OSG%~n1Base.h"
move "OSG%~n1Base.h.temp" "OSG%~n1Base.h"
del "OSG%~n1Fields.h"
move "OSG%~n1Fields.h.temp" "OSG%~n1Fields.h"

"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1.h" > "OSG%~n1.h.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1.cpp" > "OSG%~n1.cpp.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1.inl" > "OSG%~n1.inl.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1Base.h" > "OSG%~n1Base.h.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1Base.cpp" > "OSG%~n1Base.cpp.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1Base.inl" > "OSG%~n1Base.inl.temp"
"%~d0%~p0..\External\GnuWin32\bin\sed.exe" -f "%~d0%~p0CleanUpUILicense.sed" "OSG%~n1Fields.h" > "OSG%~n1Fields.h.temp"

del "OSG%~n1.h"
move "OSG%~n1.h.temp" "OSG%~n1.h"
del "OSG%~n1.cpp"
move "OSG%~n1.cpp.temp" "OSG%~n1.cpp"
del "OSG%~n1.inl"
move "OSG%~n1.inl.temp" "OSG%~n1.inl"
del "OSG%~n1Base.h"
move "OSG%~n1Base.h.temp" "OSG%~n1Base.h"
del "OSG%~n1Base.cpp"
move "OSG%~n1Base.cpp.temp" "OSG%~n1Base.cpp"
del "OSG%~n1Base.inl"
move "OSG%~n1Base.inl.temp" "OSG%~n1Base.inl"
del "OSG%~n1Fields.h"
move "OSG%~n1Fields.h.temp" "OSG%~n1Fields.h"


popd
pause
