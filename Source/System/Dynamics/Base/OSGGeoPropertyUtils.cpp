#include "OSGGeoPropertyUtils.h"

OSG_BEGIN_NAMESPACE

void zeroGeoProperty(GeoVectorProperty* GeoProp)
{
    switch(GeoProp->getFormat())
    {
        case GL_UNSIGNED_BYTE:
            zeroGeoPropertyTmpl<GLubyte>(GeoProp);
            break;
        case GL_BYTE:
            zeroGeoPropertyTmpl<GLbyte>(GeoProp);
            break;
        case GL_UNSIGNED_SHORT:
            zeroGeoPropertyTmpl<GLushort>(GeoProp);
            break;
        case GL_SHORT:
            zeroGeoPropertyTmpl<GLshort>(GeoProp);
            break;
        case GL_FLOAT:
            zeroGeoPropertyTmpl<GLfloat>(GeoProp);
            break;
        //case GL_FIXED:
            //zeroGeoPropertyTmpl<GLfixed>(GeoProp);
            //break;
        case GL_DOUBLE:
            zeroGeoPropertyTmpl<GLdouble>(GeoProp);
            break;
        default:
            SWARNING << "Property format " << GeoProp->getFormat() << " not supported" << std::endl;
            break;
    }
}

void morphGeoProperty(GeoVectorProperty* TargetGeoProp,
                      GeoVectorProperty* ResultGeoProp,
                      Real32 Weight)
{
    switch(ResultGeoProp->getFormat())
    {
        case GL_UNSIGNED_BYTE:
            morphGeoPropertyTmpl<GLubyte>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        case GL_BYTE:
            morphGeoPropertyTmpl<GLbyte>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        case GL_UNSIGNED_SHORT:
            morphGeoPropertyTmpl<GLushort>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        case GL_SHORT:
            morphGeoPropertyTmpl<GLshort>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        case GL_FLOAT:
            morphGeoPropertyTmpl<GLfloat>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        //case GL_FIXED:
            //morphGeoPropertyTmpl<GLfixed>(TargetGeoProp,
                                   //ResultGeoProp,
                                   //Weight);
            //break;
        case GL_DOUBLE:
            morphGeoPropertyTmpl<GLdouble>(TargetGeoProp,
                                   ResultGeoProp,
                                   Weight);
            break;
        default:
            SWARNING << "Property format " << ResultGeoProp->getFormat() << " not supported" << std::endl;
            break;
    }
}

OSG_END_NAMESPACE


