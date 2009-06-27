#!/bin/sh

RepositoryDir="OpenSGToolbox"
Today=`date +%F`

RemoveOldRepository=1
MakeSourceZip=1
CheckoutRepository=1
MakeLinuxBuild=0
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
export BOOST_BASE_DIR
OPENSG_BASE_DIR="/home/users/dkabala/tools/OpenSG/OpenSG-1.8-rh5"
export OPENSG_BASE_DIR
OPENSG_TOOLBOX_DIR="/home/users/dkabala/OpenSGToolbox/trunk/Builds/Linux"
export OPENSG_TOOLBOX_DIR
FMOD_BASE_DIR="/home/users/dkabala/tools/fmodapi42406linux64/api"
export FMOD_BASE_DIR
ODE_BASE_DIR="/home/users/dkabala/tools/ode/Linux_INSTALL"
export ODE_BASE_DIR

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

#make all
if test $MakeLinuxBuild -ne 0
then
   make > OpenSGToolbox-rhe5-64bit-$Today.log
   mv OpenSGToolbox-rhe5-64bit-$Today.log ../../
fi

#make the documentation
if test $MakeDoxygenBuild -ne 0
then
   make doc > OpenSGToolbox-doxygen-doc-$Today.log
   mv OpenSGToolbox-doxygen-doc-$Today.log ../../
fi

if test $MakeLinuxBuild-ne 0
then
   #Move to the Installed Directory
   pushd .
   cd Linux
   #Zip up an install of the Binaries
   mkdir OpenSGToolbox
   mv include OpenSGToolbox
   mv lib OpenSGToolbox
   tar -cf OpenSGToolbox.tar OpenSGToolbox
   gzip OpenSGToolbox.tar
   mv OpenSGToolbox.tar.gz ../../../

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

