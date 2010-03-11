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

#ifndef _OSGKEYFRME_NUMBERS_SEQUENCE_TMPL_H_
#define _OSGKEYFRME_NUMBERS_SEQUENCE_TMPL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTBAnimationDef.h"
#include "OSGVecFields.h"
#include "OSGKeyframeNumberSequence.h"

#include <map>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

template <class SequenceDesc>
class KeyframeNumberSequenceTmpl : public KeyframeNumberSequence
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          KeyframeNumberSequence                       Inherited;
    typedef          KeyframeNumberSequence                       ParentContainer;
    
    typedef          SequenceDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          KeyframeNumberSequenceTmpl<SequenceDesc> Self;

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
        SequenceDataFieldId = KeyframeNumberSequence::NextFieldId,

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

    KeyframeNumberSequenceTmpl(void);
    KeyframeNumberSequenceTmpl(const KeyframeNumberSequenceTmpl &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~KeyframeNumberSequenceTmpl(void);

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

struct KeyframeNumberSequenceTmplDescBase
{
    typedef KeyframeNumberSequence       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "KeyframeNumberSequence";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static bool        isBlendable(void) { return true; }
};

/******** Unsigned Integers *******/
/*! \brief UInt8 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceUInt8DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceUInt8";  }

    typedef UInt8             StoredType;
    typedef MFUInt8           StoredFieldType;
    typedef SFUInt8           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase> KeyframeNumberSequenceUInt8;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt8);

#endif

/*! \brief UInt16 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceUInt16DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceUInt16";  }

    typedef UInt16             StoredType;
    typedef MFUInt16           StoredFieldType;
    typedef SFUInt16           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase> KeyframeNumberSequenceUInt16;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt16);

#endif

/*! \brief UInt32 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceUInt32DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceUInt32";  }

    typedef UInt32             StoredType;
    typedef MFUInt32           StoredFieldType;
    typedef SFUInt32           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase> KeyframeNumberSequenceUInt32;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt32);

#endif

/*! \brief UInt64 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceUInt64DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceUInt64";  }

    typedef UInt64             StoredType;
    typedef MFUInt64           StoredFieldType;
    typedef SFUInt64           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase> KeyframeNumberSequenceUInt64;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt64);

#endif

/******** Signed Integers *******/
/*! \brief Int8 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceInt8DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceInt8";  }

    typedef Int8             StoredType;
    typedef MFInt8           StoredFieldType;
    typedef SFInt8           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase> KeyframeNumberSequenceInt8;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt8);

#endif

/*! \brief Int16 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceInt16DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceInt16";  }

    typedef Int16             StoredType;
    typedef MFInt16           StoredFieldType;
    typedef SFInt16           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase> KeyframeNumberSequenceInt16;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt16);

#endif

/*! \brief Int32 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceInt32DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceInt32";  }

    typedef Int32             StoredType;
    typedef MFInt32           StoredFieldType;
    typedef SFInt32           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase> KeyframeNumberSequenceInt32;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt32);

#endif

/*! \brief Int64 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceInt64DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceInt64";  }

    typedef Int64             StoredType;
    typedef MFInt64           StoredFieldType;
    typedef SFInt64           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase> KeyframeNumberSequenceInt64;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt64);

#endif

/******** Real Numbers *******/
/*! \brief Real16 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceReal16DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceReal16";  }

    typedef Real16             StoredType;
    typedef MFReal16           StoredFieldType;
    typedef SFReal16           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase> KeyframeNumberSequenceReal16;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal16);

#endif

/*! \brief Real32 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceReal32DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceReal32";  }

    typedef Real32             StoredType;
    typedef MFReal32           StoredFieldType;
    typedef SFReal32           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase> KeyframeNumberSequenceReal32;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal32);

#endif

/*! \brief Fixed32 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceFixed32DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceFixed32";  }

    typedef Fixed32             StoredType;
    typedef MFFixed32           StoredFieldType;
    typedef SFFixed32           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase> KeyframeNumberSequenceFixed32;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceFixed32);

#endif

/*! \brief Real64 KeyframeSequence
    \hideinhierarchy
*/

struct KeyframeNumberSequenceReal64DescBase : public KeyframeNumberSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeNumberSequenceReal64";  }

    typedef Real64             StoredType;
    typedef MFReal64           StoredFieldType;
    typedef SFReal64           SingleFieldType;

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

typedef KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase> KeyframeNumberSequenceReal64;

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal64);

#endif


OSG_END_NAMESPACE
#include "OSGKeyframeNumberSequenceTmpl.inl"

#endif /* _OSGKEYFRME_NUMBERS_SEQUENCE_TMPL_H_ */

