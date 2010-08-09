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

#include "OSGBoolFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSysFieldTraits.h"
#include "OSGCheckboxButton.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBoolFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGBoolFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> BoolFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BoolFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        const DataType* type(&FieldTraits<bool, 2>::getType());
        _EditableTypes.push_back(type);
        FieldEditorFactory::the()->setSingleDefaultEditor(type, &getClassType());
        FieldEditorFactory::the()->setEditorType(type, &getClassType(), "Checkbox");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void BoolFieldEditor::internalFieldChanged (void)
{

    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());
    bool Value;

    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        Value = static_cast<const SFBool*>(TheFieldHandle->getField())->getValue();
    }
    else
    {
        Value = static_cast<const MFBool*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
    }

    if(_EditingCheckbox->getSelected() != Value)
    {
        _ButtonSelectedConnection.disconnect();
        _ButtonDeselectedConnection.disconnect();

        _EditingCheckbox->setSelected(Value);
    }

    _ButtonSelectedConnection = _EditingCheckbox->connectButtonSelected(boost::bind(&BoolFieldEditor::handleButtonSelected, this, _1));
    _ButtonDeselectedConnection = _EditingCheckbox->connectButtonDeselected(boost::bind(&BoolFieldEditor::handleButtonDeselected, this, _1));

}

void BoolFieldEditor::internalStartEditing (void)
{
}

void BoolFieldEditor::internalStopEditing  (void)
{
}

void BoolFieldEditor::runCommand  (bool value)
{
    bool fieldValue;
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        fieldValue = static_cast<const SFBool*>(TheFieldHandle->getField())->getValue();
    }
    else
    {
        fieldValue = static_cast<const MFBool*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
    }

    if(value != fieldValue)
    {
        //Call the command to set the Field
        SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), 
                                                                          getEditingFieldId(), 
                                                                          (value ? "TRUE" : "FALSE"), 
                                                                          getEditingFieldIndex());

        getCommandManager()->executeCommand(SetCommand);
    }
}

void BoolFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& BoolFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void BoolFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingCheckbox->setPosition(TopLeft);
    _EditingCheckbox->setSize(BottomRight - TopLeft);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoolFieldEditor::BoolFieldEditor(void) :
    Inherited()
{
}

BoolFieldEditor::BoolFieldEditor(const BoolFieldEditor &source) :
    Inherited(source)
{
}

BoolFieldEditor::~BoolFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void BoolFieldEditor::onCreate(const BoolFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingCheckbox = CheckboxButton::create();
        _EditingCheckbox->setAlignment(Vec2f(0.05f, 0.5f));
        pushToChildren(_EditingCheckbox);
    }
}

void BoolFieldEditor::onDestroy()
{
}

void BoolFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingCheckbox = NULL;

    _ButtonSelectedConnection.disconnect();
    _ButtonDeselectedConnection.disconnect();
}


void BoolFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BoolFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BoolFieldEditor NI" << std::endl;
}

void BoolFieldEditor::handleButtonSelected(ButtonSelectedEventDetails* const details)
{
    runCommand(true);
}

void BoolFieldEditor::handleButtonDeselected(ButtonSelectedEventDetails* const details)
{
    runCommand(false);
}

OSG_END_NAMESPACE
