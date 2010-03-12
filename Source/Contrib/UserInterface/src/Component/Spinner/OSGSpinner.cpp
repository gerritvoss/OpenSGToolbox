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

EventConnection Spinner::addChangeListener(ChangeListenerPtr l)
{
    return _Model->addChangeListener(l);
}

void Spinner::updateLayout(void)
{
    if(getOrientation() == Spinner::VERTICAL_ORIENTATION)
    {
        //Next Button
        if(getNextButton() != NULL)
        {
            getNextButton()->setSize(Vec2f(getNextButton()->getPreferredSize().x(), getSize().y()/2));
            getNextButton()->setPosition(Pnt2f(getSize().x() - getNextButton()->getSize().x(), 0));
        }

        //Previous Button
        if(getPreviousButton() != NULL)
        {
            getPreviousButton()->setSize(Vec2f(getPreviousButton()->getPreferredSize().x(), getSize().y()/2));
            getPreviousButton()->setPosition(Pnt2f(getSize().x() - getPreviousButton()->getSize().x(), getSize().y()/2));
        }

        //Editor
        if(getEditor() != NULL)
        {
            getEditor()->setSize(Vec2f(getSize().x() - getNextButton()->getSize().x() - getEditorToButtonOffset(), getSize().y()));
            getEditor()->setPosition(Pnt2f(0,0));
        }

    }
    else
    {
        //Next Button
        if(getNextButton() != NULL)
        {
            getNextButton()->setSize(Vec2f(getSize().x()/2, getNextButton()->getPreferredSize().y()));
            getNextButton()->setPosition(Pnt2f(0, getSize().y() - getNextButton()->getSize().y()));
        }

        //Previous Button
        if(getPreviousButton() != NULL)
        {
            getPreviousButton()->setSize(Vec2f(getSize().x()/2, getPreviousButton()->getPreferredSize().y()));
            getPreviousButton()->setPosition(Pnt2f(getSize().x()/2, getSize().y() - getPreviousButton()->getSize().y()));
        }

        //Editor
        if(getEditor() != NULL)
        {
            getEditor()->setSize(Vec2f(getSize().x(), getSize().y() - getNextButton()->getSize().y() - getEditorToButtonOffset()));
            getEditor()->setPosition(Pnt2f(0,0));
        }
    }
}

ComponentRefPtr Spinner::createEditor(SpinnerModelPtr model)
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
    TheEditor->setSpinner(SpinnerRefPtr(this));
    return TheEditor;
}

void Spinner::setModel(SpinnerModelPtr model)
{
    _Model = model;
    setEditor(createEditor(_Model));
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

/*----------------------- constructors & destructors ----------------------*/

Spinner::Spinner(void) :
    Inherited(),
    _NextButtonActionListener(this),
    _PreviousButtonActionListener(this)
{
}

Spinner::Spinner(const Spinner &source) :
    Inherited(source),
    _Model(source._Model),
    _NextButtonActionListener(this),
    _PreviousButtonActionListener(this)
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

    if(whichField & NextButtonFieldMask && getNextButton() != NULL)
    {
        getNextButton()->addMousePressedActionListener(&_NextButtonActionListener);
    }

    if(whichField & PreviousButtonFieldMask && getPreviousButton() != NULL)
    {
        getPreviousButton()->addMousePressedActionListener(&_PreviousButtonActionListener);
    }
}

void Spinner::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Spinner NI" << std::endl;
}

void Spinner::NextButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
    boost::any NewValue(_Spinner->getNextValue());
    if(!NewValue.empty())
    {
        _Spinner->setValue(NewValue);
    }
}

void Spinner::PreviousButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
    const boost::any& NewValue(_Spinner->getPreviousValue());
    if(!NewValue.empty())
    {
        _Spinner->setValue(NewValue);
    }
}

OSG_END_NAMESPACE
