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
    Matrix m,r;
    if(t!=NULL)
    {
        //SLOG << "found a TransformNode " << endLog;
        AttachmentUnrecPtr a = node->findAttachment(PhysicsBody::getClassType());
        if(a!=NULL)
        {
            //SLOG << "found a bodyNode " << endLog;
            PhysicsBodyUnrecPtr body = dynamic_pointer_cast<PhysicsBody>(a);
            body->updateToODEState();

            //update the position
            m.setIdentity();
            r.setIdentity();
            Vec3f p = body->getPosition();
            Quaternion q = body->getQuaternion();
            r.setRotate(q);
            m.setTransform(p);
            m.mult(r);
            //CPEdit(t, Transform::MatrixFieldMask);
            t->setMatrix(m);
            //update BB
            //CPEdit(node, Node::VolumeFieldMask);
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
 *                           Class variables                               *
\***************************************************************************/
StatElemDesc<StatTimeElem> PhysicsHandler::statCollisionTime("collisionTime", 
                                                      "time for collision tests per update");
StatElemDesc<StatTimeElem> PhysicsHandler::statPerStepCollisionTime("perStepCollisionTime", 
                                                      "time for collision tests per step");

StatElemDesc<StatTimeElem> PhysicsHandler::statSimulationTime("simulationTime", 
                                                      "time for physics simulation per update");
StatElemDesc<StatTimeElem> PhysicsHandler::statPerStepSimulationTime("perStepSimulationTime", 
                                                      "time for physics simulation per step");

StatElemDesc<StatTimeElem> PhysicsHandler::statPhysicsTime("physicsTime", 
                                                      "time for entire physics update");


StatElemDesc<StatIntElem> PhysicsHandler::statNPhysicsSteps("NPhysicsSteps", 
                                                      "number of physics steps performed this update");

StatElemDesc<StatIntElem> PhysicsHandler::statNCollisionTests("NCollisionTests", 
                                                      "number of collision tests per step");

StatElemDesc<StatIntElem> PhysicsHandler::statNCollisions("NCollisions", 
                                                      "number of collisions per step");

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
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&PhysicsHandler::attachedUpdate, this, _1));
    }
}

void PhysicsHandler::attachedUpdate(EventDetails* const details)
{
    getStatistics()->reset();
    getStatistics()->getElem(statCollisionTime)->start();
    getStatistics()->getElem(statCollisionTime)->stop();
    getStatistics()->getElem(statSimulationTime)->start();
    getStatistics()->getElem(statSimulationTime)->stop();

    getStatistics()->getElem(statPhysicsTime)->start();
    _TimeSinceLast += dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime();

    if(osgFloor(_TimeSinceLast/getStepSize()) > getMaxStepsPerUpdate())
    {
        //SWARNING << "Physics Simulation slowing: droping " << osgFloor(_TimeSinceLast/getStepSize())-getMaxStepsPerUpdate() << " steps.\n";
        _TimeSinceLast = getMaxStepsPerUpdate()*getStepSize();
    }

    while(_TimeSinceLast > getStepSize())
    {
        //Update
        getStatistics()->getElem(statNPhysicsSteps)->inc();

        //collide
        getStatistics()->getElem(statPerStepCollisionTime)->start();
        getStatistics()->getElem(statNCollisionTests)->reset();
        getStatistics()->getElem(statNCollisions)->reset();
        for(UInt32 i(0) ; i<getMFSpaces()->size() ; ++i)
        {
            getSpaces(i)->Collide(getWorld());
        }
        getStatistics()->getElem(statPerStepCollisionTime)->stop();
        (*getStatistics()->getElem(statCollisionTime)) += *(getStatistics()->getElem(statPerStepCollisionTime));

        //step the world
        getStatistics()->getElem(statPerStepSimulationTime)->start();
        getWorld()->worldQuickStep(getStepSize());
        getStatistics()->getElem(statPerStepSimulationTime)->stop();
        (*getStatistics()->getElem(statSimulationTime)) += *(getStatistics()->getElem(statPerStepSimulationTime));

        _TimeSinceLast -= getStepSize();
    }

    //update matrices
    updateWorld(getUpdateNode());

    getStatistics()->getElem(statPhysicsTime)->stop();
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
