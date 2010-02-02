#!/bin/sh

SCRIPT_BASE_DIR=`dirname "$0"`

#Location of swig.exe
SWIG_EXE_PATH=swig

#Location of the swig interface file
INTERFACE_FILE_PATH=$SCRIPT_BASE_DIR/OSGSystem.i

#Location of the output file to generate
OUTPUT_FILE_PATH=$SCRIPT_BASE_DIR/../src/Bindings/OSG_wrap.cpp

#Run the swig code generation command
"$SWIG_EXE_PATH" -c++ -lua -o "$OUTPUT_FILE_PATH" "$INTERFACE_FILE_PATH"

