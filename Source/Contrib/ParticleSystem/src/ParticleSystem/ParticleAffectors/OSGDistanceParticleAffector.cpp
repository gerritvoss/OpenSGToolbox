/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGDistanceParticleAffector.h"
#include "OSGCamera.h"
#include "OSGMatrixUtility.h"
#include "OSGQuaternion.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDistanceParticleAffectorBase.cpp file.
// To modify it, please change the .fcd file (OSGDistanceParticleAffector.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DistanceParticleAffector::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DistanceParticleAffector::affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps)
{
    if(System != NULL && getParticleSystemNode() != NULL)
    {
        Vec3f Displacement;

        Matrix PSystemNodeMat(getParticleSystemNode()->getToWorld());
        Pnt3f ParticlePositionInWorldSpace = PSystemNodeMat * System->getPosition(ParticleIndex);

        Pnt3f NodePositionInWorldSpace;

        //Calculate the Distance
        switch(getDistanceFromSource())
        {
            case DISTANCE_FROM_NODE:
                if(getDistanceFromNode() != NULL)
                {
                    //DynamicVolume Vol;
                    //getDistanceFromNode()->getWorldVolume(Vol);
                    //Vol.getCenter(NodePositionInWorldSpace);
                    NodePositionInWorldSpace = getDistanceFromNode()->getToWorld() * Pnt3f(0.0,0.0,0.0);
                }
                break;
            case DISTANCE_FROM_CAMERA:
                if(getDistanceFromCamera() != NULL)
                {
                    Matrix m;
                    getDistanceFromCamera()->getViewing(m,1,1);
                    getPFromViewMat(NodePositionInWorldSpace,m);
                }
            default:
                break;
        }

        Displacement = (NodePositionInWorldSpace - ParticlePositionInWorldSpace);

        return affect(System, ParticleIndex, elps, Displacement);
    }
    else
    {
        return false;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DistanceParticleAffector::DistanceParticleAffector(void) :
    Inherited()
{
}

DistanceParticleAffector::DistanceParticleAffector(const DistanceParticleAffector &source) :
    Inherited(source)
{
}

DistanceParticleAffector::~DistanceParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DistanceParticleAffector::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DistanceParticleAffector::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DistanceParticleAffector NI" << std::endl;
}

OSG_END_NAMESPACE
