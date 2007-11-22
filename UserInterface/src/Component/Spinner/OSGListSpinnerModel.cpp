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

#include "OSGListSpinnerModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ListSpinnerModel
A ListSpinnerModel.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ListSpinnerModel::setList(const FieldList& list)
{
    _List = list;
    _CurrentListValue = _List.begin();
    produceStateChanged();
}

SharedFieldPtr ListSpinnerModel::getNextValue(void)
{
    if(_CurrentListValue == (--_List.end()))
    {
        return SharedFieldPtr();
    }
    else
    {
        return (*_CurrentListValue);
    }
}

SharedFieldPtr ListSpinnerModel::getPreviousValue(void)
{
    if(_CurrentListValue == _List.begin())
    {
        return SharedFieldPtr();
    }
    else
    {
        return (*_CurrentListValue);
    }
}

SharedFieldPtr ListSpinnerModel::getValue(void)
{
    return (*_CurrentListValue);
}

void ListSpinnerModel::setValue(SharedFieldPtr value)
{
    FieldListIter SearchIter(std::find(_List.begin(), _List.end(), value));

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

void ListSpinnerModel::setValue(const std::string& value)
{
	FieldListIter SearchIter;
    for(SearchIter = _List.begin() ; SearchIter!=_List.end() ; ++SearchIter)
    {
        std::string FieldString;
        (*SearchIter)->getValueByStr(FieldString);
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

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

