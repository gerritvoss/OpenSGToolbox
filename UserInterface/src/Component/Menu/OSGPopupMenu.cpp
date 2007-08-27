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

#include "OSGPopupMenu.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PopupMenu
A UI Menu. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PopupMenu::initMethod (void)
{
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PopupMenu::updateLayout(void)
{
	//Determine the Max Preferred Width of my MenuItems
	UInt16 MaxWidth(0);
	UInt16 TotalHeight(0);
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(MaxWidth < getChildren().getValue(i)->getPreferredSize().x())
        {
            MaxWidth = getChildren().getValue(i)->getPreferredSize().x();
	    }
	    TotalHeight += getChildren().getValue(i)->getPreferredSize().y();
	}

    //Set My preferred Size
	Pnt2s TopLeft, BottomRight;
	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getBounds(TopLeft, BottomRight);
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Vec2s InsetSize( (BottomRight-TopLeft) - (InsetsBottomRight-InsetsTopLeft) );
    beginEditCP(PopupMenuPtr(this), PreferredSizeFieldMask);
        setPreferredSize(Vec2s(MaxWidth+InsetSize.x(), TotalHeight+InsetSize.y()));
        //Sneakily set my size
        setSize(getPreferredSize());
    endEditCP(PopupMenuPtr(this), PreferredSizeFieldMask);
    
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	
	//Now position and size the Items
	UInt16 TopOffset(InsetsTopLeft.y());
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren().getValue(i), SizeFieldMask | PositionFieldMask);
            getChildren().getValue(i)->setSize(Vec2s(MaxWidth, getChildren().getValue(i)->getPreferredSize().y()));
            getChildren().getValue(i)->setPosition(Pnt2s(InsetsTopLeft.x(), TopOffset));
        endEditCP(getChildren().getValue(i), SizeFieldMask | PositionFieldMask);

        TopOffset += getChildren().getValue(i)->getPreferredSize().y();
    }
}

void PopupMenu::addItem(MenuItemPtr Item)
{
    beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
        getChildren().push_back(Item);
    endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
}

void PopupMenu::addItem(MenuItemPtr Item, const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator Itor;
        for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
        beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
            getChildren().insert(Itor, Item);
        endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
    }
}

void PopupMenu::removeItem(MenuItemPtr Item)
{
    MFComponentPtr::iterator FindResult = getChildren().find(Item);
    if(FindResult != getChildren().end())
    {
        beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
            getChildren().erase(FindResult);
        endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
    }
}

void PopupMenu::removeItem(const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator Itor;
        for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
        beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
            getChildren().erase(Itor);
        endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PopupMenu::PopupMenu(void) :
    Inherited()
{
}

PopupMenu::PopupMenu(const PopupMenu &source) :
    Inherited(source)
{
}

PopupMenu::~PopupMenu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PopupMenu::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PopupMenu::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PopupMenu NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPOPUPMENUBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPOPUPMENUBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPOPUPMENUFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

