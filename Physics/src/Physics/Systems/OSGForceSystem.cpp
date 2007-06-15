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
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>

#include "OSGForceSystem.h"
#include "Physics/Objects/Attributes/OSGLinearPositionalAttribute.h"
#include "Physics/Objects/Attributes/OSGRotationalAttribute.h"
#include "Physics/Objects/Attributes/OSGMassAttribute.h"
#include "Physics/Objects/Attributes/OSGInertiaAttribute.h"

#include "Physics/Objects/OSGPhysicsCore.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ForceSystem

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ForceSystem::initMethod (void)
{
}

void ForceSystem::update(osg::NodeCorePtr core, osg::AttachmentMap& Attributes, const IntegrationPtr Integration, const Real32& ElpsTime)
{
   //Check that this Object has a Linear Positional Attribute
   AttachmentMap::iterator LinPosAttribIter = Attributes.find( 
      osg::LinearPositionalAttribute::getClassType().getGroupId() << 16 );
   bool hasLinearComponent = LinPosAttribIter != Attributes.end();

   //Check that this Object has a Rotational Attribute
   AttachmentMap::iterator RotAttribIter = Attributes.find( 
      osg::RotationalAttribute::getClassType().getGroupId() << 16 );
   bool hasRotationalComponent = RotAttribIter != Attributes.end();
   
   /*std::cout << "osg::LinearPositionalAttribute::getClassType().getGroupId(): " << osg::LinearPositionalAttribute::getClassType().getGroupId() << std::endl;
   std::cout << "osg::RotationalAttribute::getClassType().getGroupId(): " << osg::RotationalAttribute::getClassType().getGroupId() << std::endl;
   AttachmentMap::iterator MapIter;
   for(MapIter = Attributes.begin() ; MapIter != Attributes.end() ; ++MapIter)
   {
      std::cout << "Attachment Key: " << (*MapIter).first << std::endl;
      std::cout << "   Attachment Type: " << (*MapIter).second->getType().getName() << "Attachment Type GroupID: " << (*MapIter).second->getType().getGroupId()  << ", ClassType: " << (*MapIter).second->getClassType().getName()
            << ", ClassType GroupID: " << (*MapIter).second->getClassType().getGroupId() << std::endl;
   }*/
   
   if(!hasLinearComponent &&
      !hasRotationalComponent)
   {
       SWARNING << "ForceSystem: Object does not have Positional or Rotational Attribute defined."
             << "  Has " << Attributes.size() << " Attributes." << std::endl;
       return;
   }
   

   //Are there any forces defined on this object
   if(getForces().getSize() == 0)
   {
       SWARNING << "ForceSystem: No forces defined."  << std::endl;
       return;
   }
   
   AttachmentMap::iterator MassAttribIter = Attributes.find( 
      osg::MassAttribute::getClassType().getGroupId() << 16 );
   //Is there a Mass Attribute defined on this object
   if(MassAttribIter == Attributes.end())
   {
       SWARNING << "ForceSystem: No Mass defined."  << std::endl;
       return;
   }

   AttachmentMap::iterator InertiaAttribIter = Attributes.find( 
      osg::InertiaAttribute::getClassType().getGroupId() << 16 );
   //Is there an Inertia Attribute defined on this object
   if(hasRotationalComponent && InertiaAttribIter == Attributes.end())
   {
       SWARNING << "ForceSystem: Rotational Attribute Defined, but no Inertia Attribute defined."  << std::endl;
       return;
   }

   //Currently running Eulers Method for integration
   Vec3f TotalForce;
   Vec3f TotalTorque;

   Matrix CoreTransformation;

   Vec3f Force(0.0f,0.0f,0.0f);
   Vec3f Torque(0.0f,0.0f,0.0f);
   Real32 TimeLeft = ElpsTime;
   Real32 StepSize = 0.0;
   while(TimeLeft > 0.0)
   {
      StepSize = osg::osgMin(Integration->getTimeStep(), TimeLeft);
      if(StepSize <= 0.0)
      {
         SWARNING << "ForceSystem: Integration StepSize is <= 0.  Aborting Integration."  << std::endl;
         return;
      }
      CoreTransformation = osg::PhysicsCore::Ptr::dcast(core)->getTransformation();
      TotalForce = Vec3f(0.0,0.0,0.0);
      TotalTorque = Vec3f(0.0,0.0,0.0);
      for(UInt32 i = 0 ; i < getForces().size() ; ++i)
      {
         if( getForces(i)->updateForce(Attributes, Force, Torque) )
         {
            CoreTransformation.multMatrixVec(Force);
            //CoreTransformation.multMatrixVec(Torque);
         }
         //If the Object has a Linear Positional Attribute
         if(hasLinearComponent)
         {
            TotalForce += Force;
         }
         
         //If the Object has a Rotational Attribute
         if(hasRotationalComponent)
         {
            //std::cout << "      Torque: " << Torque << std::endl;
            TotalTorque += Torque;
         }
      }
      //std::cout << "Number Forces: " << getForces().size() << std::endl;
      //std::cout << "Total Force: " << TotalForce << std::endl;
      //std::cout << "TotalTorque: " << TotalTorque << std::endl;
      
      //Apply the Forces And Torques in this timestep
      if(hasLinearComponent)
      {
         LinearPositionalAttributePtr PosAttrib = osg::LinearPositionalAttribute::Ptr::dcast( (*LinPosAttribIter).second );
         MassAttributePtr MassAttrib = osg::MassAttribute::Ptr::dcast( (*MassAttribIter).second );

         //Velocity
         PosAttrib->setVelocity( PosAttrib->getVelocity() + StepSize *(static_cast<Real32>(1.0)/MassAttrib->getMass())*TotalForce );
         
         //Position
         PosAttrib->setPosition( PosAttrib->getPosition() + StepSize * PosAttrib->getVelocity() );
      }
      if(hasRotationalComponent)
      {
         RotationalAttributePtr RotAttribute = osg::RotationalAttribute::Ptr::dcast( (*RotAttribIter).second );
         InertiaAttributePtr InertiaAttrib = osg::InertiaAttribute::Ptr::dcast( (*InertiaAttribIter).second );

         //Angular Velocity
         RotAttribute->setAngularVelocity( RotAttribute->getAngularVelocity() + StepSize *(static_cast<Real32>(1.0)/InertiaAttrib->getMomentOfInertia())*TotalTorque );

         //Angular Displacement
         Vec3f Axis(RotAttribute->getAngularVelocity());
         Real32 VelocityMagnitude(Axis.length());
         Axis.normalize();
         
         Quaternion DeltaDis( Axis, StepSize*VelocityMagnitude );
         RotAttribute->getAngularDisplacement().mult(DeltaDis);
      }
      //Update the TimeStep
      TimeLeft -= Integration->getTimeStep();
   }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ForceSystem::ForceSystem(void) :
    Inherited()
{
}

ForceSystem::ForceSystem(const ForceSystem &source) :
    Inherited(source)
{
}

ForceSystem::~ForceSystem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ForceSystem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ForceSystem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ForceSystem NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFORCESYSTEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFORCESYSTEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFORCESYSTEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

