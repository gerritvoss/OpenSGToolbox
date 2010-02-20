/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGMenuBase.h"
#include "OSGUpdateListener.h"
#include "OSGSeparatorFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief Menu class. See \ref
           PageContribUserInterfaceMenu for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Menu : public MenuBase
{
  protected:
    friend class MenuBar;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MenuBase Inherited;
    typedef Menu     Self;


    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    void addItem(MenuItemRefPtr Item);
    void addItem(MenuItemRefPtr Item, const UInt32& Index);
    void removeItem(MenuItemRefPtr Item);
    void removeItem(const UInt32& Index);
    void removeAllItems(void);
    MenuItemRefPtr getItem(const UInt32& Index);
    UInt32 getNumItems(void) const;

    void addSeparator(void);
    void addSeparator(SeparatorRefPtr TheSeparator);
    void removeSeparator(const UInt32&  Index);
    void removeSeparator(SeparatorRefPtr TheSeparator);
    void removeAllSeparators(void);
    UInt32 getNumSeparators(void) const;

    //virtual void mouseEntered(const MouseEventUnrecPtr e);
    //virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mouseReleased(const MouseEventUnrecPtr e);

    virtual void activate(void);

    virtual void detachFromEventProducer(void);
    
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Menu *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

	virtual void drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity = 1.0f) const;
	
    void setPopupVisible(bool Visible);
    
    bool getPopupVisible(void) const;
    
	class PopupUpdateListener : public UpdateListener
	{
	public:
		PopupUpdateListener(MenuRefPtr TheMenu);
        virtual void update(const UpdateEventUnrecPtr e);
        void reset(void);
	private:
		MenuRefPtr _Menu;
	    Time _PopupElps;
	};

	friend class PopupUpdateListener;

	PopupUpdateListener _PopupUpdateListener;

    EventConnection _PopupUpdateEventConnection;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MenuBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Menu &source);
};

typedef Menu *MenuP;

OSG_END_NAMESPACE

#include "OSGPopupMenu.h"

#include "OSGMenuBase.inl"
#include "OSGMenu.inl"

#endif /* _OSGMENU_H_ */
