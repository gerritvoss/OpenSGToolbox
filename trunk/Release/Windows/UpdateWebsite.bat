echo off

:Location of psftp client
set PSFTP_DIR=C:\Documents and Settings\David\My Documents\PuTTY
set PSFTP_BATCH_DIR=C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox Daily Build
set SSH_PRIVATE_KEY_FILE=C:\Documents and Settings\David\My Documents\PuTTY\dkabala-vrac-putty-private-key.ppk

:Transfer the build
"%PSFTP_DIR%\psftp.exe" -i "%SSH_PRIVATE_KEY_FILE%" -pw YUguqu9uChuSaChUspatRapha7eSTadRuSwemAfrUStufrUsWUKadEwrubRAgusT -batch -b "%PSFTP_BATCH_DIR%\TransferDailyBuild.scr" dkabala@keymaker.vrac.iastate.edu

pause

