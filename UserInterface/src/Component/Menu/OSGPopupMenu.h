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

#ifndef _OSGPOPUPMENU_H_
#define _OSGPOPUPMENU_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGPopupMenuBase.h"
#include "OSGMenuItemFields.h"
#include "OSGSingleSelectionModel.h"
#include "Event/OSGChangeListener.h"
#include "Event/OSGPopupMenuListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief PopupMenu class. See \ref 
           PageUserInterfacePopupMenu for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING PopupMenu : public PopupMenuBase
{
  private:

    typedef PopupMenuBase Inherited;

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

    void addItem(MenuItemPtr Item);
    void addItem(MenuItemPtr Item, const UInt32& Index);
    void removeItem(MenuItemPtr Item);
    void removeItem(const UInt32& Index);
    MenuItemPtr getItem(const UInt32& Index);
    UInt32 getNumItems(void) const;
    
	virtual void updateClipBounds(void);
    
	//Mouse Motion Events
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);
    
    void addPopupMenuListener(PopupMenuListenerPtr Listener);
    void removePopupMenuListener(PopupMenuListenerPtr Listener);

    void cancel(void);

    void clearSelection(void);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PopupMenuBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PopupMenu(void);
    PopupMenu(const PopupMenu &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PopupMenu(void); 
    /*! \}                                                                 */
    
    virtual void updateLayout(void);
    
	class MenuSelectionListener : public ChangeListener
	{
	public:
		MenuSelectionListener(PopupMenuPtr ThePopupMenu);
        void stateChanged(const ChangeEvent& e);
	private:
		PopupMenuPtr _PopupMenu;
	};

	friend class MenuSelectionListener;

	MenuSelectionListener _MenuSelectionListener;
	
	typedef std::set<PopupMenuListenerPtr> PopupMenuListenerSet;
    typedef PopupMenuListenerSet::iterator PopupMenuListenerSetItor;
    typedef PopupMenuListenerSet::const_iterator PopupMenuListenerSetConstItor;
	
    PopupMenuListenerSet       _PopupMenuListeners;
    void producePopupMenuWillBecomeVisible(const PopupMenuEvent& e);
    void producePopupMenuWillBecomeInvisible(const PopupMenuEvent& e);
    void producePopupMenuCanceled(const PopupMenuEvent& e);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PopupMenuBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PopupMenu &source);
    
    SingleSelectionModelPtr _SelectionModel;
};

typedef PopupMenu *PopupMenuP;

OSG_END_NAMESPACE

#include "OSGPopupMenuBase.inl"
#include "OSGPopupMenu.inl"

#define OSGPOPUPMENU_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPOPUPMENU_H_ */
