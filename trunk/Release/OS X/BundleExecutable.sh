#!/bin/sh
#Arg_1 = The Executable to make a bundle for

#===================================================================
get_dep_libs()    
#===================================================================
# Arg_1 = BinaryPath
# Arg_2 = TempFilePath
{
    DepLibs=""
    for Pattern in "libOSG" "libboost" "libode" "libtiff" "libjpeg" "libpng" "libfmod"
    do
        Libraries=`otool -L $1| grep $Pattern | sed -e 's/[ 	]*\(.*dylib\).*/\1/'`
        for Lib in $Libraries
        do
            DepLibs="$DepLibs `basename $Lib`"
            echo `basename $Lib` >> $2
        done
    done
}

SCRIPT_BASE_DIR=`dirname "$0"`

BundleName=$1
LibBundlePath=@executable_path/../Libraries/

#Make directory Structure
#BundleName.app
# |
# -- Contents
#     |
#     -- Libraries
#     -- MacOS
#         |
#         -- Executable
#     -- Info.plist
if test -e ./$BundleName.app; then
    rm -r ./$BundleName.app
fi
mkdir ./$BundleName.app
mkdir ./$BundleName.app/Contents
mkdir ./$BundleName.app/Contents/Libraries
mkdir ./$BundleName.app/Contents/MacOS

#Copy the executable into  $BundleName.app/Contents/MacOS
cp $1 ./$BundleName.app/Contents/MacOS/

#Create the Info.plist from the template
sed s-REPLACE_EXE-$BundleName- "$SCRIPT_BASE_DIR/Info.plist.template" > ./$BundleName.app/Contents/Info.plist

#Determine all of the dependent Libraries
TEMP_DEPS_FILE="/tmp/TempDeps.txt"
rm $TEMP_DEPS_FILE
touch $TEMP_DEPS_FILE
get_dep_libs ./$BundleName.app/Contents/MacOS/$1 $TEMP_DEPS_FILE

#find Paths to libs

LibrarySearchPaths=`echo $DYLD_LIBRARY_PATH  | sed 's- -\\\\s-g' | sed 's-:- -g'` 
LibrarySearchPaths="$LibrarySearchPaths / /sw/lib"
for Lib in `cat $TEMP_DEPS_FILE`
do
    for APath in $LibrarySearchPaths
    do
        RealPath=`echo $APath | sed 's-\\\\s- -g'`

        if test -e "$RealPath/$Lib";
        then
            get_dep_libs $RealPath/$Lib $TEMP_DEPS_FILE
        fi
    done
done

ALL_DEP_FILES=`sort $TEMP_DEPS_FILE | uniq`

#find Paths to libs
for Lib in $ALL_DEP_FILES
do
    for APath in $LibrarySearchPaths
    do
        RealPath=`echo $APath | sed 's-\\\\s- -g'`

        if test -e "$RealPath/$Lib";
        then
            #Copy all of the Dependent Libraries into ./$BundleName.app/Contents/Libraries
            echo $RealPath/$Lib
            cp "$RealPath/$Lib" "./$BundleName.app/Contents/Libraries/"
        fi
    done
done

#Setup the lib path to the libraries
"$SCRIPT_BASE_DIR/BundleDirLibPaths.sh" "./$BundleName.app/Contents/Libraries" "@executable_path/../Libraries/"
"$SCRIPT_BASE_DIR/BundleLibPaths.sh" "./$BundleName.app/Contents/MacOS/$1" "@executable_path/../Libraries/"

