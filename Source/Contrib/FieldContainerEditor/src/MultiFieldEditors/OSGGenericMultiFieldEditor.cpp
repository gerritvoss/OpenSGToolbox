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

#include "OSGGenericMultiFieldEditor.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGAttachmentMapFieldTraits.h"
#include "OSGChangedFunctorFieldTraits.h"
#include "OSGMaterialMapFields.h"

#include "OSGScrollPanel.h"
#include "OSGMFieldListModel.h"
#include "OSGList.h"
#include "OSGLabel.h"
#include "OSGMultiFieldListEditComponentGenerator.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGenericMultiFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGGenericMultiFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> GenericMultiFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GenericMultiFieldEditor::initMethod(InitPhase ePhase)
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
                *type != FieldTraits<AttachmentMap>::getType() &&
                *type != FieldTraits<ChangedFunctorCallback>::getType())
            {
                _EditableTypes.push_back(type);
                FieldEditorFactory::the()->setEditorType(type, &getClassType(), "GenericMultiField");
                FieldEditorFactory::the()->setMultiDefaultEditor(type, &getClassType());
            }
        }
        FieldEditorFactory::the()->removeEditorType(&FieldTraits<MaterialMap>::getType(), "GenericMultiField");
        FieldEditorFactory::the()->removeMultiDefaultEditor(&FieldTraits<MaterialMap>::getType());
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//Set Value
//    -Done by default field editor for the content type
//
//Insert Value
//    -Button on the side with a +
//
//Move
//    -Drag and drop
//
//Remove
//    -Button on the side with a -
//
//Swap
//    -Probably don't need to support
//
//Add
//    -Button on the side with a + after the last element
//    -So there will be an empty element after the last one
//
bool GenericMultiFieldEditor::internalAttachField(FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
     _FieldListGenerator->setCommandManager(_CmdManager);

    //Update the Editors
    _FieldListModel->setContainer(fc);
    _FieldListModel->setFieldId(fieldId);

    return true;
}

bool GenericMultiFieldEditor::internalDettachField(void)
{
    //Clear the Editors
    _FieldEditors.clear();

    //Clear the constraints
    _FieldListModel->setContainer(NULL);

    return true;
}

void GenericMultiFieldEditor::internalFieldChanged (void)
{
}

void GenericMultiFieldEditor::internalStartEditing (void)
{
}

void GenericMultiFieldEditor::internalStopEditing  (void)
{
}

void GenericMultiFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& GenericMultiFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void GenericMultiFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _FieldElementsScrollPanel->setPosition(Pnt2f(0.0f,0.0f));
    _FieldElementsScrollPanel->setSize(BottomRight - TopLeft);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void GenericMultiFieldEditor::onCreate(const GenericMultiFieldEditor *Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        //End of Elements Label
        _ElementEndLabel = Label::create();
        _ElementEndLabel->setText("End");
        _ElementEndLabel->setAlignment(Vec2f(0.5f,0.5f));

        //Field List Model
        _FieldListModel = MFieldListModel::create();

        _FieldListGenerator = MultiFieldListEditComponentGenerator::create();

        //Field List
        _FieldList = List::create();
        _FieldList->setPreferredSize(Vec2f(200, 300));
        _FieldList->setOrientation(List::VERTICAL_ORIENTATION);
		_FieldList->setModel(_FieldListModel);
		_FieldList->setCellGenerator(_FieldListGenerator);
		_FieldList->setSelectable(false);
        

        //Scroll Panel for everything
        _FieldElementsScrollPanel = ScrollPanel::create();

        _FieldElementsScrollPanel->setPreferredSize(Vec2f(200,300));
        _FieldElementsScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        _FieldElementsScrollPanel->setViewComponent(_FieldList);

        //Add to myself
        pushToChildren(_FieldElementsScrollPanel);
    }
}

void GenericMultiFieldEditor::onDestroy()
{
}

void GenericMultiFieldEditor::pushIndexEditor(FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    ////Insert button
    ////Remove button
    ////Editor
    //FieldEditorComponentUnrecPtr TheEditor =
        //FieldEditorFactory::the()->createSingleDefaultEditor(fc,
                                                             //fieldId,
                                                             //_CmdManager,
                                                             //index);
    //if(TheEditor != NULL)
    //{
        //_FieldEditors.push_back(TheEditor);

        ////Add to the panel
        //_FieldElementsPanel->pushToChildren(TheEditor);
    //}
}

/*----------------------- constructors & destructors ----------------------*/

GenericMultiFieldEditor::GenericMultiFieldEditor(void) :
    Inherited()
{
}

GenericMultiFieldEditor::GenericMultiFieldEditor(const GenericMultiFieldEditor &source) :
    Inherited(source)
{
}

GenericMultiFieldEditor::~GenericMultiFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GenericMultiFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GenericMultiFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GenericMultiFieldEditor NI" << std::endl;
}

OSG_END_NAMESPACE
