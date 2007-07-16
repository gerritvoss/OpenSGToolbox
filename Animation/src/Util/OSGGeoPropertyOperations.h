#ifndef _OPENSG_GEO_PROPERTY_OPERATIONS_H_
#define _OPENSG_GEO_PROPERTY_OPERATIONS_H_

#include "OSGAnimationDef.h"
#include <OpenSG/OSGGeoProperty.h>

OSG_BEGIN_NAMESPACE

//Colors
OSG_ANIMATIONLIB_DLLMAPPING osg::GeoColorsPtr createEmptyFromBase(osg::GeoColorsPtr Base);

OSG_ANIMATIONLIB_DLLMAPPING void addValueAsBaseType(osg::GeoColorsPtr Dst, const osg::GeoColorsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATIONLIB_DLLMAPPING osg::Field* getField(osg::GeoColorsPtr Colors);

//Normals
OSG_ANIMATIONLIB_DLLMAPPING osg::GeoNormalsPtr createEmptyFromBase(osg::GeoNormalsPtr Base);

OSG_ANIMATIONLIB_DLLMAPPING void addValueAsBaseType(osg::GeoNormalsPtr Dst, const osg::GeoNormalsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATIONLIB_DLLMAPPING osg::Field* getField(osg::GeoNormalsPtr Norms);

//Positions
OSG_ANIMATIONLIB_DLLMAPPING osg::GeoPositionsPtr createEmptyFromBase(osg::GeoPositionsPtr Base);

OSG_ANIMATIONLIB_DLLMAPPING void addValueAsBaseType(osg::GeoPositionsPtr Dst, const osg::GeoPositionsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATIONLIB_DLLMAPPING osg::Field* getField(osg::GeoPositionsPtr Pos);

//TexCoords
OSG_ANIMATIONLIB_DLLMAPPING osg::GeoTexCoordsPtr createEmptyFromBase(osg::GeoTexCoordsPtr Base);

OSG_ANIMATIONLIB_DLLMAPPING void addValueAsBaseType(osg::GeoTexCoordsPtr Dst, const osg::GeoTexCoordsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATIONLIB_DLLMAPPING osg::Field* getField(osg::GeoTexCoordsPtr Coords);

OSG_END_NAMESPACE

#endif
