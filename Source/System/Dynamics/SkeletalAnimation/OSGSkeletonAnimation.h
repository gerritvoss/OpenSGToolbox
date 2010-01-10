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

#ifndef _OSGSKELETONANIMATION_H_
#define _OSGSKELETONANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGJoint.h"
#include "OSGSkeleton.h"
#include "OSGKeyframeAnimator.h"
#include "OSGSkeletonAnimationBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonAnimation class. See \ref
           PageDynamicsSkeletonAnimation for a description.
*/

class OSG_DYNAMICS_DLLMAPPING SkeletonAnimation : public SkeletonAnimationBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkeletonAnimationBase Inherited;
    typedef SkeletonAnimation     Self;

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
     * @fn	void addTransformationAnimator(KeyframeAnimatorUnrecPtr TheAnimator, JointUnrecPtr TheJoint);
     * 
     * @brief Adds the supplied animator to the specified joint in the skeleton. 
     * 
     * @param  TheAnimator The animator to attach.
     * @param	TheJoint	The joint to be animated by TheAnimator
     *****************************************************************************/
    void addTransformationAnimator(KeyframeAnimatorUnrecPtr TheAnimator, JointUnrecPtr TheJoint);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonAnimationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonAnimation(void);
    SkeletonAnimation(const SkeletonAnimation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonAnimation(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /**************************************************************************//**
     * @fn	virtual void internalUpdate(const Real32& t, const Real32 prev_t)
     * 
     * @brief	Updates the skeleton animation.
     * 
     * @param	t		
     * @param	prev_t	 
     *****************************************************************************/
    virtual void internalUpdate(const Real32& t, const Real32 prev_t);

    /**************************************************************************//**
     * @fn	std::map<unsigned long, Matrix> getRelTransformations
     * (const Real32& t, const Real32& prev_t, std::set<JointUnrecPtr>& AnimatedJoints);
     * 
     * @brief Retrieves the relative transformation for each joint that is animated
     * 		  in this step of the animation.
     * 
     * @param	t		
     * @param	prev_t	 
     * @param  AnimatedJoints  A set of all joints animated at this time in the
     * 								 animation.
     *
     * @return  A map from joint field container IDs to relative trans matrices 
     *****************************************************************************/
    std::map<unsigned long, Matrix> getRelTransformations(const Real32& t, const Real32& prev_t, std::set<JointUnrecPtr>& AnimatedJoints);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonBlendedAnimation;
    friend class SkeletonAnimationBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonAnimation &source);
};

typedef SkeletonAnimation *SkeletonAnimationP;

OSG_END_NAMESPACE

#include "OSGSkeletonAnimationBase.inl"
#include "OSGSkeletonAnimation.inl"

#endif /* _OSGSKELETONANIMATION_H_ */
