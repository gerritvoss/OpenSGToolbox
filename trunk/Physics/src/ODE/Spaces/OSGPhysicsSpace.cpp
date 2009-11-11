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
#include <ode/ode.h>

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsSpace.h"
#include "ODE/OSGPhysicsWorld.h"
#include "ODE/OSGPhysicsHandler.h"
#include <OpenSG/OSGStatCollector.h>
#include "OSGCollisionContactParameters.h"
#include <boost/bind.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSpace::initMethod (void)
{
	XMLFCFileType::the()->registerHandler(&PhysicsSpace::getClassType(),boost::bind(&osg::PhysicsSpace::xmlReadHandler,_1,_2,_3),boost::bind(&osg::PhysicsSpace::xmlWriteHandler,_1));
}

void PhysicsSpace::collisionCallback (void *data, dGeomID o1, dGeomID o2)
{
    reinterpret_cast<PhysicsSpace*>(data)->collisionCallback(o1,o2);
}

bool PhysicsSpace::xmlReadHandler (rapidxml::xml_node<char>& PhysicsSpaceRoot, const XMLFCFileType::IDLookupMap& TheLookupMap, const FieldContainerPtr& PhysicsSpaceFC)
{
    //Space Object
    PhysicsSpacePtr TheSpace = PhysicsSpacePtr::dcast(PhysicsSpaceFC);

    //Activity
    ActivityPtr TheActivity;
    //Category
    UInt32 GeomCategory;
    //SpeedThreshold
    Real32 SpeedThreshold;

	rapidxml::xml_attribute<char> *curAttribute;
	for(rapidxml::node_iterator<char> NodeListItor(&PhysicsSpaceRoot); NodeListItor!=rapidxml::node_iterator<char>() ; ++NodeListItor)
	{
        //Add this Activity as a listener to this Space
        //TODO: Implement
    }
}

bool PhysicsSpace::xmlWriteHandler (const FieldContainerPtr& PhysicsSpaceFC)
{
    //TODO: Implement
	return true;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsSpace::onCreate(const PhysicsSpace *id /* = NULL */)
{
	//spaces are created in subclasses
}

void PhysicsSpace::onDestroy()
{
    if(_SpaceID)
    {
	    //dSpaceDestroy(_SpaceID);
        _SpaceID = 0;
    }
}

bool PhysicsSpace::isPlaceable(void) const
{
    return false;
}

EventConnection PhysicsSpace::addCollisionListener(CollisionListenerPtr Listener, UInt64 Category, Real32 SpeedThreshold)
{
   _CollisionListeners.insert(Listener);
   
   
    CollisionListenParams newParams;
    newParams._Category = Category;
    newParams._SpeedThreshold = SpeedThreshold;
    newParams._Listener = Listener;
    _CollisionListenParamsVec.push_back(newParams);

   return EventConnection(
       boost::bind(&PhysicsSpace::isCollisionListenerAttached, this, Listener),
       boost::bind(&PhysicsSpace::removeCollisionListener, this, Listener));
}

void PhysicsSpace::removeCollisionListener(CollisionListenerPtr Listener)
{
    CollisionListenerSetItor EraseIter(_CollisionListeners.find(Listener));
    if(EraseIter != _CollisionListeners.end())
    {
        _CollisionListeners.erase(EraseIter);
    }
   
    std::vector<CollisionListenParams>::iterator ParamsEraseItor(_CollisionListenParamsVec.begin());
    for(; ParamsEraseItor!=_CollisionListenParamsVec.end() ; ++ParamsEraseItor)
    {
        if(ParamsEraseItor->_Listener == Listener)
        {
            _CollisionListenParamsVec.erase(ParamsEraseItor);
            break;
        }
    }
}

void PhysicsSpace::collisionCallback (dGeomID o1, dGeomID o2)
{
    getParentHandler()->getStatistics()->getElem(PhysicsHandler::statNCollisionTests)->inc();

    if (dGeomIsSpace (o1) || dGeomIsSpace (o2))
    {
        // colliding a space with something
        dSpaceCollide2 (o1,o2,reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
        // collide all geoms internal to the space(s)
        if (dGeomIsSpace (o1)) dSpaceCollide (dGeomGetSpace(o1),reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
        if (dGeomIsSpace (o2)) dSpaceCollide (dGeomGetSpace(o2),reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
    }
    else
    {
        // colliding two non-space geoms, so generate contact
        // points between o1 and o2
        Int32 numContacts = dCollide(o1, o2, _ContactJoints.size(), 
            &(_ContactJoints[0].geom), sizeof(dContact));
    
        getParentHandler()->getStatistics()->getElem(PhysicsHandler::statNCollisions)->add(numContacts);

        // add these contact points to the simulation
        for (Int32 i=0; i < numContacts; i++)
        {

            getCollisionContact(dGeomGetCategoryBits(o1), dGeomGetCategoryBits(o2))->updateODEContactJoint(_ContactJoints[i]);
            dJointID jointId = dJointCreateContact(_CollideWorldID, 
                _ColJointGroupId, 
                &_ContactJoints[i]);

            dJointAttach(jointId, dGeomGetBody(o1), dGeomGetBody(o2));
        }
        if(numContacts>0)
        {
            Vec3f v1,v2,normal;
            Pnt3f position;
            dVector3 odeVec;
            Real32 projectedNormalSpeed;
            for (Int32 i=0; i < numContacts; i++)
            {
                normal += Vec3f(&_ContactJoints[i].geom.normal[0]);
                position += Vec3f(&_ContactJoints[i].geom.pos[0]);
                if(dGeomGetBody(o1))
                {
                    dBodyGetPointVel(dGeomGetBody(o1), _ContactJoints[i].geom.pos[0], _ContactJoints[i].geom.pos[1], _ContactJoints[i].geom.pos[2],odeVec);
                    v1 += Vec3f(&odeVec[0]);
                }
                if(dGeomGetBody(o2))
                {
                    dBodyGetPointVel(dGeomGetBody(o2), _ContactJoints[i].geom.pos[0], _ContactJoints[i].geom.pos[1], _ContactJoints[i].geom.pos[2],odeVec);
                    v2 += Vec3f(&odeVec[0]);
                }
            }

            normal = normal * (1.0f/static_cast<Real32>(numContacts));
            position = position * (1.0f/static_cast<Real32>(numContacts));
            v1 = v1 * (1.0f/static_cast<Real32>(numContacts));
            v2 = v2 * (1.0f/static_cast<Real32>(numContacts));
            projectedNormalSpeed = (v1+v2).projectTo(normal);

            //TODO: Add a way to get the PhysicsGeomPtr from the GeomIDs so that the PhysicsGeomPtr can be 
            //sent to the collision event
            produceCollision(position,normal,NullFC,NullFC,v1,v2,projectedNormalSpeed);

            UInt32 Index(0);
            for(; Index<_CollisionListenParamsVec.size() ; ++Index)
            {
                if((dGeomGetCategoryBits(o1) & _CollisionListenParamsVec[Index]._Category) || (dGeomGetCategoryBits(o2) & _CollisionListenParamsVec[Index]._Category))
                {
                    break;
                }
            }
            if(Index < _CollisionListenParamsVec.size())
            {
                for(UInt32 i(0); i<_CollisionListenParamsVec.size() ; ++i)
                {
                    if( ((dGeomGetCategoryBits(o1) & _CollisionListenParamsVec[i]._Category) || (dGeomGetCategoryBits(o2) & _CollisionListenParamsVec[i]._Category)) &&
                         (osgabs(projectedNormalSpeed) > _CollisionListenParamsVec[i]._SpeedThreshold)
                        )
                    {
                        //TODO: Add a way to get the PhysicsGeomPtr from the GeomIDs so that the PhysicsGeomPtr can be 
                        //sent to the collision event
                        produceCollision(_CollisionListenParamsVec[i]._Listener,position,normal,NullFC,NullFC,v1,v2,projectedNormalSpeed);
                    }
                }
            }
        }
    }
}

void PhysicsSpace::setSpaceID(dSpaceID id)
{
    _SpaceID = id;
}

CollisionContactParametersPtr PhysicsSpace::createDefaultContactParams(void) const
{
    CollisionContactParametersPtr Params = CollisionContactParameters::createEmpty();
    beginEditCP(Params);
        Params->setMode(dContactApprox1);
        Params->setMu(1.0);
        Params->setMu2(1.0);
        Params->setBounce(0.0);
        Params->setBounceSpeedThreshold(0.0);
        Params->setSoftCFM(0.1);
        Params->setSoftERP(0.2);
        Params->setMotion1(0.0);
        Params->setMotion2(0.0);
        Params->setMotionN(0.0);
        Params->setSlip1(0.0);
        Params->setSlip2(0.0);
    endEditCP(Params);

    return Params;
}

void PhysicsSpace::addCollisionContactCategory(UInt64 Category1, UInt64 Category2, CollisionContactParametersPtr ContactParams)
{
    for(UInt32 i(0) ; i<getCategory1().size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
            beginEditCP(PhysicsSpacePtr(this), CategoryCollisionParametersFieldMask);
                editCategoryCollisionParameters(i) = ContactParams;
            endEditCP(PhysicsSpacePtr(this), CategoryCollisionParametersFieldMask);
            return;
        }
    }

    beginEditCP(PhysicsSpacePtr(this), Category1FieldMask | Category2FieldMask | CategoryCollisionParametersFieldMask);
        getCategory1().push_back(Category1);
        getCategory2().push_back(Category2);
        getCategoryCollisionParameters().push_back(ContactParams);
    endEditCP(PhysicsSpacePtr(this), Category1FieldMask | Category2FieldMask | CategoryCollisionParametersFieldMask);

}

void PhysicsSpace::removeCollisionContactCategory(UInt64 Category1, UInt64 Category2)
{
    for(UInt32 i(0) ; i<getCategory1().size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
            beginEditCP(PhysicsSpacePtr(this), Category1FieldMask | Category2FieldMask | CategoryCollisionParametersFieldMask);
                MFUInt64::iterator Cat1Itor(getCategory1().begin() + i);
                MFUInt64::iterator Cat2Itor(getCategory2().begin() + i);
                MFCollisionContactParametersPtr::iterator CatParamsItor(getCategoryCollisionParameters().begin() + i);

                getCategory1().erase(Cat1Itor);
                getCategory2().erase(Cat2Itor);
                getCategoryCollisionParameters().erase(CatParamsItor);
            endEditCP(PhysicsSpacePtr(this), Category1FieldMask | Category2FieldMask | CategoryCollisionParametersFieldMask);
        }
    }
}

CollisionContactParametersPtr PhysicsSpace::getCollisionContactCategory(UInt64 Category1, UInt64 Category2)
{
    for(UInt32 i(0) ; i<getCategory1().size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
            return getCategoryCollisionParameters(i);
        }
    }
    return NullFC;
}

CollisionContactParametersPtr PhysicsSpace::getCollisionContact(UInt64 Category1, UInt64 Category2)
{
    CollisionContactParametersPtr Params(getCollisionContactCategory(Category1, Category2));
    if(Params != NullFC)
    {
        return Params;
    }
    else
    {
        return getDefaultCollisionParameters();
    }
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
dSpaceID PhysicsSpace::getSpaceID(void) const
{
    return _SpaceID;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsSpace::initSpace()
{
    setCleanup(PhysicsSpaceBase::getCleanup());
}
void PhysicsSpace::AddGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceAdd(tmpPtr->_SpaceID, g);
}

void PhysicsSpace::RemoveGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceRemove(tmpPtr->_SpaceID, g);
}

bool PhysicsSpace::ContainsGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceQuery(tmpPtr->_SpaceID, g) == 1;
}

void PhysicsSpace::AddSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceAdd(tmpPtr->_SpaceID, (dGeomID)s);
}

void PhysicsSpace::RemoveSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceRemove(tmpPtr->_SpaceID, (dGeomID)s);
}

bool PhysicsSpace::ContainsSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceQuery(tmpPtr->_SpaceID, (dGeomID)s) == 1;
}

Int32 PhysicsSpace::GetNumGeoms()
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceGetNumGeoms(tmpPtr->_SpaceID);
}

dGeomID PhysicsSpace::GetGeom( Int32 i )
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceGetGeom(tmpPtr->_SpaceID, i);
}

void PhysicsSpace::Collide( PhysicsWorldPtr w )
{
    _CollideWorldID = w->getWorldID();

    
    //free contact Joints
    dJointGroupEmpty(_ColJointGroupId);

	PhysicsSpacePtr tmpPtr(*this);
	dSpaceCollide(tmpPtr->_SpaceID, reinterpret_cast<void *>(this), &PhysicsSpace::collisionCallback);
}

void PhysicsSpace::produceCollision(const Pnt3f& Position,const Vec3f& Normal, PhysicsGeomPtr Geom1,PhysicsGeomPtr Geom2,const Vec3f& Velocity1,const Vec3f& Velocity2,const Real32& ProjectedNormalSpeed)
{
    const CollisionEventPtr TheEvent = CollisionEvent::create( PhysicsSpacePtr(this), getSystemTime(), Position, Normal, Geom1, Geom2,Velocity1,Velocity2,ProjectedNormalSpeed);
	CollisionListenerSet Listeners(_CollisionListeners);
    for(CollisionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->collision(TheEvent);
    }
    _Producer.produceEvent(CollisionMethodId,TheEvent);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsSpace::produceCollision(CollisionListenerPtr _Listener, const Pnt3f& Position,const Vec3f& Normal, PhysicsGeomPtr Geom1,PhysicsGeomPtr Geom2,const Vec3f& Velocity1,const Vec3f& Velocity2,const Real32& ProjectedNormalSpeed)
{
    const CollisionEventPtr TheEvent = CollisionEvent::create( PhysicsSpacePtr(this), getSystemTime(), Position, Normal, Geom1, Geom2,Velocity1,Velocity2,ProjectedNormalSpeed);
    _Listener->collision(TheEvent);
   _Producer.produceEvent(CollisionMethodId,TheEvent);
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsSpace::PhysicsSpace(void) :
    Inherited()
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);

    if(getDefaultCollisionParameters() == NullFC)
    {
        beginEditCP(PhysicsSpacePtr(), DefaultCollisionParametersFieldMask);
            setDefaultCollisionParameters(createDefaultContactParams());
        endEditCP(PhysicsSpacePtr(), DefaultCollisionParametersFieldMask);
    }
}

PhysicsSpace::PhysicsSpace(const PhysicsSpace &source) :
    Inherited(source)
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);
}

PhysicsSpace::~PhysicsSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & CleanupFieldMask)
    {
	    dSpaceSetCleanup(_SpaceID, getCleanup() ? 1 : 0);
    }
    if(whichField & SublevelFieldMask)
    {
	    dSpaceSetSublevel(_SpaceID, getSublevel());
    }
}

void PhysicsSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSpace NI" << std::endl;
}

