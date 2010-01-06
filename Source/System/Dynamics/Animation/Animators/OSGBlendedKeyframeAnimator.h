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

#ifndef _OSGBLENDEDKEYFRAMEANIMATOR_H_
#define _OSGBLENDEDKEYFRAMEANIMATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBlendedKeyframeAnimatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief BlendedKeyframeAnimator class. See \ref
           PageDynamicsBlendedKeyframeAnimator for a description.
*/

class OSG_DYNAMICS_DLLMAPPING BlendedKeyframeAnimator : public BlendedKeyframeAnimatorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef BlendedKeyframeAnimatorBase Inherited;
    typedef BlendedKeyframeAnimator     Self;

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
    virtual bool animate(UInt32 InterpType,
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

    // Variables should all be in BlendedKeyframeAnimatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BlendedKeyframeAnimator(void);
    BlendedKeyframeAnimator(const BlendedKeyframeAnimator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BlendedKeyframeAnimator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    bool checkSequencesValidity(void) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BlendedKeyframeAnimatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BlendedKeyframeAnimator &source);
};

typedef BlendedKeyframeAnimator *BlendedKeyframeAnimatorP;

OSG_END_NAMESPACE

#include "OSGBlendedKeyframeAnimatorBase.inl"
#include "OSGBlendedKeyframeAnimator.inl"

#endif /* _OSGBLENDEDKEYFRAMEANIMATOR_H_ */
