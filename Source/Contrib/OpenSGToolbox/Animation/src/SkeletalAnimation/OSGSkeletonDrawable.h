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

#ifndef _OSGSKELETONDRAWABLE_H_
#define _OSGSKELETONDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGSkeletonDrawableBase.h"
#include "OSGJointFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonDrawable class. See \ref 
           PageAnimationSkeletonDrawable for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING SkeletonDrawable : public SkeletonDrawableBase
{
  private:

    typedef SkeletonDrawableBase Inherited;

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
    /**************************************************************************//**
     * @fn Action::ResultE drawPrimitives (DrawActionBase *action)
     * 
     * @brief Draws a bone between each parent-child joint pair. 
	  *
	  * @param action
     * 
	  * @return  Result
    *****************************************************************************/
    Action::ResultE drawPrimitives (DrawActionBase *action);
    
	 /**************************************************************************//**
     * @fn Action::ResultE drawActionHandler( Action* action )
     * 
     * @brief  
     * 
	  * @param action
	  *
	  * @return  Result
    *****************************************************************************/
    Action::ResultE drawActionHandler( Action* action );
	 
	 /**************************************************************************//**
     * @fn Action::ResultE renderActionHandler( Action* action )
     * 
     * @brief  
	  *
	  * @param action
     * 
	  * @return  Result
    *****************************************************************************/
    Action::ResultE renderActionHandler( Action* action );
	 
	 /**************************************************************************//**
     * @fn Action::ResultE intersect( Action* action )
     * 
     * @brief  
	  *
	  * @param action
     * 
	  * @return  Result
    *****************************************************************************/
    Action::ResultE intersect( Action* action );
    /*=========================  PROTECTED  ===============================*/
  protected:
	Pnt3f _lastEndPoint;
	Pnt3f _lastStartPoint;
	Matrix _lastAbsTrans;

    // Variables should all be in SkeletonDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonDrawable(void);
    SkeletonDrawable(const SkeletonDrawable &source);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonDrawable(void); 

    /*! \}                                                                 */
	 
	 /**************************************************************************//**
     * @fn void    adjustVolume(Volume & volume)
     * 
     * @brief  
	  *
	  * @param volume
     * 
	  * @return  Result
    *****************************************************************************/
    void    adjustVolume(Volume & volume);
	 
	 /**************************************************************************//**
     * @fn void drawJointHierarchy (JointPtr TheJoint, DrawActionBase *action)
     * 
     * @brief Draws a bone between each parent-child joint pair located beneath
	  * 		  TheJoint in the joint hierarchy.
	  *
	  * @param TheJoint The joint in the hierarchy from which drawing should begin.
	  * @param action
     * 
	  * @return  Result
    *****************************************************************************/
    void drawJointHierarchy (JointPtr TheJoint, DrawActionBase *action);
	 
	 /**************************************************************************//**
     * @fn void expandVolumeByJoint (JointPtr TheJoint, Volume &volume)
     * 
     * @brief  
	  *
	  * @param TheJoint
	  * @param volume
     * 
	  * @return  Result
    *****************************************************************************/
    void expandVolumeByJoint (JointPtr TheJoint, Volume &volume);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SkeletonDrawableBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SkeletonDrawable &source);
};

typedef SkeletonDrawable *SkeletonDrawableP;

OSG_END_NAMESPACE

#include "OSGSkeletonDrawableBase.inl"
#include "OSGSkeletonDrawable.inl"

#define OSGSKELETONDRAWABLE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSKELETONDRAWABLE_H_ */


