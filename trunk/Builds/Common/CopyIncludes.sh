#!/bin/sh

for headerFile in `find $2 -type f -name '*.h'`
do
   file=`echo $headerFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   rm -f $3/$file
   sed -f $1/SedConvertIncludes $headerFile > $3/$file
   chmod 444 $3/$file
done

for headerFile in `find $2 -type f -name '*.inl'`
do
   file=`echo $headerFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   rm -f $3/$file
   sed -f $1/SedConvertIncludes $headerFile > $3/$file
   chmod 444 $3/$file
done
