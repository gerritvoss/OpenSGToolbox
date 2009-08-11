#!/bin/sh
#Arg_1 = Directory of libs to apply to
#Arg_2 = new path to libraries

ExecutableDir=/usr/local
LibraryDir=$1
#LibBundlePath=@executable_path/../Libraries/
LibBundlePath=$2

BASEDIR=`dirname "$0"`

for File in `ls -1 $LibraryDir/*.dylib`
do
    "$BASEDIR/BundleLibPaths.sh" "$File" "$LibBundlePath"
done

