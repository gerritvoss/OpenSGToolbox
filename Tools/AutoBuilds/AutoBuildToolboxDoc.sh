#!/bin/sh
#Parameters
# 

#Setup the environment
. /etc/profile
. ~/.profile

#SHELL_SCRIPT_DIR=`dirname $0`
ABS_PATH=$(cd ${0%/*} && echo $PWD/${0##*/})
SHELL_SCRIPT_DIR=`dirname $ABS_PATH`

GIT_EXE_PATH=git
CMAKE_EXE_PATH=cmake
INSTALL_PREFIX=$SHELL_SCRIPT_DIR/LocalInstall
BUILD_DIR="$SHELL_SCRIPT_DIR/LocalBuild"

AUTOBUILD_DIR=$SHELL_SCRIPT_DIR
ARTIFACT_FILE_BASE_NAME="OSGToolboxUserDoc"

TOOLBOX_REPO_URL=git://github.com/djkabala/OpenSGToolbox.git
OSG_REPO_URL=git://github.com/djkabala/OpenSGDevMaster_Toolbox.git

while getopts 'kno:c:g:p:t:a:w:u:' OPTION
do
    case $OPTION in
        t) TOOLBOX_REPO_URL_FLAG=1
           TOOLBOX_REPO_URL="$OPTARG"
            ;;
        o) OSG_REPO_URL_FLAG=1
           OSG_REPO_URL="$OPTARG"
            ;;
        c) CMAKE_EXE_PATH_FLAG=1
           CMAKE_EXE_PATH="$OPTARG"
            ;;
        g) GIT_EXE_PATH_FLAG=1
           GIT_EXE_PATH="$OPTARG"
            ;;
        p) INSTALL_PREFIX_FLAG=1
           INSTALL_PREFIX="$OPTARG"
            ;;
        n) NO_BUILD_FLAG=1
            ;;
        k) PACKAGE_FLAG=1
            ;;
        w) PUBLISH_URL_FLAG=1
           PUBLISH_URL="$OPTARG"
            ;;
        u) PUBLISH_DIR_FLAG=1
           PUBLISH_DIR="$OPTARG"
            ;;
        a) ARTIFACT_FILE_FLAG=1
           ARTIFACT_FILE_BASE_NAME="$OPTARG"
            ;;
        ?) printf "Usage: "
           exit 2
            ;;
    esac
done
shift $((OPTIND -1))

TOOLBOX_REPO_DIR=$AUTOBUILD_DIR/OpenSGToolbox
OSG_REPO_DIR=$AUTOBUILD_DIR/OpenSGDevMaster

pushd .

#Change to the Autobuild folder
cd $AUTOBUILD_DIR

#remove old log files
rm $AUTOBUILD_DIR/OpenSGDocBuild-*.log

#Log to to a log file
DATE_TIME=`date "+%Y-%m-%dT%H:%M:%S"`

LOG_FILE=$AUTOBUILD_DIR/OpenSGDocBuild-$DATE_TIME.log
exec &> $LOG_FILE

#pring to stdout too
#tail -f capture.txt >/dev/tty7 &

#Start time
date

rm -rf $OSG_REPO_DIR
rm -rf $TOOLBOX_REPO_DIR

#Clone the repositories
$GIT_EXE_PATH clone ${OSG_REPO_URL} ${OSG_REPO_DIR}
$GIT_EXE_PATH clone ${TOOLBOX_REPO_URL} ${TOOLBOX_REPO_DIR}

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
        $OSG_REPO_DIR

    #Make the documentation
    if [ "$NO_BUILD_FLAG" != 1 ]; then
        make Doc
    fi


    #Package the Doc
    if [ "$PACKAGE_FLAG" = 1 ]; then
        cd Doc

        ARTIFACT_FILE="$ARTIFACT_FILE_BASE_NAME.tgz"

        tar -czf $ARTIFACT_FILE html

        #Publish the doc
        if [ "$PUBLISH_URL_FLAG" = 1 ]; then
            #Push the package to the URL
            scp $ARTIFACT_FILE $PUBLISH_URL:$PUBLISH_DIR

            #End time
            date
            scp $LOG_FILE $PUBLISH_URL:$PUBLISH_DIR

            #ssh $ARTIFACT_FILE.tgz $PUBLISH_URL
        fi
    fi

popd 

#End time
date

popd 

