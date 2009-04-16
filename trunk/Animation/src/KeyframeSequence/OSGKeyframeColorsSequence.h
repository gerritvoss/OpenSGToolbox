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

#ifndef _OSGKEYFRAME_COLORS_SEQUENCE_H_
#define _OSGKEYFRAME_COLORS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGSFBaseTypes.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/Toolbox/OSGColorOperations.h>

OSG_BEGIN_NAMESPACE

struct KeyframeColorsSequence3ubDesc : public KeyframeColorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeColorsSequence3ub";         }
    static const Char8 *getClassName(void) { return "KeyframeColorsSequence3ubProperty"; }
    static const Char8 *getFieldName(void) { return "colors";              }
    static const Char8 *getGroupName(void) { return "KeyframeColorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeColorsSequence               Inherited;
    typedef KeyframeColorsSequence::PtrType      InheritedPtr;

    typedef KeyframeColorsSequenceDesc   InheritedDesc;

    typedef MFColor3ub                    StoredFieldType;
    typedef SFColor3ub                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc> KeyframeColorsSequence3ub;
#endif

#if !defined(OSG_COMPILEKEYFRAMECOLORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeColorsSequence3ubDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeColorsSequence3fDesc : public KeyframeColorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeColorsSequence3f";         }
    static const Char8 *getClassName(void) { return "KeyframeColorsSequence3fProperty"; }
    static const Char8 *getFieldName(void) { return "colors";              }
    static const Char8 *getGroupName(void) { return "KeyframeColorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeColorsSequence               Inherited;
    typedef KeyframeColorsSequence::PtrType      InheritedPtr;

    typedef KeyframeColorsSequenceDesc   InheritedDesc;

    typedef MFColor3f                    StoredFieldType;
    typedef SFColor3f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc> KeyframeColorsSequence3f;
#endif

#if !defined(OSG_COMPILEKEYFRAMECOLORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeColorsSequence3fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeColorsSequence4ubDesc : public KeyframeColorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeColorsSequence4ub";         }
    static const Char8 *getClassName(void) { return "KeyframeColorsSequence4ubProperty"; }
    static const Char8 *getFieldName(void) { return "colors";              }
    static const Char8 *getGroupName(void) { return "KeyframeColorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeColorsSequence               Inherited;
    typedef KeyframeColorsSequence::PtrType      InheritedPtr;

    typedef KeyframeColorsSequenceDesc   InheritedDesc;

    typedef MFColor4ub                    StoredFieldType;
    typedef SFColor4ub                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc> KeyframeColorsSequence4ub;
#endif

#if !defined(OSG_COMPILEKEYFRAMECOLORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeColorsSequence4ubDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeColorsSequence4fDesc : public KeyframeColorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeColorsSequence4f";         }
    static const Char8 *getClassName(void) { return "KeyframeColorsSequence4fProperty"; }
    static const Char8 *getFieldName(void) { return "colors";              }
    static const Char8 *getGroupName(void) { return "KeyframeColorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeColorsSequence               Inherited;
    typedef KeyframeColorsSequence::PtrType      InheritedPtr;

    typedef KeyframeColorsSequenceDesc   InheritedDesc;

    typedef MFColor4f                    StoredFieldType;
    typedef SFColor4f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc> KeyframeColorsSequence4f;
#endif

#if !defined(OSG_COMPILEKEYFRAMECOLORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeColorsSequence4fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeColorsSequence.inl"

#endif /* _OSGKEYFRAME_COLORS_SEQUENCE_H_ */