/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#define OSG_COMPILEPHYSICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGCollisionContactParameters.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CollisionContactParameters

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CollisionContactParameters::initMethod (void)
{
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

void CollisionContactParameters::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CollisionContactParameters::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CollisionContactParameters NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGCOLLISIONCONTACTPARAMETERSBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLLISIONCONTACTPARAMETERSBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLLISIONCONTACTPARAMETERSFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

