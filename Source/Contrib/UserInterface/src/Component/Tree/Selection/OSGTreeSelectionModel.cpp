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

#include "OSGTreeSelectionModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeSelectionModelBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeSelectionModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeSelectionModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TreeSelectionModel::produceSelectionAdded(const std::vector<NumberRange>& ElementsAdded, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath)
{
    TreeSelectionEventDetailsUnrecPtr Details = TreeSelectionEventDetails::create(NULL, getSystemTime(), ElementsAdded, NewLeadSelectionPath, OldLeadSelectionPath);

    Inherited::produceSelectionAdded(Details);
}

void TreeSelectionModel::produceSelectionRemoved(const std::vector<NumberRange>& ElementsRemoved, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath)
{
    TreeSelectionEventDetailsUnrecPtr Details = TreeSelectionEventDetails::create(NULL, getSystemTime(), ElementsRemoved, NewLeadSelectionPath, OldLeadSelectionPath);

    Inherited::produceSelectionRemoved(Details);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeSelectionModel::TreeSelectionModel(void) :
    Inherited()
{
}

TreeSelectionModel::TreeSelectionModel(const TreeSelectionModel &source) :
    Inherited(source)
{
}

TreeSelectionModel::~TreeSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeSelectionModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeSelectionModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeSelectionModel NI" << std::endl;
}

OSG_END_NAMESPACE
