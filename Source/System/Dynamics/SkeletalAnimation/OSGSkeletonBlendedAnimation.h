/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#ifndef _OSGSKELETONBLENDEDANIMATION_H_
#define _OSGSKELETONBLENDEDANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkeletonBlendedAnimationBase.h"
#include "OSGSkeletonAnimation.h"
#include "OSGKeyframeAnimator.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonBlendedAnimation class. See \ref
           PageDynamicsSkeletonBlendedAnimation for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonBlendedAnimation : public SkeletonBlendedAnimationBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkeletonBlendedAnimationBase Inherited;
    typedef SkeletonBlendedAnimation     Self;

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
    /**************************************************************************//**
     * @fn	virtual Real32 getCycleLength(void) const
     * 
     * @brief Returns the cycle length of the animation.	
     * 
	  * @return  The cycle length of the animation.
    *****************************************************************************/
	virtual Real32 getCycleLength(void) const;

	/**************************************************************************//**
	 * @fn	void addAnimationBlending(const SkeletonAnimationUnrecPtr TheSkeletonAnimati
	 * 		on, const Real32& BlendAmount)
	 * 
	 * @brief	Adds an animation to this blended animation.
	 * 
	 * @param	TheSkeletonAnimation	The skeleton animation. 
	 * @param	BlendAmount				The blend amount. (0 to 1) 
	 * @param	Override				If true, this skeleton animation will have
	 *									complete control over its animated joints.
	 *									The values of any other attached skeleton
	 *									animations affecting these joints will be
	 *									ignored.
	*****************************************************************************/
	void addAnimationBlending(const SkeletonAnimationUnrecPtr TheSkeletonAnimation, const Real32& BlendAmount, bool Override);

	/**************************************************************************//**
	 * @fn	void setBlendAmount(unsigned int Index, Real32 BlendAmount)
	 * 
	 * @brief	Sets a blend amount for an existing skeleton animation.
	 * 
	 * @param	Index		Zero-based index of the blend amount to be set. 
	 * @param	BlendAmount	The new blend amount. 
	*****************************************************************************/
	void setBlendAmount(unsigned int Index, Real32 BlendAmount);

	/**************************************************************************//**
	 * @fn	bool getOverrideStatus(unsigned int Index)
	 * 
	 * @brief	Gets the override status of an existing skeleton animation. 
	 * 
	 * @param	Index	Zero-based index of the skeleton animation. 
	 * 
	 * @return	The override status of the skeleton animation. 
	*****************************************************************************/
	bool getOverrideStatus(unsigned int Index);

	/**************************************************************************//**
	 * @fn	void setOverrideStatus(unsigned int Index, bool Override)
	 * 
	 * @brief	Sets the override status for an existing skeleton animation. 
	 * 
	 * @param	Index		Zero-based index of the override status to be set. 
	 * @param	Override	The new override status.
	*****************************************************************************/
	void setOverrideStatus(unsigned int Index, bool Override);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonBlendedAnimationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonBlendedAnimation(void);
    SkeletonBlendedAnimation(const SkeletonBlendedAnimation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonBlendedAnimation(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	virtual void internalUpdate(const Real32& t, const Real32 prev_t);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonBlendedAnimationBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonBlendedAnimation &source);
};

typedef SkeletonBlendedAnimation *SkeletonBlendedAnimationP;

OSG_END_NAMESPACE

#include "OSGSkeletonBlendedAnimationBase.inl"
#include "OSGSkeletonBlendedAnimation.inl"

#endif /* _OSGSKELETONBLENDEDANIMATION_H_ */
