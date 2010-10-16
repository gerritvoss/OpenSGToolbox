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
#include "OSGUIDrawUtils.h"
#include "OSGContainerUtils.h"
#include "OSGRemoveFieldElementCommand.h"
#include "OSGInsertFieldElementCommand.h"
#include "OSGAddFieldElementCommand.h"
#include "OSGCreateFieldContainerCommand.h"
#include "OSGDialogWindow.h"
#include "OSGUIDrawingSurface.h"
#include <boost/lexical_cast.hpp>

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

void GenericMultiFieldEditor::removeIndex(FieldContainer* const fc,
                                          UInt32 fieldID,
                                          UInt32 index,
                                          UIDrawingSurface* const drawingSurface,
                                          CommandManager* cmdMgr)
{
    //Call the command to set the Field
    RemoveFieldElementCommandPtr RemoveIndexCommand = RemoveFieldElementCommand::create(fc, fieldID, index);

    cmdMgr->executeCommand(RemoveIndexCommand);
}

void GenericMultiFieldEditor::insertAtIndex(FieldContainer* const fc,
                                            UInt32 fieldID,
                                            UInt32 index,
                                            const FieldContainerType* type,
                                            CommandManager* cmdMgr)
{
    const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(fc->getFieldDescription(fieldID)->getFieldType().getContentType()));

    //Create the Container
    CreateFieldContainerCommandPtr CreateCommand;
    
    //If the type is a node, then create a NodeCore instead
    //and then insert it as the core of a newly created node
    if(*ThePtrType == Node::getClassType())
    {
        CreateFieldContainerCommandPtr CreateCoreCommand = CreateFieldContainerCommand::create(type);
        cmdMgr->executeCommand(CreateCoreCommand);
        
        CreateCommand = CreateFieldContainerCommand::create(&Node::getClassType());
        cmdMgr->executeCommand(CreateCommand);

        dynamic_cast<Node*>(CreateCommand->getContainer())->setCore(dynamic_cast<NodeCore*>(CreateCoreCommand->getContainer()));
    }
    else
    {
        CreateCommand = CreateFieldContainerCommand::create(type);
        cmdMgr->executeCommand(CreateCommand);
    }
        
    EditFieldHandlePtr TheFieldHandle = fc->editField(fieldID);
    EditMFieldHandle<FieldContainerPtrMFieldBase>* TheHandle(dynamic_cast<EditMFieldHandle<FieldContainerPtrMFieldBase>*>(TheFieldHandle.get()));

    if(index >= fc->getField(fieldID)->size() ||
       !TheHandle->supportsInsert())
    {
        //Set the value of the field
        AddFieldElementCommandPtr AddCommand = AddFieldElementCommand::create(fc,
                                                                            fieldID,
                                                                            boost::lexical_cast<std::string>(CreateCommand->getContainer()->getId()));

        cmdMgr->executeCommand(AddCommand);
    }
    else
    {
        //Set the value of the field
        InsertFieldElementCommandPtr InsertIndexCommand = InsertFieldElementCommand::create(fc,
                                                                                            fieldID,
                                                                                            boost::lexical_cast<std::string>(CreateCommand->getContainer()->getId()),
                                                                                            index);

        cmdMgr->executeCommand(InsertIndexCommand);
    }
}

void GenericMultiFieldEditor::insertAtIndex(FieldContainer* const fc,
                                            UInt32 fieldID,
                                            UInt32 index,
                                            UIDrawingSurface* const drawingSurface,
                                            CommandManager* cmdMgr)
{
    //Is this a pointer field
    GetFieldHandlePtr TheFieldHandle(fc->getField(fieldID));
    if(TheFieldHandle->isPointerField())
    {
        //Create
        const FieldContainerType* ThePtrType(getFieldContainerTypeFromPtrType(fc->getFieldDescription(fieldID)->getFieldType().getContentType()));
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

        if(inputValues.size() == 1)
        {
            insertAtIndex(fc,fieldID,index,FieldContainerFactory::the()->findType(inputValues[0].c_str()),cmdMgr);
        }
        else
        {
            DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Create " + fc->getFieldDescription(fieldID)->getFieldType().getContentType().getName(),
                                                                           "Choose the type of object to create",
                                                                           DialogWindow::INPUT_COMBO,
                                                                           true,
                                                                           inputValues);
            TheDialog->connectDialogWindowClosed(boost::bind(&GenericMultiFieldEditor::handleInsertFCPtrDialogClosed,
                                                             _1,
                                                             fc,
                                                             fieldID,
                                                             index,
                                                             cmdMgr));

            Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), drawingSurface->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
            TheDialog->setPosition(CenteredPosition);
            TheDialog->setAllwaysOnTop(true);
            TheDialog->setModal(true);
            TheDialog->setResizable(true);

            drawingSurface->openWindow(TheDialog);
        }
    }
    else
    {
        //Insert the default
        InsertFieldElementCommandPtr InsertIndexCommand = InsertFieldElementCommand::create(fc, fieldID, "", index);

        cmdMgr->executeCommand(InsertIndexCommand);
    }
}

void GenericMultiFieldEditor::handleInsertFCPtrDialogClosed(DialogWindowEventDetails* const details,
                                                            FieldContainer* const fc,
                                                            UInt32 fieldID,
                                                            UInt32 index,
                                                            CommandManager* cmdMgr)
{
    if(details->getOption() != DialogWindowEventDetails::DIALOG_OPTION_CANCEL)
    {
        const FieldContainerType* TheType(FieldContainerFactory::the()->findType(details->getInput().c_str()));

        if(TheType != NULL)
        {
            insertAtIndex(fc,fieldID,index,TheType,cmdMgr);
        }
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

    //Update the List elemtent height used for this type of
    //fc editor
    const FieldContainerType* EditorType = FieldEditorFactory::the()->getSingleDefaultEditorType(&(fc->getFieldDescription(fieldId)->getFieldType().getContentType()));
    FieldEditorComponentRefPtr TheEditor = dynamic_pointer_cast<FieldEditorComponent>(EditorType->createContainer());
    _FieldList->setCellMajorAxisLength(24.0f * static_cast<Real32>(TheEditor->getNumRequestedRows()));

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

void GenericMultiFieldEditor::handleListMouseClicked(MouseEventDetails* const details)
{
    if(details->getButton() == MouseEventDetails::BUTTON1 && 
       details->getClickCount() == 1 &&
       _FieldList->getIndexForDrawingSurfaceLocation(details->getLocation()) == -1)
    {
        insertAtIndex(getEditingFC(),
                      getEditingFieldId(),
                      //Size of list,
                      _FieldList->getModel()->getSize(),
                      getParentWindow()->getParentDrawingSurface(),
                      getCommandManager().get());
    }
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
        _ListMouseClickedConnection = _FieldList->connectMouseClicked(boost::bind(&GenericMultiFieldEditor::handleListMouseClicked, this, _1));
        

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

void GenericMultiFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ElementEndLabel = NULL;
    _FieldListModel = NULL;
    _FieldListGenerator = NULL;
    _FieldList = NULL;
    _FieldList = NULL;
    _FieldElementsScrollPanel = NULL;
    _FieldEditors.clear();

    _ListMouseClickedConnection.disconnect();
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
