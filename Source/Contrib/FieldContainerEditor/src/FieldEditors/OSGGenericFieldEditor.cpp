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

#include "OSGGenericFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include <sstream>
#include "OSGAttachmentMapFieldTraits.h"
#include "OSGChangedFunctorFieldTraits.h"
#include "OSGPointerSFieldBase.h"
#include "OSGFieldContainerSFieldHandle.h"
#include "OSGPointerMFieldBase.h"
#include "OSGFieldContainerMFieldHandle.h"
#include "OSGMaterialMapFields.h"
#include <boost/lexical_cast.hpp>
#include "OSGTextField.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGenericFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGGenericFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> GenericFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GenericFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        //Fill in all of the editable types
        UInt32 NumTypes(TypeFactory::the()->getNumTypes());
        DataType* type;
        for(UInt32 i(0) ; i<NumTypes; ++i)
        {
            type = dynamic_cast<DataType*>(TypeFactory::the()->findType(i));
            if(type != NULL &&
               !(dynamic_cast<FieldType*>(type) &&
                 (dynamic_cast<FieldType*>(type)->getClass() == FieldType::PtrField ||
                  dynamic_cast<FieldType*>(type)->getClass() == FieldType::ChildPtrField)) &&
                *type != FieldTraits<AttachmentMap>::getType() &&
                *type != FieldTraits<ChangedFunctorCallback>::getType())
            {
                _EditableTypes.push_back(type);
                FieldEditorFactory::the()->setEditorType(type, &getClassType(), "Generic");
            }
        }
        FieldEditorFactory::the()->removeEditorType(&FieldTraits<MaterialMap>::getType(), "Generic");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void GenericFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    if(TheFieldHandle->isPointerField())
    {
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            GetSFieldHandle<FieldContainerPtrSFieldBase>* ThePtrFieldHandle(dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get()));
            if(ThePtrFieldHandle->get() != NULL)
            {
                _EditingTextField->setText(boost::lexical_cast<std::string>(ThePtrFieldHandle->get()->getId()));
            }
            else
            {
                _EditingTextField->setText("0");
            }
        }
        else
        {
            GetMFieldHandle<FieldContainerPtrMFieldBase>* ThePtrFieldHandle(dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
            if(ThePtrFieldHandle->size() > getEditingFieldIndex() &&
               ThePtrFieldHandle->get(getEditingFieldIndex()) != NULL)
            {
                _EditingTextField->setText(boost::lexical_cast<std::string>(ThePtrFieldHandle->get(getEditingFieldIndex())->getId()));
            }
            else
            {
                _EditingTextField->setText("0");
            }
        }
    }
    else
    {
        std::ostringstream StrStream;
        OutStream TheOutStream(StrStream);
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            TheFieldHandle->pushValueToStream(TheOutStream);
        }
        else
        {
            TheFieldHandle->pushIndexedValueToStream(TheOutStream, getEditingFieldIndex());
        }

        //Remove quotes from strings
        if(TheFieldHandle->getType().getContentType() == FieldTraits<std::string>::getType())
        {
            _EditingTextField->setText(StrStream.str().substr(1,StrStream.str().size()-2));
        }
        else
        {
            _EditingTextField->setText(StrStream.str());
        }
    }

}

void GenericFieldEditor::internalStartEditing (void)
{
    _InitialValue =  _EditingTextField->getText();
}

void GenericFieldEditor::internalStopEditing  (void)
{
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), _EditingTextField->getText(), getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void GenericFieldEditor::internalCancelEditing(void)
{
    _EditingTextField->setText(_InitialValue);
}

const std::vector<const DataType*>& GenericFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void GenericFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingTextField->setPosition(TopLeft);
    _EditingTextField->setSize(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GenericFieldEditor::GenericFieldEditor(void) :
    Inherited()
{
}

GenericFieldEditor::GenericFieldEditor(const GenericFieldEditor &source) :
    Inherited(source)
{
}

GenericFieldEditor::~GenericFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void GenericFieldEditor::onCreate(const GenericFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingTextField = TextField::create();
        pushToChildren(_EditingTextField);
        _TextFieldFocusGainedConnection = _EditingTextField->connectFocusGained(boost::bind(&GenericFieldEditor::handleTextFieldFocusGained, this, _1));
        _TextFieldFocusLostConnection = _EditingTextField->connectFocusLost(boost::bind(&GenericFieldEditor::handleTextFieldFocusLost, this, _1));
        _TextFieldActionPerformedConnection = _EditingTextField->connectActionPerformed(boost::bind(&GenericFieldEditor::handleTextFieldActionPerformed, this, _1));
        _TextFieldKeyTypedConnection = _EditingTextField->connectKeyTyped(boost::bind(&GenericFieldEditor::handleTextFieldKeyTyped, this, _1));
    }
}

void GenericFieldEditor::onDestroy()
{
}

void GenericFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingTextField = NULL;

    _TextFieldFocusGainedConnection.disconnect();
    _TextFieldFocusLostConnection.disconnect();
    _TextFieldActionPerformedConnection.disconnect();
    _TextFieldKeyTypedConnection.disconnect();
}

void GenericFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GenericFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GenericFieldEditor NI" << std::endl;
}

void GenericFieldEditor::handleTextFieldFocusGained    (FocusEventDetails* const details)
{
    startEditing();
}

void GenericFieldEditor::handleTextFieldFocusLost      (FocusEventDetails* const details)
{
    stopEditing();
}

void GenericFieldEditor::handleTextFieldActionPerformed(ActionEventDetails* const details)
{
    stopEditing();
    startEditing();
}

void GenericFieldEditor::handleTextFieldKeyTyped       (KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        cancelEditing();
        startEditing();
    }
}

OSG_END_NAMESPACE
