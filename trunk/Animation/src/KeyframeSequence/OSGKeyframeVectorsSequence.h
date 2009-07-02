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

#ifndef _OSGKEYFRAME_VECTORS_SEQUENCE_H_
#define _OSGKEYFRAME_VECTORS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGSFVecTypes.h>
#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

struct KeyframeVectorsSequence2sDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence2s";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence2sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec2s                    StoredFieldType;
    typedef SFVec2s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc> KeyframeVectorsSequence2s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence2sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence2fDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence2f";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence2fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec2f                    StoredFieldType;
    typedef SFVec2f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc> KeyframeVectorsSequence2f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence2fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence2dDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence2d";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence2dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec2d                    StoredFieldType;
    typedef SFVec2d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc> KeyframeVectorsSequence2d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence2dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence3sDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence3s";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence3sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec3s                    StoredFieldType;
    typedef SFVec3s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc> KeyframeVectorsSequence3s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence3sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence3fDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence3f";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence3fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec3f                    StoredFieldType;
    typedef SFVec3f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return lerpNormalKeyframeSequence<StoredFieldType,SingleFieldType>;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc> KeyframeVectorsSequence3f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence3fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence3dDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence3d";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence3dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec3d                    StoredFieldType;
    typedef SFVec3d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc> KeyframeVectorsSequence3d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence3dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence4sDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence4s";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence4sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec4s                    StoredFieldType;
    typedef SFVec4s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc> KeyframeVectorsSequence4s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence4sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence4fDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence4f";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence4fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec4f                    StoredFieldType;
    typedef SFVec4f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc> KeyframeVectorsSequence4f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence4fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeVectorsSequence4dDesc : public KeyframeVectorsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeVectorsSequence4d";         }
    static const Char8 *getClassName(void) { return "KeyframeVectorsSequence4dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframeVectorsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeVectorsSequence               Inherited;
    typedef KeyframeVectorsSequence::PtrType      InheritedPtr;

    typedef KeyframeVectorsSequenceDesc   InheritedDesc;

    typedef MFVec4d                    StoredFieldType;
    typedef SFVec4d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc> KeyframeVectorsSequence4d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeVectorsSequence4dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeVectorsSequence.inl"

#endif /* _OSGKEYFRAME_VECTORS_SEQUENCE_H_ */

