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

#ifndef _OSGPOPUPMENU_H_
#define _OSGPOPUPMENU_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPopupMenuBase.h"
#include "OSGSeparator.h"
#include "OSGSingleSelectionModel.h"
#include "OSGMenuItemFields.h"
#include "OSGSelectionListener.h"
#include "OSGPopupMenuListener.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief PopupMenu class. See \ref
           PageContribUserInterfacePopupMenu for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING PopupMenu : public PopupMenuBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PopupMenuBase Inherited;
    typedef PopupMenu     Self;

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

    virtual void addItem(MenuItem* const Item);
    virtual void addItem(MenuItem* const Item, const UInt32& Index);
    virtual void removeItem(MenuItem* const Item);
    virtual void removeItem(const UInt32& Index);
    virtual void removeAllItems(void);
    virtual MenuItem* getItem(const UInt32& Index);
    virtual UInt32 getNumItems(void) const;

    void addSeparator(void);
    void addSeparator(Separator* const TheSeparator);
    void removeSeparator(const UInt32&  Index);
    void removeSeparator(Separator* const TheSeparator);
    void removeAllSeparators(void);
    UInt32 getNumSeparators(void) const;
    
	virtual void updateClipBounds(void);
    
	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventUnrecPtr e);
    virtual void mouseDragged(const MouseEventUnrecPtr e);
    
    EventConnection addPopupMenuListener(PopupMenuListenerPtr Listener);
	bool isPopupMenuListenerAttached(PopupMenuListenerPtr Listener) const;
    void removePopupMenuListener(PopupMenuListenerPtr Listener);

    void cancel(void);

    void clearSelection(void);
    void setSelection(const Int32& Index);
    Int32 getSelectionIndex(void) const;

    virtual ComponentContainer* getParentContainer(void) const;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PopupMenu *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    
    virtual void updateLayout(void);
    
	class MenuSelectionListener : public SelectionListener
	{
	public:
		MenuSelectionListener(PopupMenu* const ThePopupMenu);
        virtual void selectionChanged(const SelectionEventUnrecPtr e);
	private:
		PopupMenu* _PopupMenu;
	};

	friend class MenuSelectionListener;

	MenuSelectionListener _MenuSelectionListener;
	
	typedef std::set<PopupMenuListenerPtr> PopupMenuListenerSet;
    typedef PopupMenuListenerSet::iterator PopupMenuListenerSetItor;
    typedef PopupMenuListenerSet::const_iterator PopupMenuListenerSetConstItor;
	
    PopupMenuListenerSet       _PopupMenuListeners;
    void producePopupMenuWillBecomeVisible(const PopupMenuEventUnrecPtr e);
    void producePopupMenuWillBecomeInvisible(const PopupMenuEventUnrecPtr e);
    void producePopupMenuCanceled(const PopupMenuEventUnrecPtr e);
    void producePopupMenuContentsChanged(const PopupMenuEventUnrecPtr e);
    
    void updateSeparatorSizes(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PopupMenuBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PopupMenu &source);
};

typedef PopupMenu *PopupMenuP;

OSG_END_NAMESPACE

#include "OSGPopupMenuBase.inl"
#include "OSGPopupMenu.inl"

#endif /* _OSGPOPUPMENU_H_ */
