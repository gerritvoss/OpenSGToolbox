/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGLISTGENERATEDPOPUPMENU_H_
#define _OSGLISTGENERATEDPOPUPMENU_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGListGeneratedPopupMenuBase.h"
#include "Component/List/OSGListDataListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief ListGeneratedPopupMenu class. See \ref 
           PageUserInterfaceListGeneratedPopupMenu for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ListGeneratedPopupMenu : public ListGeneratedPopupMenuBase
{
  private:

    typedef ListGeneratedPopupMenuBase Inherited;

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

    virtual void addItem(MenuItemPtr Item);
    virtual void addItem(MenuItemPtr Item, const UInt32& Index);
    virtual void removeItem(MenuItemPtr Item);
    virtual void removeItem(const UInt32& Index);
    virtual void removeAllItems(void);
    virtual MenuItemPtr getItem(const UInt32& Index);
    virtual UInt32 getNumItems(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ListGeneratedPopupMenuBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ListGeneratedPopupMenu(void);
    ListGeneratedPopupMenu(const ListGeneratedPopupMenu &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ListGeneratedPopupMenu(void); 

    /*! \}                                                                 */
	void updateMenuItems(void);
    
	class ModelListener : public ListDataListener
	{
	public :
		ModelListener(ListGeneratedPopupMenuPtr TheListGeneratedPopupMenu);
		
		//Sent when the contents of the list has changed in a way that's too complex to characterize with the previous methods.
		virtual void contentsChanged(ListDataEvent e);
		//Sent after the indices in the index0,index1 interval have been inserted in the data model.
		virtual void intervalAdded(ListDataEvent e);
		//Sent after the indices in the index0,index1 interval have been removed from the data model.
		virtual void intervalRemoved(ListDataEvent e);
	protected :
		ListGeneratedPopupMenuPtr _ListGeneratedPopupMenu;
	};

	friend class ModelListener;

	ModelListener _ModelListener;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ListGeneratedPopupMenuBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ListGeneratedPopupMenu &source);
};

typedef ListGeneratedPopupMenu *ListGeneratedPopupMenuP;

OSG_END_NAMESPACE

#include "OSGListGeneratedPopupMenuBase.inl"
#include "OSGListGeneratedPopupMenu.inl"

#define OSGLISTGENERATEDPOPUPMENU_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLISTGENERATEDPOPUPMENU_H_ */
