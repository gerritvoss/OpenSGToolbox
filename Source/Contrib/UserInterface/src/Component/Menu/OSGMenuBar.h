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

#ifndef _OSGMENUBAR_H_
#define _OSGMENUBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMenuBarBase.h"
#include "OSGSingleSelectionModel.h"

#include "OSGMenu.h"

OSG_BEGIN_NAMESPACE

/*! \brief MenuBar class. See \ref
           PageContribUserInterfaceMenuBar for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MenuBar : public MenuBarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MenuBarBase Inherited;
    typedef MenuBar     Self;

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

    void addMenu(Menu* const Menu);
    void addMenu(Menu* const Menu, const UInt32& Index);
    void removeMenu(Menu* const Menu);
    void removeMenu(const UInt32& Index);
    Menu* getMenu(const UInt32& Index);
    UInt32 getNumMenus(void) const;
    
    virtual void mousePressed(MouseEventDetails* const e);
    
    virtual void updateLayout(void);
	virtual void updateClipBounds(void);

    virtual void detachFromEventProducer(void);

    void setParentWindow(InternalWindow* const parent);

    virtual ComponentContainer* getParentContainer(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MenuBarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MenuBar(void);
    MenuBar(const MenuBar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MenuBar(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MenuBar *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    
    void handleMenuArmedSelectionChanged(SelectionEventDetails* const e);
    void handleMenuArmedMouseMoved(MouseEventDetails* const e);
    void handleMenuArmedMouseDragged(MouseEventDetails* const e);
    void handleMenuArmedPopupMenuCanceled(PopupMenuEventDetails* const e);
    void handleMenuArmedKeyTyped(KeyEventDetails* const e);

    boost::signals2::connection _SelectionChangedConnection,
                                _MouseMovedConnection,
                                _MouseDraggedConnection,
                                _KeyTypedConnection;

    std::map<Menu*, boost::signals2::connection> _PopupMenuCanceledConnections;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MenuBarBase;
    friend class InternalWindow;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MenuBar &source);
};

typedef MenuBar *MenuBarP;

OSG_END_NAMESPACE

#include "OSGMenuBarBase.inl"
#include "OSGMenuBar.inl"

#endif /* _OSGMENUBAR_H_ */
