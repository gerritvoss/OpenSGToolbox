/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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

#include "OSGPhysicsHandler.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"
#include "OSGVector.h"
#include "OSGBaseFunctions.h"
#include "OSGAction.h"
#include "OSGTransform.h"
#include "OSGGroup.h"
#include "OSGStatCollector.h"
#include "OSGUpdateEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsHandlerBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsHandler.fcd) and
// regenerate the base file.


//////////////////////////////////////////////////////////////////////////
//! this action traverses the graph to match the OpenSG representation 
//! to ODE
//////////////////////////////////////////////////////////////////////////
Action::ResultE updateOsgOde(Node* const node)
{   
    //SLOG << "entering " << node << endLog;
    TransformUnrecPtr t = dynamic_cast<Transform*>(node->getCore());
    if(t!=NULL)
    {
        //SLOG << "found a TransformNode " << endLog;
        AttachmentUnrecPtr a = node->findAttachment(PhysicsBody::getClassType());
        if(a!=NULL)
        {
            Matrix m;
            PhysicsBodyUnrecPtr body = dynamic_pointer_cast<PhysicsBody>(a);
            body->updateToODEState();

            //update the position and rotation, but keep the scaling

            Vec3f Translation, Scale;
            Quaternion Rotation, ScaleOrientation;
            t->getMatrix().getTransform(Translation,Rotation,Scale,ScaleOrientation);
            Translation = body->getPosition();
            Rotation = body->getQuaternion();
            
            m.setTransform(Translation,Rotation,Scale,ScaleOrientation);

            t->setMatrix(m);
            //update BB
            node->updateVolume();
        }
    }

    return Action::Continue; 
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
StatElemDesc<StatTimeElem> PhysicsHandler::statCollisionTime("collisionTime", 
                                                      "time for collision tests per update");

StatElemDesc<StatTimeElem> PhysicsHandler::statSimulationTime("simulationTime", 
                                                      "time for physics simulation per update");

StatElemDesc<StatTimeElem> PhysicsHandler::statTransformUpdateTime("transformUpdateTime", 
                                                                   "time to update scene nodes with physics changes");

StatElemDesc<StatTimeElem> PhysicsHandler::statPhysicsTime("physicsTime", 
                                                      "time for entire physics update");


StatElemDesc<StatIntElem> PhysicsHandler::statNPhysicsSteps("NPhysicsSteps", 
                                                            "number of physics steps performed this update");

StatElemDesc<StatRealElem> PhysicsHandler::statNCollisionTests("NCollisionTests", 
                                                           "average number of collisions tests per step");

StatElemDesc<StatRealElem> PhysicsHandler::statNCollisions("NCollisions", 
                                                           "average number of collisions per step");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHandler::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsHandler::attachUpdateProducer(ReflexiveContainer* const producer)
{
    if(_UpdateEventConnection.connected())
    {
        _UpdateEventConnection.disconnect();
    }
    //Get the Id of the UpdateEvent
    const EventDescription* Desc(producer->getProducerType().findEventDescription("Update"));
    if(Desc == NULL)
    {
        SWARNING << "There is no Update event defined on " << producer->getType().getName() << " types." << std::endl;
    }
    else
    {
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&PhysicsHandler::attachedUpdate, this, _1), boost::signals2::at_back);
    }
}

void PhysicsHandler::attachedUpdate(EventDetails* const details)
{
    commitChanges();

    //Start the physics timing statistic
    StatTimeElem *PhysicsTimeStatElem = StatCollector::getGlobalElem(statPhysicsTime);
    if(PhysicsTimeStatElem) { PhysicsTimeStatElem->start(); }

    _TimeSinceLast += dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime();

    if(osgFloor(_TimeSinceLast/getStepSize()) > getMaxStepsPerUpdate())
    {
        SWARNING << "Physics Simulation slowing: dropping " << osgFloor(_TimeSinceLast/getStepSize())-getMaxStepsPerUpdate() << " steps" << std::endl;
        _TimeSinceLast = getMaxStepsPerUpdate()*getStepSize();
    }

    StatIntElem *NPhysicsStepsStatElem = StatCollector::getGlobalElem(statNPhysicsSteps);
    StatTimeElem *CollisionTimeStatElem = StatCollector::getGlobalElem(statCollisionTime);
    StatTimeElem *DynamicsTimeStatElem = StatCollector::getGlobalElem(statSimulationTime);
    while(_TimeSinceLast > getStepSize())
    {
        //Increment the steps statistic
        if(NPhysicsStepsStatElem) { NPhysicsStepsStatElem->inc(); }

        //*********** Collision Checks *************
        //Start the collision timing statistic
        if(CollisionTimeStatElem) { CollisionTimeStatElem->start(); }

        //Do collision checks
        for(UInt32 i(0) ; i<getMFSpaces()->size() ; ++i)
        {
            getSpaces(i)->Collide(getWorld());
        }

        //Stop the collision timing statistic
        if(CollisionTimeStatElem) { CollisionTimeStatElem->stop(); }


        //*********** Simulation step *************

        //Start the simulation timing statistic
        if(DynamicsTimeStatElem) { DynamicsTimeStatElem->start(); }

        //Step the dynamics simulation
        getWorld()->worldQuickStep(getStepSize());

        //Stop the simulation timing statistic
        if(DynamicsTimeStatElem) { DynamicsTimeStatElem->stop(); }

        //Decrease the time since last simulation step
        _TimeSinceLast -= getStepSize();
    }
    StatRealElem *NCollisionTestsStatElem = StatCollector::getGlobalElem(statNCollisionTests);
    if(NCollisionTestsStatElem) { NCollisionTestsStatElem->set(NCollisionTestsStatElem->get()/static_cast<Real32>(NPhysicsStepsStatElem->get())); }
    StatRealElem *NCollisionsStatElem = StatCollector::getGlobalElem(statNCollisions);
    if(NCollisionsStatElem) { NCollisionsStatElem->set(NCollisionsStatElem->get()/static_cast<Real32>(NPhysicsStepsStatElem->get())); }

    
    
    StatTimeElem *TransformUpdateTimeStatElem = StatCollector::getGlobalElem(statTransformUpdateTime);
    //Start the transform update timing statistic
    if(TransformUpdateTimeStatElem) { TransformUpdateTimeStatElem->start(); }
    //update matrices
    updateWorld(getUpdateNode());
    //Start the transform update timing statistic
    if(TransformUpdateTimeStatElem) { TransformUpdateTimeStatElem->stop(); }

    //Stop the physics timing statistic
    if(PhysicsTimeStatElem) { PhysicsTimeStatElem->stop(); }
}

void PhysicsHandler::updateWorld(Node* const node)
{
    //update matrices
    traverse(node, 
             boost::bind(&OSG::updateOsgOde, _1));
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsHandler::onCreate(const PhysicsHandler *)
{
}

void PhysicsHandler::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsHandler::PhysicsHandler(void) :
    Inherited(),
        _TimeSinceLast(0.0f)

{
}

PhysicsHandler::PhysicsHandler(const PhysicsHandler &source) :
    Inherited(source),
        _TimeSinceLast(0.0f)

{
}

PhysicsHandler::~PhysicsHandler(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHandler::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PhysicsHandler::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHandler NI" << std::endl;
}

OSG_END_NAMESPACE
