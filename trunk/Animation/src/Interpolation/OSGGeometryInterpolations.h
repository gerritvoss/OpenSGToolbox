#ifndef _OPENSG_GEOMETRYINTERPOLATIONS_H_
#define _OPENSG_GEOMETRYINTERPOLATIONS_H_

#include "OSGAnimationDef.h"

#include <vector>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMField.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGMFMathTypes.h>

#include <OpenSG/OSGGeoPositionsFields.h> // BaseValues type
#include "GeometryAnimation/OSGGeoPositionDifferenceSet.h" // KeyframeDifferenceSets type
#include "GeometryAnimation/OSGGeoNormalDifferenceSet.h" // KeyframeDifferenceSets type
#include "GeometryAnimation/OSGGeoColorDifferenceSet.h" // KeyframeDifferenceSets type
#include "GeometryAnimation/OSGGeoTexCoordDifferenceSet.h" // KeyframeDifferenceSets type


OSG_BEGIN_NAMESPACE

//Lerp
OSG_ANIMATIONLIB_DLLMAPPING bool lerp(  const GeoPositionsPtr BaseValues,const MFGeoPositionDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoPositionsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool lerp(  const GeoNormalsPtr BaseValues,const MFGeoNormalDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoNormalsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool lerp(  const GeoColorsPtr BaseValues,const MFGeoColorDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoColorsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool lerp(  const GeoTexCoordsPtr BaseValues,const MFGeoTexCoordDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoTexCoordsPtr Value, bool isCyclic=false );

//Step
OSG_ANIMATIONLIB_DLLMAPPING bool step(  const GeoPositionsPtr BaseValues,const MFGeoPositionDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoPositionsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool step(  const GeoNormalsPtr BaseValues,const MFGeoNormalDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoNormalsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool step(  const GeoColorsPtr BaseValues,const MFGeoColorDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoColorsPtr Value, bool isCyclic=false );
OSG_ANIMATIONLIB_DLLMAPPING bool step(  const GeoTexCoordsPtr BaseValues,const MFGeoTexCoordDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoTexCoordsPtr Value, bool isCyclic=false );

OSG_END_NAMESPACE

#endif
