/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGSegmentDistribution1D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SegmentDistribution1D
An SegmentDistribution1D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SegmentDistribution1D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 SegmentDistribution1D::generate(void) const
{
   return RandomPoolManager::getRandomReal32(getSegment()[0],getSegment()[1]);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SegmentDistribution1D::SegmentDistribution1D(void) :
    Inherited()
{
}

SegmentDistribution1D::SegmentDistribution1D(const SegmentDistribution1D &source) :
    Inherited(source)
{
}

SegmentDistribution1D::~SegmentDistribution1D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SegmentDistribution1D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SegmentDistribution1D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SegmentDistribution1D NI" << std::endl;
}

OSG_END_NAMESPACE

