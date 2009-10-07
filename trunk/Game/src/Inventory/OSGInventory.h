/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                  Authors: David Kabala, Eric Langkamp                     *
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

#ifndef _OSGINVENTORY_H_
#define _OSGINVENTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGInventoryBase.h"

#include "Event/OSGInventoryListener.h"
#include <OpenSG/Toolbox/OSGEventConnection.h>

#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief Inventory class. See \ref 
           PageGameInventory for a description.
*/

class OSG_GAMELIB_DLLMAPPING Inventory : public InventoryBase
{
  private:

    typedef InventoryBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	void addItem(InventoryItemPtr Item);
	std::vector<InventoryItemPtr> getItemsOfClass(std::string className);

	EventConnection addInventoryListener(InventoryListenerPtr Listener);
	bool isInventoryListenerAttached(InventoryListenerPtr Listener) const;
    void removeInventoryListener(InventoryListenerPtr Listener);


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

	typedef std::set<InventoryListenerPtr> InventoryListenerSet;
    typedef InventoryListenerSet::iterator InventoryListenerSetItor;
    typedef InventoryListenerSet::const_iterator InventoryListenerSetConstItor;
    InventoryListenerSet       _InventoryListeners;

	virtual void produceItemAdded(const InventoryEventPtr e);
	virtual void produceInventorySorted(const InventoryEventPtr e);
	virtual void produceItemRemoved(const InventoryEventPtr e);

    // Variables should all be in InventoryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

	void setupAsRoot();
    Inventory(void);
    Inventory(const Inventory &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Inventory(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class InventoryBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Inventory &source);
};

typedef Inventory *InventoryP;

OSG_END_NAMESPACE

#include "OSGInventoryBase.inl"
#include "OSGInventory.inl"

#endif /* _OSGINVENTORY_H_ */
