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
            setName(dynamic_cast<AttachmentContainer*>(getEditingFC()),"");
            name = getName(dynamic_cast<AttachmentContainer*>(getEditingFC()));
        }
        _EditingTextField->setText(name);
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
        
        //Attach to the Changed function callback for the container
        NameAttachment->addChangedFunctor(boost::bind(&GenericNameAttachmentEditor::fieldChanged, this, _1, _2),"");
    }
}

void GenericNameAttachmentEditor::dettachFieldCallback(void)
{
    if(getEditingFC() != NULL)
    {
        //Dettach from the Changed function callback for the container
        NameUnrecPtr  NameAttachment  = 
            dynamic_cast<Name*>(dynamic_cast<AttachmentContainer*>(getEditingFC())->findAttachment(Name::getClassType().getGroupId()));
        
        //Attach to the Changed function callback for the container
        NameAttachment->subChangedFunctor(boost::bind(&GenericNameAttachmentEditor::fieldChanged, this, _1, _2));
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
        _EditingTextField->addFocusListener(&_TextFieldListener);
        _EditingTextField->addActionListener(&_TextFieldListener);
        _EditingTextField->addKeyListener(&_TextFieldListener);
    }
}

void GenericNameAttachmentEditor::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

GenericNameAttachmentEditor::GenericNameAttachmentEditor(void) :
    Inherited(),
    _TextFieldListener(this)
{
}

GenericNameAttachmentEditor::GenericNameAttachmentEditor(const GenericNameAttachmentEditor &source) :
    Inherited(source),
    _TextFieldListener(this)
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

void GenericNameAttachmentEditor::TextFieldListener::focusGained    (const FocusEventUnrecPtr  e)
{
    _GenericNameAttachmentEditor->startEditing();
}

void GenericNameAttachmentEditor::TextFieldListener::focusLost      (const FocusEventUnrecPtr  e)
{
    _GenericNameAttachmentEditor->stopEditing();
}

void GenericNameAttachmentEditor::TextFieldListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _GenericNameAttachmentEditor->stopEditing();
    _GenericNameAttachmentEditor->startEditing();
}

void GenericNameAttachmentEditor::TextFieldListener::keyTyped       (const KeyEventUnrecPtr    e)
{
    if(e->getKey() == KeyEvent::KEY_ESCAPE)
    {
        _GenericNameAttachmentEditor->cancelEditing();
        _GenericNameAttachmentEditor->startEditing();
    }
}

OSG_END_NAMESPACE
