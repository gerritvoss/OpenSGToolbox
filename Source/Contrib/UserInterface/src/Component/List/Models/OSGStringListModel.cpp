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

#include "OSGStringListModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStringListModelBase.cpp file.
// To modify it, please change the .fcd file (OSGStringListModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StringListModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 StringListModel::getSize(void) const
{
    return getMFItems()->size();
}

boost::any StringListModel::getElementAt(UInt32 index) const
{
    //Check for valid indexing
    if(index >= getMFItems()->size())
    {
        SWARNING << "Cannot get value of from index " << index << ", because the Items fields has size " << getMFItems()->size() << std::endl;
        return boost::any();
    }

    return boost::any(getItems(index));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StringListModel::StringListModel(void) :
    Inherited()
{
}

StringListModel::StringListModel(const StringListModel &source) :
    Inherited(source)
{
}

StringListModel::~StringListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StringListModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ItemsFieldMask)
    {
        produceListDataContentsChanged(this,0,getMFItems()->size());
    }
}

void StringListModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StringListModel NI" << std::endl;
}

OSG_END_NAMESPACE
