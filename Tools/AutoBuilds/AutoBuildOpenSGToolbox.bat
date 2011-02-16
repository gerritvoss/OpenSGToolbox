echo on

:These variables need to be changed to their respective locations for the machine this installer will be run on
:Location of git
set GIT_PATH=C:\Program Files (x86)\Git\bin
:Location of cmake
set CMAKE_PATH=C:\Program Files (x86)\CMake 2.8\bin
:Location of ctest
set CTEST_PATH=C:\Program Files (x86)\CMake 2.8\bin
:Location of cpack
set CPACK_PATH=C:\Program Files (x86)\CMake 2.8\bin
:Location of NSIS compiler makensis.exe
set NSIS_PATH=C:\Program Files (x86)\NSIS\Bin
:Location of Visual Studio Console command devenv.com
set VS_PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE
set CMAKE_GENERATOR=Visual Studio 10

set CMAKE_SETUP_FILE=..\..\NucleusCMakeSetup.txt

set TOOLBOX_REPOSITORY_URL=git://github.com/djkabala/OpenSGToolbox.git
set OPENSG_REPOSITORY_URL=git://github.com/djkabala/OpenSGDevMaster_Toolbox
set TOOLBOX_PROJECT_DIR=OpenSGToolbox
set OPENSG_PROJECT_DIR=OpenSG
set BUILD_DIR=LocalBuild
set SOLUTION_NAME=OpenSG.sln

:set BUILD_PROJECTS_ORDER=(OSGAllLibs)
set BUILD_PROJECTS_ORDER=(OSGBase)
:set LIBRARY_BUILD_CONFIGURATIONS=(Debug Release)
set BUILD_CONFIGURATIONS=(Release)
set TUTORIAL_BUILD_CONFIGURATIONS=(Release)

:Setup the Directory
rd /Q /S "%TOOLBOX_PROJECT_DIR%"
md "%TOOLBOX_PROJECT_DIR%"
rd /Q /S "%OPENSG_PROJECT_DIR%"
md "%OPENSG_PROJECT_DIR%"

:Checkout the Repository
"%GIT_PATH%\git.exe" clone "%TOOLBOX_REPOSITORY_URL%" "%TOOLBOX_PROJECT_DIR%"
"%GIT_PATH%\git.exe" clone "%OPENSG_REPOSITORY_URL%" "%OPENSG_PROJECT_DIR%"

:Move to Main Build Directory
pushd "%TOOLBOX_PROJECT_DIR%"
rd /Q /S "%BUILD_DIR%"
md "%BUILD_DIR%"
pushd "%BUILD_DIR%"

:Run CMake
"%CMAKE_PATH%\cmake.exe" -C "%CMAKE_SETUP_FILE%" -G "%CMAKE_GENERATOR%" -WDev "..\..\%OPENSG_PROJECT_DIR%"

:Build the Libraries
FOR %%p in %BUILD_PROJECTS_ORDER% DO FOR %%c in %BUILD_CONFIGURATIONS% DO "%VS_PATH%\devenv.com" "%SOLUTION_NAME%" /build %%c /project %%p
popd

:Build the Tutorials
:FOR %%p in %LIBRARY_BUILD_ORDER% DO (
:    pushd %%p\Tutorials
:    FOR /f "tokens=*" %%f in ('dir *.vcproj /b') DO (
:        FOR %%c in %TUTORIAL_BUILD_CONFIGURATIONS% DO "%VS_PATH%\devenv.com" %%f /build %%c
:    )
:    popd
:)

:Package the build
:pushd Release\Windows
:"%NSIS_PATH%\makensis.exe" /V3 InstallScript.nsi

:Publish the build

popd


:Move back to original Directory
popd
