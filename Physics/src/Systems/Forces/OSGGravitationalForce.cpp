/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGGravitationalForce.h"
#include "Physics/Objects/Attributes/OSGMassAttribute.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GravitationalForce

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GravitationalForce::initMethod (void)
{
}

 bool GravitationalForce::updateForce(osg::AttachmentMap& Attributes, osg::Vec3f& Force, osg::Vec3f& Torque)
 {
    AttachmentMap::iterator fcI = Attributes.find( 
       osg::MassAttribute::getClassType().getGroupId() );
    //Check for all of the Requirements
    
    if(fcI == Attributes.end() //Is Mass Attribute of the object defined
       )
    {
       SWARNING << "GravitationalForce: Not all the requirements are defined."  << std::endl;
       Force.setValue(Vec3f(0.0f,0.0f,0.0f));
       Torque.setValue(Vec3f(0.0f,0.0f,0.0f));
       return false;
    }
    
    MassAttributePtr MassAttrib = osg::MassAttribute::Ptr::dcast( (*fcI).second );
    
    //Calculate the force
    Force = MassAttrib->getMass() * getAcceleration();
    
    //Torque
    Torque = Vec3f(MassAttrib->getCenterOfMass()).cross(Force);
    return false;
 }

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GravitationalForce::GravitationalForce(void) :
    Inherited()
{
}

GravitationalForce::GravitationalForce(const GravitationalForce &source) :
    Inherited(source)
{
}

GravitationalForce::~GravitationalForce(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GravitationalForce::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GravitationalForce::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GravitationalForce NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGGRAVITATIONALFORCEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRAVITATIONALFORCEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRAVITATIONALFORCEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

