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

#include "OSGBoxDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBoxDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGBoxDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BoxDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f BoxDistribution3D::generate(void) const
{
    Vec3f Result;

    switch(getSurfaceOrVolume())
    {
    case SURFACE:
        {
            std::vector<Real32> Areas;
            Vec3f SideLengths(getMaxPoint() - getMinPoint());

            Areas.push_back(SideLengths.x() * SideLengths.y());                 //Min Z
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.y());  //Max Z
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.z());  //Min Y
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.z());  //Max Y
            Areas.push_back(Areas.back() + SideLengths.z() * SideLengths.y());  //Min X
            Areas.push_back(Areas.back() + SideLengths.z() * SideLengths.y());  //Max X

            Real32 PickSide(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(PickSide >= 0.0 && PickSide <Areas[0]/Areas.back())  //Min Z
            {
                Result = getMinPoint().subZero() +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               0.0);
            }
            else if(PickSide >= Areas[0]/Areas.back() && PickSide <Areas[1]/Areas.back())  //Max Z
            {
                Result = Vec3f(getMinPoint().x(), getMinPoint().y(),
                               getMaxPoint().z()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               0.0);
            }
            else if(PickSide >= Areas[1]/Areas.back() && PickSide <Areas[2]/Areas.back())  //Min Y
            {
                Result = getMinPoint().subZero() +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[2]/Areas.back() && PickSide <Areas[3]/Areas.back())  //Max Y
            {
                Result = Vec3f(getMinPoint().x(), getMaxPoint().y(), getMinPoint().z()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[3]/Areas.back() && PickSide <Areas[4]/Areas.back())  //Min X
            {
                Result = getMinPoint().subZero() +
                         Vec3f(0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[4]/Areas.back() && PickSide <Areas[5]/Areas.back())  //Max Y
            {
                Result = Vec3f(getMaxPoint().x(), getMinPoint().y(), getMinPoint().z()) +
                         Vec3f(0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else
            {
                assert(false && "Should never reach this point");
            }
        
        break;
        }
    case VOLUME:
    default:

        Result = getMinPoint().subZero() + Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().x() - getMinPoint().x()),
            RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().y() - getMinPoint().y()),
            RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().z() - getMinPoint().z()));
        
        break;
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoxDistribution3D::BoxDistribution3D(void) :
    Inherited()
{
}

BoxDistribution3D::BoxDistribution3D(const BoxDistribution3D &source) :
    Inherited(source)
{
}

BoxDistribution3D::~BoxDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BoxDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BoxDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BoxDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE
