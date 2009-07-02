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

#ifndef _OSGKEYFRAME_POSITIONS_SEQUENCE_H_
#define _OSGKEYFRAME_POSITIONS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGSFVecTypes.h>

OSG_BEGIN_NAMESPACE

struct KeyframePositionsSequence2sDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence2s";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence2sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt2s                    StoredFieldType;
    typedef SFPnt2s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc> KeyframePositionsSequence2s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence2sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence2fDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence2f";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence2fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt2f                    StoredFieldType;
    typedef SFPnt2f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc> KeyframePositionsSequence2f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence2fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence2dDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence2d";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence2dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt2d                    StoredFieldType;
    typedef SFPnt2d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc> KeyframePositionsSequence2d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence2dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence3sDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence3s";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence3sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt3s                    StoredFieldType;
    typedef SFPnt3s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc> KeyframePositionsSequence3s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence3sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence3fDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence3f";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence3fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt3f                    StoredFieldType;
    typedef SFPnt3f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc> KeyframePositionsSequence3f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence3fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence3dDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence3d";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence3dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt3d                    StoredFieldType;
    typedef SFPnt3d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc> KeyframePositionsSequence3d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence3dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence4sDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence4s";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence4sProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt4s                    StoredFieldType;
    typedef SFPnt4s                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc> KeyframePositionsSequence4s;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence4sDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence4fDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence4f";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence4fProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt4f                    StoredFieldType;
    typedef SFPnt4f                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc> KeyframePositionsSequence4f;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence4fDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframePositionsSequence4dDesc : public KeyframePositionsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframePositionsSequence4d";         }
    static const Char8 *getClassName(void) { return "KeyframePositionsSequence4dProperty"; }
    static const Char8 *getFieldName(void) { return "positions";              }
    static const Char8 *getGroupName(void) { return "KeyframePositionsSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframePositionsSequence               Inherited;
    typedef KeyframePositionsSequence::PtrType      InheritedPtr;

    typedef KeyframePositionsSequenceDesc   InheritedDesc;

    typedef MFPnt4d                    StoredFieldType;
    typedef SFPnt4d                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc> KeyframePositionsSequence4d;
#endif

#if !defined(OSG_COMPILEKEYFRAMEPOSITIONSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframePositionsSequence4dDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframePositionsSequence.inl"

#endif /* _OSGKEYFRAME_POSITIONS_SEQUENCE_H_ */

