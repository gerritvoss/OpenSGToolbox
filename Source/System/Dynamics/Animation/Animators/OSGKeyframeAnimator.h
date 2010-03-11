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

#ifndef _OSGKEYFRAMEANIMATOR_H_
#define _OSGKEYFRAMEANIMATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGInterpolations.h"
#include "OSGKeyframeSequence.h"

#include "OSGKeyframeAnimatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyframeAnimator class. See \ref
           PageDynamicsKeyframeAnimator for a description.
*/

class OSG_TBANIMATION_DLLMAPPING KeyframeAnimator : public KeyframeAnimatorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef KeyframeAnimatorBase Inherited;
    typedef KeyframeAnimator     Self;

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
    
    bool animate(UInt32 InterpType,
                 UInt32 ReplacementPolicy,
                 bool Cycling,
                 const Real32& time,
                 const Real32& prevTime,
                 EditFieldHandlePtr Result,
                 UInt32 Index = 0);
    
    virtual Real32 getLength(void) const;

    virtual const DataType &getDataType(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in KeyframeAnimatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeAnimator(void);
    KeyframeAnimator(const KeyframeAnimator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeAnimator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class KeyframeAnimatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const KeyframeAnimator &source);
};

typedef KeyframeAnimator *KeyframeAnimatorP;

OSG_END_NAMESPACE

#include "OSGKeyframeAnimatorBase.inl"
#include "OSGKeyframeAnimator.inl"

#endif /* _OSGKEYFRAMEANIMATOR_H_ */
