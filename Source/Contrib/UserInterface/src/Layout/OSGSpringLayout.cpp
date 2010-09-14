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

#include "OSGSpringLayout.h"
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "OSGComponentContainer.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGComponentContainer.h"

#include "OSGComponentWidthLayoutSpring.h"
#include "OSGComponentHeightLayoutSpring.h"
#include "OSGProxyLayoutSpring.h"
#include "OSGLayoutSpring.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSpringLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGSpringLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SpringLayout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


bool SpringLayout::xmlReadHandler (rapidxml::xml_node<char>& SpringLayoutRoot, const XMLFCFileType::IDLookupMap& TheLookupMap, const FieldContainerRefPtr& SpringLayoutFC)
{
	rapidxml::xml_attribute<char> *curAttribute;

	Component* Component1RefPtr;
    Component* Component2RefPtr;
	LayoutSpringRefPtr LayoutSpring1RefPtr;
	XMLFCFileType::IDLookupMap::const_iterator IDItor;

	std::string curNodeName;
	std::string Edge1, Edge2, Component1, Component2, PadOrLayoutSpring;

	for(rapidxml::node_iterator<char> NodeListItor(&SpringLayoutRoot); NodeListItor!=rapidxml::node_iterator<char>() ; ++NodeListItor)
	{
		curNodeName = std::string(NodeListItor->name()).substr(0,NodeListItor->name_size());

		curAttribute = NodeListItor->first_attribute("edge1",0,false);
		if(curAttribute == NULL)
		{
			throw XMLFCFileType::XMLFCException("Couldn't find Edge1 attribute for Spring Layout Constraint!",*NodeListItor);
		}
		Edge1 = std::string(curAttribute->value()).substr(0,curAttribute->value_size());

		curAttribute = NodeListItor->first_attribute("component1",0,false);
		if(curAttribute == NULL)
		{
			throw XMLFCFileType::XMLFCException("Couldn't find Component1 attribute for Spring Layout Constraint!",*NodeListItor);
		}
		Component1 = std::string(curAttribute->value()).substr(0,curAttribute->value_size());
		IDItor = TheLookupMap.find(boost::lexical_cast<UInt32>(Component1));
		if(IDItor == TheLookupMap.end())
		{
			throw XMLFCFileType::XMLFCException("No matching container found for ID " + Component1,*NodeListItor);
		}
		Component1RefPtr = dynamic_pointer_cast<Component>(IDItor->second._Ptr);

		if(curNodeName == "PadEdgeConstraint" || curNodeName == "SpringEdgeConstraint")
		{
			curAttribute = NodeListItor->first_attribute("edge2",0,false);
			if(curAttribute == NULL)
			{
				throw XMLFCFileType::XMLFCException("Couldn't find Edge2 attribute for Spring Layout Constraint!",*NodeListItor);
			}
			Edge2 = std::string(curAttribute->value()).substr(0,curAttribute->value_size());

			curAttribute = NodeListItor->first_attribute("component2",0,false);
			if(curAttribute == NULL)
			{
				throw XMLFCFileType::XMLFCException("Couldn't find Component2 attribute for Spring Layout Constraint!",*NodeListItor);
			}
			Component2 = std::string(curAttribute->value()).substr(0,curAttribute->value_size());
			IDItor = TheLookupMap.find(boost::lexical_cast<UInt32>(Component2));
			if(IDItor == TheLookupMap.end())
			{
				throw XMLFCFileType::XMLFCException("No matching container found for ID " + Component2,*NodeListItor);
			}
			Component2RefPtr = dynamic_pointer_cast<Component>(IDItor->second._Ptr);
		}
		
		if(curNodeName == "PadEdgeConstraint")
		{
			//In this case, PadOrLayoutSpring would be Pad
			curAttribute = NodeListItor->first_attribute("pad",0,false);
			if(curAttribute == NULL)
			{
				throw XMLFCFileType::XMLFCException("Couldn't find Pad attribute for Spring Layout Constraint!",*NodeListItor);
			}
			PadOrLayoutSpring = std::string(curAttribute->value()).substr(0,curAttribute->value_size());
			dynamic_pointer_cast<SpringLayout>(SpringLayoutFC)->putConstraint(boost::lexical_cast<UInt32>(Edge1),Component1RefPtr,boost::lexical_cast<Real32>(PadOrLayoutSpring),boost::lexical_cast<UInt32>(Edge2),Component2RefPtr);
		}
		else
		{
			curAttribute = NodeListItor->first_attribute("layoutspring",0,false);
			if(curAttribute == NULL)
			{
				throw XMLFCFileType::XMLFCException("Couldn't find LayoutSpring attribute for Spring Layout Constraint!",*NodeListItor);
			}
			PadOrLayoutSpring = std::string(curAttribute->value()).substr(0,curAttribute->value_size());
			
			IDItor = TheLookupMap.find(boost::lexical_cast<UInt32>(PadOrLayoutSpring));
			if(IDItor == TheLookupMap.end())
			{
				throw XMLFCFileType::XMLFCException("No matching container found for ID " + PadOrLayoutSpring,*NodeListItor);
			}
			LayoutSpring1RefPtr = dynamic_pointer_cast<LayoutSpring>(IDItor->second._Ptr);
			 
			if(curNodeName == "SpringEdgeConstraint")
				dynamic_pointer_cast<SpringLayout>(SpringLayoutFC)->putConstraint(boost::lexical_cast<UInt32>(Edge1),Component1RefPtr,LayoutSpring1RefPtr,boost::lexical_cast<UInt32>(Edge2),Component2RefPtr);
			else if(curNodeName == "SpringConstraint")
				dynamic_pointer_cast<SpringLayout>(SpringLayoutFC)->putConstraint(boost::lexical_cast<UInt32>(Edge1),Component1RefPtr,LayoutSpring1RefPtr);
			else
			{
				throw XMLFCFileType::XMLFCException("No SpringLayoutConstraint named " + curNodeName,*NodeListItor);
				continue;
			}
		}		
	}
}

bool SpringLayout::xmlWriteHandler (const FieldContainerRefPtr& SpringLayoutFC)
{
    //TODO: Implement
	return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SpringLayout::updateLayout(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
	Pnt2f ParentInsetsTopLeft, ParentInsetsBottomRight;
	dynamic_cast<const ComponentContainer*>(ParentComponent)->getInsideInsetsBounds(ParentInsetsTopLeft, ParentInsetsBottomRight);
    
    const_cast<SpringLayout*>(this)->setParent(const_cast<ComponentContainer*>(dynamic_cast<const
                                                                         ComponentContainer*>(ParentComponent)));
    
    SpringLayoutConstraintsRefPtr MyBoundsConstraints =
        getConstraint(const_cast<Component*>(ParentComponent));
    
    getDecycledSpring(MyBoundsConstraints->getX())->setValue(ParentInsetsTopLeft.x());
    getDecycledSpring(MyBoundsConstraints->getY())->setValue(ParentInsetsTopLeft.y());
    getDecycledSpring(MyBoundsConstraints->getWidth())->setValue( ParentInsetsBottomRight.x() - ParentInsetsTopLeft.x() );
    getDecycledSpring(MyBoundsConstraints->getHeight())->setValue( ParentInsetsBottomRight.y() - ParentInsetsTopLeft.y() );
    
    for (UInt32 i(0) ; i < Components->size() ; i++)
    {
        SpringLayoutConstraintsRefPtr TheConstraints = getConstraint( (*Components)[i] );
        Real32 x = getDecycledSpring(TheConstraints->getX())->getValue();
        Real32 y = getDecycledSpring(TheConstraints->getY())->getValue();
        Real32 width = getDecycledSpring(TheConstraints->getWidth())->getValue();
        Real32 height = getDecycledSpring(TheConstraints->getHeight())->getValue();
        
        if((*Components)[i]->getPosition().x() != x ||
           (*Components)[i]->getPosition().y() != y)
        {
            (*Components)[i]->setPosition(Pnt2f(x,y));
        }
        if((*Components)[i]->getSize().x() != width ||
           (*Components)[i]->getSize().y() != height)
        {
            (*Components)[i]->setSize(Vec2f(width, height));
        }
     }
}

void SpringLayout::clearConstraints(void)
{
    editConstraints().clear();
}

Vec2f SpringLayout::minimumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    /*SpringLayoutConstraintsRefPtr TheConstraints = getConstraint( ParentComponent );
    Real32 width = getDecycledSpring(TheConstraints->getWidth())->getMinimumValue();
    Real32 height = getDecycledSpring(TheConstraints->getHeight())->getMinimumValue();

    return Vec2f(width, height);*/
    return ParentComponent->getMinSize();
}

Vec2f SpringLayout::requestedContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    /*SpringLayoutConstraintsRefPtr TheConstraints = getConstraint( ParentComponent );
    Real32 width = getDecycledSpring(TheConstraints->getWidth())->getPreferredValue();
    Real32 height = getDecycledSpring(TheConstraints->getHeight())->getPreferredValue();

    return Vec2f(width, height);*/
    return ParentComponent->getPreferredSize();
}

Vec2f SpringLayout::preferredContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    /*SpringLayoutConstraintsRefPtr TheConstraints = getConstraint( ParentComponent );
    Real32 width = getDecycledSpring(TheConstraints->getWidth())->getPreferredValue();
    Real32 height = getDecycledSpring(TheConstraints->getHeight())->getPreferredValue();

    return Vec2f(width, height);*/
    return ParentComponent->getPreferredSize();
}

Vec2f SpringLayout::maximumContentsLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    /*SpringLayoutConstraintsRefPtr TheConstraints = getConstraint( ParentComponent );
    Real32 width = getDecycledSpring(TheConstraints->getWidth())->getMaximumValue();
    Real32 height = getDecycledSpring(TheConstraints->getHeight())->getMaximumValue();

    return Vec2f(width, height);*/
    return ParentComponent->getMaxSize();
}

bool SpringLayout::isCyclic(const LayoutSpring* TheSpring) const
{
    if(TheSpring == NULL)
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
    bool Result = TheSpring->isCyclic(this);
    if (!Result) {
        _AcyclicSprings.insert(TheSpring);
        _CyclicSprings.erase(TheSpring);
    }
    else {
        SWARNING << "A " << TheSpring->getTypeName() << " is cyclic. " << std::endl;
    }
    return Result;
}

SpringLayoutConstraintsRefPtr SpringLayout::getConstraint(Component* const TheComponent) const
{
    FieldContainerMap::const_iterator
        SearchItor(getConstraints().find(static_cast<FieldContainerMap::key_type>(TheComponent->getId())));

    if(SearchItor == getConstraints().end())
    {
        SpringLayoutConstraintsUnrecPtr TempConstraints(SpringLayoutConstraintsBase::create());

        SpringLayoutConstraintsRefPtr NewConstraints = applyDefaults(TheComponent, TempConstraints);

        const_cast<SpringLayout*>(this)->editConstraints()[static_cast<FieldContainerMap::key_type>(TheComponent->getId())] = NewConstraints;

        return NewConstraints;
    }
    else
    {
        return dynamic_pointer_cast<SpringLayoutConstraints>((*SearchItor).second);
    }
}

LayoutSpringRefPtr SpringLayout::getConstraint(const UInt32 Edge, Component* const TheComponent) const
{
    ProxyLayoutSpringUnrecPtr ConstPtr(ProxyLayoutSpring::create(Edge,
                                                                 TheComponent,
                                                                 const_cast<SpringLayout*>(this)));
    return ConstPtr;
}

void SpringLayout::putConstraint(const UInt32 e1, Component* const c1, const Real32& pad, const UInt32 e2, Component* const c2)
{
    putConstraint(e1, c1, LayoutSpring::constant(pad), e2, c2);
}

void SpringLayout::putConstraint(const UInt32 e1, Component* const c1, LayoutSpringRefPtr s, const UInt32 e2, Component* const c2)
{
    putConstraint(e1, c1, LayoutSpring::sum(s, getConstraint(e2, c2)));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SpringLayout::putConstraint(const UInt32 e, Component* const c, LayoutSpringRefPtr s)
{
    if(s != NULL)
    {
        getConstraint(c)->setConstraint(e,s);
    }
}

LayoutSpringRefPtr SpringLayout::getDecycledSpring(LayoutSpringRefPtr s) const
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

void SpringLayout::setParent(ComponentContainerRefPtr p)
{
    resetCyclicStatuses();

    SpringLayoutConstraintsRefPtr constraints = getConstraint(p);

    constraints->setWest(LayoutSpring::constant(0));
    constraints->setNorth(LayoutSpring::constant(0));

    LayoutSpringRefPtr Width = constraints->getWidth();
    if(Width->getType() == ComponentWidthLayoutSpring::getClassType() &&
        dynamic_pointer_cast<ComponentWidthLayoutSpring>(Width)->getComponent() == p)
    {
        constraints->setWidth(LayoutSpring::constant(0,0,TypeTraits<Real32>::getMax()));
    }
    
    LayoutSpringRefPtr Height = constraints->getHeight();
    if(Height->getType() == ComponentHeightLayoutSpring::getClassType() &&
        dynamic_pointer_cast<ComponentHeightLayoutSpring>(Height)->getComponent() == p)
    {
        constraints->setHeight(LayoutSpring::constant(0,0,TypeTraits<Real32>::getMax()));
    }
}

SpringLayoutConstraintsRefPtr SpringLayout::applyDefaults(Component* const c, SpringLayoutConstraintsRefPtr constraints)
{
    if(constraints == NULL)
    {
        constraints = SpringLayoutConstraintsBase::create();
    }

    if(constraints->getComponent() == NULL)
    {
            constraints->setComponent(c);
    }

    if( constraints->getHorizontalHistory().size() == 0)
    {
        constraints->setWest(LayoutSpring::constant(0));
        constraints->setWidth(LayoutSpring::width(c));
    }
    else if( constraints->getHorizontalHistory().size() == 1)
    {
        if(constraints->getWidthSpring() == NULL)
        {
            constraints->setWidth(LayoutSpring::width(c));
        }
        else
        {
            constraints->setWest(LayoutSpring::constant(0));
        }
    }
    
    if(constraints->getVerticalHistory().size() == 0)
    {
        constraints->setNorth(LayoutSpring::constant(0));
        constraints->setHeight(LayoutSpring::height(c));
    }
    else if( constraints->getVerticalHistory().size() == 1)
    {
        if(constraints->getHeightSpring() == NULL)
        {
            constraints->setHeight(LayoutSpring::height(c));
        }
        else
        {
            constraints->setNorth(LayoutSpring::constant(0));
        }
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

void SpringLayout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ConstraintsFieldMask)
    {
        updateParentContainers();
    }
}

void SpringLayout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SpringLayout NI" << std::endl;
}

OSG_END_NAMESPACE
