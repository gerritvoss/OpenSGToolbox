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

#ifndef _OSGKEYFRAME_ROTATIONS_SEQUENCE_H_
#define _OSGKEYFRAME_ROTATIONS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFMathTypes.h>
#include <OpenSG/OSGSFMathTypes.h>
#include <OpenSG/Toolbox/OSGQuatOperations.h>

OSG_BEGIN_NAMESPACE

struct KeyframeRotationsSequenceQuatDesc : public KeyframeRotationsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeRotationsSequenceQuat";         }
    static const Char8 *getClassName(void) { return "KeyframeRotationsSequenceQuatProperty"; }
    static const Char8 *getFieldName(void) { return "rotations";              }
    static const Char8 *getGroupName(void) { return "KeyframeRotationsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeRotationsSequence               Inherited;
    typedef KeyframeRotationsSequence::PtrType      InheritedPtr;

    typedef KeyframeRotationsSequenceDesc   InheritedDesc;

    typedef MFQuaternion                    StoredFieldType;
    typedef SFQuaternion                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return slerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return squadKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeRotationsSequenceQuatDesc> KeyframeRotationsSequenceQuat;
#endif

#if !defined(OSG_COMPILEKEYFRAMEROTATIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeRotationsSequenceQuatDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeRotationsSequence.inl"

#endif /* _OSGKEYFRAME_ROTATIONS_SEQUENCE_H_ */