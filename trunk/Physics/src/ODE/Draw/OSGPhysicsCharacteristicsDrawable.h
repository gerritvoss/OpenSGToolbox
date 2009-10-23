/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#ifndef _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_
#define _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsCharacteristicsDrawableBase.h"
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGMaterial.h>
#include <OpenSG/OSGBasicActorBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsCharacteristicsDrawable class. See \ref 
           PagePhysicsPhysicsCharacteristicsDrawable for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsCharacteristicsDrawable : public PhysicsCharacteristicsDrawableBase
{
  private:

    typedef PhysicsCharacteristicsDrawableBase Inherited;

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


    Action::ResultE enter(NodePtr& node);

    MaterialPtr getDefaultMaterial(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsCharacteristicsDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsCharacteristicsDrawable(void);
    PhysicsCharacteristicsDrawable(const PhysicsCharacteristicsDrawable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsCharacteristicsDrawable(void); 

    /*! \}                                                                 */
    void    adjustVolume(Volume & volume);
    
    /*==========================  PRIVATE  ================================*/
  private:
    static MaterialPtr _DefaultMaterial;

    friend class FieldContainer;
    friend class PhysicsCharacteristicsDrawableBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsCharacteristicsDrawable &source);
    DrawActionBase* _DrawAction;
};

typedef PhysicsCharacteristicsDrawable *PhysicsCharacteristicsDrawableP;

OSG_END_NAMESPACE

#include "OSGPhysicsCharacteristicsDrawableBase.inl"
#include "OSGPhysicsCharacteristicsDrawable.inl"

#endif /* _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_ */
