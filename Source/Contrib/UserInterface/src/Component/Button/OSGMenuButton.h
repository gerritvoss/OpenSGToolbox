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

#ifndef _OSGMENUBUTTON_H_
#define _OSGMENUBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMenuButtonBase.h"
#include "OSGListModel.h"
#include "OSGComponentGenerator.h"
#include "OSGListGeneratedPopupMenu.h"

OSG_BEGIN_NAMESPACE

/*! \brief MenuButton class. See \ref
           PageContribUserInterfaceMenuButton for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MenuButton : public MenuButtonBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MenuButtonBase Inherited;
    typedef MenuButton     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */

	void onCreate(const MenuButton *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

	void hidePopup(void);
	void showPopup(void);
    void updatePopupMenuConnections(void);
    
    //Expand Button Events
    void handlePopupMenuCanceled(PopupMenuEventDetails* const e);
	void handlePopupMenuWillBecomeInvisible(PopupMenuEventDetails* const e);
	void handlePopupMenuContentsChanged(PopupMenuEventDetails* const e);
    void handlePopupMenuActionPerformed(ActionEventDetails* const e);

    boost::signals2::connection   _PopupMenuCanceledConnection,
                                  _PopupMenuWillBecomeInvisibleConnection,
                                  _PopupMenuContentsChangedConnection;
    std::vector<boost::signals2::connection> _PopupMenuActionConnections;

	
    virtual void produceMenuActionPerformed(void);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MenuButtonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MenuButton &source);
};

typedef MenuButton *MenuButtonP;

OSG_END_NAMESPACE

#include "OSGMenuButtonBase.inl"
#include "OSGMenuButton.inl"

#endif /* _OSGMENUBUTTON_H_ */
