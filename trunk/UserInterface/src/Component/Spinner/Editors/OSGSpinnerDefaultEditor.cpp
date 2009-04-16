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

#include "OSGSpinnerDefaultEditor.h"
#include "Component/Spinner/OSGSpinner.h"
#include <OpenSG/Toolbox/OSGStringUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SpinnerDefaultEditor
A UI SpinnerDefaultEditor. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpinnerDefaultEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpinnerDefaultEditor::updateLayout(void)
{
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren()[i], PositionFieldMask | SizeFieldMask);
            getChildren()[i]->setPosition(Pnt2f(0,0));
            getChildren()[i]->setSize(getSize());
        endEditCP(getChildren()[i], PositionFieldMask | SizeFieldMask);
    }
}

void SpinnerDefaultEditor::commitEdit(void)
{
	try
	{
		getSpinner()->getModel()->setValue(getTextField()->getText());
	}
	catch(IllegalArgumentException&)
	{
		//Reset to the old value
		beginEditCP(getTextField(), TextField::TextFieldMask);
			std::string NewValue;
            try
            {
                getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
            }
            catch(boost::bad_any_cast &)
            {
				getTextField()->setText("");
            }
		endEditCP(getTextField(), TextField::TextFieldMask);
	}
}

void SpinnerDefaultEditor::cancelEdit(void)
{
	//Reset to the old value
	beginEditCP(getTextField(), TextField::TextFieldMask);
		std::string NewValue;
        try
        {
            getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
        }
        catch(boost::bad_any_cast &)
        {
			getTextField()->setText("");
        }
	endEditCP(getTextField(), TextField::TextFieldMask);
}

void SpinnerDefaultEditor::dismiss(SpinnerPtr spinner)
{
    if(getSpinner() != NullFC)
    {
        getSpinner()->removeChangeListener(this);
    }
}

void SpinnerDefaultEditor::stateChanged(const ChangeEvent& e)
{
    //Update the Value of the TextField
	beginEditCP(getTextField(), TextField::TextFieldMask);
		std::string NewValue;
        try
        {
            getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
        }
        catch(boost::bad_any_cast &)
        {
			getTextField()->setText("");
        }
	endEditCP(getTextField(), TextField::TextFieldMask);
}

void SpinnerDefaultEditor::setEditable(bool Editable)
{
    beginEditCP(getTextField(), TextField::EditableFieldMask);
        getTextField()->setEditable(Editable);
    endEditCP(getTextField(), TextField::EditableFieldMask);
}

bool SpinnerDefaultEditor::getEditable(void) const
{
	return getTextField()->getEditable();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SpinnerDefaultEditor::SpinnerDefaultEditor(void) :
    Inherited(),
		_EditorTextFieldListener(SpinnerDefaultEditorPtr(this))
{
}

SpinnerDefaultEditor::SpinnerDefaultEditor(const SpinnerDefaultEditor &source) :
    Inherited(source),
		_EditorTextFieldListener(SpinnerDefaultEditorPtr(this))
{
    if(getTextField() != NullFC)
    {
        beginEditCP(SpinnerDefaultEditorPtr(this), TextFieldFieldMask);

        setTextField(TextField::Ptr::dcast(getTextField()->shallowCopy()));
        
        endEditCP(SpinnerDefaultEditorPtr(this), TextFieldFieldMask);
    }
}

SpinnerDefaultEditor::~SpinnerDefaultEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpinnerDefaultEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & SpinnerFieldMask && getSpinner() != NullFC)
    {
        getSpinner()->addChangeListener(this);
        
        //Update the Value of the TextField
	    beginEditCP(getTextField(), TextField::TextFieldMask);
		    std::string NewValue;
            try
            {
                getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
            }
            catch(boost::bad_any_cast &)
            {
			    getTextField()->setText("");
            }
	    endEditCP(getTextField(), TextField::TextFieldMask);
    }

    if(whichField & TextFieldFieldMask)
    {
        beginEditCP(SpinnerDefaultEditorPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getTextField() != NullFC)
            {
                getChildren().push_back(getTextField());
				getTextField()->addActionListener(&_EditorTextFieldListener);
				getTextField()->addFocusListener(&_EditorTextFieldListener);
				getTextField()->addKeyListener(&_EditorTextFieldListener);
            }
        endEditCP(SpinnerDefaultEditorPtr(this), ChildrenFieldMask);
    }
}

void SpinnerDefaultEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SpinnerDefaultEditor NI" << std::endl;
}

void SpinnerDefaultEditor::EditorTextFieldListener::actionPerformed(const ActionEvent& e)
{
	_SpinnerDefaultEditor->commitEdit();
}

void SpinnerDefaultEditor::EditorTextFieldListener::focusGained(const FocusEvent& e)
{
	//Do Nothing
}

void SpinnerDefaultEditor::EditorTextFieldListener::focusLost(const FocusEvent& e)
{
	_SpinnerDefaultEditor->commitEdit();
}

void SpinnerDefaultEditor::EditorTextFieldListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		_SpinnerDefaultEditor->cancelEdit();
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
    static Char8 cvsid_hpp       [] = OSGSPINNERDEFAULTEDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPINNERDEFAULTEDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPINNERDEFAULTEDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

