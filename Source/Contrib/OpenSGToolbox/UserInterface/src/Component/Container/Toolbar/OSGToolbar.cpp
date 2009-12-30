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

#include "OSGToolbar.h"
#include "Component/Misc/OSGSeparator.h"
#include <deque>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Toolbar
A UI Toolbar. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Toolbar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Toolbar::setOrientation(BoxLayout::Orientation TheOrientation)
{
	beginEditCP(BoxLayout::Ptr::dcast(getLayout()), BoxLayout::OrientationFieldMask);
		BoxLayout::Ptr::dcast(getLayout())->setOrientation(TheOrientation);
	endEditCP(BoxLayout::Ptr::dcast(getLayout()), BoxLayout::OrientationFieldMask);
    
    Separator::Orientation Or;
    if(TheOrientation == BoxLayout::VERTICAL_ORIENTATION)
    {
        Or = Separator::HORIZONTAL_ORIENTATION;
    }
    else
    {
        Or = Separator::VERTICAL_ORIENTATION;
    }

    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
        {
            beginEditCP(getChildren()[i], Separator::OrientationFieldMask);
                Separator::Ptr::dcast(getChildren()[i])->setOrientation(Or);
            endEditCP(getChildren()[i], Separator::OrientationFieldMask);
        }
    }

    updateSeparatorSizes();
}

BoxLayout::Orientation Toolbar::getOrientation(void) const
{
	return BoxLayout::Orientation(BoxLayout::Ptr::dcast(getLayout())->getOrientation());
}

void Toolbar::addTool(ComponentPtr TheTool)
{
    if(TheTool->getType() == Separator::getClassType())
    {
        addSeparator(Separator::Ptr::dcast(TheTool));
    }

    beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
        getChildren().push_back(TheTool);
    endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
}

void Toolbar::removeTool(ComponentPtr TheTool)
{
    MFComponentPtr::iterator RemoveItor(getChildren().find(TheTool));
    if(RemoveItor != getChildren().end())
    {
        beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
    }
}

void Toolbar::removeTool(const UInt32&  Index)
{
    if(Index < getNumTools())
    {
        MFComponentPtr::iterator RemoveItor(getChildren().begin());
        UInt32 ToolCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() != Separator::getClassType())
            {
                ++ToolCount;
            }
            if(ToolCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }

        beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
    }
}

void Toolbar::removeAllTools(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() != Separator::getClassType())
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
    SeparatorPtr TheSeparator = Separator::create();
    beginEditCP(TheSeparator, Separator::OrientationFieldMask);
    if(getOrientation() == BoxLayout::VERTICAL_ORIENTATION)
    {
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    }
    else
    {
        TheSeparator->setOrientation(Separator::VERTICAL_ORIENTATION);
    }
    endEditCP(TheSeparator, Separator::OrientationFieldMask);

    beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
        getChildren().push_back(TheSeparator);
    endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
}

void Toolbar::addSeparator(SeparatorPtr TheSeparator)
{
    beginEditCP(TheSeparator, Separator::OrientationFieldMask);
    if(getOrientation() == BoxLayout::VERTICAL_ORIENTATION)
    {
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    }
    else
    {
        TheSeparator->setOrientation(Separator::VERTICAL_ORIENTATION);
    }
    endEditCP(TheSeparator, Separator::OrientationFieldMask);

    beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
        getChildren().push_back(TheSeparator);
    endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
}

void Toolbar::removeSeparator(const UInt32&  Index)
{
    if(Index < getNumSeparators())
    {
        MFComponentPtr::iterator RemoveItor(getChildren().begin());
        UInt32 SeparatorCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() == Separator::getClassType())
            {
                ++SeparatorCount;
            }
            if(SeparatorCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }

        beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
    }
}

void Toolbar::removeSeparator(SeparatorPtr TheSeparator)
{
    MFComponentPtr::iterator RemoveItor(getChildren().find(TheSeparator));
    if(RemoveItor != getChildren().end())
    {
        beginEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(ToolbarPtr(this), Toolbar::ChildrenFieldMask);
    }
}

void Toolbar::removeAllSeparators(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
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
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
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

    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
        {
            beginEditCP(getChildren()[i], Separator::PreferredSizeFieldMask);
            if(getOrientation() == BoxLayout::HORIZONTAL_ORIENTATION)
            {
                Separator::Ptr::dcast(getChildren()[i])->setPreferredSize(Vec2f(getChildren()[i]->getRequestedSize().x(), InsideInsetsSize.y()));
            }
            else
            {
                Separator::Ptr::dcast(getChildren()[i])->setPreferredSize(Vec2f(InsideInsetsSize.x(), getChildren()[i]->getRequestedSize().y()));
            }
            endEditCP(getChildren()[i], Separator::PreferredSizeFieldMask);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

BoxLayoutPtr Toolbar::createDefaultLayout(void) const
{
	BoxLayoutPtr TheLayout = BoxLayout::create();

	beginEditCP(TheLayout);
		TheLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
		TheLayout->setMajorAxisAlignment(0.0f);
		TheLayout->setMinorAxisAlignment(0.0f);
		TheLayout->setComponentAlignment(0.0f);
		TheLayout->setMajorAxisMinimumGap(2);
		TheLayout->setMajorAxisMaximumGap(2);
	endEditCP(TheLayout);

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
	beginEditCP(ToolbarPtr(this), Toolbar::LayoutFieldMask);
		setLayout(createDefaultLayout());
	endEditCP(ToolbarPtr(this), Toolbar::LayoutFieldMask);
}

Toolbar::~Toolbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Toolbar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

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
    static Char8 cvsid_hpp       [] = OSGTOOLBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOOLBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOOLBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

