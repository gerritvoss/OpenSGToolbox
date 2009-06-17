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

#ifndef _OSGKEYFRAME_NUMBERS_SEQUENCE_H_
#define _OSGKEYFRAME_NUMBERS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGSFSysTypes.h>

OSG_BEGIN_NAMESPACE

struct KeyframeNumbersSequenceUInt8Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceUInt8";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceUInt8Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFUInt8                    StoredFieldType;
    typedef SFUInt8                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc> KeyframeNumbersSequenceUInt8;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceUInt8Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceUInt16Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceUInt16";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceUInt16Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFUInt16                    StoredFieldType;
    typedef SFUInt16                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc> KeyframeNumbersSequenceUInt16;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceUInt16Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceUInt32Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceUInt32";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceUInt32Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFUInt32                    StoredFieldType;
    typedef SFUInt32                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc> KeyframeNumbersSequenceUInt32;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceUInt32Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceUInt64Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceUInt64";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceUInt64Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFUInt64                    StoredFieldType;
    typedef SFUInt64                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc> KeyframeNumbersSequenceUInt64;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceUInt64Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

                      
struct KeyframeNumbersSequenceInt8Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceInt8";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceInt8Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFInt8                    StoredFieldType;
    typedef SFInt8                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc> KeyframeNumbersSequenceInt8;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceInt8Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceInt16Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceInt16";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceInt16Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFInt16                    StoredFieldType;
    typedef SFInt16                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc> KeyframeNumbersSequenceInt16;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceInt16Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceInt32Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceInt32";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceInt32Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFInt32                    StoredFieldType;
    typedef SFInt32                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc> KeyframeNumbersSequenceInt32;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceInt32Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceInt64Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceInt64";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceInt64Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFInt64                    StoredFieldType;
    typedef SFInt64                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc> KeyframeNumbersSequenceInt64;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceInt64Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceReal32Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceReal32";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceReal32Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFReal32                    StoredFieldType;
    typedef SFReal32                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc> KeyframeNumbersSequenceReal32;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceReal32Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

struct KeyframeNumbersSequenceReal64Desc : public KeyframeNumbersSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeNumbersSequenceReal64";         }
    static const Char8 *getClassName(void) { return "KeyframeNumbersSequenceReal64Property"; }
    static const Char8 *getFieldName(void) { return "numbers";              }
    static const Char8 *getGroupName(void) { return "KeyframeNumbersSequence";           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeNumbersSequence               Inherited;
    typedef KeyframeNumbersSequence::PtrType      InheritedPtr;

    typedef KeyframeNumbersSequenceDesc   InheritedDesc;

    typedef MFReal64                    StoredFieldType;
    typedef SFReal64                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return lerpKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return splineKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc> KeyframeNumbersSequenceReal64;
#endif

#if !defined(OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeNumbersSequenceReal64Desc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeNumbersSequence.inl"

#endif /* _OSGKEYFRAME_NUMBERS_SEQUENCE_H_ */