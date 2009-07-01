/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGINVENTORYINTERFACE_H_
#define _OSGINVENTORYINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGInventoryInterfaceBase.h"
#include "Event/OSGInventoryListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief InventoryInterface class. See \ref 
           PageGameInventoryInterface for a description.
*/

class OSG_GAMELIB_DLLMAPPING InventoryInterface : public InventoryInterfaceBase
{
  private:

    typedef InventoryInterfaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	void setInventory();

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in InventoryInterfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    InventoryInterface(void);
    InventoryInterface(const InventoryInterface &source);

	class InventoryInterfaceListener : public InventoryListener
    {
	public :
		InventoryInterfaceListener(InventoryInterfacePtr TheInventoryInterface);
		
    virtual void itemAdded(const InventoryEvent& e);
    virtual void itemRemoved(const InventoryEvent& e);
    virtual void inventorySorted(const InventoryEvent& e);

	protected :

        InventoryInterfacePtr _InventoryInterface;
	};

    
    InventoryInterfaceListener          _InventoryInterfaceListener;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~InventoryInterface(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class InventoryInterfaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const InventoryInterface &source);
};

typedef InventoryInterface *InventoryInterfaceP;

OSG_END_NAMESPACE

#include "OSGInventoryInterfaceBase.inl"
#include "OSGInventoryInterface.inl"

#define OSGINVENTORYINTERFACE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGINVENTORYINTERFACE_H_ */
