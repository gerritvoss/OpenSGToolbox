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

#ifndef _OSGMENUITEM_H_
#define _OSGMENUITEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGMenuItemBase.h"
#include "Event/OSGActionListener.h"
#include "Event/OSGKeyAcceleratorListener.h"
#include "Component/Menu/OSGMenuFields.h"

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief MenuItem class. See \ref 
           PageUserInterfaceMenuItem for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING MenuItem : public MenuItemBase
{
  private:

    typedef MenuItemBase Inherited;

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

    virtual void activate(void);
    EventConnection addActionListener(ActionListenerPtr Listener);
	bool isActionListenerAttached(ActionListenerPtr Listener) const;
    void removeActionListener(ActionListenerPtr Listener);

	Vec2f getContentRequestedSize(void) const;

    virtual void mouseReleased(const MouseEvent& e);
    
    void setDrawAsThoughSelected(bool Selected);
    bool getDrawAsThoughSelected(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MenuItemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MenuItem(void);
    MenuItem(const MenuItem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MenuItem(void); 

	virtual void drawText(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft) const;
    
    virtual void actionPreformed(const ActionEvent& e);
	
    virtual void produceActionPerformed(const ActionEvent& e);
    
	class MenuItemKeyAcceleratorListener : public KeyAcceleratorListener
	{
	public:
		MenuItemKeyAcceleratorListener(MenuItemPtr TheMenuItem);
        virtual void acceleratorTyped(const KeyAcceleratorEvent& e);
	private:
		MenuItemPtr _MenuItem;
	};

	friend class MenuItemKeyAcceleratorListener;

	MenuItemKeyAcceleratorListener _MenuItemKeyAcceleratorListener;
    
	class KeyAcceleratorMenuFlashUpdateListener : public UpdateListener
	{
	public:
		KeyAcceleratorMenuFlashUpdateListener(MenuItemPtr TheMenuItem);
        virtual void update(const UpdateEvent& e);
        void reset(void);
	private:
		MenuItemPtr _MenuItem;
	    Time _FlashElps;
	};

	friend class KeyAcceleratorMenuFlashUpdateListener;

	KeyAcceleratorMenuFlashUpdateListener _KeyAcceleratorMenuFlashUpdateListener;

    MenuPtr getTopLevelMenu(void) const;
    bool _DrawAsThoughSelected;
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MenuItemBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MenuItem &source);

	typedef std::set<ActionListenerPtr> ActionListenerSet;
    typedef ActionListenerSet::iterator ActionListenerSetItor;
    typedef ActionListenerSet::const_iterator ActionListenerSetConstItor;
	
    ActionListenerSet       _ActionListeners;
};

typedef MenuItem *MenuItemP;

OSG_END_NAMESPACE

#include "OSGMenuItemBase.inl"
#include "OSGMenuItem.inl"

#define OSGMENUITEM_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMENUITEM_H_ */
