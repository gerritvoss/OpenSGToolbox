#!/bin/sh

for headerFile in `find $1 -type f -name '*.h'`
do
   file=`echo $headerFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   rm -f $2/$file
   sed -f ../SedConvertIncludes $headerFile > $2/$file
   chmod 444 $2/$file
done

for headerFile in `find $1 -type f -name '*.inl'`
do
   file=`echo $headerFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   rm -f $2/$file
   sed -f ../SedConvertIncludes $headerFile > $2/$file
   chmod 444 $2/$file
done
