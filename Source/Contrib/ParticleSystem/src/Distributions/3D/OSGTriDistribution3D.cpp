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

#include "OSGTriDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTriDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGTriDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TriDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f TriDistribution3D::generate(void) const
{
    Vec3f Result;

    switch(getSurfaceOrEdge())
    {
    case EDGE:
        {
            Vec3f Side1(getPoint2() - getPoint1()),
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
                Result = getPoint1().subZero() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side1;
            }
            else if(Rand < (Side1Length+Side2Length)/TotalLength)
            {
                Result = getPoint2().subZero() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side2;
            }
            else
            {
                Result = getPoint3().subZero() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side3;
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

            Result = getPoint1().subZero()
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

TriDistribution3D::TriDistribution3D(void) :
    Inherited()
{
}

TriDistribution3D::TriDistribution3D(const TriDistribution3D &source) :
    Inherited(source)
{
}

TriDistribution3D::~TriDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TriDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TriDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TriDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE
