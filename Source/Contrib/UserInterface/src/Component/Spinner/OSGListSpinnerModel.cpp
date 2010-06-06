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

#include "OSGConfig.h"

#include "OSGListSpinnerModel.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ListSpinnerModel
A ListSpinnerModel.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

std::string ListSpinnerModel::getClassModelName(void)
{
	return std::string("List Spinner Model");
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


std::string ListSpinnerModel::getModelName(void) const
{
	return getClassModelName();
}

void ListSpinnerModel::setList(const AnyList& list)
{
    _List = list;
    _CurrentListValue = _List.begin();
    produceStateChanged();
}

boost::any ListSpinnerModel::getNextValue(void)
{
    if(_CurrentListValue == (--_List.end()))
    {
        return boost::any();
    }
    else
    {
        return (*_CurrentListValue);
    }
}

boost::any ListSpinnerModel::getPreviousValue(void)
{
    if(_CurrentListValue == _List.begin())
    {
        return boost::any();
    }
    else
    {
        return (*_CurrentListValue);
    }
}

boost::any ListSpinnerModel::getValue(void)
{
    return (*_CurrentListValue);
}

void ListSpinnerModel::setValue(const boost::any& value)
{
    assert(false);
}

void ListSpinnerModel::setValue(const std::string& value)
{
	AnyListIter SearchIter;
    for(SearchIter = _List.begin() ; SearchIter!=_List.end() ; ++SearchIter)
    {
        std::string FieldString;
        try
        {
            FieldString = lexical_cast(*SearchIter);
        }
        catch (boost::bad_lexical_cast &)
        {
            //Could not convert to string
        }
        if(FieldString.compare(value) == 0)
        {
            break;
        }
    }

    if(SearchIter != _List.end())
    {
        _CurrentListValue = SearchIter;
        produceStateChanged();
    }
    else
    {
        throw IllegalArgumentException();
    }

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/


OSG_END_NAMESPACE

