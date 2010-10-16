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

#include "OSGMaterialMapKeyFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGRenderPropertiesPool.h"
#include "OSGTextField.h"
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMaterialMapKeyFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialMapKeyFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> MaterialMapKeyFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialMapKeyFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        _EditableTypes.push_back(&FieldTraits<MaterialMapKey>::getType());
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "MaterialMapKey");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void MaterialMapKeyFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    MaterialMapKey Value;
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        Value = static_cast<const SFMaterialMapKey*>(TheFieldHandle->getField())->getValue();
    }
    else
    {
        Value = static_cast<const MFMaterialMapKey*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
    }

    const Char8 *NamedProp(RenderPropertiesPool::the()->findName(Value));

    //Remove quotes from strings
    if(NamedProp)
    {
        _EditingTextField->setText(NamedProp);
    }
    else
    {
        _EditingTextField->setText("Default");
    }

}

void MaterialMapKeyFieldEditor::internalStartEditing (void)
{
    _InitialValue =  _EditingTextField->getText();
}

void MaterialMapKeyFieldEditor::internalStopEditing  (void)
{
    MaterialMapKey Key(RenderPropertiesPool::the()->getFrom1(_EditingTextField->getText().c_str()));
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), boost::lexical_cast<std::string>(Key), getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void MaterialMapKeyFieldEditor::internalCancelEditing(void)
{
    _EditingTextField->setText(_InitialValue);
}

const std::vector<const DataType*>& MaterialMapKeyFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void MaterialMapKeyFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingTextField->setPosition(TopLeft);
    _EditingTextField->setSize(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MaterialMapKeyFieldEditor::onCreate(const MaterialMapKeyFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingTextField = TextField::create();
        pushToChildren(_EditingTextField);
        _TextFieldFocusGainedConnection = _EditingTextField->connectFocusGained(boost::bind(&MaterialMapKeyFieldEditor::handleTextFieldFocusGained, this, _1));
        _TextFieldFocusLostConnection = _EditingTextField->connectFocusLost(boost::bind(&MaterialMapKeyFieldEditor::handleTextFieldFocusLost, this, _1));
        _TextFieldActionPerformedConnection = _EditingTextField->connectActionPerformed(boost::bind(&MaterialMapKeyFieldEditor::handleTextFieldActionPerformed, this, _1));
        _TextFieldKeyTypedConnection = _EditingTextField->connectKeyTyped(boost::bind(&MaterialMapKeyFieldEditor::handleTextFieldKeyTyped, this, _1));
    }
}

void MaterialMapKeyFieldEditor::onDestroy()
{
}

void MaterialMapKeyFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingTextField = NULL;

    _TextFieldFocusGainedConnection.disconnect();
    _TextFieldFocusLostConnection.disconnect();
    _TextFieldActionPerformedConnection.disconnect();
    _TextFieldKeyTypedConnection.disconnect();
}

void MaterialMapKeyFieldEditor::handleTextFieldFocusGained    (FocusEventDetails* const details)
{
    startEditing();
}

void MaterialMapKeyFieldEditor::handleTextFieldFocusLost      (FocusEventDetails* const details)
{
    stopEditing();
}

void MaterialMapKeyFieldEditor::handleTextFieldActionPerformed(ActionEventDetails* const details)
{
    stopEditing();
    startEditing();
}

void MaterialMapKeyFieldEditor::handleTextFieldKeyTyped       (KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        cancelEditing();
        startEditing();
    }
}

/*----------------------- constructors & destructors ----------------------*/

MaterialMapKeyFieldEditor::MaterialMapKeyFieldEditor(void) :
    Inherited()
{
}

MaterialMapKeyFieldEditor::MaterialMapKeyFieldEditor(const MaterialMapKeyFieldEditor &source) :
    Inherited(source)
{
}

MaterialMapKeyFieldEditor::~MaterialMapKeyFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialMapKeyFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MaterialMapKeyFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MaterialMapKeyFieldEditor NI" << std::endl;
}

OSG_END_NAMESPACE
