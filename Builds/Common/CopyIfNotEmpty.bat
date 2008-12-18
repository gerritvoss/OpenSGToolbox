
echo off
if not %~z1==0 (
     echo %~f2\%~nx3>>"%~f4"
     )
GOTO :eof

