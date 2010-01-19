/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),                            *
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

#include "OSGCollisionContactParameters.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCollisionContactParametersBase.cpp file.
// To modify it, please change the .fcd file (OSGCollisionContactParameters.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionContactParameters::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CollisionContactParameters::updateODEContactJoint(dContact &d) const
{
    d.surface.mode = getMode();
    d.surface.mu = getMu();
    d.surface.mu2 = getMu2();
    d.surface.bounce = getBounce();
    d.surface.bounce_vel = getBounceSpeedThreshold();
    d.surface.soft_cfm = getSoftCFM();
    d.surface.soft_erp = getSoftERP();
    d.surface.motion1 = getMotion1();
    d.surface.motion2= getMotion2();
    d.surface.motionN = getMotionN();
    d.surface.slip1 = getSlip1();
    d.surface.slip2 = getSlip2();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CollisionContactParameters::CollisionContactParameters(void) :
    Inherited()
{
}

CollisionContactParameters::CollisionContactParameters(const CollisionContactParameters &source) :
    Inherited(source)
{
}

CollisionContactParameters::~CollisionContactParameters(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CollisionContactParameters::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CollisionContactParameters::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CollisionContactParameters NI" << std::endl;
}

OSG_END_NAMESPACE
