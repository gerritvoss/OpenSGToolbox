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

#ifndef _OSGKEYFRAMESEQUENCETMPL_H_
#define _OSGKEYFRAMESEQUENCETMPL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include "OSGKeyframeSequenceTmplDesc.h"
#include "Interpolation/OSGKeyframeInterpolations.h"
#include "OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

template <class KeyframeSequenceDesc>
class AbstractKeyframeSequenceTmpl :
    public KeyframeSequenceDesc::Inherited
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef AbstractKeyframeSequenceTmpl<KeyframeSequenceDesc>          PropertyType;

    typedef FCPtr<typename KeyframeSequenceDesc::InheritedPtr,
                           PropertyType                 > PtrType;

    OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*---------------------------------------------------------------------*/
    virtual PtrType clone(void) = 0;

    /*---------------------------------------------------------------------*/
    typedef typename KeyframeSequenceDesc::GenericType          GenericType;


    virtual GenericType getKeyValue (const UInt32       index )       = 0;

    virtual GenericType getKeyValue (const UInt32       index ) const = 0;

    virtual void        getKeyValue (      GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        getKeyValue (      GenericType &val,
                                  const UInt32       index ) const = 0;


    virtual void        setKeyframe (const GenericType &val,
                                          const Real32 &key,
                                  const UInt32       index )       = 0;

    virtual void        addKeyframe (const GenericType &val,
                                          const Real32 &key   )       = 0;

    virtual bool        insertKeyframe(const GenericType &val,
                                          const Real32 &key,
                                    const UInt32 index)            = 0;

    virtual void        push_back(const GenericType &val,
                                          const Real32 &key   )       = 0;


    /*---------------------------------------------------------------------*/
    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

    /*---------------------------------------------------------------------*/
    AbstractKeyframeSequenceTmpl(void);
    AbstractKeyframeSequenceTmpl(const AbstractKeyframeSequenceTmpl &source);

    /*---------------------------------------------------------------------*/
    virtual ~AbstractKeyframeSequenceTmpl(void);

    /*==========================  PRIVATE  ================================*/
  private:       

    // Cannot name type Inherited because of MS compiler probs

    typedef typename KeyframeSequenceDesc::Inherited            LocalInherited;
    typedef typename KeyframeSequenceDesc::InheritedDesc        LocalInheritedDesc;

    static FieldContainerType _type;
};


template <class KeyframeSequenceDesc>
class KeyframeSequenceTmpl :
    public KeyframeSequenceDesc::Inherited
{
    /*==========================  PRIVATE  ================================*/
  private:

    // Cannot name type Inherited because of MS compiler probs

    typedef typename KeyframeSequenceDesc::Inherited     LocalInherited;
    typedef typename KeyframeSequenceDesc::InheritedDesc LocalInheritedDesc;
    typedef typename KeyframeSequenceDesc::InheritedPtr  LocalInheritedPtr;

    /*==========================  PUBLIC  =================================*/
  public:

    enum
    {
        KeyframePropDataFieldId = LocalInherited::NextFieldId,

        NextFieldId        = KeyframePropDataFieldId + 1
    };

    static const BitVector KeyframePropDataFieldMask = 
                                   1 << static_cast<Int32>(KeyframePropDataFieldId);

    typedef KeyframeSequenceTmpl<KeyframeSequenceDesc>         PropertyType;
    typedef KeyframeSequenceTmpl<KeyframeSequenceDesc>         Self;

    typedef FCPtr<LocalInheritedPtr,
                  PropertyType                 > PtrType;


    typedef typename KeyframeSequenceDesc::StoredFieldType     StoredFieldType;
    typedef typename KeyframeSequenceDesc::GenericType         StoredGenericType;
    typedef typename StoredFieldType::StoredType          StoredType;

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    static FieldAccessMethod getFPtrAccessMethod(void);
#endif

    /*---------------------------------------------------------------------*/
          StoredFieldType *getFieldPtr(void);

          StoredFieldType &getField(void);
    const StoredFieldType &getField(void) const;

    virtual const osg::Field& getKeyValues(void) const;

    virtual LocalInheritedPtr clone(void);

    virtual UInt32  getSize      (void) const;
    virtual UInt32  size         (void) const;

            StoredFieldType &operator->() { return _field; }

    virtual StoredGenericType getKeyValue(const UInt32 index);

    virtual StoredGenericType getKeyValue(const UInt32 index) const;

    virtual void              getKeyValue(      StoredGenericType &val,
                                       const UInt32             index);

    virtual void              getKeyValue(      StoredGenericType &val,
                                       const UInt32             index) const;

    virtual void              setKeyframe(const StoredGenericType &val,
                                          const Real32 &key,
                                       const UInt32             index);

    virtual void              addKeyframe(const StoredGenericType &val,
                                          const Real32 &key);

    virtual bool              insertKeyframe(const StoredGenericType &val,
                                          const Real32 &key,
                                          const UInt32 index);
    virtual void    clear();

    virtual void    resize(size_t newsize);

    virtual void    push_back(const StoredGenericType &val,
                                          const Real32 &key);

    virtual void    shrink(void);

    /*---------------------------------------------------------------------*/
    KeyframeSequenceTmpl &operator =(const KeyframeSequenceTmpl &source);

    /*---------------------------------------------------------------------*/
    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    virtual const DataType &getDataType(void) const;

    /*=========================  PROTECTED  ===============================*/    
  protected:

    virtual RawInterpFuncion getStepInterpFuncion(void);
    virtual RawInterpFuncion getLinearInterpFuncion(void);
    virtual RawInterpFuncion getCubicInterpFuncion(void);
    virtual RawInterpFuncion getLinearNormalInterpFuncion(void);
    virtual ReplacementFuncion getReplacementFuncion(void);

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

    StoredFieldType _field;

    /*---------------------------------------------------------------------*/
    KeyframeSequenceTmpl(void);
    KeyframeSequenceTmpl(const KeyframeSequenceTmpl &source);
    
    /*---------------------------------------------------------------------*/
    virtual ~KeyframeSequenceTmpl(void);

    /*---------------------------------------------------------------------*/
#if !defined(OSG_FIXED_MFIELDSYNC)
    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      KeyframeSequenceTmpl *pOther,
                                 const BitVector   &whichField);
#else
    virtual void executeSync       (      FieldContainer &other,
                                    const BitVector      &whichField,
                                    const SyncInfo       &sInfo     );

            void executeSyncImpl   (      KeyframeSequenceTmpl *pOther,
                                    const BitVector   &whichField,
                                    const SyncInfo    &sInfo     );

    virtual void execBeginEdit     (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

            void execBeginEditImpl (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*---------------------------------------------------------------------*/
    virtual void changed        (BitVector whichField, 
                                 UInt32    origin    );
            
    /*---------------------------------------------------------------------*/
    virtual UInt32       getBinSize (const BitVector    &whichField);
    virtual void copyToBin  (      BinaryDataHandler &pMem,
                             const BitVector         &whichField);
    virtual void copyFromBin(      BinaryDataHandler &pMem,
                             const BitVector         &whichField);

    /*==========================  PRIVATE  ================================*/
  private:

    static const PtrType NullPtr;

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
    static FieldDescription   *_desc[];
#endif
    static FieldContainerType  _type;
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractKeyframeSequenceTmpl<KeyframePositionsSequenceDesc> KeyframePositionsSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeVectorsSequenceDesc> KeyframeVectorsSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeRotationsSequenceDesc> KeyframeRotationsSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeTransformationsSequenceDesc> KeyframeTransformationsSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeColorsSequenceDesc> KeyframeColorsSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeNumbersSequenceDesc> KeyframeNumbersSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeDiscreetSequenceDesc> KeyframeDiscreetSequence;
typedef AbstractKeyframeSequenceTmpl<KeyframeFCPtrsSequenceDesc> KeyframeFCPtrsSequence;
#endif

#ifndef OSG_COMPILEKEYFRAMESEQUENCETMPLINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframePositionsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeVectorsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeRotationsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeTransformationsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeColorsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeNumbersSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeDiscreetSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractKeyframeSequenceTmpl,
                            KeyframeFCPtrsSequenceDesc,
                            OSG_ANIMATIONLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGKeyframeSequenceTmplBase.inl"

#endif /* _OSGKEYFRAMESEQUENCETMPL_H_ */


