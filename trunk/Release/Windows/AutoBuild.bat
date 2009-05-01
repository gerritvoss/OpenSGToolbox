echo off

:These variables need to be changed to their respective locations for the machine this installer will be run on
:Location of subversion client svn.exe
set SUBVERSION_PATH=C:\Program Files\SlikSvn\bin
:Location of NSIS compiler makensis.exe
set NSIS_PATH=C:\Program Files\NSIS
:Location of Visual Studio Console command devenv.com
set VS_PATH=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE


set REPOSITORY_URL=https://opensgtoolbox.svn.sourceforge.net/svnroot/opensgtoolbox/trunk
set PROJECT_DIR=OpenSGToolbox
set BUILD_DIR=Builds\Windows
set SOLUTION_NAME=vs-8.0-OpenSGToolbox.sln

set LIBRARY_BUILD_ORDER=(Toolbox Input Sound Animation Dynamics ParticleSystem UserInterface Game)
set LIBRARY_BUILD_CONFIGURATIONS=(Debug Release)
set TUTORIAL_BUILD_CONFIGURATIONS=(Release)

:Setup the Directory
:rd /Q /S "%PROJECT_DIR%"
:md "%PROJECT_DIR%"

:Checkout the Repository
:"%SUBVERSION_PATH%\svn.exe" checkout "%REPOSITORY_URL%" "%PROJECT_DIR%" --non-interactive

:Move to Main Build Directory
cd "%PROJECT_DIR%"
pushd "%BUILD_DIR%"

:Build the Libraries
FOR %%p in %LIBRARY_BUILD_ORDER% DO FOR %%c in %LIBRARY_BUILD_CONFIGURATIONS% DO "%VS_PATH%\devenv.com" "%SOLUTION_NAME%" /build %%c /project OSG%%p
popd

:Build the Tutorials
FOR %%p in %LIBRARY_BUILD_ORDER% DO (
    pushd %%p\Tutorials
    FOR /f "tokens=*" %%f in ('dir *.vcproj /b') DO (
        FOR %%c in %TUTORIAL_BUILD_CONFIGURATIONS% DO "%VS_PATH%\devenv.com" %%f /build %%c
    )
    popd
)

:Build the Installer
pushd Release\Windows
"%NSIS_PATH%\makensis.exe" /V 2 InstallScript.nsi
popd

:Move back to original Directory
popd

pause