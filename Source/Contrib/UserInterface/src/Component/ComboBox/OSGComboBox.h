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

#ifndef _OSGCOMBOBOX_H_
#define _OSGCOMBOBOX_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComboBoxBase.h"
#include "OSGToggleButton.h"
#include "OSGComboBoxModel.h"
#include "OSGComboBoxEditor.h"
#include "OSGComponentGenerator.h"
#include "OSGListGeneratedPopupMenu.h"
#include "OSGKeyEventDetails.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief ComboBox class. See \ref
           PageContribUserInterfaceComboBox for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComboBox : public ComboBoxBase

{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComboBoxBase Inherited;
    typedef ComboBox     Self;

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
	
    virtual void updateLayout(void);

	//Adds an item to the item list.
	void addItem(const boost::any& anObject);

	//Initializes the editor with the specified item.
	void configureEditor(ComboBoxEditor* const anEditor, const boost::any& anItem);

	//Returns the action command that is included in the event sent to action listeners.
	std::string getActionCommand(void) const;

	//Returns the list item at the specified index.
	boost::any getItemAt(const UInt32& index) const;

	//Returns the number of items in the list.
	UInt32 getItemCount(void) const;

	//Returns the list's key-selection manager.
	//JComboBox.KeySelectionManager getKeySelectionManager(void) const;

	//Returns the first item in the list that matches the given item.
	UInt32 getSelectedIndex(void) const;

	//Returns the current selected item.
	boost::any getSelectedItem(void) const;

	//Returns an array containing the selected item.
	//Object[] getSelectedObjects(void) const;

	//Causes the combo box to close its popup window.
	void hidePopup(void);

	//Inserts an item into the item list at a given index.
	void insertItemAt(const boost::any& anObject, const UInt32& index);

	//Determines the visibility of the popup.
	bool isPopupVisible(void) const;

	//Handles KeyEvents, looking for the Tab key.
	void processKeyEvent(KeyEventDetails e);

	//Removes all items from the item list.
	void removeAllItems(void);

	//Removes an item from the item list.
	void removeItem(const boost::any& anObject);

	//Removes the item at anIndex This method works only if the JComboBox uses a mutable data model.
	void removeItemAt(const UInt32& anIndex);

	//Selects the list item that corresponds to the specified keyboard character and returns true, if there is an item corresponding to that character.
	bool selectWithKey(KeyEventDetails::Key TheKey);

	//Sets the action command that should be included in the event sent to action listeners.
	void setActionCommand(std::string aCommand);

	//Sets the object that translates a keyboard character into a list selection.
	//void setKeySelectionManager(JComboBox.KeySelectionManager aManager);

	//Sets the visibility of the popup.
	void setPopupVisible(bool v);

	//Selects the item at index anIndex.
	void setSelectedIndex(const UInt32& anIndex);

	//Sets the selected item in the combo box display area to the object in the argument.
	void setSelectedItem(const boost::any& anObject);

	void setEmptyDescText(const std::string& text);

	//Causes the combo box to display its popup window.
	void showPopup(void);
	
	virtual void keyTyped(KeyEventDetails* const e);
    virtual void mouseClicked(MouseEventDetails* const e);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComboBoxBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComboBox(void);
    ComboBox(const ComboBox &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComboBox(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ComboBox *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

	//Factory method which sets the ActionEvent source's properties according to values from the Action instance.
	void configurePropertiesFromAction(Action a);

	//Notifies all listeners that have registered interest for notification on this event type.
    void produceActionPerformed(void);

	//Notifies all listeners that have registered interest for notification on this event type.
	//void produceItemStateChanged(ItemEvent e);

	//This method is public as an implementation side effect.
	void handleMenuItemActionPerformed(ActionEventDetails* const e);
    std::vector<boost::signals2::connection> _MenuItemActionConnections;

	void handleContentsChanged(ListDataEventDetails* const e);
	void handleContentsIntervalAdded(ListDataEventDetails* const e);
	void handleContentsIntervalRemoved(ListDataEventDetails* const e);
    void handleSelectionChanged(ComboBoxSelectionEventDetails* const e);
    boost::signals2::connection _ContentsChangedConnection,
                                _ContentsIntervalAddedConnection,
                                _ContentsIntervalRemovedConnection,
                                _SelectionChangedConnection;

    //Expand Button Action
    void handleExpandButtonSelected(ButtonSelectedEventDetails* const e);
    void handleExpandButtonDeselected(ButtonSelectedEventDetails* const e);
    void handleExpandPopupMenuCanceled(PopupMenuEventDetails* const e);
    void handleExpandPopupMenuWillBecomeInvisible(PopupMenuEventDetails* const e);
    void handleExpandPopupMenuWillBecomeVisible(PopupMenuEventDetails* const e);
    void handleExpandPopupMenuContentsChanged(PopupMenuEventDetails* const e);

    boost::signals2::connection _ExpandButtonSelectedConnection,
                                _ExpandButtonDeselectedConnection,
                                _ExpandPopupMenuCanceledConnection,
                                _ExpandPopupMenuWillBecomeInvisibleConnection,
                                _ExpandPopupMenuWillBecomeVisibleConnection,
                                _ExpandPopupMenuContentsChangedConnection;

    //Editor
    void handleEditorAction(ActionEventDetails* const e);

    boost::signals2::connection _EditorActionConnection;

	void updateListFromModel(void);
	void updateSelectedItemComponent(void);
	void updateComponentGeneratorSelectedItem(void);
	void updateSelectionFromEditor(void);

	void attachMenuItems(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComboBoxBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComboBox &source);
};

typedef ComboBox *ComboBoxP;

OSG_END_NAMESPACE

#include "OSGComboBoxBase.inl"
#include "OSGComboBox.inl"

#endif /* _OSGCOMBOBOX_H_ */
