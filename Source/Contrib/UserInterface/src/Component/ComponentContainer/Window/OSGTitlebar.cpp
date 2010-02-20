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

#include "OSGTitlebar.h"
#include "OSGInternalWindow.h"
#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTitlebarBase.cpp file.
// To modify it, please change the .fcd file (OSGTitlebar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Titlebar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Titlebar::setTitle(const std::string& Title)
{
    if(getTitleLabel() != NULL)
    {
        getTitleLabel()->setText(Title);
    }
}

std::string Titlebar::getTitle(void) const
{
    if(getTitleLabel() != NULL)
    {
        return getTitleLabel()->getText();
    }
    else
    {
        return std::string("");
    }
}

void Titlebar::updateLayout(void)
{
    Pnt2f InsetsTopLeft, InsetsBottomRight;
    getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
    Vec2f InsetsSize(InsetsBottomRight - InsetsTopLeft);

    Pnt2f FrameIconPos(InsetsTopLeft);
    Vec2f FrameIconSize(0.0f,0.0f);
    if(getFrameIcon() != NULL)
    {
        FrameIconSize.setValues( getFrameIcon()->getPreferredSize().x(), InsetsSize.y() );
        getFrameIcon()->setPosition(FrameIconPos);
        getFrameIcon()->setSize(FrameIconSize);
    }
    Pnt2f CloseButtonPos(InsetsBottomRight.x(), InsetsTopLeft.y()+1);
    Vec2f CloseButtonSize;
    if(getDrawClose() && getCloseButton() != NULL)
    {
        CloseButtonSize.setValues(getCloseButton()->getPreferredSize().x(), InsetsSize.y()-2);
        CloseButtonPos -= Vec2f(CloseButtonSize.x(),0) + Vec2f(3,0);
        getCloseButton()->setPosition(CloseButtonPos);
        getCloseButton()->setSize(CloseButtonSize);
    }
    Pnt2f MaximizeButtonPos(CloseButtonPos);
    Vec2f MaximizeButtonSize;
    if(getDrawMaximize() && getMaximizeButton() != NULL)
    {
        MaximizeButtonSize.setValues(getMaximizeButton()->getPreferredSize().x(), InsetsSize.y()-2);
        MaximizeButtonPos -= Vec2f(MaximizeButtonSize.x(),0) + Vec2f(3,0);
        getMaximizeButton()->setPosition(MaximizeButtonPos);
        getMaximizeButton()->setSize(MaximizeButtonSize);
    }
    Pnt2f IconifyButtonPos(MaximizeButtonPos);
    Vec2f IconifyButtonSize;
    if(getDrawIconify() && getIconifyButton() != NULL)
    {
        IconifyButtonSize.setValues(getIconifyButton()->getPreferredSize().x(), InsetsSize.y()-2);
        IconifyButtonPos -= Vec2f(IconifyButtonSize.x(),0) + Vec2f(3,0);
        getIconifyButton()->setPosition(IconifyButtonPos);
        getIconifyButton()->setSize(IconifyButtonSize);
    }
    Pnt2f TitleLabelPos(FrameIconPos + FrameIconSize);
    Vec2f TitleLabelSize;
    if(getTitleLabel() != NULL)
    {
        TitleLabelSize.setValues(IconifyButtonPos.x()-1-FrameIconPos.x()-FrameIconSize.x(), InsetsSize.y());
        getTitleLabel()->setPosition(TitleLabelPos);
        getTitleLabel()->setSize(TitleLabelSize);
    }
}

void Titlebar::updateClipBounds(void)
{
    Pnt2f TopLeft, BottomRight;
    if(getParentContainer() == NULL)
    {
        //If I have no parent container use my bounds
        getBounds(TopLeft, BottomRight);
    }
    else
    {
        //Get the intersection of:
        //My Bounds
        //My Parent Containers Clip Bounds
        //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

        //Update my Parent Container's Clip Bounds
        //dynamic_pointer_cast<Container>(getParentContainer())->updateClipBounds();

        //Get Parent Container's Clip Bounds
        Pnt2f ContainerClipTopLeft, ContainerClipBottomRight;
        dynamic_cast<InternalWindow*>(getParentWindow())->getClipBounds(ContainerClipTopLeft,ContainerClipBottomRight);

        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
        ContainerClipBottomRight -= Vec2f(getPosition());

        //Get Parent Container's Titlebar Bounds
        Pnt2f ContainerInsetTopLeft, ContainerInsetBottomRight;
        dynamic_cast<InternalWindow*>(getParentWindow())->getTitlebarBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);

        //Parent Container's Inset Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerInsetTopLeft -= Vec2f(getPosition());
        ContainerInsetBottomRight -= Vec2f(getPosition());

        //Get the intersection of my bounds with my parent containers clip bounds
        quadIntersection(MyTopLeft,MyBottomRight,
                         ContainerClipTopLeft,ContainerClipBottomRight,
                         TopLeft, BottomRight);

        quadIntersection(TopLeft,BottomRight,
                         ContainerInsetTopLeft,ContainerInsetBottomRight,
                         TopLeft, BottomRight);
    }
    //The Clip Bounds calculated are in my Parent Containers coordinate space
    //Translate these bounds into my own coordinate space
    setClipTopLeft(TopLeft);
    setClipBottomRight(BottomRight);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Titlebar::Titlebar(void) :
    Inherited()
{
}

Titlebar::Titlebar(const Titlebar &source) :
    Inherited(source)
{
    if(getIconifyButton() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(getIconifyButton()->shallowCopy());
        setIconifyButton(dynamic_pointer_cast<Button>(FCCopy));
    }
    if(getMaximizeButton() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(getMaximizeButton()->shallowCopy());
        setMaximizeButton(dynamic_pointer_cast<Button>(FCCopy));
    }
    if(getCloseButton() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(getCloseButton()->shallowCopy());
        setCloseButton(dynamic_pointer_cast<Button>(FCCopy));
    }
    if(getTitleLabel() != NULL)
    {
        FieldContainerUnrecPtr FCCopy(getTitleLabel()->shallowCopy());
        setTitleLabel(dynamic_pointer_cast<Label>(FCCopy));
    }
}

Titlebar::~Titlebar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Titlebar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & FrameIconFieldMask) ||
        (whichField & IconifyButtonFieldMask) ||
        (whichField & MaximizeButtonFieldMask) ||
        (whichField & CloseButtonFieldMask) ||
        (whichField & TitleLabelFieldMask) ||
        (whichField & DrawCloseFieldMask) ||
        (whichField & DrawMaximizeFieldMask) ||
        (whichField & DrawIconifyFieldMask)
      )
    {
        clearChildren();
        if(getFrameIcon() != NULL)
        {
            pushToChildren(getFrameIcon());
        }
        if(getTitleLabel() != NULL)
        {
            pushToChildren(getTitleLabel());
        }
        if(getDrawIconify() && getIconifyButton() != NULL)
        {
            pushToChildren(getIconifyButton());
        }
        if(getDrawMaximize() && getMaximizeButton() != NULL)
        {
            pushToChildren(getMaximizeButton());
        }
        if(getDrawClose() && getCloseButton() != NULL)
        {
            pushToChildren(getCloseButton());
        }
    }

    if(((whichField & IconifyButtonFieldMask) ||
        (whichField & ParentWindowFieldMask)) &&
       getParentWindow() != NULL &&
       getIconifyButton() != NULL &&
       getParentWindow()->getIconable() != getIconifyButton()->getEnabled())
    {
        getIconifyButton()->setEnabled(getParentWindow()->getIconable());
    }

    if(((whichField & MaximizeButtonFieldMask) ||
        (whichField & ParentWindowFieldMask)) &&
       getParentWindow() != NULL &&
       getMaximizeButton() != NULL &&
       getParentWindow()->getMaximizable() != getMaximizeButton()->getEnabled())
    {
        getMaximizeButton()->setEnabled(getParentWindow()->getMaximizable());
    }

    if(((whichField & CloseButtonFieldMask) ||
        (whichField & ParentWindowFieldMask)) &&
       getParentWindow() != NULL &&
       getCloseButton() != NULL &&
       getParentWindow()->getClosable() != getCloseButton()->getEnabled())
    {
        getCloseButton()->setEnabled(getParentWindow()->getClosable());
    }
}

void Titlebar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Titlebar NI" << std::endl;
}

OSG_END_NAMESPACE
