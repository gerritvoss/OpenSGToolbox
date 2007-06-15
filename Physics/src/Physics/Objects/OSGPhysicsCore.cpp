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
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGRenderAction.h>

#include "OSGPhysicsCore.h"
#include <Physics/Objects/Attributes/OSGLinearPositionalAttribute.h>
#include <Physics/Objects/Attributes/OSGRotationalAttribute.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsCore

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsCore::initMethod (void)
{
   PhysicsActor::regClassEnter(
      osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            PhysicsCorePtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&PhysicsCore::physicsActor),
      getClassType());
   
   DrawAction::registerEnterDefault(
      getClassType(),
      osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            PhysicsCorePtr    ,
            CNodePtr        ,
            Action         *>(&PhysicsCore::drawEnter));
   
   DrawAction::registerLeaveDefault(
      getClassType(),
      osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            PhysicsCorePtr    ,
            CNodePtr        ,
            Action         *>(&PhysicsCore::drawLeave));
   
   RenderAction::registerEnterDefault(
         getClassType(),
         osgTypedMethodFunctor2BaseCPtrRef<
         Action::ResultE,
         PhysicsCorePtr    ,
         CNodePtr        ,
         Action         *>(&PhysicsCore::renderEnter));
   
   RenderAction::registerLeaveDefault(
         getClassType(),
         osgTypedMethodFunctor2BaseCPtrRef<
         Action::ResultE,
         PhysicsCorePtr    ,
         CNodePtr        ,
         Action         *>(&PhysicsCore::renderLeave));
}

NewActionTypes::ResultE PhysicsCore::physicsActor(ActorBase::FunctorArgumentType& funcArg )
{
   PhysicsActor   *pPA         = dynamic_cast<PhysicsActor *>(funcArg.getActor());
   update( pPA->getElpsTime() );
   return NewActionTypes::Continue;
}

void PhysicsCore::update(const Real32& ElpsTime)
{
   //Apply Each of my systems
   for(unsigned int i = 0 ; i < getSystems().size() ; ++i)
   {
      getSystems(i)->update(NodeCorePtr(this), getAttributes(), getIntegration(), ElpsTime);
   }

   //Calculate the new Matrix for this node
   //If there is a Positional Attribute
   PhysicsObjectAttributePtr PosAttrib = findAttribute(osg::LinearPositionalAttribute::getClassType());
   
   //If there is a Rotational Attribute
   PhysicsObjectAttributePtr RotAttrib = findAttribute(osg::RotationalAttribute::getClassType());

   beginEditCP(PhysicsCorePtr(this), TransformationFieldMask);
   getTransformation().identity();
   if(PosAttrib != NullFC)
   {
      if(RotAttrib != NullFC)
      {
      getTransformation().setTransform(
         osg::Vec3f(osg::LinearPositionalAttribute::Ptr::dcast(PosAttrib)->getPosition()),
         osg::RotationalAttribute::Ptr::dcast(RotAttrib)->getAngularDisplacement(),
         osg::Vec3f(1.0,1.0,1.0),
         osg::Quaternion(),
         osg::Vec3f(osg::RotationalAttribute::Ptr::dcast(RotAttrib)->getCenterOfRotation()));
      }
      else
      {
         //Then set the translation of this cores matrix to that position
         getTransformation().setTranslate(osg::LinearPositionalAttribute::Ptr::dcast(PosAttrib)->getPosition());
      }
   }
   else if(RotAttrib != NullFC)
   {
      //Then set the Orientation of this cores matrix to that orientation
      getTransformation().setTransform(osg::Vec3f(0.0,0.0,0.0),
         osg::RotationalAttribute::Ptr::dcast(RotAttrib)->getAngularDisplacement(),
         osg::Vec3f(1.0,1.0,1.0),
         osg::Quaternion(),
         osg::Vec3f(osg::RotationalAttribute::Ptr::dcast(RotAttrib)->getCenterOfRotation()));
   }
   
   endEditCP(PhysicsCorePtr(this), TransformationFieldMask);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE PhysicsCore::drawEnter(Action *action)
{
   DrawAction *da = dynamic_cast<DrawAction *>(action);

   // should use the chunk, but it's not updated yet
   glPushMatrix ();
   glMultMatrixf(getTransformation().getValues());

   da->selectVisibles();

   return Action::Continue;
}

Action::ResultE PhysicsCore::drawLeave(Action *)
{
   glPopMatrix();

   return Action::Continue;
}
/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE PhysicsCore::renderEnter(Action *action)
{
   RenderAction *pAction = dynamic_cast<RenderAction *>(action);

   pAction->pushVisibility();

   pAction->push_matrix(this->getTransformation());

   return Action::Continue;
}

Action::ResultE PhysicsCore::renderLeave(Action *action)
{
   RenderAction *pAction = dynamic_cast<RenderAction *>(action);

   pAction->popVisibility();

   pAction->pop_matrix();

   return Action::Continue;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsCore::PhysicsCore(void) :
    Inherited()
{
}

PhysicsCore::PhysicsCore(const PhysicsCore &source) :
    Inherited(source)
{
}

PhysicsCore::~PhysicsCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsCore::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & TransformationFieldMask)
    {
        invalidateVolume();
    }
    Inherited::changed(whichField, origin);
}

void PhysicsCore::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsCore NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPHYSICSCOREBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSCOREBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSCOREFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

