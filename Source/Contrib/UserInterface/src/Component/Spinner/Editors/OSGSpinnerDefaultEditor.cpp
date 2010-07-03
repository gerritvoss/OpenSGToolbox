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

#include "OSGSpinnerDefaultEditor.h"
#include "OSGSpinner.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSpinnerDefaultEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGSpinnerDefaultEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpinnerDefaultEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpinnerDefaultEditor::updateLayout(void)
{
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->setPosition(Pnt2f(0,0));
        getChildren(i)->setSize(getSize());
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
        std::string NewValue;
        try
        {
            getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
        }
        catch(boost::bad_any_cast &)
        {
            getTextField()->setText("");
        }
    }
}

void SpinnerDefaultEditor::cancelEdit(void)
{
    //Reset to the old value
    std::string NewValue;
    try
    {
        getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
    }
    catch(boost::bad_any_cast &)
    {
        getTextField()->setText("");
    }
}

void SpinnerDefaultEditor::dismiss(Spinner* const spinner)
{
    if(getSpinner() != NULL)
    {
        getSpinner()->removeChangeListener(this);
    }
}

void SpinnerDefaultEditor::stateChanged(const ChangeEventUnrecPtr e)
{
    //Update the Value of the TextField
    std::string NewValue;
    try
    {
        getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
    }
    catch(boost::bad_any_cast &)
    {
        getTextField()->setText("");
    }
}

void SpinnerDefaultEditor::setEditable(bool Editable)
{
    getTextField()->setEditable(Editable);
}

bool SpinnerDefaultEditor::getEditable(void) const
{
    return getTextField()->getEditable();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SpinnerDefaultEditor::onCreate(const SpinnerDefaultEditor * Id)
{
    if(Id != NULL &&
       Id->getTextField() != NULL)
    {
        FieldContainerUnrecPtr TheFC(Id->getTextField()->shallowCopy());

        setTextField(dynamic_pointer_cast<TextField>(TheFC));
        
    }
}

void SpinnerDefaultEditor::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

SpinnerDefaultEditor::SpinnerDefaultEditor(void) :
    Inherited(),
		_EditorTextFieldListener(this)
{
}

SpinnerDefaultEditor::SpinnerDefaultEditor(const SpinnerDefaultEditor &source) :
    Inherited(source),
		_EditorTextFieldListener(this)
{
}

SpinnerDefaultEditor::~SpinnerDefaultEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpinnerDefaultEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SpinnerFieldMask && getSpinner() != NULL)
    {
        getSpinner()->addChangeListener(this);
        
        //Update the Value of the TextField
		    std::string NewValue;
            try
            {
                getTextField()->setText(lexical_cast(getSpinner()->getModel()->getValue()));
            }
            catch(boost::bad_any_cast &)
            {
			    getTextField()->setText("");
            }
    }

    if(whichField & TextFieldFieldMask)
    {
            clearChildren();
            if(getTextField() != NULL)
            {
                pushToChildren(getTextField());
				getTextField()->addActionListener(&_EditorTextFieldListener);
				getTextField()->addFocusListener(&_EditorTextFieldListener);
				getTextField()->addKeyListener(&_EditorTextFieldListener);
            }
    }
}

void SpinnerDefaultEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SpinnerDefaultEditor NI" << std::endl;
}

void SpinnerDefaultEditor::EditorTextFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
	_SpinnerDefaultEditor->commitEdit();
}

void SpinnerDefaultEditor::EditorTextFieldListener::focusGained(const FocusEventUnrecPtr e)
{
	//Do Nothing
}

void SpinnerDefaultEditor::EditorTextFieldListener::focusLost(const FocusEventUnrecPtr e)
{
	_SpinnerDefaultEditor->commitEdit();
}

void SpinnerDefaultEditor::EditorTextFieldListener::keyPressed(const KeyEventUnrecPtr e)
{
	if(e->getKey() == KeyEvent::KEY_ESCAPE)
	{
		_SpinnerDefaultEditor->cancelEdit();
	}
}

OSG_END_NAMESPACE
