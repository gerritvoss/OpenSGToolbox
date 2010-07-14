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

#ifndef _OSGKEYFRME_COLORS_SEQUENCE_TMPL_H_
#define _OSGKEYFRME_COLORS_SEQUENCE_TMPL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTBAnimationDef.h"
#include "OSGVecFields.h"
#include "OSGKeyframeColorSequence.h"

#include <map>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

template <class SequenceDesc>
class KeyframeColorSequenceTmpl : public KeyframeColorSequence
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          KeyframeColorSequence                       Inherited;
    typedef          KeyframeColorSequence                       ParentContainer;
    
    typedef          SequenceDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          KeyframeColorSequenceTmpl<SequenceDesc> Self;

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
        SequenceDataFieldId = KeyframeColorSequence::NextFieldId,

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

    StoredType getRawKeyValue (const UInt32 index );

    StoredType getRawKeyValue (const UInt32 index ) const;

    void       getRawKeyValue (StoredType   &val,
                               const UInt32 index );

    void       getRawKeyValue (StoredType   &val,
                               const UInt32 index ) const;


    void       setRawKeyframe (const StoredType &val,
                               const Real32     &key,
                               const UInt32     index );

    void       addRawKeyframe (const StoredType &val,
                               const Real32     &key );

    void       insertRawKeyframe(const StoredType &val,
                                 const Real32     &key,
                                 const UInt32     index);

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
    virtual void zeroField(EditFieldHandlePtr Result, UInt32 Index) const;

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

    KeyframeColorSequenceTmpl(void);
    KeyframeColorSequenceTmpl(const KeyframeColorSequenceTmpl &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~KeyframeColorSequenceTmpl(void);

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

struct KeyframeColorSequenceTmplDescBase
{
    typedef KeyframeColorSequence       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "KeyframeColorSequence";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static bool        isBlendable(void) { return true; }
};

/******** UInt8 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor3ubDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor3ub";  }

    typedef Color3ub             StoredType;
    typedef MFColor3ub           StoredFieldType;
    typedef SFColor3ub           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase> KeyframeColorSequenceColor3ub;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3ub);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor4ubDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor4ub";  }

    typedef Color4ub             StoredType;
    typedef MFColor4ub           StoredFieldType;
    typedef SFColor4ub           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase> KeyframeColorSequenceColor4ub;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4ub);

#endif

/******** Real32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor3fDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor3f";  }

    typedef Color3f             StoredType;
    typedef MFColor3f           StoredFieldType;
    typedef SFColor3f           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase> KeyframeColorSequenceColor3f;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3f);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor4fDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor4f";  }

    typedef Color4f             StoredType;
    typedef MFColor4f           StoredFieldType;
    typedef SFColor4f           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase> KeyframeColorSequenceColor4f;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4f);

#endif

/******** Fixed32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor3fxDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor3fx";  }

    typedef Color3fx             StoredType;
    typedef MFColor3fx           StoredFieldType;
    typedef SFColor3fx           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase> KeyframeColorSequenceColor3fx;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3fx);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeColorSequenceColor4fxDescBase : public KeyframeColorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeColorSequenceColor4fx";  }

    typedef Color4fx             StoredType;
    typedef MFColor4fx           StoredFieldType;
    typedef SFColor4fx           SingleFieldType;

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

typedef KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase> KeyframeColorSequenceColor4fx;

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4fx);

#endif

OSG_END_NAMESPACE
#include "OSGKeyframeColorSequenceTmpl.inl"

#endif /* _OSGKEYFRME_COLORS_SEQUENCE_TMPL_H_ */

