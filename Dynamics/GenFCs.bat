echo %~p1

pushd .
cd %~p1
"C:\Documents and Settings\All Users\Documents\Libraries\OpenSG\fcdCompile.exe" -b -f "%~n1%~x1"

"C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\External\GnuWin32\bin\sed.exe" -f "C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\Dynamics\CleanUpFC.sed" "OSG%~n1.h" > "OSG%~n1.h.temp"
"C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\External\GnuWin32\bin\sed.exe" -f "C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\Dynamics\CleanUpFC.sed" "OSG%~n1Base.h" > "OSG%~n1Base.h.temp"
"C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\External\GnuWin32\bin\sed.exe" -f "C:\Documents and Settings\David\My Documents\Work\OpenSGToolbox\Dynamics\CleanUpFC.sed" "OSG%~n1Fields.h" > "OSG%~n1Fields.h.temp"

del "OSG%~n1.h"
move "OSG%~n1.h.temp" "OSG%~n1.h"
del "OSG%~n1Base.h"
move "OSG%~n1Base.h.temp" "OSG%~n1Base.h"
del "OSG%~n1Fields.h"
move "OSG%~n1Fields.h.temp" "OSG%~n1Fields.h"

popd