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

#include "OSGTriDistribution2D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TriDistribution2D
An TriDistribution2D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TriDistribution2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
Vec2f TriDistribution2D::generate(void) const
{
    Vec2f Result;

    switch(getSurfaceOrEdge())
    {
    case EDGE:
        {
            Vec2f Side1(getPoint2() - getPoint1()),
                  Side2(getPoint3() - getPoint2()),
                  Side3(getPoint1() - getPoint3());

            Real32 Side1Length(Side1.length()),
                   Side2Length(Side2.length()),
                   Side3Length(Side3.length());

            Real32 TotalLength(Side1Length + Side2Length + Side3Length);

            Real32 Rand(RandomPoolManager::getRandomReal32(0.0,1.0));

            Real32 PickEdge(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(Rand < Side1Length/TotalLength)
            {
                Result = getPoint1() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side1;
            }
            else if(Rand < (Side1Length+Side2Length)/TotalLength)
            {
                Result = getPoint2() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side2;
            }
            else
            {
                Result = getPoint3() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side3;
            }
            break;
        }
    case SURFACE:
    default:
        {
            Real32 s(RandomPoolManager::getRandomReal32(0.0,1.0)),
                   t(RandomPoolManager::getRandomReal32(0.0,1.0));

            if(s+t > 1.0)
            {
                s = 1.0f - s;
                t = 1.0f - t;
            }

            Result = getPoint1()
                   + s*(getPoint2() - getPoint1())
                   + t*(getPoint3() - getPoint1());
            break;
        }
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TriDistribution2D::TriDistribution2D(void) :
    Inherited()
{
}

TriDistribution2D::TriDistribution2D(const TriDistribution2D &source) :
    Inherited(source)
{
}

TriDistribution2D::~TriDistribution2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TriDistribution2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TriDistribution2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TriDistribution2D NI" << std::endl;
}

OSG_END_NAMESPACE

