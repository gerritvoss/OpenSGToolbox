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

#include "OSGMatrixElementsFieldEditor.h"
#include "OSGMatrix.h"
#include "OSGMathFieldTraits.h"
#include "OSGMathFields.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include <boost/lexical_cast.hpp>
#include "OSGTextField.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMatrixElementsFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGMatrixElementsFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> MatrixElementsFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MatrixElementsFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        _EditableTypes.push_back(&FieldTraits<Matrix4f>::getType());
        _EditableTypes.push_back(&FieldTraits<Matrix4fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Matrix4d>::getType());
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "Elements");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void MatrixElementsFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());

    for(UInt32 i(0) ; i<4 ; ++i)
    {
        for(UInt32 j(0) ; j<4 ; ++j)
        {
            if(type == FieldTraits<Matrix4f>::getType())
            {
                Real32 Value;
                if(TheFieldHandle->getCardinality() == FieldType::SingleField)
                {
                    Value = static_cast<const SFMatrix*>(TheFieldHandle->getField())->getValue()[j][i];
                }
                else
                {
                    Value = static_cast<const MFMatrix*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex())[j][i];
                }
                _EditingTextFields[4*i+j]->setText(boost::lexical_cast<std::string>(Value));
            }
            else if(type == FieldTraits<Matrix4fx>::getType())
            {
                Fixed32 Value;
                if(TheFieldHandle->getCardinality() == FieldType::SingleField)
                {
                    Value = static_cast<const SFMatrix4fx*>(TheFieldHandle->getField())->getValue()[j][i];
                }
                else
                {
                    Value = static_cast<const MFMatrix4fx*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex())[j][i];
                }
                _EditingTextFields[4*i+j]->setText(boost::lexical_cast<std::string>(Value));
            }
            else if(type == FieldTraits<Matrix4d>::getType())
            {
                Real64 Value;
                if(TheFieldHandle->getCardinality() == FieldType::SingleField)
                {
                    Value = static_cast<const SFMatrix4d*>(TheFieldHandle->getField())->getValue()[j][i];
                }
                else
                {
                    Value = static_cast<const MFMatrix4d*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex())[j][i];
                }
                _EditingTextFields[4*i+j]->setText(boost::lexical_cast<std::string>(Value));
            }
        }
    }
}

void MatrixElementsFieldEditor::internalStartEditing (void)
{
    if(_SelectedTextField >= 0 && _SelectedTextField < 16)
    {
        _InitialValue =  _EditingTextFields[static_cast<UInt32>(_SelectedTextField)]->getText();
    }
}

void MatrixElementsFieldEditor::internalStopEditing  (void)
{
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), getEditorValue(), getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void MatrixElementsFieldEditor::internalCancelEditing(void)
{
    if(_SelectedTextField >= 0 && _SelectedTextField < 16)
    {
        _EditingTextFields[static_cast<UInt32>(_SelectedTextField)]->setText(_InitialValue);
    }
}

const std::vector<const DataType*>& MatrixElementsFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void MatrixElementsFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    Vec2f Gap(1.0,1.0);
    Vec2f ElementSize(((BottomRight - TopLeft)- (Gap * 5.0f)) * 0.25);
    for(UInt32 i(0) ; i<4 ; ++i)  //Row
    {
        for(UInt32 j(0) ; j<4 ; ++j)  //Columns
        {
            _EditingTextFields[i*4 + j]->setPosition(TopLeft + 
                                                     Vec2f(Gap.x() * static_cast<Real32>(j+1), Gap.y() * static_cast<Real32>(i+1)) +
                                                     Vec2f(ElementSize.x() * static_cast<Real32>(j), ElementSize.y() * static_cast<Real32>(i)));
            _EditingTextFields[i*4 + j]->setSize(ElementSize);
        }
    }
}

UInt32 MatrixElementsFieldEditor::getNumRequestedRows(void) const
{
    return 4;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MatrixElementsFieldEditor::onCreate(const MatrixElementsFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        for(UInt32 i(0) ; i<16 ; ++i)
        {
            _EditingTextFields.push_back(TextField::create());
            pushToChildren(_EditingTextFields.back());
            _TextFieldConnections.push_back(_EditingTextFields.back()->connectFocusGained(boost::bind(&MatrixElementsFieldEditor::handleTextFieldFocusGained, this, _1, i)));
            _TextFieldConnections.push_back(_EditingTextFields.back()->connectFocusLost(boost::bind(&MatrixElementsFieldEditor::handleTextFieldFocusLost, this, _1, i)));
            _TextFieldConnections.push_back(_EditingTextFields.back()->connectActionPerformed(boost::bind(&MatrixElementsFieldEditor::handleTextFieldActionPerformed, this, _1, i)));
            _TextFieldConnections.push_back(_EditingTextFields.back()->connectKeyTyped(boost::bind(&MatrixElementsFieldEditor::handleTextFieldKeyTyped, this, _1, i)));
        }
    }
}

void MatrixElementsFieldEditor::onDestroy()
{
}

void MatrixElementsFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    for(ConnectionsVector::iterator Itor(_TextFieldConnections.begin()) ; Itor != _TextFieldConnections.end(); ++Itor)
    {
        Itor->disconnect();
    }

    _TextFieldConnections.clear();
    _EditingTextFields.clear();
}

void MatrixElementsFieldEditor::handleTextFieldFocusGained    (FocusEventDetails* const details,
                                        UInt32 ElementIndex)
{
    _SelectedTextField = ElementIndex;
    startEditing();
}

void MatrixElementsFieldEditor::handleTextFieldFocusLost      (FocusEventDetails* const details,
                                        UInt32 ElementIndex)
{
    stopEditing();
    _SelectedTextField = -1;
}

void MatrixElementsFieldEditor::handleTextFieldActionPerformed(ActionEventDetails* const details,
                                        UInt32 ElementIndex)
{
    stopEditing();
    _SelectedTextField = ElementIndex;
    startEditing();
}

void MatrixElementsFieldEditor::handleTextFieldKeyTyped       (KeyEventDetails* const details,
                                        UInt32 ElementIndex)
{
    if(details->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        _SelectedTextField = ElementIndex;
        cancelEditing();
        startEditing();
    }
}
    
std::string MatrixElementsFieldEditor::getEditorValue(void) const
{
    std::string Result("");
    for(TextFieldsVector::const_iterator Itor(_EditingTextFields.begin()) ; Itor != _EditingTextFields.end(); ++Itor)
    {
        try
        {
            Real32 Value(boost::lexical_cast<Real32>((*Itor)->getText()));
        }
        catch(boost::bad_lexical_cast & ex)
        {
            return std::string("");
        }
        Result += (*Itor)->getText() + " ";
    }
    return Result;
}

/*----------------------- constructors & destructors ----------------------*/

MatrixElementsFieldEditor::MatrixElementsFieldEditor(void) :
    Inherited()
{
}

MatrixElementsFieldEditor::MatrixElementsFieldEditor(const MatrixElementsFieldEditor &source) :
    Inherited(source)
{
}

MatrixElementsFieldEditor::~MatrixElementsFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MatrixElementsFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MatrixElementsFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MatrixElementsFieldEditor NI" << std::endl;
}

OSG_END_NAMESPACE
