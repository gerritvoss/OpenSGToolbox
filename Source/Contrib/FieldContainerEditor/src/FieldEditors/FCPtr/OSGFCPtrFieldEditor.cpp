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

    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        GetSFieldHandle<FieldContainerPtrSFieldBase>* ThePtrFieldHandle(dynamic_cast<GetSFieldHandle<FieldContainerPtrSFieldBase>*>(TheFieldHandle.get()));
        if(ThePtrFieldHandle->get() != NULL)
        {
            _EditingTextField->setText(boost::lexical_cast<std::string>(ThePtrFieldHandle->get()->getId()));
        }
        else
        {
            _EditingTextField->setText("NULL");
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
            _EditingTextField->setText("NULL");
        }
    }
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

    _EditingMenuButton->setSize(Vec2f(25.0f,BottomRight.y() - TopLeft.y()));
    _EditingMenuButton->setPosition(BottomRight - _EditingMenuButton->getSize());

    _EditingTextField->setPosition(TopLeft);
    _EditingTextField->setSize(BottomRight - TopLeft -
                               Vec2f(_EditingMenuButton->getSize().x(), 0.0f));
    
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void FCPtrFieldEditor::onCreate(const FCPtrFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingTextField = TextField::create();
        pushToChildren(_EditingTextField);
        _EditingTextField->addFocusListener(&_TextFieldListener);
        _EditingTextField->addActionListener(&_TextFieldListener);
        _EditingTextField->addKeyListener(&_TextFieldListener);

        DefaultListModelRefPtr FCCommandsListModel = DefaultListModel::create();
        FCCommandsListModel->pushBack(boost::any(std::string("Create ...")));
        FCCommandsListModel->pushBack(boost::any(std::string("Find ...")));

        _EditingMenuButton = MenuButton::create();
        //_EditingMenuButton =
            //dynamic_pointer_cast<Button>(dynamic_cast<ComboBox*>(ComboBox::getClassType().getPrototype())->getExpandButton()->shallowCopy());
        _EditingMenuButton->setModel(FCCommandsListModel);
        _EditingMenuButton->addMenuActionListener(&_MenuButtonFieldListener);
        pushToChildren(_EditingMenuButton);
    }
}

void FCPtrFieldEditor::onDestroy()
{
}

void FCPtrFieldEditor::openCreateHandler(void)
{
    const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType()));
    if(ThePtrType == NULL)
    {
        return;
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
    TheDialog->addDialogWindowListener(&_CreateContainerDialogListener);

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), getParentWindow()->getParentDrawingSurface()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setAllwaysOnTop(true);
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
    TheDialog->addDialogWindowListener(&_FindContainerDialogListener);

    Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), getParentWindow()->getParentDrawingSurface()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
    TheDialog->setPosition(CenteredPosition);
    TheDialog->setAllwaysOnTop(true);
    TheDialog->setResizable(true);

    getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
}

void FCPtrFieldEditor::handleMenuSelected(const ActionEventUnrecPtr e)
{
    switch(_EditingMenuButton->getSelectionIndex())
    {
        case 0:     //Create
            openCreateHandler();
            break;
        case 1:     //Find
            openFindContainerHandler();
            break;
        default:
            assert(false);
            break;
    }
}

void FCPtrFieldEditor::handleCreateContainerClosed(const DialogWindowEventUnrecPtr e)
{
    if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
    {
        const FieldContainerType* TheType(FieldContainerFactory::the()->findType(e->getInput().c_str()));

        if(TheType != NULL)
        {
            //Create the Container
            CreateFieldContainerCommandPtr CreateCommand = CreateFieldContainerCommand::create(TheType);
            getCommandManager()->executeCommand(CreateCommand);

            //Set the value of the field
            SetFieldValueCommandPtr SetCommand =
                SetFieldValueCommand::create(getEditingFC(),
                                             getEditingFieldId(),
                                             boost::lexical_cast<std::string>(CreateCommand->getContainer()->getId()),
                                             getEditingFieldIndex());

            getCommandManager()->executeCommand(SetCommand);
        }
    }
}

void FCPtrFieldEditor::handleFindContainerClosed(const DialogWindowEventUnrecPtr e)
{
    if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
    {
        std::vector<FieldContainer*> fcStore(_FindFCStore->getList());
        //Set the value of the field
        SetFieldValueCommandPtr SetCommand =
            SetFieldValueCommand::create(getEditingFC(),
                                         getEditingFieldId(),
                                         boost::lexical_cast<std::string>(fcStore[e->getInputIndex()]->getId()),
                                         getEditingFieldIndex());

        getCommandManager()->executeCommand(SetCommand);
    }
}

/*----------------------- constructors & destructors ----------------------*/

FCPtrFieldEditor::FCPtrFieldEditor(void) :
    Inherited(),
    _TextFieldListener(this),
    _MenuButtonFieldListener(this),
    _CreateContainerDialogListener(this),
    _FindContainerDialogListener(this),
    _FindFCStore()
{
}

FCPtrFieldEditor::FCPtrFieldEditor(const FCPtrFieldEditor &source) :
    Inherited(source),
    _TextFieldListener(this),
    _MenuButtonFieldListener(this),
    _CreateContainerDialogListener(this),
    _FindContainerDialogListener(this),
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

void FCPtrFieldEditor::TextFieldListener::focusGained    (const FocusEventUnrecPtr  e)
{
    _FCPtrFieldEditor->startEditing();
}

void FCPtrFieldEditor::TextFieldListener::focusLost      (const FocusEventUnrecPtr  e)
{
    _FCPtrFieldEditor->stopEditing();
}

void FCPtrFieldEditor::TextFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _FCPtrFieldEditor->stopEditing();
    _FCPtrFieldEditor->startEditing();
}

void FCPtrFieldEditor::TextFieldListener::keyTyped       (const KeyEventUnrecPtr    e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        _FCPtrFieldEditor->cancelEditing();
        _FCPtrFieldEditor->startEditing();
    }
}

void FCPtrFieldEditor::MenuButtonFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _FCPtrFieldEditor->handleMenuSelected(e);
}

void FCPtrFieldEditor::CreateContainerDialogListener::dialogClosing(const DialogWindowEventUnrecPtr e)
{
}

void FCPtrFieldEditor::CreateContainerDialogListener::dialogClosed(const DialogWindowEventUnrecPtr e)
{
    _FCPtrFieldEditor->handleCreateContainerClosed(e);
}

void FCPtrFieldEditor::FindContainerDialogListener::dialogClosing(const DialogWindowEventUnrecPtr e)
{
}

void FCPtrFieldEditor::FindContainerDialogListener::dialogClosed(const DialogWindowEventUnrecPtr e)
{
    _FCPtrFieldEditor->handleFindContainerClosed(e);
}

OSG_END_NAMESPACE
