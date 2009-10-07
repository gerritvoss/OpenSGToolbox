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

#ifndef _OSGCOMBOBOX_H_
#define _OSGCOMBOBOX_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComboBoxBase.h"

#include <OpenSG/Input/OSGMouseAdapter.h>
#include "Component/List/OSGListDataListener.h"
#include "Event/OSGPopupMenuListener.h"
#include "Event/OSGActionListener.h"
#include "Event/OSGButtonSelectedListener.h"
#include "OSGComboBoxSelectionListener.h"
#include <boost/any.hpp>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief ComboBox class. See \ref 
           PageUserInterfaceComboBox for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComboBox : public ComboBoxBase, public ActionListener, public ListDataListener, public ComboBoxSelectionListener
{
  private:

    typedef ComboBoxBase Inherited;

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
	
    virtual void updateLayout(void);

	//This method is public as an implementation side effect.
	virtual void actionPerformed(const ActionEventPtr e);

	//This method is public as an implementation side effect.
	virtual void contentsChanged(const ListDataEventPtr e);

	//This method is public as an implementation side effect.
	virtual void intervalAdded(const ListDataEventPtr e);

	//This method is public as an implementation side effect.
	virtual void intervalRemoved(const ListDataEventPtr e);

	//This protected method is implementation specific.
    virtual void selectionChanged(const ComboBoxSelectionEventPtr e);

	//Adds an ItemListener.
	//EventConnection addItemListener(ItemListenerPtr aListener);
	//bool isItemListenerAttached(ItemListenerPtr aListener) const;

	//Adds a PopupMenu listener which will listen to notification messages from the popup portion of the combo box.
	EventConnection addPopupMenuListener(PopupMenuListenerPtr Listener);
	bool isPopupMenuListenerAttached(PopupMenuListenerPtr Listener) const;

	//Adds an ActionListener.
	EventConnection addActionListener(ActionListenerPtr Listener);
	bool isActionListenerAttached(ActionListenerPtr Listener) const;

	//Removes an ActionListener.
	void removeActionListener(ActionListenerPtr Listener);

	//Removes an ItemListener.
	//void removeItemListener(ItemListenerPtr aListener);

	//Removes a PopupMenuListener.
	void removePopupMenuListener(PopupMenuListenerPtr Listener);

	//Adds an item to the item list.
	void addItem(const boost::any& anObject);

	//Initializes the editor with the specified item.
	void configureEditor(ComboBoxEditorPtr anEditor, const boost::any& anItem);

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
	void processKeyEvent(KeyEvent e);

	//Removes all items from the item list.
	void removeAllItems(void);

	//Removes an item from the item list.
	void removeItem(const boost::any& anObject);

	//Removes the item at anIndex This method works only if the JComboBox uses a mutable data model.
	void removeItemAt(const UInt32& anIndex);

	//Selects the list item that corresponds to the specified keyboard character and returns true, if there is an item corresponding to that character.
	bool selectWithKey(KeyEvent::Key TheKey);

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

	//Causes the combo box to display its popup window.
	void showPopup(void);
	
	virtual void keyTyped(const KeyEventPtr e);
    virtual void mouseClicked(const MouseEventPtr e);

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

	//Factory method which sets the ActionEvent source's properties according to values from the Action instance.
	void configurePropertiesFromAction(Action a);


	//Factory method which creates the PropertyChangeListener used to update the ActionEvent source as properties change on its Action instance.
	//PropertyChangeListener createActionPropertyChangeListener(Action a);

	//Returns an instance of the default key-selection manager.
	//JComboBox.KeySelectionManager createDefaultKeySelectionManager();

	//Notifies all listeners that have registered interest for notification on this event type.
    void produceActionPerformed(const ActionEventPtr e);

	//Notifies all listeners that have registered interest for notification on this event type.
	//void produceItemStateChanged(ItemEvent e);
    
	typedef std::set<ActionListenerPtr> ActionListenerSet;
    typedef ActionListenerSet::iterator ActionListenerSetItor;
    typedef ActionListenerSet::const_iterator ActionListenerSetConstItor;
	
    ActionListenerSet       _ActionListeners;

    //Expand Button Action Listener
	class ExpandButtonSelectedListener : public ButtonSelectedListener, public PopupMenuListener
	{
	public:
		ExpandButtonSelectedListener(ComboBoxPtr TheComboBox);
		virtual void buttonSelected(const ButtonSelectedEventPtr e);
		virtual void buttonDeselected(const ButtonSelectedEventPtr e);

		virtual void popupMenuCanceled(const PopupMenuEventPtr e);
		virtual void popupMenuWillBecomeInvisible(const PopupMenuEventPtr e);
		virtual void popupMenuWillBecomeVisible(const PopupMenuEventPtr e);
		virtual void popupMenuContentsChanged(const PopupMenuEventPtr e);
	private:
		ComboBoxPtr _ComboBox;
	};

	friend class ExpandButtonSelectedListener;

	ExpandButtonSelectedListener _ExpandButtonSelectedListener;
	
    //Editor Listener
	class EditorListener : public ActionListener
	{
	public:
		EditorListener(ComboBoxPtr TheComboBox);
		
	    virtual void actionPerformed(const ActionEventPtr e);
	private:
		ComboBoxPtr _ComboBox;
	};

	friend class EditorListener;

	EditorListener _EditorListener;

	void updateListFromModel(void);
	void updateSelectedItemComponent(void);
	void updateComponentGeneratorSelectedItem(void);
	void updateSelectionFromEditor(void);

	void attachMenuItems(void);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComboBoxBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComboBox &source);
};

typedef ComboBox *ComboBoxP;

OSG_END_NAMESPACE

#include "OSGComboBoxBase.inl"
#include "OSGComboBox.inl"

#endif /* _OSGCOMBOBOX_H_ */
