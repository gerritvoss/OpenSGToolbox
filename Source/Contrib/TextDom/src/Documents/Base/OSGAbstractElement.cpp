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

#include "OSGAbstractElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractElementBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractElement.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractElement::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


//    Adds an attribute to the element.
void AbstractElement::addAttribute(std::string name,UInt32 value)
{
	//TODO:
	return;
}

//    Adds a set of attributes to the element.
void AbstractElement::addAttributes(std::map<std::string,UInt32> &attr)
{
	//TODO:
	return;
}
  
//  Checks whether a given attribute name/value is defined.
bool AbstractElement::containsAttribute(std::string name, UInt32 value)  const
{
	//TODO:
	return false;
}

//  Checks whether the element contains all the attributes.
bool AbstractElement::containsAttributes(std::map<std::string,UInt32>& attrs) const
{
	//TODO:
	return false;
}
   
//   Copies a set of attributes.
std::map<std::string,UInt32> AbstractElement::copyAttributes() const
{
	//TODO:
	std::map<std::string,UInt32> temp;
	return temp;
}
   
//   Dumps a debugging representation of the element hierarchy.
void AbstractElement::dump(std::ostream &OutputStream, UInt32 indentAmount) const
{
	//TODO:
	return;
}
   
//   Gets the value of an attribute.
UInt32 	AbstractElement::getAttribute(std::string attrName) const
{
	//TODO:
	return -1;
}
   
//   Gets the number of attributes that are defined.
UInt32 AbstractElement::getAttributeCount(void) const
{
	//TODO:
	return 0;
}
   
//   Gets the names of all attributes.
std::vector<std::string>	AbstractElement::getAttributeNames() const
{
	//TODO:
	std::vector<std::string> temp;
	return temp;
}
   
//  Gets the attributes for the element.
std::map<std::string,UInt32>& AbstractElement::getAttributes() const
{
	//TODO:
	std::map<std::string,UInt32> temp;
	return temp;
}
   
//   Returns the child TreeNode at index childIndex.
Element* 	AbstractElement::getChildAt(UInt32 childIndex) const
{
	//REALLY NEED TO DO!!!
	return NULL;
}
   
//   Returns the number of children TreeNode's receiver contains.
UInt32	AbstractElement::getChildCount(void) const
{
	//REALLY NEED TO DO!!!
	return 0;
}
   
//  Retrieves the underlying model.
Document*	AbstractElement::getDocument(void) const
{
	//TODO:
	return NULL;
}
    
// Returns the index of node in the receivers children.
UInt32 AbstractElement::getIndex(Element* const node) const
{
	//REALLY NEED TO DO!!!
	//MFRecElementPtr::iterator temp = getChildElements().find(getChildElements().begin(),getChildElements().end(),node);
	return 0;
}
     
// Gets the name of the element.
std::string	AbstractElement::getName(void) const
{
	return "AbstractElement";
}

//Returns the parent TreeNode of the receiver.
Element* AbstractElement::getParent(void) const
{
	//TODO:
	return NULL;
}
      
//Gets the parent of the element.
Element* 	AbstractElement::getParentElement(void) const
{
	//TODO:
	return NULL;
}
      
// //Gets the resolving parent.
//std::map<std::string,UInt32>& AbstractElement::getResolveParent() const
//{
//	//TODO:
//	std::map<std::string,UInt32> temp;
//	return temp;
//}
      
//Checks whether a given attribute is defined.
bool AbstractElement::isDefined(std::string attrName) const
{
	//TODO:	
	return false;
}

//Checks whether two attribute sets are equal.
bool AbstractElement::isEqual(std::map<std::string,UInt32> attr) const
{
	//TODO:	
	return false;
}

//Removes an attribute from the set.
void AbstractElement::removeAttribute(std::string name)
{
	//TODO:
	return;
}
      
//Removes a set of attributes for the element.
void AbstractElement::removeAttributes(std::map<std::string,UInt32> attrs)
{
	//TODO:
	return;
}
      
//Removes a set of attributes for the element.
void AbstractElement::removeAttributes(std::vector<std::string> names)
{
	//TODO:
	return;
}
      
////Sets the resolving parent.
//void AbstractElement::setResolveParent(std::map<std::string,UInt32> parent)
//{
//	//TODO:
//	return;
//}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractElement::AbstractElement(void) :
    Inherited()
{
}

AbstractElement::AbstractElement(const AbstractElement &source) :
    Inherited(source)
{
}

AbstractElement::~AbstractElement(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractElement::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractElement::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractElement NI" << std::endl;
}

OSG_END_NAMESPACE
