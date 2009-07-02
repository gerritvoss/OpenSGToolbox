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

#ifndef _OSGKEYFRAME_TRANSFORMATIONS_SEQUENCE_H_
#define _OSGKEYFRAME_TRANSFORMATIONS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/OSGMatrix.h>

OSG_BEGIN_NAMESPACE

struct KeyframeTransformationsSequence44fDesc : public KeyframeTransformationsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeTransformationsSequence44f";         }
    static const Char8 *getClassName(void) { return "KeyframeTransformationsSequence44fProperty"; }
    static const Char8 *getFieldName(void) { return "transformations";              }
    static const Char8 *getGroupName(void) { return "KeyframeTransformationsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeTransformationsSequence               Inherited;
    typedef KeyframeTransformationsSequence::PtrType      InheritedPtr;

    typedef KeyframeTransformationsSequenceDesc   InheritedDesc;

    typedef MFMatrix                    StoredFieldType;
    typedef SFMatrix                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeTransformationsSequence44fDesc> KeyframeTransformationsSequence44f;
#endif

#if !defined(OSG_COMPILEKEYFRAMETRANSFORMATIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeTransformationsSequence44fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif
OSG_END_NAMESPACE

#include "OSGKeyframeTransformationsSequence.inl"

#endif /* _OSGKEYFRAME_TRANSFORMATIONS_SEQUENCE_H_ */

