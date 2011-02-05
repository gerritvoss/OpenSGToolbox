#!/bin/sh

#Setup the environment
. /etc/profile
. ~/.profile

AUTOBUILD_DIR=~/Work/ScheduledBuilds/OpenSGToolbox

TOOLBOX_REPO_DIR=$AUTOBUILD_DIR/OpenSGToolbox
OSG_REPO_DIR=$AUTOBUILD_DIR/OpenSGDevMaster
TOOLBOX_REPO_URL=git://github.com/djkabala/OpenSGToolbox.git
OSG_REPO_URL=git://github.com/djkabala/OpenSGDevMaster_Toolbox.git
CMAKE_SETUP_FILE=~/Work/ScheduledBuilds/OpenSGToolbox/OpenSGToolboxCMakeSetup.txt

CMAKE_INSTALL_PREFIX=~/public_html/OpenSGToolbox/V2

BUILD_DIR=$OSG_REPO_DIR/LocalBuild

pushd .

#Change to the Autobuild folder
cd $AUTOBUILD_DIR

#remove old log files
rm OpenSGToolboxBuild-*.log

#Log to to a log file
DATE_TIME=`date "+%Y-%m-%dT%H:%M:%S"`
exec &> $AUTOBUILD_DIR/OpenSGToolboxBuild-$DATE_TIME.log

#pring to stdout too
#tail -f capture.txt >/dev/tty7 &

#Start time
date

rm -rf $OSG_REPO_DIR
rm -rf $TOOLBOX_REPO_DIR

#Clone the repositories
git clone ${OSG_REPO_URL} ${OSG_REPO_DIR}
git clone ${TOOLBOX_REPO_URL} ${TOOLBOX_REPO_DIR}

pushd .
    cd ${OSG_REPO_DIR}

    mkdir $BUILD_DIR
    mkdir $BUILD_DIR/Release

    cd $BUILD_DIR/Release

    #Run the cmake configuration
    cmake -C $CMAKE_SETUP_FILE ../..

    #Make the documentation
    make install -j2

    #Package the Build

popd 

#Publish the Build

#End time
date

popd 

