/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGKEYFRAMESEQUENCETMPLDESC_H_
#define _OSGKEYFRAMESEQUENCETMPLDESC_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGColor.h>
#include "OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

struct KeyframeSequencePropertyDesc
{
    /*---------------------------------------------------------------------*/
    static const char *getTypeName (void)  { return "KeyframeSequence"; }

};



struct KeyframeSequenceDesc
{
};

//Positions
struct KeyframePositionsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Pnt3f                  GenericType;

};

//Vectors
struct KeyframeVectorsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Vec3f                  GenericType;

};

//Rotations
struct KeyframeRotationsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeRotationsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeRotationsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeRotationsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Quaternion                  GenericType;

};

//Transformations
struct KeyframeTransformationsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeTransformationsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeTransformationsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeTransformationsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Matrix4f                  GenericType;

};

//Colors
struct KeyframeColorsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeColorsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeColorsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeColorsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Color4f                  GenericType;

};

//Numbers
struct KeyframeNumbersSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef Real32                  GenericType;

};

//Discreet
struct KeyframeDiscreetSequenceDesc : public KeyframeSequenceDesc
{
public:
    //---------------------------------------------------------------------//
    static const Char8 *getTypeName (void) { return "KeyframeDiscreetSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeDiscreetSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeDiscreetSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    //---------------------------------------------------------------------//

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef std::string                  GenericType;

};

//FCPtrs
struct KeyframeFCPtrsSequenceDesc : public KeyframeSequenceDesc
{
public:
    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeFCPtrsSequence";         }
    
    static const Char8 *getGroupName(void) { return "KeyframeFCPtrsSequence";         }
    static const Char8 *getClassName(void) { return "KeyframeFCPtrsSequenceProperty"; }
    
    static InitContainerF getInitMethod(void) { return NULL; }
    
    /*---------------------------------------------------------------------*/

    typedef KeyframeSequence             Inherited;
    typedef KeyframeSequencePtr          InheritedPtr;
    
    typedef KeyframeSequencePropertyDesc InheritedDesc;
    
    typedef FieldContainerPtr                  GenericType;

};






OSG_END_NAMESPACE

#endif /* _OSGKEYFRAMESEQUENCETMPLDESC_H_ */