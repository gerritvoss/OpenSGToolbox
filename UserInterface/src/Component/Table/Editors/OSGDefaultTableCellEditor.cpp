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

#include "OSGDefaultTableCellEditor.h"
#include "Background/OSGColorUIBackground.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Component/Text/OSGTextField.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultTableCellEditor
A UI Default Table Cell Editor. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultTableCellEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultTableCellEditor::getTableCellEditorComponent(TablePtr table, SharedFieldPtr value, bool isSelected, UInt32 row, UInt32 column)
{
	if(value == NULL){
		return NullFC;
	}
	TextFieldPtr TheTextField = TextField::create();
	beginEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask | TextField::HorizontalAlignmentFieldMask | TextField::CaretPositionFieldMask);
		std::string tempString;
		if(value->getType() == SFString::getClassType())
		{
			tempString = dynamic_cast<SFString*>(value.get())->getValue();
		}
		else
		{
			value->getValueByStr(tempString);
		}
		TheTextField->setText(tempString);
		TheTextField->setPreferredSize(Vec2s(100,30));
		TheTextField->setHorizontalAlignment(0.5);
		TheTextField->selectAll();
		TheTextField->setCaretPosition(TheTextField->getText().size());
	endEditCP(TheTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask | TextField::HorizontalAlignmentFieldMask | TextField::CaretPositionFieldMask);
	ColorUIBackgroundPtr tempBackground;
	tempBackground = ColorUIBackground::create();

	beginEditCP(TheTextField, TextField::BackgroundFieldMask);
		TheTextField->setBackground(tempBackground);
	endEditCP(TheTextField, TextField::BackgroundFieldMask);

	beginEditCP(tempBackground, ColorUIBackground::ColorFieldMask);
		//if(isSelected){
		//	tempBackground->setColor(Color4f(0.4, 0.4, 1.0, 1.0));
		//}
		//else{
			tempBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		//}
	endEditCP(tempBackground, ColorUIBackground::ColorFieldMask);

	LineBorderPtr tempBorder;

	tempBorder = LineBorder::create();
	beginEditCP(tempBorder, LineBorder::ColorFieldMask);
		tempBorder->setColor(Color4f(0.0, 0.0, 1.0, 1.0));
	endEditCP(tempBorder, LineBorder::ColorFieldMask);

	beginEditCP(TheTextField, TextField::BorderFieldMask);
		TheTextField->setBorder(tempBorder);
	endEditCP(TheTextField, TextField::BorderFieldMask);

    beginEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
        setDefaultStringEditor(TheTextField);
    endEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
    getDefaultStringEditor()->addActionListener(&_DefaultStringEditorListener);
    getDefaultStringEditor()->addFocusListener(&_DefaultStringEditorListener);
    getDefaultStringEditor()->addKeyListener(&_DefaultStringEditorListener);
	return getDefaultStringEditor();
}

void DefaultTableCellEditor::cancelCellEditing(void)
{
    if(getDefaultStringEditor() != NullFC)
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultStringEditorListener);
    }
    AbstractCellEditor::cancelCellEditing();
    beginEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
        setDefaultStringEditor(NullFC);
    endEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
}

SharedFieldPtr DefaultTableCellEditor::getCellEditorValue(void) const
{
    _Value->setValue(getDefaultStringEditor()->getText());
    return SharedFieldPtr(_Value);
}

bool DefaultTableCellEditor::isCellEditable(const Event& anEvent) const
{
    if(/*anEvent.getType() != MouseEvent::getClassType() ||*/
       (anEvent.getType() == MouseEvent::getClassType() &&
       dynamic_cast<const MouseEvent&>(anEvent).getClickCount() >= getClickCountToStart()))
    {
        return AbstractCellEditor::isCellEditable(anEvent);
    }
    else
    {
        return false;
    }
}

bool DefaultTableCellEditor::shouldSelectCell(const Event& anEvent) const
{
    return AbstractCellEditor::shouldSelectCell(anEvent);
}

bool DefaultTableCellEditor::stopCellEditing(void)
{
    if(getDefaultStringEditor() != NullFC)
    {
        getDefaultStringEditor()->removeActionListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeFocusListener(&_DefaultStringEditorListener);
        getDefaultStringEditor()->removeKeyListener(&_DefaultStringEditorListener);
    }
    bool Return =  AbstractCellEditor::stopCellEditing();
    beginEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
        setDefaultStringEditor(NullFC);
    endEditCP(DefaultTableCellEditorPtr(this), DefaultStringEditorFieldMask);
    return Return;
}

void DefaultTableCellEditor::DefaultStringEditorListener::actionPerformed(const ActionEvent& e)
{
    _DefaultTableCellEditor->stopCellEditing();
}

void DefaultTableCellEditor::DefaultStringEditorListener::focusGained(const FocusEvent& e)
{
	//Do nothing
}

void DefaultTableCellEditor::DefaultStringEditorListener::focusLost(const FocusEvent& e)
{
    _DefaultTableCellEditor->stopCellEditing();
}

void DefaultTableCellEditor::DefaultStringEditorListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE ||
		e.getKey() == KeyEvent::KEY_CANCEL)
	{
		_DefaultTableCellEditor->cancelCellEditing();
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultTableCellEditor::DefaultTableCellEditor(void) :
    Inherited(),
        _DefaultStringEditorListener(DefaultTableCellEditorPtr(this)),
        _Value(new SFString(""))
{
}

DefaultTableCellEditor::DefaultTableCellEditor(const DefaultTableCellEditor &source) :
    Inherited(source),
        _DefaultStringEditorListener(DefaultTableCellEditorPtr(this)),
        _Value(new SFString(""))
{
}

DefaultTableCellEditor::~DefaultTableCellEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultTableCellEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultTableCellEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultTableCellEditor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTTABLECELLEDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTTABLECELLEDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTTABLECELLEDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

