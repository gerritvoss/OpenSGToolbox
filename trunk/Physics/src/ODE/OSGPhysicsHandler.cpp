/*---------------------------------------------------------------------------*\
 *                                                                     *
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
#include "OSGPhysicsDef.h"

#include "OSGPhysicsHandler.h"

#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
//////////////////////////////////////////////////////////////////////////
//! collision handling
//////////////////////////////////////////////////////////////////////////
#include "OSGPhysics.h"


OSG_USING_NAMESPACE
/************************************************************************/
/* init ode stuff!call this once when you have loaded a ode scene from
    file                                                                */
/************************************************************************/
Action::ResultE initOde(NodePtr& node)
{   
    AttachmentPtr a;
    a = node->findAttachment(PhysicsWorld::getClassType());
    if(a!=NullFC)
    {
        PhysicsWorldPtr world = PhysicsWorldPtr::dcast(a);
        world->initWorld();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsHashSpace::getClassType());
    if(a!=NullFC)
    {
        PhysicsHashSpacePtr space = PhysicsHashSpacePtr::dcast(a);
        space->initHashSpace();

        return Action::Continue;
    }

    a = node->findAttachment(PhysicsBoxGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsBoxGeomPtr box = PhysicsBoxGeomPtr::dcast(a);
        box->initBoxGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsSphereGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsSphereGeomPtr sphere = PhysicsSphereGeomPtr::dcast(a);
        sphere->initSphereGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsPlaneGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsPlaneGeomPtr sphere = PhysicsPlaneGeomPtr::dcast(a);
        sphere->initPlaneGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsCCylinderGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsCCylinderGeomPtr ccylinder = PhysicsCCylinderGeomPtr::dcast(a);
        ccylinder->initCCylinderGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsRayGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsRayGeomPtr ray = PhysicsRayGeomPtr::dcast(a);
        ray->initRayGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsTriMeshGeom::getClassType());
    if(a!=NullFC)
    {
        PhysicsTriMeshGeomPtr tri = PhysicsTriMeshGeomPtr::dcast(a);
        tri->initTriMeshGeom();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsAMotorJoint::getClassType());
    if(a!=NullFC)
    {
        PhysicsAMotorJointPtr joint = PhysicsAMotorJointPtr::dcast(a);
        joint->initAMotorJoint();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsSliderJoint::getClassType());
    if(a!=NullFC)
    {
        PhysicsSliderJointPtr joint = PhysicsSliderJointPtr::dcast(a);
        joint->initSliderJoint();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsHinge2Joint::getClassType());
    if(a!=NullFC)
    {
        PhysicsHinge2JointPtr joint = PhysicsHinge2JointPtr::dcast(a);
        joint->initHinge2Joint();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsHingeJoint::getClassType());
    if(a!=NullFC)
    {
        PhysicsHingeJointPtr joint = PhysicsHingeJointPtr::dcast(a);
        joint->initHingeJoint();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsUniversalJoint::getClassType());
    if(a!=NullFC)
    {
        PhysicsUniversalJointPtr joint = PhysicsUniversalJointPtr::dcast(a);
        joint->initUniversalJoint();

        return Action::Continue;
    }
    a = node->findAttachment(PhysicsBallJoint::getClassType());
    if(a!=NullFC)
    {
        PhysicsBallJointPtr joint = PhysicsBallJointPtr::dcast(a);
        joint->initBallJoint();

        return Action::Continue;
    }
    return Action::Continue;

}


//////////////////////////////////////////////////////////////////////////
//! this action traverses the graph to match the OpenSG representation 
//! to ODE
//////////////////////////////////////////////////////////////////////////
Action::ResultE updateOsgOde(NodePtr& node)
{   
    //SLOG << "entering " << node << endLog;
    TransformPtr t = TransformPtr::dcast(node->getCore());
    Matrix m,r;
    if(t!=NullFC)
    {
        //SLOG << "found a TransformNode " << endLog;
        AttachmentPtr a = node->findAttachment(PhysicsBody::getClassType());
        if(a!=NullFC)
        {
            //SLOG << "found a bodyNode " << endLog;
            PhysicsBodyPtr body = PhysicsBodyPtr::dcast(a);
            body->updateToODEState();
            // If the object is moving normally, dampen the movement a bit to simulate low-level friction
            // (the amount of dampening should depend on whether the object is contacting another or not,
            // and a contact-type-specific dampening amount, but oh well, this generally works)
            //beginEditCP(body, PhysicsBody::ForceFieldMask | PhysicsBody::TorqueFieldMask);
            //    Vec3f vel = body->getLinearVel();
            //    body->addForce(vel * -0.01f);
            //    vel = body->getAngularVel();
            //    body->addTorque(vel * -0.01f);
            //endEditCP(body, PhysicsBody::ForceFieldMask | PhysicsBody::TorqueFieldMask);

            //update the position
            m.setIdentity();
            r.setIdentity();
            Vec3f p = body->getPosition();
            Quaternion q = body->getQuaternion();
            r.setRotate(q);
            m.setTransform(p);
            m.mult(r);
            CPEdit(t, Transform::MatrixFieldMask);
            t->setMatrix(m);
            //update BB
            CPEdit(node, Node::VolumeFieldMask);
            node->updateVolume();

            if(p.z() < -10)
            {
                //subRefCP(node);
            }
        }
    }

    return Action::Continue; 
}


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsHandler

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
StatElemDesc<StatTimeElem> PhysicsHandler::statCollisionTime("collisionTime", 
                                                      "time for collision tests per update");

StatElemDesc<StatTimeElem> PhysicsHandler::statSimulationTime("simulationTime", 
                                                      "time for physics simulation per update");

StatElemDesc<StatTimeElem> PhysicsHandler::statPhysicsTime("physicsTime", 
                                                      "time for entire physics update");


StatElemDesc<StatIntElem> PhysicsHandler::statNPhysicsSteps("NPhysicsSteps", 
                                                      "number of physics steps performed this update");

StatElemDesc<StatIntElem> PhysicsHandler::statNCollisionTests("NCollisionTests", 
                                                      "number of collision tests");

StatElemDesc<StatIntElem> PhysicsHandler::statNCollisions("NCollisions", 
                                                      "number of collisions");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHandler::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsHandler::onCreate(const PhysicsHandler *)
{
}

void PhysicsHandler::onDestroy()
{
}

StatCollector* PhysicsHandler::getStatistics(void)
{
    if(_statistics == NULL)
    {
        _statistics = StatCollector::create();
        _ownStat = true;
    }

    return _statistics;
}

void PhysicsHandler::setStatistics(StatCollector *stat)
{
    if (_ownStat) {
       delete _statistics;
    }
    _statistics = stat;
    _ownStat = false;
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/

void PhysicsHandler::update(Time ElapsedTime, NodePtr UpdateNode)
{

    getStatistics()->getElem(statPhysicsTime)->start();
    _TimeSinceLast += ElapsedTime;

    while(_TimeSinceLast > getStepSize())
    {
        //Update
        getStatistics()->getElem(statNPhysicsSteps)->inc();
        //collide
        getStatistics()->getElem(statCollisionTime)->start();
        getSpace()->Collide(getWorld());
        getStatistics()->getElem(statCollisionTime)->stop();

        //step the world
        getStatistics()->getElem(statSimulationTime)->start();
        getWorld()->worldQuickStep(getStepSize());
        getStatistics()->getElem(statSimulationTime)->stop();

        //update matrices
        updateWorld(UpdateNode);

        _TimeSinceLast -= getStepSize();
    }
    getStatistics()->getElem(statPhysicsTime)->stop();
}

void PhysicsHandler::updateWorld(NodePtr node)
{
    //update matrices
    traverse(node, 
        osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
        NodePtr        >(updateOsgOde));
}

void PhysicsHandler::odeInit(NodePtr node)
{
    traverse(node, 
        osgTypedFunctionFunctor1CPtrRef<Action::ResultE,
        NodePtr        >(initOde));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsHandler::PhysicsHandler(void) :
    Inherited(),
        _statistics(NULL),
        _ownStat(false),
        _TimeSinceLast(0.0f)
{
}

PhysicsHandler::PhysicsHandler(const PhysicsHandler &source) :
    Inherited(source),
        _statistics(NULL),
        _ownStat(false),
        _TimeSinceLast(0.0f)
{
}

PhysicsHandler::~PhysicsHandler(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHandler::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & WorldFieldMask && getWorld() != NullFC)
    {
        beginEditCP(getWorld(), PhysicsWorld::InternalParentHandlerFieldMask);
            getWorld()->setInternalParentHandler(PhysicsHandlerPtr(this));
        endEditCP(getWorld(), PhysicsWorld::InternalParentHandlerFieldMask);
    }
}

void PhysicsHandler::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHandler NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsHandler.cpp,v 1.2 2006/08/19 00:21:46 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSHANDLERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSHANDLERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSHANDLERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

