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

#include "OSGAbstractBranchElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractBranchElementBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractBranchElement.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractBranchElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


//   Returns the children of the receiver as an Enumeration.
//std::vector<std::string> AbstractBranchElement::children(void)
//{
//	//TODO:
//	std::vector<std::string> temp;
//	return temp;
//}

//   Returns true if the receiver allows children.
bool AbstractBranchElement::getAllowsChildren(void) const
{
	//TODO:
	return true;
}

//  Gets a child element.
ElementRefPtr	AbstractBranchElement::getElement(UInt32 index) const
{
	//REALLY NEED TO DO!!!:
	if(index < getElementCount())
		return getChildElements(index);
	else return NULL;
}

//  Gets the number of children for the element.
UInt32 AbstractBranchElement::getElementCount(void) const
{
	//REALLY NEED TO DO!!!:
	return getMFChildElements()->size();
}

//  Gets the child element index closest to the given model offset.
UInt32 AbstractBranchElement::getElementIndex(UInt32 offset) const
{
	//TODO:
	return 0;
}

//  Gets the ending offset in the model for the element.
UInt32 AbstractBranchElement::getEndOffset(void) const
{
	//TODO:
	return 0;
}

// Gets the element name.
std::string AbstractBranchElement::getName(void) const
{
	return "Abstract Branch Element";
}
 
// Gets the starting offset in the model for the element.
UInt32 AbstractBranchElement::getStartOffset(void) const
{
	//TODO:
	return 0;
}
 
// Checks whether the element is a leaf.
bool	AbstractBranchElement::isLeaf(void) const
{
	//TODO:
	return false;
}
 
//Gets the child element that contains the given model position.
ElementRefPtr AbstractBranchElement::positionToElement(UInt32 pos) const
{
	//TODO:
	return NULL;
}
  
//Replaces content with a new set of elements.
void AbstractBranchElement::replace(int offset, int length, MFRecElementPtr elems)
{
	//TODO:
	return;
}
  
//Converts the element to a string.
std::string AbstractBranchElement::toString(void) const
{
	//TODO:
	return "Abstract Branch Element";	
}
      
void AbstractBranchElement::removeChildElement(UInt32 index)
{
	MFUnrecElementPtr *temp = this->editMFChildElements();
	temp->erase(temp->begin() + index);
	//this->editMFChildElements().erase(this->getMFChildElements().begin() + index);
	commitChanges();
}

void AbstractBranchElement::addChildElement(UInt32 index,ElementRefPtr newPtr)
{
		MFUnrecElementPtr *temp = this->editMFChildElements();
		temp->insert(temp->begin()+index,newPtr);
		commitChanges();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractBranchElement::AbstractBranchElement(void) :
    Inherited()
{
}

AbstractBranchElement::AbstractBranchElement(const AbstractBranchElement &source) :
    Inherited(source)
{
}

AbstractBranchElement::~AbstractBranchElement(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractBranchElement::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractBranchElement::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractBranchElement NI" << std::endl;
}

OSG_END_NAMESPACE
