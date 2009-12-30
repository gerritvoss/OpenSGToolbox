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

#include "OSGDefaultComboBoxEditor.h"
#include "Component/Text/OSGTextField.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultComboBoxEditor
A UI DefaultComboBoxEditor. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultComboBoxEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection DefaultComboBoxEditor::addActionListener(ActionListenerPtr Listener)
{
	if(getEditor() != NullFC)
	{
		return getEditor()->addActionListener(Listener);
	}
    return EventConnection();
}

void DefaultComboBoxEditor::removeActionListener(ActionListenerPtr Listener)
{
	if(getEditor() != NullFC)
	{
		getEditor()->removeActionListener(Listener);
	}
}

bool DefaultComboBoxEditor::isActionListenerAttached(ActionListenerPtr Listener) const
{
	if(getEditor() != NullFC)
	{
		return getEditor()->isActionListenerAttached(Listener);
	}
}

ComponentPtr DefaultComboBoxEditor::getEditorComponent(void)
{
	return getEditor();
}

boost::any DefaultComboBoxEditor::getItem(void)
{
    return boost::any(getEditor()->getText());
}

void DefaultComboBoxEditor::selectAll(void)
{
	//TODO: Implement
	if(getEditor() != NullFC)
	{
		getEditor()->selectAll();
	}
}

void DefaultComboBoxEditor::setItem(const boost::any& anObject)
{	
	//Update the text of the TextField to this new Item
	std::string TheText;
    try
    {
        TheText = lexical_cast(anObject);
    }
    catch (boost::bad_lexical_cast &)
    {
        //Could not convert to string
    }
	beginEditCP(getEditor(), TextField::TextFieldMask);
		getEditor()->setText(TheText);
	endEditCP(getEditor(), TextField::TextFieldMask);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultComboBoxEditor::DefaultComboBoxEditor(void) :
    Inherited(),
    _TextFieldListener(DefaultComboBoxEditorPtr(this))
{
}

DefaultComboBoxEditor::DefaultComboBoxEditor(const DefaultComboBoxEditor &source) :
    Inherited(source),
    _TextFieldListener(DefaultComboBoxEditorPtr(this))
{
    if(getEditor() != NullFC)
    {
        beginEditCP(DefaultComboBoxEditorPtr(this), EditorFieldMask);
			setEditor(TextField::Ptr::dcast(getEditor()->shallowCopy()));
        endEditCP(DefaultComboBoxEditorPtr(this), EditorFieldMask);
    }
}

DefaultComboBoxEditor::~DefaultComboBoxEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultComboBoxEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & EditorFieldMask) && getEditor() != NullFC)
	{
		getEditor()->addFocusListener(&_TextFieldListener);
	}
}

void DefaultComboBoxEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultComboBoxEditor NI" << std::endl;
}

void DefaultComboBoxEditor::TextFieldListener::focusGained(const FocusEventPtr e)
{
	//TODO: Implement
	_DefaultComboBoxEditor->selectAll();
}

void DefaultComboBoxEditor::TextFieldListener::focusLost(const FocusEventPtr e)
{
	//TODO: Implement
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTCOMBOBOXEDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTCOMBOBOXEDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTCOMBOBOXEDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

