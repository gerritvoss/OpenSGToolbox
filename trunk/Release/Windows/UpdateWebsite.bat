echo off

:Location of psftp client
set PSFTP_DIR=C:\Documents and Settings\David\My Documents\PuTTY
set PSFTP_BATCH_DIR=C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox Daily Build

:Transfer the build
"%PSFTP_DIR%\psftp.exe" Keymaker -batch -b "%PSFTP_BATCH_DIR%\TransferDailyBuild.scr"

