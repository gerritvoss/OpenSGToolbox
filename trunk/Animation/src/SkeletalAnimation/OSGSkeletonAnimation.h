/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, John Morales                     *
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

#include <OpenSG/OSGConfig.h>

#include "OSGSkeletonAnimationBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonAnimation class. See \ref 
           PageAnimationSkeletonAnimation for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING SkeletonAnimation : public SkeletonAnimationBase
{
  private:

    typedef SkeletonAnimationBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    virtual Real32 getLength(void) const;

	void addTransformationAnimator(KeyframeAnimatorPtr TheAnimator, JointPtr TheJoint);

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

    /**************************************************************************//**
     * @fn	virtual void internalUpdate(const Real32& t, const Real32 prev_t)
     * 
     * @brief	Updates the skeleton animation.
     * 
     * @param	t		
     * @param	prev_t	 
    *****************************************************************************/
    virtual void internalUpdate(const Real32& t, const Real32 prev_t);
	std::map<unsigned long, Matrix> getRelTransformations(const Real32& t, const Real32& prev_t, std::set<JointPtr>& AnimatedJoints);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SkeletonAnimationBase;
	friend class SkeletonBlendedAnimation;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SkeletonAnimation &source);
};

typedef SkeletonAnimation *SkeletonAnimationP;

OSG_END_NAMESPACE

#include "OSGSkeletonAnimationBase.inl"
#include "OSGSkeletonAnimation.inl"

#define OSGSKELETONANIMATION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSKELETONANIMATION_H_ */
