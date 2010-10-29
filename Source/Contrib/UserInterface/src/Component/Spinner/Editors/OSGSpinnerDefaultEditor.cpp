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
        if(getChildren(i)->getPosition() != Pnt2f(0,0))
        {
            getChildren(i)->setPosition(Pnt2f(0,0));
        }
        if(getChildren(i)->getSize() != getSize())
        {
            getChildren(i)->setSize(getSize());
        }
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
            getTextField()->setText(getSpinner()->getModel()->getValueAsString());
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
        getTextField()->setText(getSpinner()->getModel()->getValueAsString());
    }
    catch(boost::bad_any_cast &)
    {
        getTextField()->setText("");
    }
}

void SpinnerDefaultEditor::dismiss(Spinner* const spinner)
{
    _ModelStateChangedConnection.disconnect();
}

void SpinnerDefaultEditor::handleModelStateChanged(ChangeEventDetails* const e)
{
    //Update the Value of the TextField
    std::string NewValue;
    try
    {
        getTextField()->setText(getSpinner()->getModel()->getValueAsString());
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

void SpinnerDefaultEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ModelStateChangedConnection.disconnect();
    _EditorTextFieldActionConnection.disconnect();
    _EditorTextFieldFocusLostConnection.disconnect();
    _EditorTextFieldKeyPressedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

SpinnerDefaultEditor::SpinnerDefaultEditor(void) :
    Inherited()
{
}

SpinnerDefaultEditor::SpinnerDefaultEditor(const SpinnerDefaultEditor &source) :
    Inherited(source)
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

    if(whichField & SpinnerFieldMask)
    {
        _EditorTextFieldActionConnection.disconnect();
        if(getSpinner() != NULL)
        {
            _ModelStateChangedConnection = getSpinner()->getModel()->connectStateChanged(boost::bind(&SpinnerDefaultEditor::handleModelStateChanged, this, _1));
            
            if(getTextField() != NULL)
            {
                //Update the Value of the TextField
	            std::string NewValue;
                try
                {
                    getTextField()->setText(getSpinner()->getModel()->getValueAsString());
                }
                catch(boost::bad_any_cast &)
                {
		            getTextField()->setText("");
                }
            }
        }
    }

    if(whichField & TextFieldFieldMask)
    {
        clearChildren();
        _EditorTextFieldActionConnection.disconnect();
        _EditorTextFieldFocusLostConnection.disconnect();
        _EditorTextFieldKeyPressedConnection.disconnect();
        if(getTextField() != NULL)
        {
            pushToChildren(getTextField());
            _EditorTextFieldActionConnection = getTextField()->connectActionPerformed(boost::bind(&SpinnerDefaultEditor::handleEditorTextFieldActionPerformed, this, _1));
            _EditorTextFieldFocusLostConnection = getTextField()->connectFocusLost(boost::bind(&SpinnerDefaultEditor::handleEditorTextFieldFocusLost, this, _1));
            _EditorTextFieldKeyPressedConnection = getTextField()->connectKeyPressed(boost::bind(&SpinnerDefaultEditor::handleEditorTextFieldKeyPressed, this, _1));
        }
    }
}

void SpinnerDefaultEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SpinnerDefaultEditor NI" << std::endl;
}

void SpinnerDefaultEditor::handleEditorTextFieldActionPerformed(ActionEventDetails* const e)
{
	commitEdit();
}

void SpinnerDefaultEditor::handleEditorTextFieldFocusLost(FocusEventDetails* const e)
{
	commitEdit();
}

void SpinnerDefaultEditor::handleEditorTextFieldKeyPressed(KeyEventDetails* const e)
{
	if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
	{
		cancelEdit();
	}
}

OSG_END_NAMESPACE
