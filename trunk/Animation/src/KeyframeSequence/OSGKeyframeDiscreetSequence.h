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

#ifndef _OSGKEYFRAME_DISCREETS_SEQUENCE_H_
#define _OSGKEYFRAME_DISCREETS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGSFBaseTypes.h>
#include <OpenSG/OSGGL.h>
#include <OpenSG/Toolbox/OSGGLenumUtils.h>

OSG_BEGIN_NAMESPACE

struct KeyframeDiscreetSequenceStringDesc : public KeyframeDiscreetSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeDiscreetSequenceString";         }
    static const Char8 *getClassName(void) { return "KeyframeDiscreetSequenceStringProperty"; }
    static const Char8 *getFieldName(void) { return "values";              }
    static const Char8 *getGroupName(void) { return "KeyframeDiscreetSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeDiscreetSequence               Inherited;
    typedef KeyframeDiscreetSequence::PtrType      InheritedPtr;

    typedef KeyframeDiscreetSequenceDesc   InheritedDesc;

    typedef MFString                    StoredFieldType;
    typedef SFString                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc> KeyframeDiscreetSequenceString;
#endif

#if !defined(OSG_COMPILEKEYFRAMEDISCREETSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeDiscreetSequenceStringDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif


//struct KeyframeDiscreetSequenceGLenumDesc : public KeyframeDiscreetSequenceDesc
//{
//    static FieldDescription *_desc[];
    /*---------------------------------------------------------------------*/
//    static const Char8 *getTypeName (void) { return "KeyframeDiscreetSequenceGLenum";         }
//    static const Char8 *getClassName(void) { return "KeyframeDiscreetSequenceGLenumProperty"; }
//    static const Char8 *getFieldName(void) { return "values";              }
//    static const Char8 *getGroupName(void) { return "KeyframeDiscreetSequence";           }
//    static InitContainerF     getInitMethod(void) { return NULL; }

//    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
//    typedef KeyframeDiscreetSequence               Inherited;
//    typedef KeyframeDiscreetSequence::PtrType      InheritedPtr;

//    typedef KeyframeDiscreetSequenceDesc   InheritedDesc;

//    typedef MFGLenum                    StoredFieldType;
//    typedef SFGLenum                    SingleFieldType;
//    typedef InheritedDesc::GenericType GenericType;
    
//    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
//    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
//    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return NULL;}
//    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return NULL;}
//    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
//};

//#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
//typedef KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc> KeyframeDiscreetSequenceGLenum;
//#endif

#if !defined(OSG_COMPILEKEYFRAMEDISCREETSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeDiscreetSequenceGLenumDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeDiscreetSequence.inl"

#endif /* _OSGKEYFRAME_DISCREETS_SEQUENCE_H_ */

