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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFieldFactory.h>

#include "OSGDefaultTreeCellEditor.h"
#include "Component/Text/OSGTextField.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTreeCellEditor
A UI Default Tree Cell Editor.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTreeCellEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultTreeCellEditor::getTreeCellEditorComponent(TreePtr TheTree, SharedFieldPtr Value, bool IsSelected, bool IsExpanded, UInt32 row)
{
    _EditingValue = SharedFieldPtr(FieldFactory::the().createField(Value->getType().getId()));
    _EditingValue->setAbstrValue( *(Value.get()) );

	if(_EditingValue == NULL){
		return NullFC;
	}

    if(_EditingValue->getType() == SFString::getClassType())
    {
        //Use String Text Field As Editing Component
	    beginEditCP(getDefaultStringEditor(), TextField::TextFieldMask | TextField::CaretPositionFieldMask);
		    std::string tempString;
			tempString = dynamic_cast<SFString*>(_EditingValue.get())->getValue();
		    getDefaultStringEditor()->setText(tempString);
		    getDefaultStringEditor()->selectAll();
		    getDefaultStringEditor()->setCaretPosition(getDefaultStringEditor()->getText().size());
	    endEditCP(getDefaultStringEditor(), TextField::TextFieldMask | TextField::CaretPositionFieldMask);

        getDefaultStringEditor()->addActionListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->addFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->addKeyListener(&_DefaultTextFieldEditorListener);

	    return getDefaultStringEditor();
    }
    else
    {
        //Use Default Text Field As Editing Component
	    beginEditCP(getDefaultEditor(), TextField::TextFieldMask | TextField::CaretPositionFieldMask);
		    std::string tempString;
			_EditingValue->getValueByStr(tempString);
		    getDefaultEditor()->setText(tempString);
		    getDefaultEditor()->selectAll();
		    getDefaultEditor()->setCaretPosition(getDefaultEditor()->getText().size());
	    endEditCP(getDefaultEditor(), TextField::TextFieldMask | TextField::CaretPositionFieldMask);

        getDefaultEditor()->addActionListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->addFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->addKeyListener(&_DefaultTextFieldEditorListener);

	    return getDefaultEditor();
    }
}

ComponentPtr DefaultTreeCellEditor::getCellEditor(SharedFieldPtr Value, bool IsSelected)
{
    return getTreeCellEditorComponent(NullFC, Value, IsSelected, false, 0);
}

void DefaultTreeCellEditor::cancelCellEditing(void)
{
    if(_EditingValue->getType() == SFString::getClassType())
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultTextFieldEditorListener);
    }
    else
    {
        getDefaultEditor()->removeActionListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->removeFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->removeKeyListener(&_DefaultTextFieldEditorListener);
    }

    Inherited::cancelCellEditing();
}

SharedFieldPtr DefaultTreeCellEditor::getCellEditorValue(void) const
{
    if(_EditingValue->getType() == SFString::getClassType())
    {
        dynamic_cast<SFString*>(_EditingValue.get())->setValue(getDefaultStringEditor()->getText());
    }
    else
    {
        _EditingValue->pushValueByStr(getDefaultStringEditor()->getText().c_str());
    }
    return _EditingValue;
}

bool DefaultTreeCellEditor::isCellEditable(const Event& anEvent) const
{
    if(/*anEvent.getType() != MouseEvent::getClassType() ||*/
       (anEvent.getType() == MouseEvent::getClassType() &&
       dynamic_cast<const MouseEvent&>(anEvent).getClickCount() >= getClickCountToStart()))
    {
        return Inherited::isCellEditable(anEvent);
    }
    else
    {
        return false;
    }
}

bool DefaultTreeCellEditor::shouldSelectCell(const Event& anEvent) const
{
    return Inherited::shouldSelectCell(anEvent);
}

bool DefaultTreeCellEditor::stopCellEditing(void)
{
    if(_EditingValue->getType() == SFString::getClassType())
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultTextFieldEditorListener);
    }
    else
    {
        getDefaultEditor()->removeActionListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->removeFocusListener(&_DefaultTextFieldEditorListener);
        getDefaultEditor()->removeKeyListener(&_DefaultTextFieldEditorListener);
    }

    return Inherited::stopCellEditing();
}

ComponentPtr DefaultTreeCellEditor::getComponent(void) const
{
    if(_EditingValue->getType() == SFString::getClassType())
    {
        return getDefaultStringEditor();
    }
    else
    {
        return getDefaultEditor();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTreeCellEditor::DefaultTreeCellEditor(void) :
    Inherited(),
        _DefaultTextFieldEditorListener(DefaultTreeCellEditorPtr(this)),
        _EditingValue(new SFString())
{
}

DefaultTreeCellEditor::DefaultTreeCellEditor(const DefaultTreeCellEditor &source) :
    Inherited(source),
        _DefaultTextFieldEditorListener(DefaultTreeCellEditorPtr(this)),
        _EditingValue(new SFString())
{
}

DefaultTreeCellEditor::~DefaultTreeCellEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTreeCellEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultTreeCellEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultTreeCellEditor NI" << std::endl;
}


void DefaultTreeCellEditor::DefaultTextFieldEditorListener::actionPerformed(const ActionEvent& e)
{
    _DefaultTreeCellEditor->stopCellEditing();
}

void DefaultTreeCellEditor::DefaultTextFieldEditorListener::focusGained(const FocusEvent& e)
{
	//Do nothing
}

void DefaultTreeCellEditor::DefaultTextFieldEditorListener::focusLost(const FocusEvent& e)
{
    _DefaultTreeCellEditor->stopCellEditing();
}

void DefaultTreeCellEditor::DefaultTextFieldEditorListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE ||
		e.getKey() == KeyEvent::KEY_CANCEL)
	{
		_DefaultTreeCellEditor->cancelCellEditing();
	}
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDEFAULTTREECELLEDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTTREECELLEDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTTREECELLEDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

