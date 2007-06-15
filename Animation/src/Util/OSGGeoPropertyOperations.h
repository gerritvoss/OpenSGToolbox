#ifndef _OPENSG_GEO_PROPERTY_OPERATIONS_H_
#define _OPENSG_GEO_PROPERTY_OPERATIONS_H_

#include "OSGAnimationConfig.h"
#include <OpenSG/OSGGeoProperty.h>

OSG_BEGIN_NAMESPACE

//Colors
OSG_ANIMATION_FUNC_API osg::GeoColorsPtr createEmptyFromBase(osg::GeoColorsPtr Base);

OSG_ANIMATION_FUNC_API void addValueAsBaseType(osg::GeoColorsPtr Dst, const osg::GeoColorsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATION_FUNC_API osg::Field* getField(osg::GeoColorsPtr Colors);

//Normals
OSG_ANIMATION_FUNC_API osg::GeoNormalsPtr createEmptyFromBase(osg::GeoNormalsPtr Base);

OSG_ANIMATION_FUNC_API void addValueAsBaseType(osg::GeoNormalsPtr Dst, const osg::GeoNormalsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATION_FUNC_API osg::Field* getField(osg::GeoNormalsPtr Norms);

//Positions
OSG_ANIMATION_FUNC_API osg::GeoPositionsPtr createEmptyFromBase(osg::GeoPositionsPtr Base);

OSG_ANIMATION_FUNC_API void addValueAsBaseType(osg::GeoPositionsPtr Dst, const osg::GeoPositionsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATION_FUNC_API osg::Field* getField(osg::GeoPositionsPtr Pos);

//TexCoords
OSG_ANIMATION_FUNC_API osg::GeoTexCoordsPtr createEmptyFromBase(osg::GeoTexCoordsPtr Base);

OSG_ANIMATION_FUNC_API void addValueAsBaseType(osg::GeoTexCoordsPtr Dst, const osg::GeoTexCoordsPtr Src,
                        const osg::UInt32 SrcIndex);

OSG_ANIMATION_FUNC_API osg::Field* getField(osg::GeoTexCoordsPtr Coords);

OSG_END_NAMESPACE

#endif
