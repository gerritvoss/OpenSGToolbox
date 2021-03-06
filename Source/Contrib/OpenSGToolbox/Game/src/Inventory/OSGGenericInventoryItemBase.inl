/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class GenericInventoryItem!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GenericInventoryItemBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GenericInventoryItemBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
GenericInventoryItemPtr GenericInventoryItemBase::create(void) 
{
    GenericInventoryItemPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = GenericInventoryItemPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
GenericInventoryItemPtr GenericInventoryItemBase::createEmpty(void) 
{ 
    GenericInventoryItemPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the GenericInventoryItem::_sfDetails field.
inline
const SFString *GenericInventoryItemBase::getSFDetails(void) const
{
    return &_sfDetails;
}

//! Get the GenericInventoryItem::_sfDetails field.
inline
SFString *GenericInventoryItemBase::editSFDetails(void)
{
    return &_sfDetails;
}

#ifndef OSG_2_PREP
//! Get the GenericInventoryItem::_sfDetails field.
inline
SFString *GenericInventoryItemBase::getSFDetails(void)
{
    return &_sfDetails;
}
#endif


//! Get the value of the GenericInventoryItem::_sfDetails field.
inline
std::string &GenericInventoryItemBase::editDetails(void)
{
    return _sfDetails.getValue();
}

//! Get the value of the GenericInventoryItem::_sfDetails field.
inline
const std::string &GenericInventoryItemBase::getDetails(void) const
{
    return _sfDetails.getValue();
}

#ifndef OSG_2_PREP
//! Get the value of the GenericInventoryItem::_sfDetails field.
inline
std::string &GenericInventoryItemBase::getDetails(void)
{
    return _sfDetails.getValue();
}
#endif

//! Set the value of the GenericInventoryItem::_sfDetails field.
inline
void GenericInventoryItemBase::setDetails(const std::string &value)
{
    _sfDetails.setValue(value);
}


OSG_END_NAMESPACE

