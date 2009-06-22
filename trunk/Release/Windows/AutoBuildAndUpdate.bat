
set yy=%date:~-4%
set mm=%date:~-7,2%
set dd=%date:~-10,2%

set BuildFileNameInfix=-vs2005-%mm%-%dd%-%yy%

:erase Old log files
erase OpenSGTooblox*.log
erase OpenSGToolbox*.log

:Run the Build
CMD /c AutoBuild.bat > WindowsBuild%BuildFileNameInfix%.log

:Update the Website
CMD /c UpdateWebsite.bat
