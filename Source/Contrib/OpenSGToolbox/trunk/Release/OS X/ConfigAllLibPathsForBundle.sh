#!/bin/sh

OPENSG_LIB_DIR=/Users/davidkabala/Documents/Work/OpenSG/OpenSG/AppleInstall/lib
BOOST_LIB_DIR=/Users/davidkabala/Documents/Work/boost_1_39_0/AppleInstall/lib
ODE_LIB_DIR=/Users/davidkabala/Documents/Work/ode-0.11.1/AppleInstall/lib
OPENSG_TOOLBOX_LIB_DIR=/Users/davidkabala/Documents/Work/OpenSGToolbox/trunk/Builds/Apple/lib

BASEDIR=`dirname "$0"`

"$BASEDIR/BundleDirLibPaths.sh" "$OPENSG_LIB_DIR/dbg" "@executable_path/../Libraries/"
"$BASEDIR/BundleDirLibPaths.sh" "$OPENSG_LIB_DIR/opt" "@executable_path/../Libraries/"
"$BASEDIR/BundleDirLibPaths.sh" "$BOOST_LIB_DIR" "@executable_path/../Libraries/"
"$BASEDIR/BundleDirLibPaths.sh" "$ODE_LIB_DIR" "@executable_path/../Libraries/"
"$BASEDIR/BundleDirLibPaths.sh" "$OPENSG_TOOLBOX_LIB_DIR" "@executable_path/../Libraries/"

