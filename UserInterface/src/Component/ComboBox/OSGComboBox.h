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
#include "Component/List/OSGListCellRenderer.h"
#include "Event/OSGPopupMenuListener.h"
#include "Event/OSGActionListener.h"
#include "Event/OSGButtonSelectedListener.h"
#include "OSGComboBoxModel.h"

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
	virtual void actionPerformed(const ActionEvent& e);

	//This method is public as an implementation side effect.
	virtual void contentsChanged(ListDataEvent e);

	//This method is public as an implementation side effect.
	virtual void intervalAdded(ListDataEvent e);

	//This method is public as an implementation side effect.
	virtual void intervalRemoved(ListDataEvent e);

	//This protected method is implementation specific.
    virtual void selectionChanged(const ComboBoxSelectionEvent& e);

	//Adds an ItemListener.
	//void addItemListener(ItemListenerPtr aListener);

	//Adds a PopupMenu listener which will listen to notification messages from the popup portion of the combo box.
	void addPopupMenuListener(PopupMenuListenerPtr Listener);

	//Adds an ActionListener.
	void addActionListener(ActionListenerPtr Listener);

	//Removes an ActionListener.
	void removeActionListener(ActionListenerPtr Listener);

	//Removes an ItemListener.
	//void removeItemListener(ItemListenerPtr aListener);

	//Removes a PopupMenuListener.
	void removePopupMenuListener(PopupMenuListenerPtr Listener);

	//Adds an item to the item list.
	void addItem(SharedFieldPtr anObject);

	//Initializes the editor with the specified item.
	void configureEditor(ComboBoxEditorPtr anEditor, SharedFieldPtr anItem);

	//Returns the action command that is included in the event sent to action listeners.
	std::string getActionCommand(void) const;

	//Returns the list item at the specified index.
	SharedFieldPtr getItemAt(const UInt32& index) const;

	//Returns the number of items in the list.
	UInt32 getItemCount(void) const;

	//Returns the list's key-selection manager.
	//JComboBox.KeySelectionManager getKeySelectionManager(void) const;

	//Returns the data model currently used by the JComboBox.
	ComboBoxModelPtr getModel(void) const;

	//Returns the renderer used to display the selected item in the JComboBox field.
	ListCellRendererPtr getRenderer(void) const;

	//Returns the first item in the list that matches the given item.
	UInt32 getSelectedIndex(void) const;

	//Returns the current selected item.
	SharedFieldPtr getSelectedItem(void) const;

	//Returns an array containing the selected item.
	//Object[] getSelectedObjects(void) const;

	//Causes the combo box to close its popup window.
	void hidePopup(void);

	//Inserts an item into the item list at a given index.
	void insertItemAt(SharedFieldPtr anObject, const UInt32& index);

	//Determines the visibility of the popup.
	bool isPopupVisible(void) const;

	//Handles KeyEvents, looking for the Tab key.
	void processKeyEvent(KeyEvent e);

	//Removes all items from the item list.
	void removeAllItems(void);

	//Removes an item from the item list.
	void removeItem(SharedFieldPtr anObject);

	//Removes the item at anIndex This method works only if the JComboBox uses a mutable data model.
	void removeItemAt(const UInt32& anIndex);

	//Selects the list item that corresponds to the specified keyboard character and returns true, if there is an item corresponding to that character.
	bool selectWithKey(KeyEvent::Key TheKey);

	//Sets the action command that should be included in the event sent to action listeners.
	void setActionCommand(std::string aCommand);

	//Sets the object that translates a keyboard character into a list selection.
	//void setKeySelectionManager(JComboBox.KeySelectionManager aManager);

	//Sets the data model that the JComboBox uses to obtain the list of items.
	void setModel(ComboBoxModelPtr aModel);

	//Sets the visibility of the popup.
	void setPopupVisible(bool v);

	//Sets the renderer that paints the list items and the item selected from the list in the JComboBox field.
	void setRenderer(ListCellRendererPtr aRenderer);

	//Selects the item at index anIndex.
	void setSelectedIndex(const UInt32& anIndex);

	//Sets the selected item in the combo box display area to the object in the argument.
	void setSelectedItem(SharedFieldPtr anObject);

	//Causes the combo box to display its popup window.
	void showPopup(void);
	
	virtual void keyTyped(const KeyEvent& e);
    virtual void mouseClicked(const MouseEvent& e);

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
	
    ComboBoxModelPtr _Model;
    ListCellRendererPtr _CellRenderer;

	//Factory method which sets the ActionEvent source's properties according to values from the Action instance.
	void configurePropertiesFromAction(Action a);


	//Factory method which creates the PropertyChangeListener used to update the ActionEvent source as properties change on its Action instance.
	//PropertyChangeListener createActionPropertyChangeListener(Action a);

	//Returns an instance of the default key-selection manager.
	//JComboBox.KeySelectionManager createDefaultKeySelectionManager();

	//Notifies all listeners that have registered interest for notification on this event type.
    void produceActionPerformed(const ActionEvent& e);

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
		virtual void buttonSelected(const ButtonSelectedEvent& e);
		virtual void buttonDeselected(const ButtonSelectedEvent& e);

		virtual void popupMenuCanceled(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeInvisible(const PopupMenuEvent& e);
		virtual void popupMenuWillBecomeVisible(const PopupMenuEvent& e);
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
		
	    virtual void actionPerformed(const ActionEvent& e);
	private:
		ComboBoxPtr _ComboBox;
	};

	friend class EditorListener;

	EditorListener _EditorListener;

	void updateListFromModel(void);
	void updateSelectedItemComponent(void);
	void updateRendererSelcetedItem(void);
	void updateSelectionFromEditor(void);

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

#define OSGCOMBOBOX_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMBOBOX_H_ */
