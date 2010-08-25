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

#include "OSGTreeSelectionEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeSelectionEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeSelectionEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeSelectionEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

TreeSelectionEventDetailsTransitPtr TreeSelectionEventDetails::create(  FieldContainer* const Source,
                                                          Time TimeStamp,
                                                          const std::vector<NumberRange>& ElementsChanged,
                                                          Int32 NewLeadSelectionPath,
                                                          Int32 OldLeadSelectionPath)
{
    TreeSelectionEventDetails* TheEventDetails = TreeSelectionEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setNewLeadSelectionPath(NewLeadSelectionPath);
    TheEventDetails->setOldLeadSelectionPath(OldLeadSelectionPath);
    TheEventDetails->editMFElementsChanged()->resize(ElementsChanged.size());
    for(UInt32 i(0) ; i<ElementsChanged.size() ; ++i)
    {
        (*TheEventDetails->editMFElementsChanged())[i] = Vec2s(ElementsChanged[i].getMin(), ElementsChanged[i].getMax());
    }

    return TreeSelectionEventDetailsTransitPtr(TheEventDetails);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeSelectionEventDetails::TreeSelectionEventDetails(void) :
    Inherited()
{
}

TreeSelectionEventDetails::TreeSelectionEventDetails(const TreeSelectionEventDetails &source) :
    Inherited(source)
{
}

TreeSelectionEventDetails::~TreeSelectionEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeSelectionEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeSelectionEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeSelectionEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
