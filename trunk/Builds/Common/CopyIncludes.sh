#!/bin/sh

#Function for copying a file
#Arg 1: The folder where SedConvertIncludes is located
#Arg 2: The Filename to write to
#Arg 3: The folder to copy the file to
#Arg 4: The File to read from
copy_includes()
{
   rm -f $3/$2
   sed -f $1/SedConvertIncludes $4 > $3/$2
   chmod 444 $3/$2
}

#Create a sed file off of a template that will
#relpace the local include paths in the headers
#and inlines with there path to a flat directory
#for their respective library
SedConvertFile=ConvertIncludes.sed
sed s-REPLACE-$4- "$1/ConvertIncludesTemplate.sed" > $SedConvertFile

#Find all of the header files
for headerFile in `find $2 -type f -name '*.h'`
do
   file=`echo $headerFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   if [ ! -e "$3/$file" ] ; then
      copy_includes $1 $file $3 $headerFile
   elif [ -n "`find $headerFile -cnewer $3/$file`" ] ; then
      copy_includes $1 $file $3 $headerFile
   fi
done

#find all of the inline files
for inlineFile in `find $2 -type f -name '*.inl'`
do
   file=`echo $inlineFile | sed 's/\(.*\)\/\(.*\)/\2/'`
   if [ ! -e "$3/$file" ] ; then
      copy_includes $1 $file $3 $inlineFile
   elif [ -n "`find $inlineFile -cnewer $3/$file`" ] ; then
      copy_includes $1 $file $3 $inlineFile
   fi
done

rm $SedConvertFile
