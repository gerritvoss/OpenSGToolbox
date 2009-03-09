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
#include "Component/Menu/OSGListGeneratedPopupMenu.h"

#include <set>

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
	void addPopupMenuListener(PopupMenuListenerPtr Listener);
    

	//Removes a PopupMenuListener.
	void removePopupMenuListener(PopupMenuListenerPtr Listener);
    
	//Determines the visibility of the popup.
	bool isPopupVisible(void) const;
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
    
    //Expand Button Action Listener
	class MenuButtonEventsListener : public PopupMenuListener
	{
	public:
		MenuButtonEventsListener(MenuButtonPtr TheMenuButton);

		virtual void popupMenuCanceled(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeVisible(const PopupMenuEvent& e);
		virtual void popupMenuContentsChanged(const PopupMenuEvent& e);
	private:
		MenuButtonPtr _MenuButton;
	};

	friend class MenuButtonEventsListener;

	MenuButtonEventsListener _MenuButtonEventsListener;
    
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
