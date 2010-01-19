#!/bin/sh

ReleaseScriptsDir="/home/users/dkabala/OpenSGToolbox/trunk/Release/Linux"

pushd .
cd $ReleaseScriptsDir

./AutoBuild.sh
./UpdateWebsite.sh

popd
