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
            if(type != NULL)
            {
                _EditableTypes.push_back(type);
                FieldEditorFactory::the()->setDefaultEditor(type, &getClassType());
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void GenericFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

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

    _EditingTextField->setText(StrStream.str());
}

void GenericFieldEditor::internalStartEditing (void)
{
}

void GenericFieldEditor::internalStopEditing  (void)
{
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), _EditingTextField->getText(), getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void GenericFieldEditor::internalCancelEditing(void)
{
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
    Inherited(),
    _TextFieldListener(this)
{
}

GenericFieldEditor::GenericFieldEditor(const GenericFieldEditor &source) :
    Inherited(source),
    _TextFieldListener(this)
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
        _EditingTextField->addFocusListener(&_TextFieldListener);
        _EditingTextField->addActionListener(&_TextFieldListener);
        _EditingTextField->addKeyListener(&_TextFieldListener);
    }
}

void GenericFieldEditor::onDestroy()
{
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

void GenericFieldEditor::TextFieldListener::focusGained    (const FocusEventUnrecPtr  e)
{
    _GenericFieldEditor->startEditing();
}

void GenericFieldEditor::TextFieldListener::focusLost      (const FocusEventUnrecPtr  e)
{
    _GenericFieldEditor->cancelEditing();
}

void GenericFieldEditor::TextFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _GenericFieldEditor->stopEditing();
    _GenericFieldEditor->startEditing();
}

void GenericFieldEditor::TextFieldListener::keyTyped       (const KeyEventUnrecPtr    e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        _GenericFieldEditor->cancelEditing();
    }
}

OSG_END_NAMESPACE
