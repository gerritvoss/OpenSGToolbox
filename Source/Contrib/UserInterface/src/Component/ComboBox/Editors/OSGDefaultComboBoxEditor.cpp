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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDefaultComboBoxEditor.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultComboBoxEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultComboBoxEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultComboBoxEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection DefaultComboBoxEditor::addActionListener(ActionListenerPtr Listener)
{
	if(getEditor() != NULL)
	{
		return getEditor()->addActionListener(Listener);
	}
    return EventConnection();
}

void DefaultComboBoxEditor::removeActionListener(ActionListenerPtr Listener)
{
	if(getEditor() != NULL)
	{
		getEditor()->removeActionListener(Listener);
	}
}

bool DefaultComboBoxEditor::isActionListenerAttached(ActionListenerPtr Listener) const
{
	if(getEditor() != NULL)
	{
		return getEditor()->isActionListenerAttached(Listener);
	}
}

ComponentRefPtr DefaultComboBoxEditor::getEditorComponent(void)
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
	if(getEditor() != NULL)
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
    getEditor()->setText(TheText);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultComboBoxEditor::onCreate(const DefaultComboBoxEditor * Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL && Id->getEditor() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(Id->getEditor()->shallowCopy());
        setEditor(dynamic_pointer_cast<TextField>(FCCopy));
    }
}

void DefaultComboBoxEditor::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

DefaultComboBoxEditor::DefaultComboBoxEditor(void) :
    Inherited(),
    _TextFieldListener(this)
{
}

DefaultComboBoxEditor::DefaultComboBoxEditor(const DefaultComboBoxEditor &source) :
    Inherited(source),
    _TextFieldListener(this)
{
}

DefaultComboBoxEditor::~DefaultComboBoxEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultComboBoxEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if((whichField & EditorFieldMask) && getEditor() != NULL)
	{
		getEditor()->addFocusListener(&_TextFieldListener);
	}
}

void DefaultComboBoxEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultComboBoxEditor NI" << std::endl;
}

void DefaultComboBoxEditor::TextFieldListener::focusGained(const FocusEventUnrecPtr e)
{
	//TODO: Implement
	_DefaultComboBoxEditor->selectAll();
}

void DefaultComboBoxEditor::TextFieldListener::focusLost(const FocusEventUnrecPtr e)
{
	//TODO: Implement
}

OSG_END_NAMESPACE
