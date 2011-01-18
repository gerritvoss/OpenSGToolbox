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

#ifndef _OSGANIMATOR_H_
#define _OSGANIMATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimatorBase.h"

OSG_BEGIN_NAMESPACE

class OSG_TBANIMATION_DLLMAPPING Animator : public AnimatorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    /*! 
     * Enumeration for the interpolation method used by animators.
     */
    enum InterpolationType
    {
        LINEAR_INTERPOLATION           =1,  /*!< Linear interpolation */
        CUBIC_INTERPOLATION            =2,  /*!< Cubic interpolation */
        STEP_INTERPOLATION             =4,  /*!< Step interpolation */
        LINEAR_NORMAL_INTERPOLATION    =8,  /*!< Linear normal  interpolation */
        SPHERICAL_LINEAR_INTERPOLATION =16, /*!< Spherical linear interpolation */
        NORMALIZED_LINEAR_INTERPOLATION=32  /*!< Normalized linear interpolation */
    };

    /*! 
     * Enumeration for the replacement policy to use when applying the
     * result of an animator to the value it is attached to.
     */
    enum ValueReplacementPolicy
    {
        OVERWRITE          =1, /*!< Overwrite the current value */
        ADDITIVE_ABSOLUTE  =2, /*!< Add the result with the value */
        ADDITIVE_SINCE_LAST=4  /*!< Add the difference of the previous result and
                                 the current result with the value */
    };

    typedef AnimatorBase Inherited;
    typedef Animator     Self;

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
                         Real32 time,
                         Real32 PrevTime,
                         EditFieldHandlePtr Result,
                         UInt32 Index = 0) = 0;
                      
    virtual Real32 getLength(void) const = 0;

    virtual const DataType* getDataType(void) const = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Animator(void);
    Animator(const Animator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Animator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimatorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Animator &source);
};

typedef Animator *AnimatorP;

OSG_END_NAMESPACE

#include "OSGAnimatorBase.inl"
#include "OSGAnimator.inl"

#endif /* _OSGANIMATOR_H_ */
