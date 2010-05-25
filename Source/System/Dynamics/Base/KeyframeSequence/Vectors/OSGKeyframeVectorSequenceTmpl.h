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

#ifndef _OSGKEYFRME_VECTORS_SEQUENCE_TMPL_H_
#define _OSGKEYFRME_VECTORS_SEQUENCE_TMPL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTBAnimationDef.h"
#include "OSGVecFields.h"
#include "OSGKeyframeVectorSequence.h"

#include <map>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

template <class SequenceDesc>
class KeyframeVectorSequenceTmpl : public KeyframeVectorSequence
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          KeyframeVectorSequence                       Inherited;
    typedef          KeyframeVectorSequence                       ParentContainer;
    
    typedef          SequenceDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          KeyframeVectorSequenceTmpl<SequenceDesc> Self;

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
        SequenceDataFieldId = KeyframeVectorSequence::NextFieldId,

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

    KeyframeVectorSequenceTmpl(void);
    KeyframeVectorSequenceTmpl(const KeyframeVectorSequenceTmpl &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~KeyframeVectorSequenceTmpl(void);

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

struct KeyframeVectorSequenceTmplDescBase
{
    typedef KeyframeVectorSequence       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "KeyframeVectorSequence";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static bool        isBlendable(void) { return true; }
};

/******** Int16 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec2sDescBase : public KeyframeVectorSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec2s";  }

    typedef Vec2s             StoredType;
    typedef MFVec2s           StoredFieldType;
    typedef SFVec2s           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase> KeyframeVectorSequenceVec2s;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2s);

#endif


/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec3sDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec3s";  }

    typedef Vec3s             StoredType;
    typedef MFVec3s           StoredFieldType;
    typedef SFVec3s           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase> KeyframeVectorSequenceVec3s;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3s);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec4sDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec4s";  }

    typedef Vec4s             StoredType;
    typedef MFVec4s           StoredFieldType;
    typedef SFVec4s           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase> KeyframeVectorSequenceVec4s;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4s);

#endif

/******** Real32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec2fDescBase : public KeyframeVectorSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec2f";  }

    typedef Vec2f             StoredType;
    typedef MFVec2f           StoredFieldType;
    typedef SFVec2f           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase> KeyframeVectorSequenceVec2f;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2f);

#endif


/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec3fDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec3f";  }

    typedef Vec3f             StoredType;
    typedef MFVec3f           StoredFieldType;
    typedef SFVec3f           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase> KeyframeVectorSequenceVec3f;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3f);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec4fDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec4f";  }

    typedef Vec4f             StoredType;
    typedef MFVec4f           StoredFieldType;
    typedef SFVec4f           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase> KeyframeVectorSequenceVec4f;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4f);

#endif

/******** Fixed32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec2fxDescBase : public KeyframeVectorSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec2fx";  }

    typedef Vec2fx             StoredType;
    typedef MFVec2fx           StoredFieldType;
    typedef SFVec2fx           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase> KeyframeVectorSequenceVec2fx;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2fx);

#endif


/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec3fxDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec3fx";  }

    typedef Vec3fx             StoredType;
    typedef MFVec3fx           StoredFieldType;
    typedef SFVec3fx           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase> KeyframeVectorSequenceVec3fx;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3fx);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec4fxDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec4fx";  }

    typedef Vec4fx             StoredType;
    typedef MFVec4fx           StoredFieldType;
    typedef SFVec4fx           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase> KeyframeVectorSequenceVec4fx;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4fx);

#endif

/******** Real64 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec2dDescBase : public KeyframeVectorSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec2d";  }

    typedef Vec2d             StoredType;
    typedef MFVec2d           StoredFieldType;
    typedef SFVec2d           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase> KeyframeVectorSequenceVec2d;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2d);

#endif


/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec3dDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec3d";  }

    typedef Vec3d             StoredType;
    typedef MFVec3d           StoredFieldType;
    typedef SFVec3d           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase> KeyframeVectorSequenceVec3d;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3d);

#endif

/*! \brief
    \hideinhierarchy
*/

struct KeyframeVectorSequenceVec4dDescBase : public KeyframeVectorSequenceTmplDescBase
{    
    static const Char8 *getTypeName (void) { return "KeyframeVectorSequenceVec4d";  }

    typedef Vec4d             StoredType;
    typedef MFVec4d           StoredFieldType;
    typedef SFVec4d           SingleFieldType;

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

typedef KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase> KeyframeVectorSequenceVec4d;

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4d);

#endif

OSG_END_NAMESPACE
#include "OSGKeyframeVectorSequenceTmpl.inl"

#endif /* _OSGKEYFRME_VECTORS_SEQUENCE_TMPL_H_ */

