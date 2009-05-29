#!/bin/sh

RepositoryDir="OpenSGToolbox"

if test $# -gt 0
then
   RepositoryDir=$1
fi

#Create the directory to checkout the repository into
if test -d $RepositoryDir
then
   Then remove the directory
   rm -rf $RepositoryDir
fi

mkdir $RepositoryDir

#Check out the repository into this folder
pushd .
cd $RepositoryDir
svn co https://opensgtoolbox.svn.sourceforge.net/svnroot/opensgtoolbox/trunk .

#set up envitonment variables
BOOST_BASE_DIR="/home/users/dkabala/tools/boost_1_38_0/Linux_INSTALL"
export BOOST_BASE_DIR
OPENSG_BASE_DIR="/home/users/dkabala/tools/OpenSG/OpenSG-1.8-rh5"
export OPENSG_BASE_DIR
OPENSG_TOOLBOX_DIR="/home/users/dkabala/OpenSGToolbox/trunk/Builds/Linux"
export OPENSG_TOOLBOX_DIR
FMOD_BASE_DIR="/home/users/dkabala/tools/fmodapi42406linux64/api"
export FMOD_BASE_DIR

#Move to the Build Directory
pushd .
cd Builds

#make all
make

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

popd

popd
