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

#include "OSGGenericNameAttachmentEditor.h"
#include "OSGNameAttachment.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTextField.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGenericNameAttachmentEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGGenericNameAttachmentEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GenericNameAttachmentEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool GenericNameAttachmentEditor::attachContainer(FieldContainer* fc)
{
    //Cancel current editing
    cancelEditing();

    //Check that this is a valid FieldContainer
    if(fc == NULL)
    {
        SWARNING << "Cannot attach to a Null FieldContainer." << std::endl;
        return false;
    }

    //Check that this is an attachment container
    if(!isTypeEditable(fc->getType()))
    {
        SWARNING << "Cannot attach to a FieldContainer that is not an AttachmentContainer." << std::endl;
        return false;
    }


    //Attach to the field
    setEditingFC(fc);

    //Tell the Editor that the field has changed
    fieldChanged(fc, Name::SimpleFieldMask);

    //Attach to the Changed function callback for the container
    attachFieldCallback();

    return true;
}

bool GenericNameAttachmentEditor::dettachContainer(void)
{
    //Cancel current editing
    cancelEditing();

    dettachFieldCallback();

    //Dettach from the field
    setEditingFC(NULL);

    return true;
}

void GenericNameAttachmentEditor::startEditing (void)
{
    if(!_isEditing)
    {
        _isEditing = true;
        _InitialValue =  _EditingTextField->getText();
        dettachFieldCallback();
    }
}

void GenericNameAttachmentEditor::stopEditing  (void)
{
    if(_isEditing)
    {
        _isEditing = false;
        attachFieldCallback();

        NameUnrecPtr  NameAttachment  = 
            dynamic_cast<Name*>(dynamic_cast<AttachmentContainer*>(getEditingFC())->findAttachment(Name::getClassType().getGroupId()));

        if(NameAttachment == NULL)
        {
            setName(dynamic_cast<AttachmentContainer*>(getEditingFC()),"");
            attachFieldCallback();
            NameAttachment  = 
                dynamic_cast<Name*>(dynamic_cast<AttachmentContainer*>(getEditingFC())->findAttachment(Name::getClassType().getGroupId()));
        }

        //Call the command to set the Field
        SetFieldValueCommandPtr SetCommand =
            SetFieldValueCommand::create(NameAttachment,
                                         Name::SimpleFieldId,
                                         _EditingTextField->getText());

        getCommandManager()->executeCommand(SetCommand);
    }
}

void GenericNameAttachmentEditor::fieldChanged(FieldContainer *fc, ConstFieldMaskArg whichField)
{
    if(whichField & Name::SimpleFieldMask)
    {
        const Char8* name(getName(dynamic_cast<AttachmentContainer*>(getEditingFC())));
        if(!name)
        {
            _EditingTextField->setText("");
        }
        else
        {
            _EditingTextField->setText(name);
        }
    }
}

void GenericNameAttachmentEditor::cancelEditing(void)
{
    if(_isEditing)
    {
        _isEditing = false;
        _EditingTextField->setText(_InitialValue);
        attachFieldCallback();
    }
}

bool GenericNameAttachmentEditor::isEditing(void) const
{
    return _isEditing;
}

bool GenericNameAttachmentEditor::isTypeEditable(const DataType& type) const
{
    return type.isDerivedFrom(AttachmentContainer::getClassType());
}

void GenericNameAttachmentEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    _EditingTextField->setPosition(TopLeft);
    _EditingTextField->setSize(BottomRight - TopLeft);
}

void GenericNameAttachmentEditor::attachFieldCallback(void)
{
    if(getEditingFC() != NULL)
    {
        NameUnrecPtr  NameAttachment  = 
            dynamic_cast<Name*>(dynamic_cast<AttachmentContainer*>(getEditingFC())->findAttachment(Name::getClassType().getGroupId()));
        
        if(NameAttachment != NULL)
        {
            //Attach to the Changed function callback for the container
            NameAttachment->addChangedFunctor(boost::bind(&GenericNameAttachmentEditor::fieldChanged, this, _1, _2),"");
        }
    }
}

void GenericNameAttachmentEditor::dettachFieldCallback(void)
{
    if(getEditingFC() != NULL)
    {
        //Dettach from the Changed function callback for the container
        NameUnrecPtr  NameAttachment  = 
            dynamic_cast<Name*>(dynamic_cast<AttachmentContainer*>(getEditingFC())->findAttachment(Name::getClassType().getGroupId()));
        
        if(NameAttachment != NULL)
        {
            //Attach to the Changed function callback for the container
            NameAttachment->subChangedFunctor(boost::bind(&GenericNameAttachmentEditor::fieldChanged, this, _1, _2));
        }
    }
}

void GenericNameAttachmentEditor::handleTextFieldFocusGained    (FocusEventDetails* const details)
{
    startEditing();
}

void GenericNameAttachmentEditor::handleTextFieldFocusLost      (FocusEventDetails* const details)
{
    stopEditing();
}

void GenericNameAttachmentEditor::handleTextFieldActionPerformed(ActionEventDetails* const details)
{
    stopEditing();
    startEditing();
}

void GenericNameAttachmentEditor::handleTextFieldKeyTyped       (KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        cancelEditing();
        startEditing();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void GenericNameAttachmentEditor::onCreate(const GenericNameAttachmentEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _EditingTextField = TextField::create();
        pushToChildren(_EditingTextField);

        _TextFieldFocusGainedConnection = _EditingTextField->connectFocusGained(boost::bind(&GenericNameAttachmentEditor::handleTextFieldFocusGained, this, _1));
        _TextFieldFocusLostConnection = _EditingTextField->connectFocusLost(boost::bind(&GenericNameAttachmentEditor::handleTextFieldFocusLost, this, _1));
        _TextFieldActionPerformedConnection = _EditingTextField->connectActionPerformed(boost::bind(&GenericNameAttachmentEditor::handleTextFieldActionPerformed, this, _1));
        _TextFieldKeyTypedConnection = _EditingTextField->connectKeyTyped(boost::bind(&GenericNameAttachmentEditor::handleTextFieldKeyTyped, this, _1));
    }
}

void GenericNameAttachmentEditor::onDestroy()
{
}

void GenericNameAttachmentEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingTextField = NULL;

    _TextFieldFocusGainedConnection.disconnect();
    _TextFieldFocusLostConnection.disconnect();
    _TextFieldActionPerformedConnection.disconnect();
    _TextFieldKeyTypedConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

GenericNameAttachmentEditor::GenericNameAttachmentEditor(void) :
    Inherited()
{
}

GenericNameAttachmentEditor::GenericNameAttachmentEditor(const GenericNameAttachmentEditor &source) :
    Inherited(source)
{
}

GenericNameAttachmentEditor::~GenericNameAttachmentEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GenericNameAttachmentEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void GenericNameAttachmentEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GenericNameAttachmentEditor NI" << std::endl;
}

OSG_END_NAMESPACE
