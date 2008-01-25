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

#include "OSGSpringLayoutConstraints.h"
#include "Layout/Spring/OSGLayoutSpring.h"
#include "Component/OSGComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SpringLayoutConstraints
A UI SpringLayoutConstraints. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpringLayoutConstraints::initMethod (void)
{
}

SpringLayoutConstraintsPtr SpringLayoutConstraints::create(LayoutSpringPtr XSpring, LayoutSpringPtr YSpring)
{
    SpringLayoutConstraintsPtr NewConstraints = createEmpty();

    beginEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask);
        NewConstraints->setWestSpring(XSpring);
        NewConstraints->setNorthSpring(YSpring);
    endEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask);

    return NewConstraints;
}

SpringLayoutConstraintsPtr SpringLayoutConstraints::create(LayoutSpringPtr XSpring, LayoutSpringPtr YSpring, LayoutSpringPtr WidthSpring, LayoutSpringPtr HeightSpring)
{
    SpringLayoutConstraintsPtr NewConstraints = createEmpty();

    beginEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask | WidthSpringFieldMask | HeightSpringFieldMask);
        NewConstraints->setWestSpring(XSpring);
        NewConstraints->setNorthSpring(YSpring);
        NewConstraints->setWidthSpring(WidthSpring);
        NewConstraints->setHeightSpring(HeightSpring);
    endEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask | WidthSpringFieldMask | HeightSpringFieldMask);

    return NewConstraints;
}

SpringLayoutConstraintsPtr SpringLayoutConstraints::create(ComponentPtr TheComponent)
{
    SpringLayoutConstraintsPtr NewConstraints = createEmpty();

    beginEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask | WidthSpringFieldMask | HeightSpringFieldMask | ComponentFieldMask);
        NewConstraints->setWestSpring(LayoutSpring::constant(TheComponent->getPosition().x()));
        NewConstraints->setNorthSpring(LayoutSpring::constant(TheComponent->getPosition().y()));
        NewConstraints->setWidthSpring(LayoutSpring::width(TheComponent));
        NewConstraints->setHeightSpring(LayoutSpring::height(TheComponent));
        NewConstraints->setComponent(TheComponent);
    endEditCP(NewConstraints, WestSpringFieldMask | NorthSpringFieldMask | WidthSpringFieldMask | HeightSpringFieldMask | ComponentFieldMask);

    return NewConstraints;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpringLayoutConstraints::setX(LayoutSpringPtr x)
{
    setWest(x);
}

LayoutSpringPtr SpringLayoutConstraints::getX(void)
{
    return getWest();
}

void SpringLayoutConstraints::setY(LayoutSpringPtr y)
{
    setNorth(y);
}
LayoutSpringPtr SpringLayoutConstraints::getY(void)
{
    return getNorth();
}

void SpringLayoutConstraints::setWidth(LayoutSpringPtr width)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), WidthSpringFieldMask);
        setWidthSpring(width);
    endEditCP(SpringLayoutConstraintsPtr(this), WidthSpringFieldMask);
    
    pushToHistory(WIDTH_EDGE, width, true);
}

LayoutSpringPtr SpringLayoutConstraints::getWidth(void)
{
    if(getWidthSpring() == NullFC)
    {
        if(defined(EAST_EDGE) && defined(WEST_EDGE))
        {
            return difference(getEastSpring(), getWestSpring());
        }
        else if(defined(HORIZONTAL_CENTER_EDGE) && defined(WEST_EDGE))
        {
            return scale(difference(getHorizontalCenterSpring(), getWestSpring()), 2.0f);
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getWidthSpring();
    }
}

void SpringLayoutConstraints::setHeight(LayoutSpringPtr height)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), HeightSpringFieldMask);
        setHeightSpring(height);
    endEditCP(SpringLayoutConstraintsPtr(this), HeightSpringFieldMask);
    
    pushToHistory(HEIGHT_EDGE, height, false);
}

LayoutSpringPtr SpringLayoutConstraints::getHeight(void)
{
    if(getHeightSpring() == NullFC)
    {
        if(defined(SOUTH_EDGE) && defined(NORTH_EDGE))
        {
            return difference(getSouthSpring(), getNorthSpring());
        }
        else if(defined(VERTICAL_CENTER_EDGE) && defined(NORTH_EDGE))
        {
            return scale(difference(getVerticalCenterSpring(), getSouthSpring()), 2.0f);
        }
        else if(defined(BASELINE_EDGE) && defined(NORTH_EDGE))
        {
            return relativeBaselineToHeight(difference(getBaselineSpring(), getNorthSpring()));
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getHeightSpring();
    }
}

void SpringLayoutConstraints::setNorth(LayoutSpringPtr north)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), NorthSpringFieldMask);
        setNorthSpring(north);
    endEditCP(SpringLayoutConstraintsPtr(this), NorthSpringFieldMask);
    
    pushToHistory(NORTH_EDGE, north, false);
}

LayoutSpringPtr SpringLayoutConstraints::getNorth(void)
{
    if(getNorthSpring() == NullFC)
    {
        if(defined(SOUTH_EDGE) && defined(HEIGHT_EDGE))
        {
            return difference(getSouthSpring(), getHeightSpring());
        }
        else if(defined(VERTICAL_CENTER_EDGE) && defined(HEIGHT_EDGE))
        {
            return difference(getVerticalCenterSpring(), scale(getHeightSpring(), 0.5f));
        }
        else if(defined(VERTICAL_CENTER_EDGE) && defined(SOUTH_EDGE))
        {
            return difference(scale(getVerticalCenterSpring(), 2.0f), getSouthSpring());
        }
        else if(defined(BASELINE_EDGE) && defined(HEIGHT_EDGE))
        {
            return difference(getBaselineSpring(), heightToRelativeBaseline(getHeightSpring()));
        }
        else if(defined(BASELINE_EDGE) && defined(SOUTH_EDGE))
        {
            return scale(difference(getBaselineSpring(), heightToRelativeBaseline(getSouthSpring())), 2.0f);
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getNorthSpring();
    }
}

void SpringLayoutConstraints::setEast(LayoutSpringPtr east)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), EastSpringFieldMask);
        setEastSpring(east);
    endEditCP(SpringLayoutConstraintsPtr(this), EastSpringFieldMask);
    
    pushToHistory(EAST_EDGE, east, true);
}

LayoutSpringPtr SpringLayoutConstraints::getEast(void)
{
    if(getEastSpring() == NullFC)
    {
        if(defined(WEST_EDGE) && defined(WIDTH_EDGE))
        {
            return sum(getWestSpring(), getWidthSpring());
        }
        else if(defined(HORIZONTAL_CENTER_EDGE) && defined(WIDTH_EDGE))
        {
            return sum(getHorizontalCenterSpring(), scale(getWidthSpring(), 0.5f));
        }
        else if(defined(HORIZONTAL_CENTER_EDGE) && defined(WEST_EDGE))
        {
            return sum(scale(getHorizontalCenterSpring(), 2.0f), getWestSpring());
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getEastSpring();
    }
}

void SpringLayoutConstraints::pushToHistory(Edge TheEdge, LayoutSpringPtr Value, bool isHorizontal)
{
    std::deque<Edge>& History(isHorizontal ? _HorizontalHistory : _VerticalHistory);
    bool valid(true);
    
    std::deque<Edge>::iterator SearchItor(std::find(History.begin(), History.end(), TheEdge));
    if (SearchItor != History.end())
    {
        History.erase(SearchItor);
        valid = false;
    }
    else if (History.size() == 2 && Value != NullFC)
    {
        History.pop_front();
        valid = false;
    }
    if (Value != NullFC)
    {
        History.push_back(TheEdge);
    }
    if (!valid)
    {
        std::deque<Edge> All;
        if(isHorizontal)
        {
            All.push_back(EAST_EDGE);
            All.push_back(WEST_EDGE);
            All.push_back(HORIZONTAL_CENTER_EDGE);
            All.push_back(WIDTH_EDGE);
        }
        else
        {
            All.push_back(NORTH_EDGE);
            All.push_back(SOUTH_EDGE);
            All.push_back(VERTICAL_CENTER_EDGE);
            All.push_back(BASELINE_EDGE);
            All.push_back(HEIGHT_EDGE);
        }
        for (UInt32 i(0); i < All.size(); ++i)
        {
            if (std::find(History.begin(), History.end(), All[i]) == History.end())
            {
                setConstraint(All[i], NullFC);
            }
        }
    }
}

void SpringLayoutConstraints::setSouth(LayoutSpringPtr south)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), SouthSpringFieldMask);
        setSouthSpring(south);
    endEditCP(SpringLayoutConstraintsPtr(this), SouthSpringFieldMask);
    
    pushToHistory(SOUTH_EDGE, south, false);
}
LayoutSpringPtr SpringLayoutConstraints::getSouth(void)
{
    if(getSouthSpring() == NullFC)
    {
        if(defined(NORTH_EDGE) && defined(HEIGHT_EDGE))
        {
            return sum(getNorthSpring(), getHeightSpring());
        }
        else if(defined(VERTICAL_CENTER_EDGE) && defined(HEIGHT_EDGE))
        {
            return sum(getVerticalCenterSpring(), scale(getHeightSpring(), 0.5f));
        }
        else if(defined(VERTICAL_CENTER_EDGE) && defined(NORTH_EDGE))
        {
            return sum(scale(getVerticalCenterSpring(), 2.0f), getNorthSpring());
        }
        else if(defined(BASELINE_EDGE) && defined(HEIGHT_EDGE))
        {
            return sum(getBaselineSpring(), heightToRelativeBaseline(getHeightSpring()));
        }
        else if(defined(BASELINE_EDGE) && defined(NORTH_EDGE))
        {
            return scale(sum(getBaselineSpring(), heightToRelativeBaseline(getNorthSpring())), 2.0f);
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getSouthSpring();
    }
}

void SpringLayoutConstraints::setWest(LayoutSpringPtr west)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), WestSpringFieldMask);
        setWestSpring(west);
    endEditCP(SpringLayoutConstraintsPtr(this), WestSpringFieldMask);
    
    pushToHistory(WEST_EDGE, west, true);
}

LayoutSpringPtr SpringLayoutConstraints::getWest(void)
{
    if(getWestSpring() == NullFC)
    {
        if(defined(EAST_EDGE) && defined(WIDTH_EDGE))
        {
            return difference(getEastSpring(), getWidthSpring());
        }
        else if(defined(HORIZONTAL_CENTER_EDGE) && defined(WIDTH_EDGE))
        {
            return difference(getHorizontalCenterSpring(), scale(getWidthSpring(), 0.5f));
        }
        else if(defined(HORIZONTAL_CENTER_EDGE) && defined(EAST_EDGE))
        {
            return difference(scale(getHorizontalCenterSpring(), 2.0f), getEastSpring());
        }
        else
        {
            return NullFC;
        }
    }
    else
    {
        return getWestSpring();
    }
}

void SpringLayoutConstraints::setHorizontalCenter(LayoutSpringPtr horizontalCenter)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), HorizontalCenterSpringFieldMask);
        setHorizontalCenterSpring(horizontalCenter);
    endEditCP(SpringLayoutConstraintsPtr(this), HorizontalCenterSpringFieldMask);
    
    pushToHistory(HORIZONTAL_CENTER_EDGE, horizontalCenter, true);
}

LayoutSpringPtr SpringLayoutConstraints::getHorizontalCenter(void)
{
    if(getHorizontalCenterSpring() == NullFC)
    {
        return sum(getWest(), scale(getWidth(), 0.5f));
    }
    else
    {
        return getHorizontalCenterSpring();
    }
}

void SpringLayoutConstraints::setVerticalCenter(LayoutSpringPtr verticalCenter)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), VerticalCenterSpringFieldMask);
        setVerticalCenterSpring(verticalCenter);
    endEditCP(SpringLayoutConstraintsPtr(this), VerticalCenterSpringFieldMask);
    
    pushToHistory(VERTICAL_CENTER_EDGE, verticalCenter, false);
}

LayoutSpringPtr SpringLayoutConstraints::getVerticalCenter(void)
{
    if(getVerticalCenterSpring() == NullFC)
    {
        return sum(getNorth(), scale(getHeight(), 0.5f));
    }
    else
    {
        return getVerticalCenterSpring();
    }
}

void SpringLayoutConstraints::setBaseline(LayoutSpringPtr baseline)
{
    beginEditCP(SpringLayoutConstraintsPtr(this), BaselineSpringFieldMask);
        setBaselineSpring(baseline);
    endEditCP(SpringLayoutConstraintsPtr(this), BaselineSpringFieldMask);
    
    pushToHistory(BASELINE_EDGE, baseline, false);
}

LayoutSpringPtr SpringLayoutConstraints::getBaseline(void)
{
    if(getBaselineSpring() == NullFC)
    {
        return sum(getNorth(), heightToRelativeBaseline(getHeight()));
    }
    else
    {
        return getBaselineSpring();
    }
}

void SpringLayoutConstraints::setConstraint(UInt32 Edge, LayoutSpringPtr s)
{
    switch(Edge)
    {
    case NORTH_EDGE:
    case Y_EDGE:
        setNorth(s);
        break;
    case EAST_EDGE:
        setEast(s);
        break;
    case SOUTH_EDGE:
        setSouth(s);
        break;
    case WEST_EDGE:
    case X_EDGE:
        setWest(s);
        break;
    case HORIZONTAL_CENTER_EDGE:
        setHorizontalCenter(s);
        break;
    case VERTICAL_CENTER_EDGE:
        setVerticalCenter(s);
        break;
    case BASELINE_EDGE:
        setBaseline(s);
        break;
    case WIDTH_EDGE:
        setWidth(s);
        break;
    case HEIGHT_EDGE:
        setHeight(s);
        break;
    default:
        return;
    }
}

void SpringLayoutConstraints::reset(void)
{
    if(getNorthSpring() != NullFC)
    {
        getNorthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getSouthSpring() != NullFC)
    {
        getSouthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getEastSpring() != NullFC)
    {
        getEastSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getWestSpring() != NullFC)
    {
        getWestSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getWidthSpring() != NullFC)
    {
        getWidthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getHeightSpring() != NullFC)
    {
        getHeightSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getHorizontalCenterSpring() != NullFC)
    {
        getHorizontalCenterSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getVerticalCenterSpring() != NullFC)
    {
        getVerticalCenterSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getBaselineSpring() != NullFC)
    {
        getBaselineSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
}

LayoutSpringPtr SpringLayoutConstraints::getConstraint(UInt32 TheEdge)
{
    switch(TheEdge)
    {
    case NORTH_EDGE:
    case Y_EDGE:
        return getNorth();
        break;
    case EAST_EDGE:
        return getEast();
        break;
    case SOUTH_EDGE:
        return getSouth();
        break;
    case WEST_EDGE:
    case X_EDGE:
        return getWest();
        break;
    case HORIZONTAL_CENTER_EDGE:
        return getHorizontalCenter();
        break;
    case VERTICAL_CENTER_EDGE:
        return getVerticalCenter();
        break;
    case BASELINE_EDGE:
        return getBaseline();
        break;
    case WIDTH_EDGE:
        return getWidth();
        break;
    case HEIGHT_EDGE:
        return getHeight();
        break;
    default:
        return NullFC;
    }
}

LayoutSpringPtr SpringLayoutConstraints::sum(LayoutSpringPtr s1, LayoutSpringPtr s2)
{
    return LayoutSpring::sum(s1,s2);
}

LayoutSpringPtr SpringLayoutConstraints::difference(LayoutSpringPtr s1, LayoutSpringPtr s2)
{
    return LayoutSpring::difference(s1,s2);
}

LayoutSpringPtr SpringLayoutConstraints::scale(LayoutSpringPtr s, Real32 factor)
{
    return LayoutSpring::scale(s,factor);
}

Int32 SpringLayoutConstraints::getBaselineFromHeight(const Int32& height) const
{
    return getComponent()->getBaseline(getComponent()->getPreferredSize().x(), height);
}

Int32 SpringLayoutConstraints::getHeightFromBaseLine(const Int32& baseline) const
{
    //TODO: Implement
    return 0;
}

LayoutSpringPtr SpringLayoutConstraints::heightToRelativeBaseline(LayoutSpringPtr s)
{
    //TODO: Implement
    return NullFC;
}

LayoutSpringPtr SpringLayoutConstraints::relativeBaselineToHeight(LayoutSpringPtr s)
{
    //TODO: Implement
    return NullFC;
}

bool SpringLayoutConstraints::defined(const UInt32 Edge) const
{
    switch(Edge)
    {
    case NORTH_EDGE:
    case Y_EDGE:
        return getNorthSpring() != NullFC;
        break;
    case EAST_EDGE:
        return getEastSpring() != NullFC;
        break;
    case SOUTH_EDGE:
        return getSouthSpring() != NullFC;
        break;
    case WEST_EDGE:
    case X_EDGE:
        return getWestSpring() != NullFC;
        break;
    case HORIZONTAL_CENTER_EDGE:
        return getHorizontalCenterSpring() != NullFC;
        break;
    case VERTICAL_CENTER_EDGE:
        return getVerticalCenterSpring() != NullFC;
        break;
    case BASELINE_EDGE:
        return getBaselineSpring() != NullFC;
        break;
    case WIDTH_EDGE:
        return getWidthSpring() != NullFC;
        break;
    case HEIGHT_EDGE:
        return getHeightSpring() != NullFC;
        break;
    default:
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SpringLayoutConstraints::SpringLayoutConstraints(void) :
    Inherited()
{
}

SpringLayoutConstraints::SpringLayoutConstraints(const SpringLayoutConstraints &source) :
    Inherited(source)
{
}

SpringLayoutConstraints::~SpringLayoutConstraints(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpringLayoutConstraints::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SpringLayoutConstraints::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SpringLayoutConstraints NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSPRINGLAYOUTCONSTRAINTSBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPRINGLAYOUTCONSTRAINTSBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPRINGLAYOUTCONSTRAINTSFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

