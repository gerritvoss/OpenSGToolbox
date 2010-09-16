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

#ifndef _OSGMENUITEM_H_
#define _OSGMENUITEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMenuItemBase.h"
#include "OSGMenuFields.h"
#include "OSGKeyAcceleratorEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MenuItem class. See \ref
           PageContribUserInterfaceMenuItem for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MenuItem : public MenuItemBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MenuItemBase Inherited;
    typedef MenuItem     Self;

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

    virtual void activate(void);
	Vec2f getContentRequestedSize(void) const;

    virtual void mouseReleased(MouseEventDetails* const e);
    
    void setDrawAsThoughSelected(bool Selected);
    bool getDrawAsThoughSelected(void) const;

    virtual void detachFromEventProducer(void);

    void setParentWindow(InternalWindow* const parent);

    Menu* getParentMenu(void) const;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawText(Graphics* const TheGraphics, const Pnt2f& TopLeft, Real32 Opacity = 1.0f) const;
    
    virtual void actionPreformed(ActionEventDetails* const e);
    
    void handleAcceleratorTyped(KeyEventDetails* const e);
    boost::signals2::connection _AcceleratorTypedConnection;


    void handleFlashUpdate(UpdateEventDetails* const e);
    boost::signals2::connection _FlashUpdateConnection;
    Time _FlashElps;

    Menu* getTopLevelMenu(void) const;
    bool _DrawAsThoughSelected;
    std::string _AcceleratorText;
    Int32 _MnemonicTextPosition;

    void updateAcceleratorText(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MenuItemBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MenuItem &source);
};

typedef MenuItem *MenuItemP;

OSG_END_NAMESPACE

#include "OSGMenu.h"

#include "OSGMenuItemBase.inl"
#include "OSGMenuItem.inl"

#endif /* _OSGMENUITEM_H_ */
