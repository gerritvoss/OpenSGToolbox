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

#include "OSGToolbar.h"
#include "OSGSeparator.h"
#include <deque>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGToolbarBase.cpp file.
// To modify it, please change the .fcd file (OSGToolbar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Toolbar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Toolbar::setOrientation(BoxLayout::Orientation TheOrientation)
{
    dynamic_cast<BoxLayout*>(getLayout())->setOrientation(TheOrientation);

    Separator::Orientation Or;
    if(TheOrientation == BoxLayout::VERTICAL_ORIENTATION)
    {
        Or = Separator::HORIZONTAL_ORIENTATION;
    }
    else
    {
        Or = Separator::VERTICAL_ORIENTATION;
    }

    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
        {
            dynamic_cast<Separator*>(getChildren(i))->setOrientation(Or);
        }
    }

    updateSeparatorSizes();
}

BoxLayout::Orientation Toolbar::getOrientation(void) const
{
    return BoxLayout::Orientation(dynamic_cast<BoxLayout*>(getLayout())->getOrientation());
}

void Toolbar::addTool(ComponentRefPtr TheTool)
{
    if(TheTool->getType() == Separator::getClassType())
    {
        addSeparator(dynamic_pointer_cast<Separator>(TheTool));
    }

    pushToChildren(TheTool);
}

void Toolbar::removeTool(ComponentRefPtr TheTool)
{
    removeObjFromChildren(TheTool);
}

void Toolbar::removeTool(const UInt32&  Index)
{
    if(Index < getNumTools())
    {
        UInt32 ToolCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() != Separator::getClassType())
            {
                ++ToolCount;
            }
            if(ToolCount == Index)
            {
                break;
            }
        }

        removeFromChildren(ToolCount);
    }
}

void Toolbar::removeAllTools(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() != Separator::getClassType())
        {
            RemoveIndecies.push_front(i);
        }
    }
    for(UInt32 i(0) ; i<RemoveIndecies.size() ; ++i)
    {
        removeTool(RemoveIndecies[i]);
    }
}

void Toolbar::addSeparator(void)
{
    SeparatorRefPtr TheSeparator = Separator::create();
    if(getOrientation() == BoxLayout::VERTICAL_ORIENTATION)
    {
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    }
    else
    {
        TheSeparator->setOrientation(Separator::VERTICAL_ORIENTATION);
    }

    pushToChildren(TheSeparator);
}

void Toolbar::addSeparator(SeparatorRefPtr TheSeparator)
{
    if(getOrientation() == BoxLayout::VERTICAL_ORIENTATION)
    {
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    }
    else
    {
        TheSeparator->setOrientation(Separator::VERTICAL_ORIENTATION);
    }

    pushToChildren(TheSeparator);
}

void Toolbar::removeSeparator(const UInt32&  Index)
{
    if(Index < getNumSeparators())
    {
        UInt32 SeparatorCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() == Separator::getClassType())
            {
                ++SeparatorCount;
            }
            if(SeparatorCount == Index)
            {
                break;
            }
        }

        removeFromChildren(SeparatorCount);
    }
}

void Toolbar::removeSeparator(SeparatorRefPtr TheSeparator)
{
    removeObjFromChildren(TheSeparator);
}

void Toolbar::removeAllSeparators(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
        {
            RemoveIndecies.push_front(i);
        }
    }
    for(UInt32 i(0) ; i<RemoveIndecies.size() ; ++i)
    {
        removeSeparator(RemoveIndecies[i]);
    }
}

UInt32 Toolbar::getNumSeparators(void) const
{
    UInt32 NumSeparators(0);
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
        {
            ++NumSeparators;
        }
    }
    return NumSeparators;
}

void Toolbar::updateSeparatorSizes(void)
{
    Pnt2f InsideInsetsTopLeft, InsideInsetsBottomRight;
    getInsideInsetsBounds(InsideInsetsTopLeft, InsideInsetsBottomRight);
    Vec2f InsideInsetsSize(InsideInsetsBottomRight - InsideInsetsTopLeft);

    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
        {
            if(getOrientation() == BoxLayout::HORIZONTAL_ORIENTATION)
            {
                dynamic_cast<Separator*>(getChildren(i))->setPreferredSize(Vec2f(getChildren(i)->getRequestedSize().x(), InsideInsetsSize.y()));
            }
            else
            {
                dynamic_cast<Separator*>(getChildren(i))->setPreferredSize(Vec2f(InsideInsetsSize.x(), getChildren(i)->getRequestedSize().y()));
            }
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Toolbar::onCreate(const Toolbar * Id)
{
	Inherited::onCreate(Id);

	if(Id != NULL)
	{
        setLayout(createDefaultLayout());
    }
}

void Toolbar::onDestroy()
{
}

BoxLayoutRefPtr Toolbar::createDefaultLayout(void) const
{
    BoxLayoutRefPtr TheLayout = BoxLayout::create();

    TheLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    TheLayout->setMajorAxisAlignment(0.0f);
    TheLayout->setMinorAxisAlignment(0.0f);
    TheLayout->setComponentAlignment(0.0f);
    TheLayout->setMajorAxisMinimumGap(2);
    TheLayout->setMajorAxisMaximumGap(2);

    return TheLayout;
}

/*----------------------- constructors & destructors ----------------------*/

Toolbar::Toolbar(void) :
    Inherited()
{
}

Toolbar::Toolbar(const Toolbar &source) :
    Inherited(source)
{
}

Toolbar::~Toolbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Toolbar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SizeFieldMask)
    {
        updateSeparatorSizes();
    }
}

void Toolbar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Toolbar NI" << std::endl;
}

OSG_END_NAMESPACE
