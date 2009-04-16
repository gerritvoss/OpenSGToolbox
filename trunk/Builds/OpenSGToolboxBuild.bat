
echo off

set SVNPath="C:\Program Files\SlikSvn\bin\svn.exe"
set VisualStudioPath="C:\Program Files\SlikSvn\bin\svn.exe"
set RepositoryDir="OpenSGToolbox"

set OPENSG="C:\Program Files\OpenSG\lib"
set BOOST_BASE_DIR="C:\Program Files\boost\boost_1_35_0"

mkdir %RepositoryDir%

::%SVNPath% co https://subversion.vrac.iastate.edu/Subversion/OpenSGToolbox/svn/OpenSGToolbox %RepositoryDir%

cd %RepositoryDir%\Builds\Windows

pause
