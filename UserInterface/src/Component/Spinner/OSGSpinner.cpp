/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGSpinner.h"

#include "Component/Spinner/Editors/OSGSpinnerDefaultEditor.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Spinner
A UI Spinner. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Spinner::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Spinner::updateLayout(void)
{
    if(getOrientation() == VERTICAL_ALIGNMENT)
    {
        //Next Button
        if(getNextButton() != NullFC)
        {
            beginEditCP(getNextButton(), PositionFieldMask | SizeFieldMask);
                getNextButton()->setSize(Vec2s(getNextButton()->getPreferredSize().x(), getSize().y()/2));
                getNextButton()->setPosition(Pnt2s(getSize().x() - getNextButton()->getSize().x(), 0));
            endEditCP(getNextButton(), PositionFieldMask | SizeFieldMask);
        }

        //Previous Button
        if(getPreviousButton() != NullFC)
        {
            beginEditCP(getPreviousButton(), PositionFieldMask | SizeFieldMask);
                getPreviousButton()->setSize(Vec2s(getPreviousButton()->getPreferredSize().x(), getSize().y()/2));
                getPreviousButton()->setPosition(Pnt2s(getSize().x() - getPreviousButton()->getSize().x(), getSize().y()/2));
            endEditCP(getPreviousButton(), PositionFieldMask | SizeFieldMask);
        }
        
        //Editor
        if(getEditor() != NullFC)
        {
            beginEditCP(getEditor(), PositionFieldMask | SizeFieldMask);
                getEditor()->setSize(Vec2s(getSize().x() - getNextButton()->getSize().x(), getSize().y()));
                getEditor()->setPosition(Pnt2s(0,0));
            endEditCP(getEditor(), PositionFieldMask | SizeFieldMask);
        }
        
    }
    else
    {
        //Next Button
        if(getNextButton() != NullFC)
        {
            beginEditCP(getNextButton(), PositionFieldMask | SizeFieldMask);
                getNextButton()->setSize(Vec2s(getSize().x()/2, getNextButton()->getPreferredSize().y()));
                getNextButton()->setPosition(Pnt2s(0, getSize().y() - getNextButton()->getSize().y()));
            endEditCP(getNextButton(), PositionFieldMask | SizeFieldMask);
        }

        //Previous Button
        if(getPreviousButton() != NullFC)
        {
            beginEditCP(getPreviousButton(), PositionFieldMask | SizeFieldMask);
                getPreviousButton()->setSize(Vec2s(getSize().x()/2, getPreviousButton()->getPreferredSize().y()));
                getPreviousButton()->setPosition(Pnt2s(getSize().x()/2, getSize().y() - getPreviousButton()->getSize().y()));
            endEditCP(getPreviousButton(), PositionFieldMask | SizeFieldMask);
        }
        
        //Editor
        if(getEditor() != NullFC)
        {
            beginEditCP(getEditor(), PositionFieldMask | SizeFieldMask);
                getEditor()->setSize(Vec2s(getSize().x(), getSize().y() - getNextButton()->getSize().y()));
                getEditor()->setPosition(Pnt2s(0,0));
            endEditCP(getEditor(), PositionFieldMask | SizeFieldMask);
        }
    }
}

ComponentPtr Spinner::createEditor(SpinnerModelPtr model)
{
    //TODO: Implement
    SpinnerDefaultEditorPtr TheEditor = SpinnerDefaultEditor::create();
    beginEditCP(TheEditor, SpinnerDefaultEditor::SpinnerFieldMask);
        TheEditor->setSpinner(SpinnerPtr(this));
    endEditCP(TheEditor, SpinnerDefaultEditor::SpinnerFieldMask);
    return TheEditor;
}

void Spinner::setModel(SpinnerModelPtr model)
{
    _Model = model;
    beginEditCP(SpinnerPtr(this), EditorFieldMask);
        setEditor(createEditor(_Model));
    endEditCP(SpinnerPtr(this), EditorFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Spinner::Spinner(void) :
    Inherited(),
    _NextButtonActionListener(SpinnerPtr(this)),
    _PreviousButtonActionListener(SpinnerPtr(this))
{
}

Spinner::Spinner(const Spinner &source) :
    Inherited(source),
    _Model(source._Model),
    _NextButtonActionListener(SpinnerPtr(this)),
    _PreviousButtonActionListener(SpinnerPtr(this))
{
    if(getNextButton() != NullFC &&
        getPreviousButton() != NullFC)
    {
        beginEditCP(SpinnerPtr(this), NextButtonFieldMask | PreviousButtonFieldMask );

        setNextButton(Button::Ptr::dcast(getNextButton()->shallowCopy()));
        setPreviousButton(Button::Ptr::dcast(getPreviousButton()->shallowCopy()));
        
        endEditCP(SpinnerPtr(this), NextButtonFieldMask | PreviousButtonFieldMask);
    }
}

Spinner::~Spinner(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Spinner::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & NextButtonFieldMask ||
       whichField & PreviousButtonFieldMask ||
       whichField & EditorFieldMask)
    {
        beginEditCP(SpinnerPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getNextButton() != NullFC)
            {
                getChildren().push_back(getNextButton());
            }
            if(getPreviousButton() != NullFC)
            {
                getChildren().push_back(getPreviousButton());
            }
            if(getEditor() != NullFC)
            {
                getChildren().push_back(getEditor());
            }

        endEditCP(SpinnerPtr(this), ChildrenFieldMask);
    }
    
    if(whichField & NextButtonFieldMask && getNextButton() != NullFC)
    {
        getNextButton()->addMousePressedActionListener(&_NextButtonActionListener);
    }
    
    if(whichField & PreviousButtonFieldMask && getPreviousButton() != NullFC)
    {
        getPreviousButton()->addMousePressedActionListener(&_PreviousButtonActionListener);
    }
}

void Spinner::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Spinner NI" << std::endl;
}


void Spinner::NextButtonActionListener::actionPerformed(const ActionEvent& e)
{
    SharedFieldPtr NewValue(_Spinner->getNextValue());
    if(NewValue != SharedFieldPtr())
    {
        _Spinner->setValue(NewValue);
    }
}

void Spinner::PreviousButtonActionListener::actionPerformed(const ActionEvent& e)
{
    SharedFieldPtr NewValue(_Spinner->getPreviousValue());
    if(NewValue != SharedFieldPtr())
    {
        _Spinner->setValue(NewValue);
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSPINNERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPINNERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPINNERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

