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

#ifndef _OSGSKELETON_H_
#define _OSGSKELETON_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGSkeletonBase.h"
#include "Events/OSGSkeletonListener.h"
#include <set>
#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief Skeleton class. See \ref 
           PageAnimationSkeleton for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING Skeleton : public SkeletonBase
{
  private:

    typedef SkeletonBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /**************************************************************************//**
     * @fn	EventConnection addSkeletonListener(SkeletonListenerPtr Listener)
     * 
     * @brief	Adds a skeleton listener to this instance. 
     * 
     * @param	Listener	The listener to add. 
     * 
     * @return	
    *****************************************************************************/
    EventConnection addSkeletonListener(SkeletonListenerPtr Listener);

    /**************************************************************************//**
     * @fn	bool isSkeletonListenerAttached(SkeletonListenerPtr Listener) const
     * 
     * @brief	Query if skeleton listener 'Listener' is attached to this instance. 
     * 
     * @param	Listener	The listener. 
     * 
     * @return	true if skeleton listener attached, false if not. 
    *****************************************************************************/
    bool isSkeletonListenerAttached(SkeletonListenerPtr Listener) const;

    /**************************************************************************//**
     * @fn	void removeSkeletonListener(SkeletonListenerPtr Listener)
     * 
     * @brief	Removes the skeleton listener described by Listener. 
     * 
     * @param	Listener	The listener to remove. 
    *****************************************************************************/
    void removeSkeletonListener(SkeletonListenerPtr Listener);

	/**************************************************************************//**
	 * @fn	void setJointParentSkeleton(JointPtr TheJoint)
	 * 
	 * @brief	Sets a TheJoint's parent skeleton to this instance and recursively
	 *			does the same for all of TheJoint's descendants.
	 * 
	 * @param	The joint to update.
	*****************************************************************************/
	void setJointParentSkeleton(JointPtr TheJoint);
	//void updateBlendedGeometry();

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

    /**************************************************************************//**
     * @fn	void skeletonUpdated(void)
     * 
     * @brief	Skeleton updated.
    *****************************************************************************/
    void skeletonUpdated(void);

    /**************************************************************************//**
     * @fn	void updateJointTransformations(void)
     * 
     * @brief	Updates the transformations of all joints in this skeleton. 
    *****************************************************************************/
    void updateJointTransformations(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SkeletonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Skeleton(void);
    Skeleton(const Skeleton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Skeleton(void); 

    /*! \}                                                                 */
	typedef std::set<SkeletonListenerPtr> SkeletonListenerSet;
    typedef SkeletonListenerSet::iterator SkeletonListenerSetItor;
    typedef SkeletonListenerSet::const_iterator SkeletonListenerSetConstItor;
	
    SkeletonListenerSet       _SkeletonListeners;

	void produceChangedEvent(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SkeletonBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Skeleton &source);
};

typedef Skeleton *SkeletonP;

OSG_END_NAMESPACE

#include "OSGSkeletonBase.inl"
#include "OSGSkeleton.inl"

#define OSGSKELETON_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSKELETON_H_ */


