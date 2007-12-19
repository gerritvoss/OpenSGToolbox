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

#ifndef _OSGDEFAULTTREECELLEDITOR_H_
#define _OSGDEFAULTTREECELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDefaultTreeCellEditorBase.h"
#include "Event/OSGActionListener.h"
#include "Event/OSGFocusListener.h"
#include <OpenSG/Input/OSGKeyAdapter.h>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeCellEditor class. See \ref 
           PageUserInterfaceDefaultTreeCellEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultTreeCellEditor : public DefaultTreeCellEditorBase
{
  private:

    typedef DefaultTreeCellEditorBase Inherited;

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
	virtual ComponentPtr getTreeCellEditorComponent(TreePtr TheTree, SharedFieldPtr Value, bool IsSelected, bool IsExpanded, UInt32 row);
    
    virtual ComponentPtr getCellEditor(SharedFieldPtr Value, bool IsSelected);
    
    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Returns the value contained in the editor.
    virtual SharedFieldPtr getCellEditorValue(void) const;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    //Returns a reference to the editor component.
    ComponentPtr getComponent(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultTreeCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTreeCellEditor(void);
    DefaultTreeCellEditor(const DefaultTreeCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTreeCellEditor(void); 

    /*! \}                                                                 */

	class DefaultTextFieldEditorListener : public ActionListener,public FocusListener,public KeyAdapter
	{
	public :
		DefaultTextFieldEditorListener(DefaultTreeCellEditorPtr TheDefaultTreeCellEditor);
		
        virtual void actionPerformed(const ActionEvent& e);
        virtual void focusGained(const FocusEvent& e);
        virtual void focusLost(const FocusEvent& e);
        virtual void keyPressed(const KeyEvent& e);
	protected :
		DefaultTreeCellEditorPtr _DefaultTreeCellEditor;
	};

	friend class DefaultTextFieldEditorListener;

	DefaultTextFieldEditorListener _DefaultTextFieldEditorListener;

    SharedFieldPtr _EditingValue;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultTreeCellEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultTreeCellEditor &source);
};

typedef DefaultTreeCellEditor *DefaultTreeCellEditorP;

OSG_END_NAMESPACE

#include "OSGDefaultTreeCellEditorBase.inl"
#include "OSGDefaultTreeCellEditor.inl"

#define OSGDEFAULTTREECELLEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTTREECELLEDITOR_H_ */
