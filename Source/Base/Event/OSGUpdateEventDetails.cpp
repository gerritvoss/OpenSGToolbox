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

#include "OSGUpdateEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUpdateEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGUpdateEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UpdateEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

UpdateEventDetailsTransitPtr UpdateEventDetails::create(FieldContainer* const Source,
                                                        Time TimeStamp,
                                                        Time ElapsedTime)
{
    UpdateEventDetails* TheEventDetails = UpdateEventDetails::createUnregistered();

    TheEventDetails->setSource     (Source     );
    TheEventDetails->setTimeStamp  (TimeStamp  );
    TheEventDetails->setElapsedTime(ElapsedTime);

    return UpdateEventDetailsTransitPtr(TheEventDetails);
}

UpdateEventDetailsTransitPtr UpdateEventDetails::create(UpdateEventDetails* const Details,
                                                        FieldContainer*     const NewSource)
{
    UpdateEventDetails* TheEventDetails = UpdateEventDetails::createUnregistered();

    TheEventDetails->setSource     (NewSource                );
    TheEventDetails->setTimeStamp  (Details->getTimeStamp()  );
    TheEventDetails->setElapsedTime(Details->getElapsedTime());

    return UpdateEventDetailsTransitPtr(TheEventDetails);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UpdateEventDetails::UpdateEventDetails(void) :
    Inherited()
{
}

UpdateEventDetails::UpdateEventDetails(const UpdateEventDetails &source) :
    Inherited(source)
{
}

UpdateEventDetails::~UpdateEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UpdateEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void UpdateEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UpdateEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
