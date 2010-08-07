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

#ifndef _OSGKEYFRAMEFCPTRSEQUENCE_H_
#define _OSGKEYFRAMEFCPTRSEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeFCPtrSequenceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyframeFCPtrSequence class. See \ref
           PageDynamicsKeyframeFCPtrSequence for a description.
*/

class OSG_TBANIMATION_DLLMAPPING KeyframeFCPtrSequence : public KeyframeFCPtrSequenceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef KeyframeFCPtrSequenceBase Inherited;
    typedef KeyframeFCPtrSequence     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */


    virtual FieldContainer* getKeyValue (const UInt32       index )      ;

    virtual FieldContainer* getKeyValue (const UInt32       index ) const;


    virtual void        setKeyframe (FieldContainer* const val,
                                     const Real32 &key,
                                     const UInt32       index )      ;

    virtual void        addKeyframe (FieldContainer* const val,
                                     const Real32 &key   )      ;

    virtual void        insertKeyframe(FieldContainer* const val,
                                       const Real32 &key,
                                       const UInt32 index)           ;

    virtual void        push_back(FieldContainer* const val,
                                  const Real32 &key   );

    virtual UInt32      size       (void) const;
    virtual bool        isBlendable(void) const;

    virtual const Field& getKeyValues(void) const;

    virtual const DataType* getDataType(void) const;

    virtual void        clear    (      void               );

    virtual bool interpolate(UInt32 Type,
                             Real32 time,
                             Real32 prevTime,
                             UInt32 ReplacePolicy,
                             bool isCyclic,
                             EditFieldHandlePtr Result,
                             UInt32 Index,
                             Real32 Blend);

    virtual void zeroField(EditFieldHandlePtr Result, UInt32 Index) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in KeyframeFCPtrSequenceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeFCPtrSequence(void);
    KeyframeFCPtrSequence(const KeyframeFCPtrSequence &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeFCPtrSequence(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    bool isTypeSameAsValues(const DataType& type) const;
    /*==========================  PRIVATE  ================================*/
    DataType *_SequenceDataType;
  private:

    friend class FieldContainer;
    friend class KeyframeFCPtrSequenceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const KeyframeFCPtrSequence &source);
};

typedef KeyframeFCPtrSequence *KeyframeFCPtrSequenceP;

OSG_END_NAMESPACE

#include "OSGKeyframeFCPtrSequenceBase.inl"
#include "OSGKeyframeFCPtrSequence.inl"

#endif /* _OSGKEYFRAMEFCPTRSEQUENCE_H_ */
