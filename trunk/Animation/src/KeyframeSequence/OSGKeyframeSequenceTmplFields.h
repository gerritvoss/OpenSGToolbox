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
#ifndef _OSGKEYFRAMEFIELDS_H_
#define _OSGKEYFRAMEFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"

OSG_BEGIN_NAMESPACE

typedef KeyframePositionsSequence::PtrType KeyframePositionsSequencePtr;
typedef KeyframeVectorsSequence::PtrType KeyframeVectorsSequencePtr;
typedef KeyframeRotationsSequence::PtrType KeyframeRotationsSequencePtr;
typedef KeyframeTransformationsSequence::PtrType KeyframeTransformationsSequencePtr;
typedef KeyframeColorsSequence::PtrType KeyframeColorsSequencePtr;
typedef KeyframeNumbersSequence::PtrType KeyframeNumbersSequencePtr;
typedef KeyframeDiscreetSequence::PtrType KeyframeDiscreetSequencePtr;
typedef KeyframeFCPtrsSequence::PtrType KeyframeFCPtrsSequencePtr;


typedef RefPtr<KeyframePositionsSequencePtr> KeyframePositionsSequenceRefPtr;
typedef RefPtr<KeyframeVectorsSequencePtr> KeyframeVectorsSequenceRefPtr;
typedef RefPtr<KeyframeRotationsSequencePtr> KeyframeRotationsSequenceRefPtr;
typedef RefPtr<KeyframeTransformationsSequencePtr> KeyframeTransformationsSequenceRefPtr;
typedef RefPtr<KeyframeColorsSequencePtr> KeyframeColorsSequenceRefPtr;
typedef RefPtr<KeyframeNumbersSequencePtr> KeyframeNumbersSequenceRefPtr;
typedef RefPtr<KeyframeDiscreetSequencePtr> KeyframeDiscreetSequenceRefPtr;
typedef RefPtr<KeyframeFCPtrsSequencePtr> KeyframeFCPtrsSequenceRefPtr;


#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

template <>
struct FieldDataTraits<KeyframePositionsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframePositionsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframePositionsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframePositionsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframePositionsSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeVectorsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeVectorsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeVectorsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeVectorsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeVectorsSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeRotationsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeRotationsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeRotationsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeRotationsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeRotationsSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeTransformationsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeTransformationsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeTransformationsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeTransformationsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeTransformationsSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeColorsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeColorsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeColorsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeColorsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeColorsSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeNumbersSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeNumbersSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeNumbersSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeNumbersSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeNumbersSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeDiscreetSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeDiscreetSequencePtr, true>
{
    //---------------------------------------------------------------------//
    typedef FieldDataTraits<KeyframeDiscreetSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    //---------------------------------------------------------------------//
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeDiscreetSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeDiscreetSequencePtr"; }

};

template <>
struct FieldDataTraits<KeyframeFCPtrsSequencePtr> :
    public FieldTraitsRecurseMapper<KeyframeFCPtrsSequencePtr, true>
{
    /*---------------------------------------------------------------------*/
    typedef FieldDataTraits<KeyframeFCPtrsSequencePtr>  Self;
    static  DataType                         _type;

    enum           { StringConvertable = Self::ToStringConvertable };
    enum           { bHasParent        = 0x01                      };

    /*---------------------------------------------------------------------*/
    static DataType &getType  (void) { return _type;               }
    static Char8    *getSName (void) { return "SFKeyframeFCPtrsSequencePtr"; }
    static Char8    *getMName (void) { return "MFKeyframeFCPtrsSequencePtr"; }

};

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)

typedef SField<KeyframePositionsSequencePtr> SFKeyframePositionsSequencePtr;
typedef SField<KeyframeVectorsSequencePtr> SFKeyframeVectorsSequencePtr;
typedef SField<KeyframeRotationsSequencePtr> SFKeyframeRotationsSequencePtr;
typedef SField<KeyframeTransformationsSequencePtr> SFKeyframeTransformationsSequencePtr;
typedef SField<KeyframeColorsSequencePtr> SFKeyframeColorsSequencePtr;
typedef SField<KeyframeNumbersSequencePtr> SFKeyframeNumbersSequencePtr;
typedef SField<KeyframeDiscreetSequencePtr> SFKeyframeDiscreetSequencePtr;
typedef SField<KeyframeFCPtrsSequencePtr> SFKeyframeFCPtrsSequencePtr;

typedef MField<KeyframePositionsSequencePtr> MFKeyframePositionsSequencePtr;
typedef MField<KeyframeVectorsSequencePtr> MFKeyframeVectorsSequencePtr;
typedef MField<KeyframeRotationsSequencePtr> MFKeyframeRotationsSequencePtr;
typedef MField<KeyframeTransformationsSequencePtr> MFKeyframeTransformationsSequencePtr;
typedef MField<KeyframeColorsSequencePtr> MFKeyframeColorsSequencePtr;
typedef MField<KeyframeNumbersSequencePtr> MFKeyframeNumbersSequencePtr;
typedef MField<KeyframeDiscreetSequencePtr> MFKeyframeDiscreetSequencePtr;
typedef MField<KeyframeFCPtrsSequencePtr> MFKeyframeFCPtrsSequencePtr;
#endif

#ifndef OSG_COMPILEKEYFRAMESEQUENCETMPLFIELDINST
OSG_DLLEXPORT_DECL1(SField, KeyframePositionsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframePositionsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeVectorsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeVectorsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeRotationsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeRotationsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeTransformationsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeTransformationsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeColorsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeColorsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeNumbersSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeNumbersSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeDiscreetSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeDiscreetSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

OSG_DLLEXPORT_DECL1(SField, KeyframeFCPtrsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)
OSG_DLLEXPORT_DECL1(MField, KeyframeFCPtrsSequencePtr, OSG_ANIMATIONLIB_DLLMAPPING)

#endif

OSG_END_NAMESPACE

#endif /* _OSGKEYFRAMEFIELDS_H_ */

