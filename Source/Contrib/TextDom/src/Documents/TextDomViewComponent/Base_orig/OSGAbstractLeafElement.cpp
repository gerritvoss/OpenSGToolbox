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

#include "OSGAbstractLeafElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractLeafElementBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractLeafElement.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractLeafElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


////Returns the children of the receiver as an Enumeration.
//std::vector<std::string> AbstractLeafElement::children() 
//{
//	//TODO:
//	std::vector<std::string> temp;
//	return temp;
//}

//Returns true if the receiver allows children.
bool AbstractLeafElement::getAllowsChildren()  const 
{
	//TODO:
	return true;
}

//Gets a child element.
ElementRefPtr 	AbstractLeafElement::getElement(UInt32 index) const
{
	//REALLY NEED TO DO!!!:
	return NULL;
}

//Returns the number of child elements.    
UInt32 AbstractLeafElement::getElementCount(void) const
{
	//REALLY NEED TO DO!!!:
	return 0;
}

//Gets the child element index closest to the given model offset.
UInt32 AbstractLeafElement::getElementIndex(UInt32 pos) const
{
	//TODO:
	return 0;
}
  
//Gets the ending offset in the model for the element.
UInt32 AbstractLeafElement::getEndOffset(void) const
{
	//TODO:
	return 0;
}
  
//Gets the element name.
std::string	AbstractLeafElement::getName(void) const
{
	return "Abstract Leaf Element";
}
  
//Gets the starting offset in the model for the element.
UInt32 AbstractLeafElement::getStartOffset(void) const
{
	//TODO:
	return 0;
}
  
//Checks whether the element is a leaf.
bool AbstractLeafElement::isLeaf(void) const
{
	//TODO:
	return false;
}
  
//Converts the element to a string.
std::string AbstractLeafElement::toString(void) const
{
	//TODO:
	return "";
}
  
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractLeafElement::AbstractLeafElement(void) :
    Inherited()
{
}

AbstractLeafElement::AbstractLeafElement(const AbstractLeafElement &source) :
    Inherited(source)
{
}

AbstractLeafElement::~AbstractLeafElement(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractLeafElement::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractLeafElement::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractLeafElement NI" << std::endl;
}

OSG_END_NAMESPACE
