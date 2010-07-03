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

#ifndef _OSGDEFAULTTABLECELLEDITOR_H_
#define _OSGDEFAULTTABLECELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultTableCellEditorBase.h"
#include "OSGActionListener.h"
#include "OSGFocusListener.h"
#include "OSGKeyAdapter.h"
#include "OSGTextField.h"
#include "OSGSpinner.h"
#include "OSGComboBox.h"
#include "OSGCheckboxButton.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTableCellEditor class. See \ref
           PageContribUserInterfaceDefaultTableCellEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTableCellEditor : public DefaultTableCellEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTableCellEditorBase Inherited;
    typedef DefaultTableCellEditor     Self;

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
    
	virtual ComponentTransitPtr getTableCellEditorComponent(Table* const table, const boost::any& value, bool isSelected, UInt32 row, UInt32 column);

    virtual ComponentTransitPtr getCellEditor(const boost::any& Value, bool IsSelected);

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Returns the value contained in the editor.
    virtual boost::any getCellEditorValue(void) const;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const EventUnrecPtr anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const EventUnrecPtr anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    //Returns a reference to the editor component.
    Component* getComponent(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultTableCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTableCellEditor(void);
    DefaultTableCellEditor(const DefaultTableCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTableCellEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    class DefaultStringEditorListener : public ActionListener,public FocusListener,public KeyAdapter
    {
      public :
        DefaultStringEditorListener(DefaultTableCellEditor* const TheDefaultTableCellEditor);

        virtual void actionPerformed(const ActionEventUnrecPtr e);
        virtual void focusGained(const FocusEventUnrecPtr e);
        virtual void focusLost(const FocusEventUnrecPtr e);
        virtual void keyPressed(const KeyEventUnrecPtr e);
      protected :
        DefaultTableCellEditor* _DefaultTableCellEditor;
    };

	friend class DefaultStringEditorListener;

	DefaultStringEditorListener _DefaultStringEditorListener;
    
    mutable std::string _Value;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTableCellEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTableCellEditor &source);
};

typedef DefaultTableCellEditor *DefaultTableCellEditorP;

OSG_END_NAMESPACE

#include "OSGDefaultTableCellEditorBase.inl"
#include "OSGDefaultTableCellEditor.inl"

#endif /* _OSGDEFAULTTABLECELLEDITOR_H_ */
