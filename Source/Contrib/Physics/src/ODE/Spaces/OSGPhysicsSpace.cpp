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

#include "OSGPhysicsSpace.h"
#include "OSGStatCollector.h"
#include "rapidxml.h"
#include "rapidxml_iterators.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsSpaceBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsSpace.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
bool PhysicsSpace::registerXMLHandler(void)
{
    return XMLFCFileType::the()->registerHandler(&PhysicsSpace::getClassType(),boost::bind(&OSG::PhysicsSpace::xmlReadHandler,_1,_2,_3),boost::bind(&OSG::PhysicsSpace::xmlWriteHandler,_1));
}

void PhysicsSpace::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPre)
    {
        //addPostFactoryInitFunction(boost::bind(&PhysicsSpace::registerXMLHandler));
    }
}

void PhysicsSpace::collisionCallback (void *data, dGeomID o1, dGeomID o2)
{
    reinterpret_cast<PhysicsSpace*>(data)->collisionCallback(o1,o2);
}

bool PhysicsSpace::xmlReadHandler (rapidxml::xml_node<char>& PhysicsSpaceRoot, const XMLFCFileType::IDLookupMap& TheLookupMap, const FieldContainerUnrecPtr& PhysicsSpaceFC)
{
    //Space Object
    PhysicsSpaceUnrecPtr TheSpace = dynamic_pointer_cast<PhysicsSpace>(PhysicsSpaceFC);

    //Activity
    ActivityUnrecPtr TheActivity;
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
	return false;
}

bool PhysicsSpace::xmlWriteHandler (const FieldContainerUnrecPtr& PhysicsSpaceFC)
{
    //TODO: Implement
	return false;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsSpace::onCreate(const PhysicsSpace *id)
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

boost::signals2::connection PhysicsSpace::connectCollision(const CollisionEventType::slot_type &listener, 
                                                           UInt64 Category,
                                                           Real32 SpeedThreshold,
                                                           boost::signals2::connect_position at)
{
    CollisionListenParams newParams(Category, SpeedThreshold, &listener);
    _CollisionListenParamsVec.push_back(newParams);

    return Inherited::connectCollision(listener,at);
}

boost::signals2::connection PhysicsSpace::connectCollision(const CollisionEventType::group_type &group,
                                                           const CollisionEventType::slot_type &listener, 
                                                           UInt64 Category,
                                                           Real32 SpeedThreshold,
                                                           boost::signals2::connect_position at)
{
    CollisionListenParams newParams(Category, SpeedThreshold, &listener);
    _CollisionListenParamsVec.push_back(newParams);

   return Inherited::connectCollision(group, listener, at);
}

void PhysicsSpace::collisionCallback (dGeomID o1, dGeomID o2)
{
    StatRealElem *NCollisionTestsStatElem = StatCollector::getGlobalElem(PhysicsHandler::statNCollisionTests);
    if(NCollisionTestsStatElem) { NCollisionTestsStatElem->add(1.0f); }

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
        _DiscardCollision = false;

        // colliding two non-space geoms, so generate contact
        // points between o1 and o2
        Int32 numContacts = dCollide(o1, o2, _ContactJoints.size(), 
            &(_ContactJoints[0].geom), sizeof(dContact));
    
        StatRealElem *NCollisionsStatElem = StatCollector::getGlobalElem(PhysicsHandler::statNCollisions);
        if(NCollisionsStatElem) { NCollisionsStatElem->add(static_cast<Real32>(numContacts)); }

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

            //TODO: Add a way to get the PhysicsGeomUnrecPtr from the GeomIDs so that the PhysicsGeomUnrecPtr can be 
            //sent to the collision event
            produceCollision(position,
                                normal,
                                NULL,
                                NULL,
                                dGeomGetCategoryBits(o1),
                                dGeomGetCollideBits (o1),
                                dGeomGetCategoryBits(o2),
                                dGeomGetCollideBits (o2),
                                v1,
                                v2,
                                osgAbs(projectedNormalSpeed));

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
                         (osgAbs(projectedNormalSpeed) >= _CollisionListenParamsVec[i]._SpeedThreshold)
                        )
                    {
                        //TODO: Add a way to get the PhysicsGeomUnrecPtr from the GeomIDs so that the PhysicsGeomUnrecPtr can be 
                        //sent to the collision event
                        produceCollision(_CollisionListenParamsVec[i]._Listener,
                                position,
                                normal,
                                NULL,
                                NULL,
                                dGeomGetCategoryBits(o1),
                                dGeomGetCollideBits (o1),
                                dGeomGetCategoryBits(o2),
                                dGeomGetCollideBits (o2),
                                v1,
                                v2,
                                osgAbs(projectedNormalSpeed));
                    }
                }
            }
        }
        if(!_DiscardCollision)
        {
            // add these contact points to the simulation
            for (Int32 i=0; i < numContacts; i++)
            {

                getCollisionContact(dGeomGetCategoryBits(o1), dGeomGetCategoryBits(o2))->updateODEContactJoint(_ContactJoints[i]);
                dJointID jointId = dJointCreateContact(_CollideWorldID, 
                    _ColJointGroupId, 
                    &_ContactJoints[i]);

                dJointAttach(jointId, dGeomGetBody(o1), dGeomGetBody(o2));
            }
        }
    }
}

void PhysicsSpace::setSpaceID(dSpaceID id)
{
    _SpaceID = id;
}

CollisionContactParametersTransitPtr PhysicsSpace::createDefaultContactParams(void) const
{
    CollisionContactParameters* Params = CollisionContactParameters::createEmpty();
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

    return CollisionContactParametersTransitPtr(Params);
}

void PhysicsSpace::addCollisionContactCategory(UInt64 Category1, UInt64 Category2, CollisionContactParameters* const ContactParams)
{
    for(UInt32 i(0) ; i<getMFCategory1()->size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
                (*editMFCategoryCollisionParameters())[i] = ContactParams;
            return;
        }
    }

        editMFCategory1()->push_back(Category1);
        editMFCategory2()->push_back(Category2);
        pushToCategoryCollisionParameters(ContactParams);

}

void PhysicsSpace::removeCollisionContactCategory(UInt64 Category1, UInt64 Category2)
{
    for(UInt32 i(0) ; i<getMFCategory1()->size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
                MFUInt64::iterator Cat1Itor(editMFCategory1()->begin() + i);
                MFUInt64::iterator Cat2Itor(editMFCategory2()->begin() + i);

                editMFCategory1()->erase(Cat1Itor);
                editMFCategory2()->erase(Cat2Itor);
                removeFromCategoryCollisionParameters(i);
        }
    }
}

CollisionContactParameters* PhysicsSpace::getCollisionContactCategory(UInt64 Category1, UInt64 Category2)
{
    for(UInt32 i(0) ; i<getMFCategory1()->size() ; ++i)
    {
        if((getCategory1(i) == Category1 && getCategory2(i) == Category2) || (getCategory1(i) == Category2 && getCategory2(i) == Category1))
        {
            return getCategoryCollisionParameters(i);
        }
    }
    return NULL;
}

CollisionContactParameters* PhysicsSpace::getCollisionContact(UInt64 Category1, UInt64 Category2)
{
    CollisionContactParametersUnrecPtr Params(getCollisionContactCategory(Category1, Category2));
    if(Params != NULL)
    {
        return Params;
    }
    else
    {
        return getDefaultCollisionParameters();
    }
}

dSpaceID PhysicsSpace::getSpaceID(void) const
{
    return _SpaceID;
}

void PhysicsSpace::initSpace()
{
    setCleanup(PhysicsSpaceBase::getCleanup());
}

void PhysicsSpace::AddGeom( dGeomID g)
{
	dSpaceAdd(_SpaceID, g);
}

void PhysicsSpace::RemoveGeom( dGeomID g)
{
	dSpaceRemove(_SpaceID, g);
}

bool PhysicsSpace::ContainsGeom( dGeomID g)
{
	return dSpaceQuery(_SpaceID, g) == 1;
}

void PhysicsSpace::AddSpace( dSpaceID s)
{
	dSpaceAdd(_SpaceID, (dGeomID)s);
}

void PhysicsSpace::RemoveSpace( dSpaceID s)
{
	dSpaceRemove(_SpaceID, (dGeomID)s);
}

bool PhysicsSpace::ContainsSpace( dSpaceID s)
{
	return dSpaceQuery(_SpaceID, (dGeomID)s) == 1;
}

Int32 PhysicsSpace::GetNumGeoms()
{
	return dSpaceGetNumGeoms(_SpaceID);
}

dGeomID PhysicsSpace::GetGeom( Int32 i )
{
	return dSpaceGetGeom(_SpaceID, i);
}

void PhysicsSpace::Collide( PhysicsWorld* const w )
{
    _CollideWorldID = w->getWorldID();

    
    //free contact Joints
    dJointGroupEmpty(_ColJointGroupId);

	dSpaceCollide(_SpaceID, reinterpret_cast<void *>(this), &PhysicsSpace::collisionCallback);
}

void PhysicsSpace::produceCollision(const Pnt3f& Position,
                                    const Vec3f& Normal, 
                                    PhysicsGeom* const Geom1,
                                    PhysicsGeom* const Geom2,
                                    UInt64 Geom1Cat,
                                    UInt64 Geom1Col,
                                    UInt64 Geom2Cat,
                                    UInt64 Geom2Col,
                                    const Vec3f& Velocity1,
                                    const Vec3f& Velocity2,
                                    const Real32& ProjectedNormalSpeed)
{                           
    CollisionEventDetailsUnrecPtr Details = CollisionEventDetails::create(this,
                                                                          getTimeStamp(),
                                                                          Position,
                                                                          Normal,
                                                                          Geom1,
                                                                          Geom2,
                                                                          Geom1Cat,
                                                                          Geom1Col,
                                                                          Geom2Cat,
                                                                          Geom2Col,
                                                                          Velocity1,
                                                                          Velocity2,
                                                                          ProjectedNormalSpeed);
   
    Inherited::produceCollision(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsSpace::produceCollision(const CollisionEventType::slot_type* listener, 
                                    const Pnt3f& Position,
                                    const Vec3f& Normal, 
                                    PhysicsGeom* const Geom1,
                                    PhysicsGeom* const Geom2,
                                    UInt64 Geom1Cat,
                                    UInt64 Geom1Col,
                                    UInt64 Geom2Cat,
                                    UInt64 Geom2Col,
                                    const Vec3f& Velocity1,
                                    const Vec3f& Velocity2,
                                    const Real32& ProjectedNormalSpeed)
{
    CollisionEventDetailsUnrecPtr Details = CollisionEventDetails::create(this,
                                                                          getTimeStamp(),
                                                                          Position,
                                                                          Normal,
                                                                          Geom1,
                                                                          Geom2,
                                                                          Geom1Cat,
                                                                          Geom1Col,
                                                                          Geom2Cat,
                                                                          Geom2Col,
                                                                          Velocity1,
                                                                          Velocity2,
                                                                          ProjectedNormalSpeed);

    (*listener)(Details, CollisionEventId);
   
    Inherited::produceCollision(Details);
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsSpace::PhysicsSpace(void) :
    Inherited()
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);

    if(getDefaultCollisionParameters() == NULL)
    {
        CollisionContactParametersUnrecPtr DefaultParams(createDefaultContactParams());
        setDefaultCollisionParameters(DefaultParams);
    }
}

PhysicsSpace::PhysicsSpace(const PhysicsSpace &source) :
    Inherited(source)
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);

    if(getDefaultCollisionParameters() == NULL)
    {
        CollisionContactParametersUnrecPtr DefaultParams(createDefaultContactParams());
        setDefaultCollisionParameters(DefaultParams);
    }
}

PhysicsSpace::~PhysicsSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSpace::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

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

OSG_END_NAMESPACE
