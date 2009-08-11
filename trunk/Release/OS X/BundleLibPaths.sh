#!/bin/sh
#Arg_1 = Directory of libs to apply to
#Arg_2 = new path to libraries

ExecutableDir=/usr/local
File=$1
#LibBundlePath=@executable_path/../Libraries/
LibBundlePath=$2

#===================================================================
rename_libs()    
#===================================================================
# Arg_1 = LibraryPattern
{
    Libraries=`otool -L $File | grep $1 | sed -e 's/[ 	]*\(.*dylib\).*/\1/'`
    for Lib in $Libraries
	do
        
        LibFileName=`echo $Lib | sed -e 's/.*\/\(.*\.dylib\)/\1/'`
        install_name_tool -change $Lib $LibBundlePath$LibFileName $File
	done
}

# Get all of the OSG family libraries
rename_libs libOSG
# Get all of the boost family libraries
rename_libs libboost
# Get tiff libraries
rename_libs libtiff
# Get jpeg libraries
rename_libs libjpeg
# Get png libraries
rename_libs libpng
# Get fmod libraries
rename_libs libfmod
# Get ode libraries
rename_libs libode

