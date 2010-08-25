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

#include "OSGSpringLayoutConstraints.h"
#include "OSGLayoutSpring.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSpringLayoutConstraintsBase.cpp file.
// To modify it, please change the .fcd file (OSGSpringLayoutConstraints.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpringLayoutConstraints::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


SpringLayoutConstraintsTransitPtr SpringLayoutConstraints::create(LayoutSpringRefPtr XSpring, LayoutSpringRefPtr YSpring)
{
    SpringLayoutConstraints* NewConstraints = createEmpty();

    NewConstraints->setWestSpring(XSpring);
    NewConstraints->setNorthSpring(YSpring);

    return SpringLayoutConstraintsTransitPtr(NewConstraints);
}

SpringLayoutConstraintsTransitPtr SpringLayoutConstraints::create(LayoutSpringRefPtr XSpring, LayoutSpringRefPtr YSpring, LayoutSpringRefPtr WidthSpring, LayoutSpringRefPtr HeightSpring)
{
    SpringLayoutConstraints* NewConstraints = createEmpty();

    NewConstraints->setWestSpring(XSpring);
    NewConstraints->setNorthSpring(YSpring);
    NewConstraints->setWidthSpring(WidthSpring);
    NewConstraints->setHeightSpring(HeightSpring);

    return SpringLayoutConstraintsTransitPtr(NewConstraints);
}

SpringLayoutConstraintsTransitPtr SpringLayoutConstraints::create(Component* const TheComponent)
{
    SpringLayoutConstraints* NewConstraints = createEmpty();

    NewConstraints->setWestSpring(LayoutSpring::constant(TheComponent->getPosition().x()));
    NewConstraints->setNorthSpring(LayoutSpring::constant(TheComponent->getPosition().y()));
    NewConstraints->setWidthSpring(LayoutSpring::width(TheComponent));
    NewConstraints->setHeightSpring(LayoutSpring::height(TheComponent));
    NewConstraints->setComponent(TheComponent);

    return SpringLayoutConstraintsTransitPtr(NewConstraints);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpringLayoutConstraints::setX(LayoutSpringRefPtr x)
{
    setWest(x);
}

LayoutSpringRefPtr SpringLayoutConstraints::getX(void)
{
    return getWest();
}

void SpringLayoutConstraints::setY(LayoutSpringRefPtr y)
{
    setNorth(y);
}
LayoutSpringRefPtr SpringLayoutConstraints::getY(void)
{
    return getNorth();
}

void SpringLayoutConstraints::setWidth(LayoutSpringRefPtr width)
{
    setWidthSpring(width);

    pushToHistory(WIDTH_EDGE, width, true);
}

LayoutSpringRefPtr SpringLayoutConstraints::getWidth(void)
{
    if(getWidthSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getWidthSpring();
    }
}

void SpringLayoutConstraints::setHeight(LayoutSpringRefPtr height)
{
    setHeightSpring(height);

    pushToHistory(HEIGHT_EDGE, height, false);
}

LayoutSpringRefPtr SpringLayoutConstraints::getHeight(void)
{
    if(getHeightSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getHeightSpring();
    }
}

void SpringLayoutConstraints::setNorth(LayoutSpringRefPtr north)
{
    setNorthSpring(north);

    pushToHistory(NORTH_EDGE, north, false);
}

LayoutSpringRefPtr SpringLayoutConstraints::getNorth(void)
{
    if(getNorthSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getNorthSpring();
    }
}

void SpringLayoutConstraints::setEast(LayoutSpringRefPtr east)
{
    setEastSpring(east);

    pushToHistory(EAST_EDGE, east, true);
}

LayoutSpringRefPtr SpringLayoutConstraints::getEast(void)
{
    if(getEastSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getEastSpring();
    }
}

void SpringLayoutConstraints::pushToHistory(Edge TheEdge, LayoutSpringRefPtr Value, bool isHorizontal)
{
    std::deque<Edge>& History(isHorizontal ? _HorizontalHistory : _VerticalHistory);
    bool valid(true);

    std::deque<Edge>::iterator SearchItor(std::find(History.begin(), History.end(), TheEdge));
    if (SearchItor != History.end())
    {
        History.erase(SearchItor);
        valid = false;
    }
    else if (History.size() == 2 && Value != NULL)
    {
        History.pop_front();
        valid = false;
    }
    if (Value != NULL)
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
                setConstraint(All[i], NULL);
            }
        }
    }
}

void SpringLayoutConstraints::setSouth(LayoutSpringRefPtr south)
{
    setSouthSpring(south);

    pushToHistory(SOUTH_EDGE, south, false);
}
LayoutSpringRefPtr SpringLayoutConstraints::getSouth(void)
{
    if(getSouthSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getSouthSpring();
    }
}

void SpringLayoutConstraints::setWest(LayoutSpringRefPtr west)
{
    setWestSpring(west);

    pushToHistory(WEST_EDGE, west, true);
}

LayoutSpringRefPtr SpringLayoutConstraints::getWest(void)
{
    if(getWestSpring() == NULL)
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
            return NULL;
        }
    }
    else
    {
        return getWestSpring();
    }
}

void SpringLayoutConstraints::setHorizontalCenter(LayoutSpringRefPtr horizontalCenter)
{
    setHorizontalCenterSpring(horizontalCenter);

    pushToHistory(HORIZONTAL_CENTER_EDGE, horizontalCenter, true);
}

LayoutSpringRefPtr SpringLayoutConstraints::getHorizontalCenter(void)
{
    if(getHorizontalCenterSpring() == NULL)
    {
        return sum(getWest(), scale(getWidth(), 0.5f));
    }
    else
    {
        return getHorizontalCenterSpring();
    }
}

void SpringLayoutConstraints::setVerticalCenter(LayoutSpringRefPtr verticalCenter)
{
    setVerticalCenterSpring(verticalCenter);

    pushToHistory(VERTICAL_CENTER_EDGE, verticalCenter, false);
}

LayoutSpringRefPtr SpringLayoutConstraints::getVerticalCenter(void)
{
    if(getVerticalCenterSpring() == NULL)
    {
        return sum(getNorth(), scale(getHeight(), 0.5f));
    }
    else
    {
        return getVerticalCenterSpring();
    }
}

void SpringLayoutConstraints::setBaseline(LayoutSpringRefPtr baseline)
{
    setBaselineSpring(baseline);

    pushToHistory(BASELINE_EDGE, baseline, false);
}

LayoutSpringRefPtr SpringLayoutConstraints::getBaseline(void)
{
    if(getBaselineSpring() == NULL)
    {
        return sum(getNorth(), heightToRelativeBaseline(getHeight()));
    }
    else
    {
        return getBaselineSpring();
    }
}

void SpringLayoutConstraints::setConstraint(UInt32 Edge, LayoutSpringRefPtr s)
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
    if(getNorthSpring() != NULL)
    {
        getNorthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getSouthSpring() != NULL)
    {
        getSouthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getEastSpring() != NULL)
    {
        getEastSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getWestSpring() != NULL)
    {
        getWestSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getWidthSpring() != NULL)
    {
        getWidthSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getHeightSpring() != NULL)
    {
        getHeightSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getHorizontalCenterSpring() != NULL)
    {
        getHorizontalCenterSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getVerticalCenterSpring() != NULL)
    {
        getVerticalCenterSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
    if(getBaselineSpring() != NULL)
    {
        getBaselineSpring()->setValue(LayoutSpring::VALUE_NOT_SET);
    }
}

LayoutSpringRefPtr SpringLayoutConstraints::getConstraint(UInt32 TheEdge)
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
            return NULL;
    }
}

LayoutSpringRefPtr SpringLayoutConstraints::sum(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2)
{
    return LayoutSpring::sum(s1,s2);
}

LayoutSpringRefPtr SpringLayoutConstraints::difference(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2)
{
    return LayoutSpring::difference(s1,s2);
}

LayoutSpringRefPtr SpringLayoutConstraints::scale(LayoutSpringRefPtr s, Real32 factor)
{
    return LayoutSpring::scale(s,factor);
}

Real32 SpringLayoutConstraints::getBaselineFromHeight(const Real32& height) const
{
    return getComponent()->getBaseline(getComponent()->getPreferredSize().x(), height);
}

Real32 SpringLayoutConstraints::getHeightFromBaseLine(const Real32& baseline) const
{
    //TODO: Implement
    return 0;
}

LayoutSpringRefPtr SpringLayoutConstraints::heightToRelativeBaseline(LayoutSpringRefPtr s)
{
    //TODO: Implement
    return NULL;
}

LayoutSpringRefPtr SpringLayoutConstraints::relativeBaselineToHeight(LayoutSpringRefPtr s)
{
    //TODO: Implement
    return NULL;
}

bool SpringLayoutConstraints::defined(const UInt32 Edge) const
{
    switch(Edge)
    {
        case NORTH_EDGE:
        case Y_EDGE:
            return getNorthSpring() != NULL;
            break;
        case EAST_EDGE:
            return getEastSpring() != NULL;
            break;
        case SOUTH_EDGE:
            return getSouthSpring() != NULL;
            break;
        case WEST_EDGE:
        case X_EDGE:
            return getWestSpring() != NULL;
            break;
        case HORIZONTAL_CENTER_EDGE:
            return getHorizontalCenterSpring() != NULL;
            break;
        case VERTICAL_CENTER_EDGE:
            return getVerticalCenterSpring() != NULL;
            break;
        case BASELINE_EDGE:
            return getBaselineSpring() != NULL;
            break;
        case WIDTH_EDGE:
            return getWidthSpring() != NULL;
            break;
        case HEIGHT_EDGE:
            return getHeightSpring() != NULL;
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

void SpringLayoutConstraints::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SpringLayoutConstraints::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SpringLayoutConstraints NI" << std::endl;
}

OSG_END_NAMESPACE
