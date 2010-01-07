/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPL_H_
#define _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsDef.h"
#include "OSGVecFields.h"
#include "OSGKeyframeTransformationSequence.h"

#include <map>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

template <class SequenceDesc>
class KeyframeTransformationSequenceTmpl : public KeyframeTransformationSequence
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          KeyframeTransformationSequence                       Inherited;
    typedef          KeyframeTransformationSequence                       ParentContainer;
    
    typedef          SequenceDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          KeyframeTransformationSequenceTmpl<SequenceDesc> Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename SequenceDesc::StoredType      StoredType;
    typedef typename SequenceDesc::StoredFieldType StoredFieldType;

    typedef typename StoredFieldType::EditHandle      StoredEditHandle;
    typedef typename StoredFieldType::EditHandlePtr   StoredEditHandlePtr;
    typedef typename StoredFieldType::GetHandle       StoredGetHandle;
    typedef typename StoredFieldType::GetHandlePtr    StoredGetHandlePtr;

    typedef typename StoredFieldType::reference       reference;
    typedef typename StoredFieldType::const_reference const_reference;

    typedef typename SequenceDesc::ConcreteInterpFunction ConcreteInterpFunction;
    typedef typename SequenceDesc::InterpolationFuncMap InterpolationFuncMap;

    enum
    {
        SequenceDataFieldId = KeyframeTransformationSequence::NextFieldId,

        NextFieldId        = SequenceDataFieldId + 1
    };

    static const BitVector SequenceDataFieldMask = 
                           1 << static_cast<Int32>(SequenceDataFieldId);

    OSG_FIELD_CONTAINER_TMPL_DECL;

    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

          StoredFieldType *editFieldPtr(void);
    const StoredFieldType *getFieldPtr (void) const;

          StoredFieldType &editField   (void);
    const StoredFieldType &getField    (void) const;

    virtual GenericType getKeyValue (const UInt32       index )      ;

    virtual GenericType getKeyValue (const UInt32       index ) const;

    virtual void        getKeyValue (      GenericType &val,
                                  const UInt32       index )      ;

    virtual void        getKeyValue (      GenericType &val,
                                  const UInt32       index ) const;


    virtual void        setKeyframe (const GenericType &val,
                                          const Real32 &key,
                                  const UInt32       index )      ;

    virtual void        addKeyframe (const GenericType &val,
                                          const Real32 &key   )      ;

    virtual void        insertKeyframe(const GenericType &val,
                                          const Real32 &key,
                                    const UInt32 index)           ;

    virtual void        push_back(const GenericType &val,
                                          const Real32 &key   );

    virtual UInt32      size       (void) const;
    virtual bool        isBlendable(void) const;

    virtual const Field& getKeyValues(void) const;
    
    virtual const DataType &getDataType(void) const;

    virtual void        clear    (      void               );
    virtual void        resize   (      size_t      newsize);
    virtual void        shrink   (void                     );

    bool interpolate(const UInt32& Type, const Real32& time, const Real32& prevTime, const UInt32& ReplacePolicy, bool isCyclic, Field& Result, UInt32 Index, Real32 Blend);
    virtual void zeroField(Field& Result, UInt32 Index) const;

    //virtual       SequenceTransitPtr  clone        (void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent,
                      const BitVector bvFlags ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/    
  protected:

    friend class FieldContainer;

    StoredFieldType _field;

    virtual RawInterpFuncion bindInterpFunction(UInt32 InterpolationFunctionId) const;
    virtual ReplacementFuncion getReplacementFuncion(void) const;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    KeyframeTransformationSequenceTmpl(void);
    KeyframeTransformationSequenceTmpl(const KeyframeTransformationSequenceTmpl &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~KeyframeTransformationSequenceTmpl(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual ObjCPtr createAspectCopy(const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */
    
#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      Self              *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    EditFieldHandlePtr editHandleField(void);
    GetFieldHandlePtr  getHandleField (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void changed        (ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         detail);
            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    //void onCreate(const Self                 *p = NULL);
    //void onDestroy(     UInt32 uiContainerId          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Binary Operations                       */
    /*! \{                                                                 */

    virtual UInt32 getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    Self &operator =(const Self &source);

    static void classDescInserter(TypeObject &oType);

    static void initMethod(InitPhase ePhase);
    static void exitMethod(InitPhase ePhase);

//    static const ObjPtr NullPtr;

    static TypeObject  _type;
};

struct KeyframeTransformationSequenceTmplDescBase
{
    typedef KeyframeTransformationSequence       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "KeyframeTransformationSequence";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static bool        isBlendable(void) { return true; }
};

/******** Real32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeTransformationSequenceMatrix4fDescBase : public KeyframeTransformationSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeTransformationSequenceMatrix4f";  }

    typedef Matrix4f             StoredType;
    typedef MFMatrix           StoredFieldType;
    typedef SFMatrix           SingleFieldType;

    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;
    typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    static InterpolationFuncMap _interpolationFuncs;

    static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}

    static void initMethod(InitPhase ePhase)
    {
        if(ePhase == TypeObject::SystemPost)
        {
            _interpolationFuncs[Animator::STEP_INTERPOLATION] = stepKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::CUBIC_INTERPOLATION] = splineKeyframeSequence<StoredFieldType,SingleFieldType>;
        }
    }
};

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

typedef KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase> KeyframeTransformationSequenceMatrix4f;

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4f);

#endif

/******** Fixed32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeTransformationSequenceMatrix4fxDescBase : public KeyframeTransformationSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeTransformationSequenceMatrix4fx";  }

    typedef Matrix4fx             StoredType;
    typedef MFMatrix4fx           StoredFieldType;
    typedef SFMatrix4fx           SingleFieldType;

    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;
    typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    static InterpolationFuncMap _interpolationFuncs;

    static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}

    static void initMethod(InitPhase ePhase)
    {
        if(ePhase == TypeObject::SystemPost)
        {
            _interpolationFuncs[Animator::STEP_INTERPOLATION] = stepKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::CUBIC_INTERPOLATION] = splineKeyframeSequence<StoredFieldType,SingleFieldType>;
        }
    }
};

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

typedef KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase> KeyframeTransformationSequenceMatrix4fx;

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4fx);

#endif

/******** Real64 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeTransformationSequenceMatrix4dDescBase : public KeyframeTransformationSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeTransformationSequenceMatrix4d";  }

    typedef Matrix4d             StoredType;
    typedef MFMatrix4d           StoredFieldType;
    typedef SFMatrix4d           SingleFieldType;

    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;
    typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    static InterpolationFuncMap _interpolationFuncs;

    static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}

    static void initMethod(InitPhase ePhase)
    {
        if(ePhase == TypeObject::SystemPost)
        {
            _interpolationFuncs[Animator::STEP_INTERPOLATION] = stepKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            _interpolationFuncs[Animator::CUBIC_INTERPOLATION] = splineKeyframeSequence<StoredFieldType,SingleFieldType>;
        }
    }
};

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

typedef KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase> KeyframeTransformationSequenceMatrix4d;

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4d);

#endif

OSG_END_NAMESPACE
#include "OSGKeyframeTransformationSequenceTmpl.inl"

#endif /* _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPL_H_ */

