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

#include "OSGDocumentEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDocumentEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGDocumentEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DocumentEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


DocumentEventDetailsTransitPtr DocumentEventDetails::create(FieldContainer* const Source,
                                                  Time TimeStamp,
                                                  Document* const TheDocument,
                                                  Int32 Offset,
                                                  UInt32 Length)
{
    DocumentEventDetails* TheEventDetails = DocumentEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setDocument(TheDocument);
    TheEventDetails->setOffset(Offset);
    TheEventDetails->setLength(Length);

    return DocumentEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DocumentEventDetails::DocumentEventDetails(void) :
    Inherited()
{
}

DocumentEventDetails::DocumentEventDetails(const DocumentEventDetails &source) :
    Inherited(source)
{
}

DocumentEventDetails::~DocumentEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DocumentEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DocumentEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DocumentEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
