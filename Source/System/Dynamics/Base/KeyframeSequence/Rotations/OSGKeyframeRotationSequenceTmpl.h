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

#ifndef _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPL_H_
#define _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTBAnimationDef.h"
#include "OSGMathFields.h"
#include "OSGKeyframeRotationSequence.h"

#include <map>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

template <class SequenceDesc>
class KeyframeRotationSequenceTmpl : public KeyframeRotationSequence
{
    /*==========================  PRIVATE  ================================*/

  private:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef          KeyframeRotationSequence                       Inherited;
    typedef          KeyframeRotationSequence                       ParentContainer;
    
    typedef          SequenceDesc                           PropDesc;

    typedef typename Inherited::TypeObject                     TypeObject;
    typedef typename TypeObject::InitPhase                     InitPhase;

    typedef          KeyframeRotationSequenceTmpl<SequenceDesc> Self;

    OSG_GEN_INTERNALPTR(Self);

    typedef typename SequenceDesc::StoredType      StoredType;
    typedef typename SequenceDesc::StoredFieldType StoredFieldType;
    typedef typename SequenceDesc::SingleFieldType SingleFieldType;

    typedef typename StoredFieldType::EditHandle      StoredEditHandle;
    typedef typename StoredFieldType::EditHandlePtr   StoredEditHandlePtr;
    typedef typename StoredFieldType::GetHandle       StoredGetHandle;
    typedef typename StoredFieldType::GetHandlePtr    StoredGetHandlePtr;

    typedef typename StoredFieldType::reference       reference;
    typedef typename StoredFieldType::const_reference const_reference;

    typedef typename SequenceDesc::ConcreteInterpFunction  ConcreteInterpFunction;
    typedef typename SequenceDesc::ConcreteReplaceFunction ConcreteReplaceFunction;

    enum
    {
        SequenceDataFieldId = KeyframeRotationSequence::NextFieldId,

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
    
    virtual const DataType* getDataType(void) const;

    virtual void        clear    (      void               );
    virtual void        resize   (      size_t      newsize);
    virtual void        shrink   (void                     );

    virtual bool interpolate(UInt32 Type,
                             Real32 time,
                             Real32 prevTime,
                             UInt32 ReplacePolicy,
                             bool isCyclic,
                             EditFieldHandlePtr Result,
                             UInt32 Index,
                             Real32 Blend);

    virtual void zeroField(EditFieldHandlePtr Result, UInt32 Index) const;

    bool interpolate(UInt32 Type,
                     Real32 time,
                     Real32 prevTime,
                     UInt32 ReplacePolicy,
                     bool isCyclic,
                     StoredType& Result,
                     Real32 Blend);

    void zeroField(StoredType& Result) const;

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

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    KeyframeRotationSequenceTmpl(void);
    KeyframeRotationSequenceTmpl(const KeyframeRotationSequenceTmpl &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~KeyframeRotationSequenceTmpl(void);

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

struct KeyframeRotationSequenceTmplDescBase
{
    typedef KeyframeRotationSequence       PropertParent;
    
    typedef PropertParent::TypeObject TypeObject;
    typedef TypeObject::InitPhase     InitPhase;

    static const Char8 *getGroupName (void) 
    {
        return "KeyframeRotationSequence";  
    }

    static void initMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}
    static void exitMethod(InitPhase OSG_CHECK_ARG(ePhase)) {}

    static bool        isBlendable(void) { return true; }
};

/******** Real32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeRotationSequenceQuaternionDescBase : public KeyframeRotationSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeRotationSequenceQuaternion";  }

    typedef Quaternion             StoredType;
    typedef MFQuaternion           StoredFieldType;
    typedef SFQuaternion           SingleFieldType;

    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, Real32, StoredType& , bool )> ConcreteInterpFunction;
    typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    typedef boost::function<bool (Real32, StoredType& , bool)> InterpReplaceFunction;
    typedef boost::function<bool (InterpReplaceFunction,
                                  Real32,
                                  Real32,
                                  bool,
                                  StoredType& Result,
                                  Real32)> ConcreteReplaceFunction;

    typedef std::map<UInt32, ConcreteReplaceFunction> ReplaceFuncMap;

    static InterpolationFuncMap _interpolationFuncs;
    static ReplaceFuncMap _replacementFuncs;

    static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}
    static ReplaceFuncMap &getReplacementFuncMap(void) { return _replacementFuncs;}

    static void initMethod(InitPhase ePhase);
};

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

typedef KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase> KeyframeRotationSequenceQuaternion;

OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaternion);

#endif


/******** Fixed32 *******/
/*! \brief
    \hideinhierarchy
*/

struct KeyframeRotationSequenceQuaternionfxDescBase : public KeyframeRotationSequenceTmplDescBase
{    

    static const Char8 *getTypeName (void) { return "KeyframeRotationSequenceQuaternionfx";  }

    typedef Quaternionfx             StoredType;
    typedef MFQuaternionfx           StoredFieldType;
    typedef SFQuaternionfx           SingleFieldType;

    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, Real32, StoredType& , bool )> ConcreteInterpFunction;
    typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    typedef boost::function<bool (Real32, StoredType& , bool)> InterpReplaceFunction;
    typedef boost::function<bool (InterpReplaceFunction,
                                  Real32,
                                  Real32,
                                  bool,
                                  StoredType& Result,
                                  Real32)> ConcreteReplaceFunction;

    typedef std::map<UInt32, ConcreteReplaceFunction> ReplaceFuncMap;

    static InterpolationFuncMap _interpolationFuncs;
    static ReplaceFuncMap _replacementFuncs;

    static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}
    static ReplaceFuncMap &getReplacementFuncMap(void) { return _replacementFuncs;}

    static void initMethod(InitPhase ePhase);
};

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

typedef KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase> KeyframeRotationSequenceQuaternionfx;

OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaternionfx);

#endif


/******** Real64 *******/
/*! \brief
    \hideinhierarchy
*/

//struct KeyframeRotationSequenceQuaterniondDescBase : public KeyframeRotationSequenceTmplDescBase
//{    

    //static const Char8 *getTypeName (void) { return "KeyframeRotationSequenceQuaterniond";  }

    //typedef Quaterniond             StoredType;
    //typedef MFQuaterniond           StoredFieldType;
    //typedef SFQuaterniond           SingleFieldType;

    //typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;
    //typedef std::map<UInt32, ConcreteInterpFunction> InterpolationFuncMap;

    //static InterpolationFuncMap _interpolationFuncs;

    //static InterpolationFuncMap &getInterpolationFuncMap(void) { return _interpolationFuncs;}

    //static void initMethod(InitPhase ePhase)
    //{
        //if(ePhase == TypeObject::SystemPost)
        //{
            //_interpolationFuncs[Animator::STEP_INTERPOLATION] = stepKeyframeSequence<StoredFieldType,SingleFieldType>;
            //_interpolationFuncs[Animator::LINEAR_INTERPOLATION] = slerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            //_interpolationFuncs[Animator::SPHERICAL_LINEAR_INTERPOLATION] = slerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            //_interpolationFuncs[Animator::NORMALIZED_LINEAR_INTERPOLATION] = nlerpKeyframeSequence<StoredFieldType,SingleFieldType>;
            //_interpolationFuncs[Animator::CUBIC_INTERPOLATION] = squadKeyframeSequence<StoredFieldType,SingleFieldType>;
        //}
    //}

//};

//#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles

//typedef KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase> KeyframeRotationSequenceQuaterniond;

//OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaterniond);

//#endif



OSG_END_NAMESPACE
#include "OSGKeyframeRotationSequenceTmpl.inl"

#endif /* _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPL_H_ */

