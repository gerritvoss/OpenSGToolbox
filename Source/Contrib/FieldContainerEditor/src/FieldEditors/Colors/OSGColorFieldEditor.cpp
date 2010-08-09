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

#include "OSGColorFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSysFieldTraits.h"
#include "OSGColorLayer.h"
#include "OSGDefaultColorSelectionModel.h"
#include "OSGDialogWindow.h"
#include "OSGUIDrawUtils.h"
#include "OSGUIDrawingSurface.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGColorFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGColorFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const DataType*> ColorFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        _EditableTypes.push_back(&FieldTraits<Color3f>::getType());
        _EditableTypes.push_back(&FieldTraits<Color4f>::getType());
        _EditableTypes.push_back(&FieldTraits<Color3ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Color4ub>::getType());
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "ColorChooserWindow");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Color4f ColorFieldEditor::getValueAsColor4f(void) const
{
    
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    if(type == FieldTraits<Color3f>::getType())
    {
        Color3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFColor3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFColor3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        return Color4f(Value.red(), Value.green(), Value.blue(), 1.0f);
    }
    else if(type == FieldTraits<Color4f>::getType())
    {
        Color4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFColor4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFColor4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        return Value;
    }
    else if(type == FieldTraits<Color3ub>::getType())
    {
        Color3ub Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFColor3ub*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFColor3ub*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        return Color4f(Value.red(), Value.green(), Value.blue(), 1.0f);
    }
    else if(type == FieldTraits<Color4ub>::getType())
    {
        Color4ub Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFColor4ub*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFColor4ub*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        return Color4f(Value.red(), Value.green(), Value.blue(), Value.alpha());
    }
    assert(false && "Should not reach this.");
    return Color4f();
}

void ColorFieldEditor::internalFieldChanged (void)
{
    ColorLayerRefPtr ButtonBG = dynamic_cast<ColorLayer*>(_EditingButton->getBackground());

    ButtonBG->setColor(getValueAsColor4f());
}

void ColorFieldEditor::internalStartEditing (void)
{
    _ColorModel->setSelectedColor(getValueAsColor4f(), false);
    DialogWindowRefPtr TheDialog = DialogWindow::createColorChooserDialog("Choose a color", "Choose a color", true, _ColorModel,true);

    Pnt2f CenteredPosition = calculateAlignment(getParentWindow()->getPosition(), getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);

    _ColorDialogClosedConnection = TheDialog->connectDialogWindowClosed(boost::bind(&ColorFieldEditor::handleColorDialogClosed, this, _1));

    getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
}

void ColorFieldEditor::internalStopEditing  (void)
{
}

void ColorFieldEditor::runCommand  (void)
{
    Color4f ModelValue(_ColorModel->getSelectedColor());
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());

    std::ostringstream StrStream;
    OutStream TheOutStream(StrStream);
    if(type == FieldTraits<Color3f>::getType())
    {
        FieldTraits<Color3f>::putToStream(Color3f(ModelValue.red(), ModelValue.green(), ModelValue.blue()), TheOutStream);
    }
    else if(type == FieldTraits<Color4f>::getType())
    {
        FieldTraits<Color4f>::putToStream(ModelValue, TheOutStream);
    }
    else if(type == FieldTraits<Color3ub>::getType())
    {
        FieldTraits<Color3ub>::putToStream(Color3ub(ModelValue.red(), ModelValue.green(), ModelValue.blue()), TheOutStream);
    }
    else if(type == FieldTraits<Color4ub>::getType())
    {
        FieldTraits<Color4ub>::putToStream(Color4ub(ModelValue.red(), ModelValue.green(), ModelValue.blue(), ModelValue.alpha()), TheOutStream);
    }

    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), 
                                                                      getEditingFieldId(), 
                                                                      StrStream.str(), 
                                                                      getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void ColorFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& ColorFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void ColorFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingButton->setPosition(TopLeft);
    _EditingButton->setSize(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ColorFieldEditor::ColorFieldEditor(void) :
    Inherited()
{
}

ColorFieldEditor::ColorFieldEditor(const ColorFieldEditor &source) :
    Inherited(source)
{
}

ColorFieldEditor::~ColorFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void ColorFieldEditor::onCreate(const ColorFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _ColorModel = DefaultColorSelectionModel::create();
        _EditingButton = Button::create();
        _ButtonActionConnection = _EditingButton->connectActionPerformed(boost::bind(&ColorFieldEditor::handleButtonAction, this, _1));

        ColorLayerRefPtr ButtonBG = ColorLayer::create();
        _EditingButton->setBackgrounds(ButtonBG);
        
        pushToChildren(_EditingButton);
    }
}

void ColorFieldEditor::onDestroy()
{
}

void ColorFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingButton = NULL;
    _ColorModel = NULL;

    _ButtonActionConnection.disconnect();
    _ColorDialogClosedConnection.disconnect();
}

void ColorFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ColorFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ColorFieldEditor NI" << std::endl;
}

void ColorFieldEditor::handleButtonAction(ActionEventDetails* const details)
{
    internalStartEditing();
}

void ColorFieldEditor::handleColorDialogClosed(DialogWindowEventDetails* const details)
{
    if( details->getOption() != DialogWindowEventDetails::DIALOG_OPTION_CANCEL)
    {
        runCommand();
    }
    _ColorDialogClosedConnection.disconnect();
}

OSG_END_NAMESPACE
