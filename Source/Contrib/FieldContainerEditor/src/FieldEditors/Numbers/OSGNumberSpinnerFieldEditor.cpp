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

#include "OSGNumberSpinnerFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSysFieldTraits.h"
#include "OSGStringUtils.h"
#include "OSGSpinner.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNumberSpinnerFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGNumberSpinnerFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const DataType*> NumberSpinnerFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NumberSpinnerFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        _EditableTypes.push_back(&FieldTraits<UInt8>::getType());
        _EditableTypes.push_back(&FieldTraits<UInt16>::getType());
        _EditableTypes.push_back(&FieldTraits<UInt32>::getType());
        _EditableTypes.push_back(&FieldTraits<UInt64>::getType());
        _EditableTypes.push_back(&FieldTraits<Int8>::getType());
        _EditableTypes.push_back(&FieldTraits<Int16>::getType());
        _EditableTypes.push_back(&FieldTraits<Int32>::getType());
        _EditableTypes.push_back(&FieldTraits<Int64>::getType());
        //_EditableTypes.push_back(&FieldTraits<Real16>::getType());
        _EditableTypes.push_back(&FieldTraits<Real32>::getType());
        _EditableTypes.push_back(&FieldTraits<Real64>::getType());
        _EditableTypes.push_back(&FieldTraits<Fixed32>::getType());
        
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "Spinner");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool NumberSpinnerFieldEditor::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    Inherited::internalAttachField(fc, fieldId, index);

    const DataType& type(fc->getFieldDescription(fieldId)->getFieldType().getContentType());

    if(type == FieldTraits<UInt8>::getType())
    {
        UInt8SpinnerModelPtr model(new UInt8SpinnerModel());
        model->setMaximum(TypeTraits<UInt8>::getMax());
        model->setMinimum(TypeTraits<UInt8>::getMin());
        model->setStepSize(TypeTraits<UInt8>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<UInt16>::getType())
    {
        UInt16SpinnerModelPtr model(new UInt16SpinnerModel());
        model->setMaximum(TypeTraits<UInt16>::getMax());
        model->setMinimum(TypeTraits<UInt16>::getMin());
        model->setStepSize(TypeTraits<UInt16>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<UInt32>::getType())
    {
        UInt32SpinnerModelPtr model(new UInt32SpinnerModel());
        model->setMaximum(TypeTraits<UInt32>::getMax());
        model->setMinimum(TypeTraits<UInt32>::getMin());
        model->setStepSize(TypeTraits<UInt32>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<UInt64>::getType())
    {
        UInt64SpinnerModelPtr model(new UInt64SpinnerModel());
        model->setMaximum(TypeTraits<UInt64>::getMax());
        model->setMinimum(TypeTraits<UInt64>::getMin());
        model->setStepSize(TypeTraits<UInt64>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Int8>::getType())
    {
        Int8SpinnerModelPtr model(new Int8SpinnerModel());
        model->setMaximum(TypeTraits<Int8>::getMax());
        model->setMinimum(TypeTraits<Int8>::getMin());
        model->setStepSize(TypeTraits<Int8>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Int16>::getType())
    {
        Int16SpinnerModelPtr model(new Int16SpinnerModel());
        model->setMaximum(TypeTraits<Int16>::getMax());
        model->setMinimum(TypeTraits<Int16>::getMin());
        model->setStepSize(TypeTraits<Int16>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Int32>::getType())
    {
        Int32SpinnerModelPtr model(new Int32SpinnerModel());
        model->setMaximum(TypeTraits<Int32>::getMax());
        model->setMinimum(TypeTraits<Int32>::getMin());
        model->setStepSize(TypeTraits<Int32>::getOneElement());
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Int64>::getType())
    {
        Int64SpinnerModelPtr model(new Int64SpinnerModel());
        model->setMaximum(TypeTraits<Int64>::getMax());
        model->setMinimum(TypeTraits<Int64>::getMin());
        model->setStepSize(TypeTraits<Int64>::getOneElement());
        _EditingSpinnerModel = model;
    }
    /*else if(type == FieldTraits<Real16>::getType())
    {
        Real16SpinnerModelPtr model(new Real16SpinnerModel());
        model->setMaximum(TypeTraits<Real16>::getMax());
        model->setMinimum(TypeTraits<Real16>::getMin());
        model->setStepSize(0.1);
        _EditingSpinnerModel = model;
    }*/
    else if(type == FieldTraits<Real32>::getType())
    {
        Real32SpinnerModelPtr model(new Real32SpinnerModel());
        model->setMaximum(TypeTraits<Real32>::getMax());
        model->setMinimum(TypeTraits<Real32>::getMin());
        model->setStepSize(0.1);
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Real64>::getType())
    {
        Real64SpinnerModelPtr model(new Real64SpinnerModel());
        model->setMaximum(TypeTraits<Real64>::getMax());
        model->setMinimum(TypeTraits<Real64>::getMin());
        model->setStepSize(0.1);
        _EditingSpinnerModel = model;
    }
    else if(type == FieldTraits<Fixed32>::getType())
    {
        Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
        model->setMaximum(TypeTraits<Fixed32>::getMax());
        model->setMinimum(TypeTraits<Fixed32>::getMin());
        model->setStepSize(0.1);
        _EditingSpinnerModel = model;
    }
    else
    {
        return false;
    }
    _SpinnerStateChangedConnection = _EditingSpinnerModel->connectStateChanged(boost::bind(&NumberSpinnerFieldEditor::handleSpinnerStateChanged, this, _1));
    _EditingSpinner->setModel(_EditingSpinnerModel);

    return true;
}

void NumberSpinnerFieldEditor::internalFieldChanged (void)
{
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    _SpinnerStateChangedConnection.disconnect();
    if(type == FieldTraits<UInt8>::getType())
    {
        UInt8 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFUInt8*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFUInt8*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<UInt8SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<UInt16>::getType())
    {
        UInt16 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFUInt16*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFUInt16*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<UInt16SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<UInt32>::getType())
    {
        UInt32 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFUInt32*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFUInt32*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<UInt32SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<UInt64>::getType())
    {
        UInt64 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFUInt64*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFUInt64*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<UInt64SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Int8>::getType())
    {
        Int8 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFInt8*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFInt8*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Int8SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Int16>::getType())
    {
        Int16 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFInt16*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFInt16*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Int16SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Int32>::getType())
    {
        Int32 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFInt32*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFInt32*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Int32SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Int64>::getType())
    {
        Int64 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFInt64*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFInt64*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Int64SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    /*else if(type == FieldTraits<Real16>::getType())
    {
        Real16 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFReal16*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFReal16*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Real16SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }*/
    else if(type == FieldTraits<Real32>::getType())
    {
        Real32 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFReal32*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFReal32*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Real32SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Real64>::getType())
    {
        Real64 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFReal64*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFReal64*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Real64SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else if(type == FieldTraits<Fixed32>::getType())
    {
        Fixed32 Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFFixed32*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFFixed32*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModel.get())->setNumberValue(Value);
    }
    else
    {
        assert(false && "Should not reach this.");
    }
    _SpinnerStateChangedConnection = _EditingSpinnerModel->connectStateChanged(boost::bind(&NumberSpinnerFieldEditor::handleSpinnerStateChanged, this, _1));
}

void NumberSpinnerFieldEditor::internalStartEditing (void)
{
}

void NumberSpinnerFieldEditor::internalStopEditing  (void)
{
}

void NumberSpinnerFieldEditor::runCommand  (void)
{
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), 
                                                                      getEditingFieldId(), 
                                                                      lexical_cast(_EditingSpinnerModel->getValue()), 
                                                                      getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void NumberSpinnerFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& NumberSpinnerFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void NumberSpinnerFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingSpinner->setPosition(TopLeft);
    _EditingSpinner->setSize(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

NumberSpinnerFieldEditor::NumberSpinnerFieldEditor(void) :
    Inherited()
{
}

NumberSpinnerFieldEditor::NumberSpinnerFieldEditor(const NumberSpinnerFieldEditor &source) :
    Inherited(source)
{
}

NumberSpinnerFieldEditor::~NumberSpinnerFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void NumberSpinnerFieldEditor::onCreate(const NumberSpinnerFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingSpinner = Spinner::create();
        pushToChildren(_EditingSpinner);
    }
}

void NumberSpinnerFieldEditor::onDestroy()
{
}

void NumberSpinnerFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingSpinner = NULL;

    _SpinnerStateChangedConnection.disconnect();
}

void NumberSpinnerFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void NumberSpinnerFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump NumberSpinnerFieldEditor NI" << std::endl;
}

void NumberSpinnerFieldEditor::handleSpinnerStateChanged(ChangeEventDetails* const details)
{
    runCommand();
}

OSG_END_NAMESPACE
