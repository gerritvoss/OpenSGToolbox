#!/bin/sh

#mkdir temp directory
if [ ! -d temp  ]
then
    mkdir temp


    #Run the osg code generators
    for file in `ls *.fcd`
    do
        git mv "$file" "OSG$file"

        #Copy all of the .h, .inl, and .cpp files into temp
        BaseFileName=`echo $file | sed -e "s/\(.*\)\.fcd/\1/"`
        cp "OSG$BaseFileName.h" temp
        cp "OSG$BaseFileName.cpp" temp
        cp "OSG$BaseFileName.inl" temp


        ~/Documents/Work/OpenSGToolbox/OpenSG-2.0/Tools/fcd2code/GenFCs.sh OSG$file
    done
else
    for file in `ls *.fcd`
    do
        ~/Documents/Work/OpenSGToolbox/OpenSG-2.0/Tools/fcd2code/GenFCs.sh $file
    done

fi

