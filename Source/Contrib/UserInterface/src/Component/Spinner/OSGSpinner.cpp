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

#include "OSGSpinner.h"

#include "OSGListSpinnerModel.h"
#include "OSGNumberSpinnerModel.h"

#include "OSGSpinnerEditor.h"
#include "OSGButton.h"
#include "OSGSpinnerDefaultEditor.h"
#include "OSGSpinnerNumberEditor.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSpinnerBase.cpp file.
// To modify it, please change the .fcd file (OSGSpinner.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Spinner::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void Spinner::updateLayout(void)
{
    Pnt2f Pos;
    Vec2f Size;
    if(getOrientation() == Spinner::VERTICAL_ORIENTATION)
    {
        //Next Button
        if(getNextButton() != NULL)
        {
            Size.setValues(getNextButton()->getPreferredSize().x(), getSize().y()/2);
            if(getNextButton()->getSize() != Size)
            {
                getNextButton()->setSize(Size);
            }
            Pos.setValues(getSize().x() - getNextButton()->getSize().x(), 0);
            if(getNextButton()->getPosition() != Pos)
            {
                getNextButton()->setPosition(Pos);
            }
        }

        //Previous Button
        if(getPreviousButton() != NULL)
        {
            Size.setValues(getPreviousButton()->getPreferredSize().x(), getSize().y()/2);
            if(getPreviousButton()->getSize() != Size)
            {
                getPreviousButton()->setSize(Size);
            }
            Pos.setValues(getSize().x() - getPreviousButton()->getSize().x(), getSize().y()/2);
            if(getPreviousButton()->getPosition() != Pos)
            {
                getPreviousButton()->setPosition(Pos);
            }
        }

        //Editor
        if(getEditor() != NULL)
        {
            Size.setValues(getSize().x() - getNextButton()->getSize().x() - getEditorToButtonOffset(), getSize().y());
            if(getEditor()->getSize() != Size)
            {
                getEditor()->setSize(Size);
            }
            Pos.setValues(0,0);
            if(getEditor()->getPosition() != Pos)
            {
                getEditor()->setPosition(Pos);
            }
        }

    }
    else
    {
        //Next Button
        if(getNextButton() != NULL)
        {
            Size.setValues(getSize().x()/2, getNextButton()->getPreferredSize().y());
            if(getNextButton()->getSize() != Size)
            {
                getNextButton()->setSize(Size);
            }
            Pos.setValues(0, getSize().y() - getNextButton()->getSize().y());
            if(getNextButton()->getPosition() != Pos)
            {
                getNextButton()->setPosition(Pos);
            }
        }

        //Previous Button
        if(getPreviousButton() != NULL)
        {
            Size.setValues(getSize().x()/2, getPreviousButton()->getPreferredSize().y());
            if(getPreviousButton()->getSize() != Size)
            {
                getPreviousButton()->setSize(Size);
            }
            Pos.setValues(getSize().x()/2, getSize().y() - getPreviousButton()->getSize().y());
            if(getPreviousButton()->getPosition() != Pos)
            {
                getPreviousButton()->setPosition(Pos);
            }
        }

        //Editor
        if(getEditor() != NULL)
        {
            Size.setValues(getSize().x(), getSize().y() - getNextButton()->getSize().y() - getEditorToButtonOffset());
            if(getEditor()->getSize() != Size)
            {
                getEditor()->setSize(Size);
            }
            Pos.setValues(0,0);
            if(getEditor()->getPosition() != Pos)
            {
                getEditor()->setPosition(Pos);
            }
        }
    }
}

ComponentTransitPtr Spinner::createEditor(SpinnerModelPtr model)
{
    //TODO: Implement
    SpinnerDefaultEditorRefPtr TheEditor;
    if(model->getModelName().compare(ListSpinnerModel::getClassModelName()) == 0)
    {
        TheEditor = SpinnerDefaultEditor::create();
    }
    else if(model->getModelName().compare(getNumberSpinnerModelClassModelName()) == 0)
    {
        TheEditor = SpinnerNumberEditor::create();
    }
    else
    {
        TheEditor = SpinnerDefaultEditor::create();
    }
    TheEditor->setSpinner(this);
    return ComponentTransitPtr(TheEditor.get());
}

void Spinner::setModel(SpinnerModelPtr model)
{
    _Model = model;
    setEditor(ComponentUnrecPtr(createEditor(_Model)));
}

void Spinner::setEditable(bool Editable)
{
    if(getEditor() != NULL && getEditor()->getType().isDerivedFrom(SpinnerEditor::getClassType()))
    {
        dynamic_cast<SpinnerEditor*>(getEditor())->setEditable(Editable);
    }
}

bool Spinner::getEditable(void) const
{
    if(getEditor() != NULL && getEditor()->getType().isDerivedFrom(SpinnerEditor::getClassType()))
    {
        return dynamic_cast<SpinnerEditor*>(getEditor())->getEditable();
    }
    else
    {
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Spinner::onCreate(const Spinner * Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL &&
       Id->getNextButton() != NULL &&
       Id->getPreviousButton() != NULL)
    {
        FieldContainerUnrecPtr TheFC(NULL);

        TheFC = Id->getNextButton()->shallowCopy();
        setNextButton(dynamic_pointer_cast<Button>(TheFC));

        TheFC = Id->getPreviousButton()->shallowCopy();
        setPreviousButton(dynamic_pointer_cast<Button>(TheFC));
    }
}

void Spinner::onDestroy()
{
}

void Spinner::resolveLinks(void)
{
    Inherited::resolveLinks();

    _NextButtonActionConnection.disconnect();
    _PreviousButtonActionConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

Spinner::Spinner(void) :
    Inherited()
{
}

Spinner::Spinner(const Spinner &source) :
    Inherited(source),
    _Model(source._Model)
{
}

Spinner::~Spinner(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Spinner::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & NextButtonFieldMask ||
       whichField & PreviousButtonFieldMask ||
       whichField & EditorFieldMask)
    {
        clearChildren();
        if(getNextButton() != NULL)
        {
            pushToChildren(getNextButton());
        }
        if(getPreviousButton() != NULL)
        {
            pushToChildren(getPreviousButton());
        }
        if(getEditor() != NULL)
        {
            pushToChildren(getEditor());
        }

    }

    if(whichField & NextButtonFieldMask)
    {
        _NextButtonActionConnection.disconnect();
        if(getNextButton() != NULL)
        {
            _NextButtonActionConnection = getNextButton()->connectMousePressedActionPerformed(boost::bind(&Spinner::handleNextButtonAction, this, _1));
        }
    }

    if(whichField & PreviousButtonFieldMask)
    {
        _PreviousButtonActionConnection.disconnect();
        if(getPreviousButton() != NULL)
        {
            _PreviousButtonActionConnection = getPreviousButton()->connectMousePressedActionPerformed(boost::bind(&Spinner::handlePreviousButtonAction, this, _1));
        }
    }
}

void Spinner::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Spinner NI" << std::endl;
}

void Spinner::handleNextButtonAction(ActionEventDetails* const e)
{
    boost::any NewValue(getNextValue());
    if(!NewValue.empty())
    {
        setValue(NewValue);
    }
}

void Spinner::handlePreviousButtonAction(ActionEventDetails* const e)
{
    const boost::any& NewValue(getPreviousValue());
    if(!NewValue.empty())
    {
        setValue(NewValue);
    }
}

OSG_END_NAMESPACE
