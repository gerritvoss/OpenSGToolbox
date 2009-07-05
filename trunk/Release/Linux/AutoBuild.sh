#!/bin/sh

RepositoryDir="OpenSGToolbox"
Today=`date +%F`

RemoveOldRepository=1
MakeSourceZip=1
CheckoutRepository=1
MakeLinuxBuild=1
MakeDoxygenBuild=1

if test $# -gt 0
then
   RepositoryDir=$1
fi

#Create the directory to checkout the repository into
if test -d $RepositoryDir
then
   if test $RemoveOldRepository -ne 0
   then
      #Then remove the directory
      rm -rf $RepositoryDir
   fi
fi

mkdir $RepositoryDir

#Check out the repository into this folder
pushd .
cd $RepositoryDir
if test $CheckoutRepository -ne 0
then
   svn co https://opensgtoolbox.svn.sourceforge.net/svnroot/opensgtoolbox/trunk .
fi

#set up envitonment variables
BOOST_BASE_DIR="/home/users/dkabala/tools/boost_1_38_0/Linux_INSTALL"
OPENSG_BASE_DIR="/home/users/dkabala/tools/OpenSG/OpenSG-1.8-rh5"
FMOD_BASE_DIR="/home/users/dkabala/tools/fmodapi42406linux64"
ODE_BASE_DIR="/home/users/dkabala/tools/ode-0.11.1/Linux_INSTALL/"
DOXYGEN_EXECUTABLE="/home/users/dkabala/bin/doxygen-1.5.9"
CMAKE_EXECUTABLE="/home/users/dkabala/bin/cmake"
CTEST_EXECUTABLE="/home/users/dkabala/bin/ctest"
CPACK_EXECUTABLE="/home/users/dkabala/bin/cpack"

#Make a source zip
if test $MakeSourceZip -ne 0
then
   echo "Making the source build"
   pushd .
   cd ..
   tar -cf OpenSGToolbox-source-$Today.tar $RepositoryDir
   gzip OpenSGToolbox-source-$Today.tar
   popd
fi


#Move to the Build Directory
pushd .
cd Builds

mkdir Debug
mkdir Release

#Run cmake to make the builds
pushd .
cd Debug
$CMAKE_EXECUTABLE -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=../Linux -D FMOD_BASE_DIR=$FMOD_BASE_DIR -D OPENSG_BASE_DIR=$OPENSG_BASE_DIR -D BOOST_ROOT=$BOOST_BASE_DIR -D ODE_BASE_DIR=$ODE_BASE_DIR -D BUILD_DYNAMICS=ON -D BUILD_PARTICLE_SYSTEMS=ON -D BUILD_ANIMATION=ON -D BUILD_INPUT=ON -D BUILD_METABOLIC=ON -D BUILD_USERINTERFACE=ON -D BUILD_GAME=ON -D BUILD_VIDEO=ON -D BUILD_PHYSICS=ON -D BUILD_SOUND=ON -D CONFIGURE_TUTORIALS=ON -D ENABLE_USER_DOCUMENTATION=ON -D ENABLE_DEVELOPER_DOCUMENTATION=ON ../..
popd

pushd .
cd Release
$CMAKE_EXECUTABLE -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=../Linux -D FMOD_BASE_DIR=$FMOD_BASE_DIR -D OPENSG_BASE_DIR=$OPENSG_BASE_DIR -D BOOST_ROOT=$BOOST_BASE_DIR -D ODE_BASE_DIR=$ODE_BASE_DIR -D BUILD_DYNAMICS=ON -D BUILD_PARTICLE_SYSTEMS=ON -D BUILD_ANIMATION=ON -D BUILD_INPUT=ON -D BUILD_METABOLIC=ON -D BUILD_USERINTERFACE=ON -D BUILD_GAME=ON -D BUILD_VIDEO=ON -D BUILD_PHYSICS=ON -D BUILD_SOUND=ON -D CONFIGURE_TUTORIALS=ON -D ENABLE_USER_DOCUMENTATION=ON -D ENABLE_DEVELOPER_DOCUMENTATION=ON ../..
popd

#make all
if test $MakeLinuxBuild -ne 0
then
   pushd .
   cd Debug
   make install -j4
   popd

   pushd .
   cd Release
   make install -j4
   popd

   #make > OpenSGToolbox-rhe5-64bit-$Today.log
   #mv OpenSGToolbox-rhe5-64bit-$Today.log ../../
fi

#make the documentation
if test $MakeDoxygenBuild -ne 0
then
   make doc > OpenSGToolbox-doxygen-doc-$Today.log
   mv OpenSGToolbox-doxygen-doc-$Today.log ../../
fi

if test $MakeLinuxBuild -ne 0
then
   #Move to the Installed Directory
   pushd .
   cd Linux
   #Zip up an install of the Binaries
   mkdir OpenSGToolbox
   mv include OpenSGToolbox
   mv lib OpenSGToolbox
   tar -cf OpenSGToolbox-rhe5-64bit-$Today.tar OpenSGToolbox
   gzip OpenSGToolbox-rhe5-64bit-$Today.tar
   mv OpenSGToolbox-rhe5-64bit-$Today.tar.gz ../../../

   popd
fi

popd

if test $MakeDoxygenBuild -ne 0
then
   pushd .
   cd Website/documentation/api
   #Zip up an install of the documentation
   mkdir OpenSGToolbox-Documentation
   mv OSG* OpenSGToolbox-Documentation
   tar  -cf OpenSGToolbox-doxygen-doc-$Today.tar OpenSGToolbox-Documentation
   gzip OpenSGToolbox-doxygen-doc-$Today.tar
   mv OpenSGToolbox-doxygen-doc-$Today.tar.gz ../../../../
   popd
fi

