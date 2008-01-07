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

#include "OSGSpringLayout.h"
#include "Component/Container/OSGContainer.h"
#include "Layout/Spring/OSGLayoutSpring.h"
#include "Layout/OSGSpringLayoutConstraints.h"
#include "Component/Container/OSGContainer.h"

#include "Layout/Spring/OSGComponentWidthLayoutSpring.h"
#include "Layout/Spring/OSGComponentHeightLayoutSpring.h"
#include "Layout/Spring/OSGProxyLayoutSpring.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SpringLayout
A UI SpringLayout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpringLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpringLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	Pnt2s borderTopLeft, borderBottomRight;
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);

    //TODO: Implement
}

bool SpringLayout::isCyclic(LayoutSpringPtr TheSpring) const
{
    if(TheSpring == NullFC)
    {
        return false;
    }
    if(_CyclicSprings.find(TheSpring) != _CyclicSprings.end())
    {
        return true;
    }
    if(_AcyclicSprings.find(TheSpring) != _AcyclicSprings.end())
    {
        return false;
    }
    _CyclicSprings.insert(TheSpring);
    bool Result = TheSpring->isCyclic(SpringLayoutPtr(this));
    if (!Result) {
        _AcyclicSprings.insert(TheSpring);
        _CyclicSprings.erase(TheSpring);
    }
    else {
        SWARNING << "A " << TheSpring->getTypeName() << " is cyclic. " << std::endl;
    }
    return Result;
}

SpringLayoutConstraintsPtr SpringLayout::getConstraints(ComponentPtr TheComponent)
{
    FieldContainerMap::const_iterator SearchItor(Inherited::getConstraints().find(static_cast<FieldContainerMap::key_type>(TheComponent.getFieldContainerId())));

    if(SearchItor == Inherited::getConstraints().end())
    {
        SpringLayoutConstraintsPtr NewConstraints = applyDefaults(TheComponent, SpringLayoutConstraintsBase::create());

        beginEditCP(SpringLayoutPtr(this), ConstraintsFieldMask);
            Inherited::getConstraints()[static_cast<FieldContainerMap::key_type>(TheComponent.getFieldContainerId())] = NewConstraints;
        endEditCP(SpringLayoutPtr(this), ConstraintsFieldMask);

        return NewConstraints;
    }
    else
    {
        return SpringLayoutConstraints::Ptr::dcast((*SearchItor).second);
    }
}

LayoutSpringPtr SpringLayout::getConstraint(const UInt32 Edge, ComponentPtr TheComponent) const
{
    return ProxyLayoutSpring::create(Edge, TheComponent, SpringLayoutPtr(this));
}

void SpringLayout::putConstraint(const UInt32 e1, ComponentPtr c1, const UInt32& pad, const UInt32 e2, ComponentPtr c2)
{
    putConstraint(e1, c1, LayoutSpring::constant(pad), e2, c2);
}

void SpringLayout::putConstraint(const UInt32 e1, ComponentPtr c1, LayoutSpringPtr s, const UInt32 e2, ComponentPtr c2)
{
    putConstraint(e1, c1, LayoutSpring::sum(s, getConstraint(e2, c2)));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SpringLayout::putConstraint(const UInt32 e, ComponentPtr c, LayoutSpringPtr s)
{
    if(s != NullFC)
    {
        getConstraints(c)->setConstraint(e,s);
    }
}

LayoutSpringPtr SpringLayout::getDecycledSpring(LayoutSpringPtr s)
{
    if(isCyclic(s))
    {
        return _CyclicDummySpring;
    }
    else
    {
        return s;
    }
}

void SpringLayout::resetCyclicStatuses(void)
{
    _CyclicSprings.clear();
    _AcyclicSprings.clear();
}

void SpringLayout::setParent(ContainerPtr p)
{
    resetCyclicStatuses();

    SpringLayoutConstraintsPtr constraints = getConstraints(p);

    constraints->setWest(LayoutSpring::constant(0));
    constraints->setNorth(LayoutSpring::constant(0));

    LayoutSpringPtr Width = constraints->getWidth();
    if(Width->getType() == ComponentWidthLayoutSpring::getClassType() &&
        ComponentWidthLayoutSpring::Ptr::dcast(Width)->getComponent() == p)
    {
        constraints->setWidth(LayoutSpring::constant(0,0,TypeTraits<Int32>::getMax()));
    }
    
    LayoutSpringPtr Height = constraints->getHeight();
    if(Height->getType() == ComponentHeightLayoutSpring::getClassType() &&
        ComponentHeightLayoutSpring::Ptr::dcast(Height)->getComponent() == p)
    {
        constraints->setHeight(LayoutSpring::constant(0,0,TypeTraits<Int32>::getMax()));
    }
}

SpringLayoutConstraintsPtr SpringLayout::applyDefaults(ComponentPtr c, SpringLayoutConstraintsPtr& constraints)
{
    if(constraints == NullFC)
    {
        constraints = SpringLayoutConstraintsBase::create();
    }

    if(constraints->getComponent() == NullFC)
    {
        beginEditCP(constraints, SpringLayoutConstraints::ComponentFieldMask);
            constraints->setComponent(c);
        endEditCP(constraints, SpringLayoutConstraints::ComponentFieldMask);
    }

    if(constraints->isHorizontalDefined())
    {
        constraints->setWest(LayoutSpring::constant(0));
        constraints->setWidth(LayoutSpring::width(c));
    }
    
    if(constraints->isVerticalDefined())
    {
        constraints->setNorth(LayoutSpring::constant(0));
        constraints->setHeight(LayoutSpring::height(c));
    }

    return constraints;
}

/*----------------------- constructors & destructors ----------------------*/

SpringLayout::SpringLayout(void) :
    Inherited()
{
    _CyclicDummySpring = LayoutSpring::constant(LayoutSpring::VALUE_NOT_SET);
}

SpringLayout::SpringLayout(const SpringLayout &source) :
    Inherited(source)
{
    _CyclicDummySpring = LayoutSpring::constant(LayoutSpring::VALUE_NOT_SET);
}

SpringLayout::~SpringLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SpringLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SpringLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SpringLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSPRINGLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPRINGLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPRINGLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

