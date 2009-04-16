/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef _OSGMENUBUTTON_H_
#define _OSGMENUBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGMenuButtonBase.h"
#include "Component/List/OSGListDataListener.h"
#include "Event/OSGPopupMenuListener.h"
#include "Event/OSGActionListener.h"
#include "Component/Menu/OSGListGeneratedPopupMenu.h"

#include <set>
#include <boost/any.hpp>

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief MenuButton class. See \ref 
           PageUserInterfaceMenuButton for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING MenuButton : public MenuButtonBase
{
  private:

    typedef MenuButtonBase Inherited;

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
	//Adds a PopupMenu listener which will listen to notification messages from the popup portion of the combo box.
	EventConnection addPopupMenuListener(PopupMenuListenerPtr Listener);
	bool isPopupMenuListenerAttached(PopupMenuListenerPtr Listener) const;
    

	//Removes a PopupMenuListener.
	void removePopupMenuListener(PopupMenuListenerPtr Listener);

    EventConnection addMenuActionListener(ActionListenerPtr Listener);
	bool isMenuActionListenerAttached(ActionListenerPtr Listener) const;
    void removeMenuActionListener(ActionListenerPtr Listener);
    
	//Determines the visibility of the popup.
	bool isPopupVisible(void) const;

    
    Int32 getSelectionIndex(void) const;
    boost::any getSelectionValue(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MenuButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MenuButton(void);
    MenuButton(const MenuButton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MenuButton(void); 

    /*! \}                                                                 */

	void hidePopup(void);
	void showPopup(void);
    void updatePopupMenuConnections(void);
    
    //Expand Button Action Listener
	class MenuButtonEventsListener : public PopupMenuListener, public ActionListener
	{
	public:
		MenuButtonEventsListener(MenuButtonPtr TheMenuButton);

		virtual void popupMenuCanceled(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeVisible(const PopupMenuEvent& e);
		virtual void popupMenuContentsChanged(const PopupMenuEvent& e);
        
        virtual void actionPerformed(const ActionEvent& e);
	private:
		MenuButtonPtr _MenuButton;
	};

	friend class MenuButtonEventsListener;

	MenuButtonEventsListener _MenuButtonEventsListener;
	
	
	typedef std::set<ActionListenerPtr> MenuActionListenerSet;
    typedef MenuActionListenerSet::iterator MenuActionListenerSetItor;
    typedef MenuActionListenerSet::const_iterator MenuActionListenerSetConstItor;
	
    MenuActionListenerSet       _MenuActionListeners;
	
    virtual void produceMenuActionPerformed(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MenuButtonBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MenuButton &source);
};

typedef MenuButton *MenuButtonP;

OSG_END_NAMESPACE

#include "OSGMenuButtonBase.inl"
#include "OSGMenuButton.inl"

#define OSGMENUBUTTON_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMENUBUTTON_H_ */
