
set yy=%date:~-4%
set mm=%date:~-7,2%
set dd=%date:~-10,2%

:erase Old log files
erase *.log

:Run the Build
CMD /c AutoBuild.bat > WindowsBuild-%mm%-%dd%-%yy%.log

:Update the Website
CMD /c UpdateWebsite.bat
