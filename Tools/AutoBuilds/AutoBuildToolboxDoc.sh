#!/bin/sh

#Setup the environment
. /etc/profile
. ~/.profile

AUTOBUILD_DIR=~/Work/ScheduledBuilds/OSGToolboxDoc

TOOLBOX_REPO_DIR=$AUTOBUILD_DIR/OpenSGToolbox
OSG_REPO_DIR=$AUTOBUILD_DIR/OpenSGDevMaster
TOOLBOX_REPO_URL=git://github.com/djkabala/OpenSGToolbox.git
OSG_REPO_URL=git://github.com/djkabala/OpenSGDevMaster_Toolbox.git

CMAKE_INSTALL_PREFIX=~/public_html/OpenSGToolbox/V2

BUILD_DIR=$OSG_REPO_DIR/DocBuild

pushd .

#Change to the Autobuild folder
cd $AUTOBUILD_DIR

#remove old log files
rm OpenSGDocBuild-*.log

#Log to to a log file
DATE_TIME=`date "+%Y-%m-%dT%H:%M:%S"`
exec &> $AUTOBUILD_DIR/OpenSGDocBuild-$DATE_TIME.log

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

    rm -rf $BUILD_DIR
    mkdir $BUILD_DIR
    cd $BUILD_DIR

    #Run the cmake configuration
    cmake -DDOXYGEN_DOT_EXECUTABLE=/usr/local/bin/dot \
        -DDOXYGEN_DOT_PATH=/usr/local/bin \
        -DDOXYGEN_EXECUTABLE=/Applications/Doxygen.app/Contents/Resources/doxygen \
        -DOSGBUILD_ENABLE_PACKAGING=OFF \
        -DOSGBUILD_EXAMPLES_ADVANCED=OFF \
        -DOSGBUILD_EXAMPLES_SIMPLE=OFF \
        -DOSGBUILD_OSGBase=ON \
        -DOSGBUILD_OSGCluster=ON \
        -DOSGBUILD_OSGContribBackgroundLoader=ON \
        -DOSGBUILD_OSGContribCSM=OFF \
        -DOSGBUILD_OSGContribCSMSimplePlugin=OFF \
        -DOSGBUILD_OSGContribCgFX=ON \
        -DOSGBUILD_OSGContribComputeBase=OFF \
        -DOSGBUILD_OSGContribFieldContainerEditor=ON \
        -DOSGBUILD_OSGContribGUI=ON \
        -DOSGBUILD_OSGContribLua=ON \
        -DOSGBUILD_OSGContribLuaToolbox=ON \
        -DOSGBUILD_OSGContribPLY=OFF \
        -DOSGBUILD_OSGContribParticleSystem=ON \
        -DOSGBUILD_OSGContribPhysics=ON \
        -DOSGBUILD_OSGContribSound=ON \
        -DOSGBUILD_OSGContribTextDom=ON \
        -DOSGBUILD_OSGContribTrapezoidalShadowMaps=ON \
        -DOSGBUILD_OSGContribUserInterface=ON \
        -DOSGBUILD_OSGContribVTK=OFF \
        -DOSGBUILD_OSGContribVideo=ON \
        -DOSGBUILD_OSGDrawable=ON \
        -DOSGBUILD_OSGDynamics=ON \
        -DOSGBUILD_OSGEffectGroups=ON \
        -DOSGBUILD_OSGFileIO=ON \
        -DOSGBUILD_OSGGroup=ON \
        -DOSGBUILD_OSGImageFileIO=ON \
        -DOSGBUILD_OSGState=ON \
        -DOSGBUILD_OSGSystem=ON \
        -DOSGBUILD_OSGTBAnimation=ON \
        -DOSGBUILD_OSGTBFileIO=ON \
        -DOSGBUILD_OSGTestGroupLib=OFF \
        -DOSGBUILD_OSGTestSystemLib=OFF \
        -DOSGBUILD_OSGText=ON \
        -DOSGBUILD_OSGUtil=ON \
        -DOSGBUILD_OSGWindow=ON \
        -DOSGBUILD_OSGWindowCarbon=ON \
        -DOSGBUILD_OSGWindowCocoa=ON \
        -DOSGBUILD_OSGWindowCoreGL=OFF \
        -DOSGBUILD_OSGWindowGLUT=OFF \
        -DOSGBUILD_OSGWindowQT4=OFF \
        -DOSGBUILD_OSGWindowWIN32=OFF \
        -DOSGBUILD_OSGWindowX=OFF \
        -DOSGBUILD_TESTS=OFF \
        -DOSGBUILD_UNITTESTS=OFF \
        -DOSGCOMPAT_ENABLE=OFF \
        -DOSGCOMPAT_ENABLE_DEPRECATED=OFF \
        -DOSG_CORE_EXTENSIONS=$TOOLBOX_REPO_DIR/Source \
        -DOSG_OSGContribFieldContainerEditor_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/FieldContainerEditor/src \
        -DOSG_OSGContribLuaToolbox_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/Lua/ToolboxBindings/src \
        -DOSG_OSGContribLua_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/Lua/src \
        -DOSG_OSGContribParticleSystem_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/ParticleSystem/src \
        -DOSG_OSGContribPhysics_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/Physics/src \
        -DOSG_OSGContribSound_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/Sound/src \
        -DOSG_OSGContribTextDom_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/TextDom/src \
        -DOSG_OSGContribUserInterface_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/UserInterface/src \
        -DOSG_OSGContribVideo_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/Contrib/Video/src \
        -DOSG_OSGTBAnimation_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/System/Dynamics \
        -DOSG_OSGTBFileIO_SOURCE_DIR=$TOOLBOX_REPO_DIR/Source/System/FileIO \
        -DOSG_DOXY_DOC_TYPE=User \
        -DOSG_GENERATE_SEPARATE_LIB_DOC=ON \
        -DOSG_EXTRA_EXTERNAL_MODULES="OSGTBAnimation;OSGTBFileIO;OSGContribFieldContainerEditor;OSGContribLua;OSGContribLuaToolbox;OSGContribParticleSystem;OSGContribPhysics;OSGContribSound;OSGContribTextDom;OSGContribUserInterface;OSGContribVideo" \
        -DOSG_LUA_BUILD_WITH_DEBUGGER=ON \
        ..
    #Make the documentation
    make Doc

    #Package the Doc
    cd Doc
    tar -czf OSGToolboxDoc.tgz html
    mv OSGToolboxDoc.tgz $AUTOBUILD_DIR/OSGToolboxDoc.tgz

popd 

#Publish the doc

#End time
date

popd 

