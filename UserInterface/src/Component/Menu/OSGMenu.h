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

#ifndef _OSGMENU_H_
#define _OSGMENU_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGMenuBase.h"
#include <OpenSG/Input/OSGUpdateListener.h>

OSG_BEGIN_NAMESPACE

/*! \brief Menu class. See \ref 
           PageUserInterfaceMenu for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING Menu : public MenuBase
{
  private:

    typedef MenuBase Inherited;
    friend class MenuBar;

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

    //virtual void mouseEntered(const MouseEvent& e);
    //virtual void mouseExited(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MenuBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Menu(void);
    Menu(const Menu &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Menu(void); 

    /*! \}                                                                 */

	virtual void drawInternal(const GraphicsPtr Graphics) const;
	
    void setPopupVisible(bool Visible);
    
    bool getPopupVisible(void) const;
    
	class PopupUpdateListener : public UpdateListener
	{
	public:
		PopupUpdateListener(MenuPtr TheMenu);
        virtual void update(const UpdateEvent& e);
        void reset(void);
	private:
		MenuPtr _Menu;
	    Time _PopupElps;
	};

	friend class PopupUpdateListener;

	PopupUpdateListener _PopupUpdateListener;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MenuBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Menu &source);
};

typedef Menu *MenuP;

OSG_END_NAMESPACE

#include "OSGMenuBase.inl"
#include "OSGMenu.inl"

#define OSGMENU_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMENU_H_ */
