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

#include "OSGFCPtrFieldEditor.h"

#include "OSGSetFieldValueCommand.h"
#include "OSGCreateFieldContainerCommand.h"
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
#include "OSGDefaultListModel.h"

#include "OSGDialogWindow.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGButton.h"
#include "OSGScrollPanel.h"
#include "OSGUIDrawUtils.h"
#include "OSGList.h"
#include "OSGDerivedFieldContainerComboBoxModel.h"
#include "OSGContainerUtils.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGUIDrawingSurface.h"

#include "OSGFCPtrEditorAllStore.h"
#include "OSGNameAttachment.h"
#include "OSGTextField.h"
#include "OSGMenuButton.h"
#include "OSGComboBox.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFCPtrFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGFCPtrFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
 
std::vector<const DataType*> FCPtrFieldEditor::_EditableTypes = std::vector<const DataType*>();
FCPtrEditorStorePtr FCPtrFieldEditor::_DefaultFindFCStorePrototype = FCPtrEditorAllStore::create();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FCPtrFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        //Fill in all of the editable types
        UInt32 NumTypes(TypeFactory::the()->getNumTypes());
        FieldType* type;
        for(UInt32 i(0) ; i<NumTypes; ++i)
        {
            type = dynamic_cast<FieldType*>(TypeFactory::the()->findType(i));
            if(type != NULL &&
               (type->getClass() == FieldType::PtrField ||
               type->getClass() == FieldType::ChildPtrField))
            {
                _EditableTypes.push_back(&type->getContentType());
                FieldEditorFactory::the()->setEditorType(&type->getContentType(), &getClassType(),
                                                         "FieldContainerPtr");
            }
        }
    }
}

FCPtrEditorStorePtr FCPtrFieldEditor::getDefaultFindFCStorePrototype(void)
{
    return _DefaultFindFCStorePrototype;
}

void FCPtrFieldEditor::setDefaultFindFCStorePrototype(FCPtrEditorStorePtr fcStore)
{
    _DefaultFindFCStorePrototype = fcStore;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool FCPtrFieldEditor::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    Inherited::internalAttachField(fc, fieldId, index);
    if(!_FindFCStore)
    {
        const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(fc->getFieldDescription(fieldId)->getFieldType().getContentType()));
        _FindFCStore = _DefaultFindFCStorePrototype->clone();
    }
    return true;
}

bool FCPtrFieldEditor::internalDettachField(void)
{
    return true;
}

void FCPtrFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    assert(TheFieldHandle->getType().getClass() == FieldType::PtrField ||
           TheFieldHandle->getType().getClass() == FieldType::ChildPtrField);

    //Get the Editing FCPtr
    FieldContainer* EditingFC(NULL);
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        GetSFieldHandle<FieldContainerPtrSFieldBase>* ThePtrFieldHandle(dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get()));
        EditingFC = ThePtrFieldHandle->get();
    }
    else
    {
        GetMFieldHandle<FieldContainerPtrMFieldBase>* ThePtrFieldHandle(dynamic_cast<GetMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));
        EditingFC = ThePtrFieldHandle->get(getEditingFieldIndex());
    }

    //Update the Editing Text
    std::string EditingText("NULL");
    std::string Name("");
    std::string TypeName("");

    if(EditingFC != NULL)
    {
        //Get the Id of the FieldContainer
        EditingText = boost::lexical_cast<std::string>(EditingFC->getId());

        //If the FieldContainer has a name attachment then get the name
        if(EditingFC->getType().isDerivedFrom(AttachmentContainer::getClassType()) && 
           getName(dynamic_cast<AttachmentContainer*>(EditingFC)))
        {
            Name = getName(dynamic_cast<AttachmentContainer*>(EditingFC));
        }

        //Get the name of the type of the FieldContainer
        TypeName = EditingFC->getType().getName();
    }


    //Update the Labels and TextFields
    _EditingTextField->setText(EditingText);
    _NameTypeLabel->setText(Name + " [" + TypeName + "]");
}

void FCPtrFieldEditor::internalStartEditing (void)
{
    _InitialValue =  _EditingTextField->getText();
}

void FCPtrFieldEditor::internalStopEditing  (void)
{
    std::string FCId(_EditingTextField->getText());
    if(_EditingTextField->getText().compare("NULL") == 0)
    {
        FCId = "0";
    }
    else
    {
        //Make sure the Id can be cast to a UInt32
        try
        {
            UInt32 CastTest = boost::lexical_cast<UInt32>(FCId);
        }
        catch(boost::bad_lexical_cast &)
        {
            //If it can't then cancel editing
            internalCancelEditing();
            return;
        }
    }

    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), FCId, getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void FCPtrFieldEditor::internalCancelEditing(void)
{
    _EditingTextField->setText(_InitialValue);
}

const std::vector<const DataType*>& FCPtrFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void FCPtrFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    //Menu Button
    _EditingMenuButton->setSize(Vec2f(_EditingMenuButton->getPreferredSize().x(),BottomRight.y() - TopLeft.y()));
    _EditingMenuButton->setPosition(BottomRight - _EditingMenuButton->getSize());

    //Editing Text Field
    _EditingTextField->setPosition(Pnt2f(BottomRight.x() - _EditingTextField->getPreferredSize().x() - _EditingMenuButton->getPreferredSize().x(), TopLeft.y()));
    _EditingTextField->setSize(Vec2f(_EditingTextField->getPreferredSize().x(), BottomRight.y() - TopLeft.y()));

    //Name/Type Label
    _NameTypeLabel->setPosition(TopLeft);
    _NameTypeLabel->setSize(Vec2f(_EditingTextField->getPosition().x() - TopLeft.x(), BottomRight.y() - TopLeft.y()));
    
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void FCPtrFieldEditor::onCreate(const FCPtrFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        //Name/Type Label
        _NameTypeLabel = Label::create();
        _NameTypeLabel->setBorders(NULL);
        _NameTypeLabel->setBackgrounds(NULL);
        pushToChildren(_NameTypeLabel);

        //Editing Text Field
        _EditingTextField = TextField::create();
        pushToChildren(_EditingTextField);
        _TextFieldFocusGainedConnection = _EditingTextField->connectFocusGained(boost::bind(&FCPtrFieldEditor::handleTextFieldFocusGained, this, _1));
        _TextFieldFocusLostConnection = _EditingTextField->connectFocusLost(boost::bind(&FCPtrFieldEditor::handleTextFieldFocusLost, this, _1));
        _TextFieldActionPerformedConnection = _EditingTextField->connectActionPerformed(boost::bind(&FCPtrFieldEditor::handleTextFieldActionPerformed, this, _1));
        _TextFieldKeyTypedConnection = _EditingTextField->connectKeyTyped(boost::bind(&FCPtrFieldEditor::handleTextFieldKeyTyped, this, _1));
        _EditingTextField->setPreferredSize(Vec2f(45.0f, 17.0f));

        DefaultListModelRefPtr FCCommandsListModel = DefaultListModel::create();
        FCCommandsListModel->pushBack(boost::any(std::string("Create ...")));
        FCCommandsListModel->pushBack(boost::any(std::string("Load ...")));
        FCCommandsListModel->pushBack(boost::any(std::string("Find ...")));

        _EditingMenuButton = MenuButton::create();
        _EditingMenuButton->setPreferredSize(Vec2f(25.0f, 25.0f));
        //_EditingMenuButton =
            //dynamic_pointer_cast<Button>(dynamic_cast<ComboBox*>(ComboBox::getClassType().getPrototype())->getExpandButton()->shallowCopy());
        _EditingMenuButton->setModel(FCCommandsListModel);

        //Get the Default ComboBox expander
        Button* ProtoButton = dynamic_cast<ComboBox*>(ComboBox::getClassType().getPrototype())->getExpandButton();

        //Backgrounds
        _EditingMenuButton->setBackground(ProtoButton->getBackground());
        _EditingMenuButton->setFocusedBackground(ProtoButton->getFocusedBackground());
        _EditingMenuButton->setDisabledBackground(ProtoButton->getDisabledBackground());
        _EditingMenuButton->setRolloverBackground(ProtoButton->getRolloverBackground());
        _EditingMenuButton->setActiveBackground(ProtoButton->getActiveBackground());

        //Foregrounds
        _EditingMenuButton->setForeground(ProtoButton->getForeground());
        _EditingMenuButton->setFocusedForeground(ProtoButton->getFocusedForeground());
        _EditingMenuButton->setDisabledForeground(ProtoButton->getDisabledForeground());
        _EditingMenuButton->setRolloverForeground(ProtoButton->getRolloverForeground());
        _EditingMenuButton->setActiveForeground(ProtoButton->getActiveForeground());

        //DrawObjects
        _EditingMenuButton->setDrawObject(ProtoButton->getDrawObject());
        _EditingMenuButton->setFocusedDrawObject(ProtoButton->getFocusedDrawObject());
        _EditingMenuButton->setDisabledDrawObject(ProtoButton->getDisabledDrawObject());
        _EditingMenuButton->setRolloverDrawObject(ProtoButton->getRolloverDrawObject());
        _EditingMenuButton->setActiveDrawObject(ProtoButton->getActiveDrawObject());

        //Borders
        _EditingMenuButton->setBorder(ProtoButton->getBorder());
        _EditingMenuButton->setFocusedBorder(ProtoButton->getFocusedBorder());
        _EditingMenuButton->setDisabledBorder(ProtoButton->getDisabledBorder());
        _EditingMenuButton->setRolloverBorder(ProtoButton->getRolloverBorder());
        _EditingMenuButton->setActiveBorder(ProtoButton->getActiveBorder());

        _MenuButtonActionConnection = _EditingMenuButton->connectMenuActionPerformed(boost::bind(&FCPtrFieldEditor::handleMenuButtonAction, this, _1));
        pushToChildren(_EditingMenuButton);
    }
}

void FCPtrFieldEditor::onDestroy()
{
}

void FCPtrFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingTextField = NULL;
    _EditingMenuButton = NULL;

    _TextFieldFocusGainedConnection.disconnect();
    _TextFieldFocusLostConnection.disconnect();
    _TextFieldActionPerformedConnection.disconnect();
    _TextFieldKeyTypedConnection.disconnect();
    _MenuButtonActionConnection.disconnect();
    _CreateContainerDialogClosedConnection.disconnect();
    _FindContainerDialogClosedConnection.disconnect();
}

void FCPtrFieldEditor::openCreateHandler(void)
{
    const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType()));
    if(ThePtrType == NULL)
    {
        return;
    }

    //If the type is a node, then create a NodeCore instead
    //and then insert it as the core of a newly created node
    if(*ThePtrType == Node::getClassType())
    {
        ThePtrType = &NodeCore::getClassType();
    }

    std::vector<std::string> inputValues;
    UInt32 NumFieldContainersFound(0);
    const FieldContainerType* FoundType(NULL);
    for(UInt32 j(0) ; NumFieldContainersFound<FieldContainerFactory::the()->getNumTypes(); ++j)
    {
        FoundType = FieldContainerFactory::the()->findType(j);
        if(FoundType != NULL)
        {
            if(FoundType->isDerivedFrom(*ThePtrType)  && !FoundType->isAbstract())
            {
                inputValues.push_back(FoundType->getName());
            }
            ++NumFieldContainersFound;
        }
    }

    DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Create Field Container",
                                                                   "Choose the type of object to create",
                                                                   DialogWindow::INPUT_COMBO,
                                                                   true,
                                                                   inputValues);
    _CreateContainerDialogClosedConnection = TheDialog->connectDialogWindowClosed(boost::bind(&FCPtrFieldEditor::handleCreateContainerDialogClosed, this, _1));

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), getParentWindow()->getParentDrawingSurface()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setAllwaysOnTop(true);
    TheDialog->setModal(true);
    TheDialog->setResizable(true);

    getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
}

void FCPtrFieldEditor::openFindContainerHandler(void)
{
    const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType()));
    if(ThePtrType == NULL)
    {
        return;
    }

    std::vector<std::string> inputValues;
    _FindFCStore->setTypeToStore(ThePtrType);
    std::vector<FieldContainer*> fcStore(_FindFCStore->getList());

    std::string value;
    for(UInt32 i(0) ; i<fcStore.size(); ++i)
    {
        value.clear();
        if(fcStore[i]->getType().isDerivedFrom(AttachmentContainer::getClassType()) &&
           getName(dynamic_cast<AttachmentContainer*>(fcStore[i])))
        {
            value += std::string(getName(dynamic_cast<AttachmentContainer*>(fcStore[i]))) + " ";
        }
        value += "[" + fcStore[i]->getType().getName() + "] " + boost::lexical_cast<std::string>(fcStore[i]->getId());
        inputValues.push_back(value);
    }

    DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Find Field Container",
                                                                   "Choose the container to use",
                                                                   DialogWindow::INPUT_LIST,
                                                                   true,
                                                                   inputValues);
    _FindContainerDialogClosedConnection = TheDialog->connectDialogWindowClosed(boost::bind(&FCPtrFieldEditor::handleFindContainerDialogClosed, this, _1));

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), getParentWindow()->getParentDrawingSurface()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setAllwaysOnTop(true);
    TheDialog->setResizable(true);

    getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
}

void FCPtrFieldEditor::handleMenuButtonAction(ActionEventDetails* const details)
{
    switch(_EditingMenuButton->getSelectionIndex())
    {
        case 0:     //Create
            openCreateHandler();
            break;
        case 1:     //Load
            //openFindContainerHandler();
            break;
        case 2:     //Find
            openFindContainerHandler();
            break;
        default:
            assert(false);
            break;
    }
}

void FCPtrFieldEditor::handleCreateContainerDialogClosed(DialogWindowEventDetails* const details)
{
    if(details->getOption() != DialogWindowEventDetails::DIALOG_OPTION_CANCEL)
    {
        const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType()));

        const FieldContainerType* TheType(FieldContainerFactory::the()->findType(details->getInput().c_str()));

        if(TheType != NULL)
        {
            //Create the Container
            CreateFieldContainerCommandPtr CreateCommand;
            
            //If the type is a node, then create a NodeCore instead
            //and then insert it as the core of a newly created node
            if(*ThePtrType == Node::getClassType())
            {
                CreateFieldContainerCommandPtr CreateCoreCommand = CreateFieldContainerCommand::create(TheType);
                getCommandManager()->executeCommand(CreateCoreCommand);
                
                CreateCommand = CreateFieldContainerCommand::create(&Node::getClassType());
                getCommandManager()->executeCommand(CreateCommand);

                dynamic_cast<Node*>(CreateCommand->getContainer())->setCore(dynamic_cast<NodeCore*>(CreateCoreCommand->getContainer()));
            }
            else
            {
                CreateCommand = CreateFieldContainerCommand::create(TheType);
                getCommandManager()->executeCommand(CreateCommand);
            }

            //Set the value of the field
            SetFieldValueCommandPtr SetCommand =
                SetFieldValueCommand::create(getEditingFC(),
                                             getEditingFieldId(),
                                             boost::lexical_cast<std::string>(CreateCommand->getContainer()->getId()),
                                             getEditingFieldIndex());

            getCommandManager()->executeCommand(SetCommand);
        }
    }
    _CreateContainerDialogClosedConnection.disconnect();
}

void FCPtrFieldEditor::handleFindContainerDialogClosed(DialogWindowEventDetails* const details)
{
    if(details->getOption() != DialogWindowEventDetails::DIALOG_OPTION_CANCEL)
    {
        std::vector<FieldContainer*> fcStore(_FindFCStore->getList());
        //Set the value of the field
        SetFieldValueCommandPtr SetCommand =
            SetFieldValueCommand::create(getEditingFC(),
                                         getEditingFieldId(),
                                         boost::lexical_cast<std::string>(fcStore[details->getInputIndex()]->getId()),
                                         getEditingFieldIndex());

        getCommandManager()->executeCommand(SetCommand);
    }
    _FindContainerDialogClosedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

FCPtrFieldEditor::FCPtrFieldEditor(void) :
    Inherited(),
    _FindFCStore()
{
}

FCPtrFieldEditor::FCPtrFieldEditor(const FCPtrFieldEditor &source) :
    Inherited(source),
    _FindFCStore()

{
}

FCPtrFieldEditor::~FCPtrFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FCPtrFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void FCPtrFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FCPtrFieldEditor NI" << std::endl;
}

void FCPtrFieldEditor::handleTextFieldFocusGained    (FocusEventDetails* const details)
{
    startEditing();
}

void FCPtrFieldEditor::handleTextFieldFocusLost      (FocusEventDetails* const details)
{
    stopEditing();
}

void FCPtrFieldEditor::handleTextFieldActionPerformed(ActionEventDetails* const details)
{
    stopEditing();
    startEditing();
}

void FCPtrFieldEditor::handleTextFieldKeyTyped       (KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        cancelEditing();
        startEditing();
    }
}

OSG_END_NAMESPACE
