%module osgbase
%{
#include <OpenSG/OSGBaseFunctions.h>
%}

namespace osg {
    typedef float Real32;
    typedef unsigned int UInt32;
    typedef int Int32;
    typedef long Int64;
    typedef char Char8;

    Real32 osgrand(void);

    void osgGetHostname(char *szBuffer, UInt32 uiSize);
}

