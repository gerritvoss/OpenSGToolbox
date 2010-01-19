#include "OSGPhysicsUtils.h"
#include "OSGAction.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

PhysicsHandlerFinder::PhysicsHandlerFinder(void) :
    _found()
{
}

PhysicsHandlerUnrecPtr PhysicsHandlerFinder::operator() (NodeUnrecPtr root)
{
    _found=NULL;

    traverse(root, boost::bind(&PhysicsHandlerFinder::check,
        this, _1
        ));

    return _found;
}

PhysicsHandlerUnrecPtr PhysicsHandlerFinder::find(NodeUnrecPtr root)
{
    PhysicsHandlerFinder f;      

    return f(root);
}

Action::ResultE PhysicsHandlerFinder::check(Node*& node)
{
    AttachmentUnrecPtr a = node->findAttachment(PhysicsHandler::getClassType());
    if(a!=NULL)
    {
        _found = dynamic_pointer_cast<PhysicsHandler>(a);
        return Action::Quit;
    }
    return Action::Continue;        
}

// ------------------------------------------------

PhysicsGeometryFinder::PhysicsGeometryFinder(void) :
    _found()
{
}

NodeUnrecPtr PhysicsGeometryFinder::operator() (NodeUnrecPtr root)
{
    _found=NULL;

    traverse(root, boost::bind(&PhysicsGeometryFinder::check,
        this, _1
        ));

    return _found;
}

NodeUnrecPtr PhysicsGeometryFinder::find(NodeUnrecPtr root)
{
    PhysicsGeometryFinder f;      

    return f(root);
}

Action::ResultE PhysicsGeometryFinder::check(Node*& node)
{
    GeometryUnrecPtr triGeo = dynamic_cast<Geometry*>(node->getCore()); 
    if(triGeo!=NULL)
    {
        _found = node;
        return Action::Quit;
    }
    return Action::Continue;        
}

// ------------------------------------------------

PhysicsAttachmentsFinder::PhysicsAttachmentsFinder(void){
}

void PhysicsAttachmentsFinder::traverse(NodeUnrecPtr root)
{
    _FoundHandlers.clear();
    _FoundWorlds.clear();
    _FoundGeoms.clear();
    _FoundSpaces.clear();
    _FoundBodies.clear();
    _FoundJoints.clear();

    OSG::traverse(root, boost::bind(&PhysicsAttachmentsFinder::check,
        this, _1
        ));
}

Action::ResultE PhysicsAttachmentsFinder::check(Node*& node)
{
    AttachmentUnrecPtr Att;
    //Loop through all of the attachments on this node
    for(AttachmentMap::const_iterator MapItor(node->getSFAttachments()->getValue().begin())
            ; MapItor != node->getSFAttachments()->getValue().end()
            ; ++MapItor)
    {
        //Check for Physics Handlers
        if(MapItor->second->getType().isDerivedFrom(PhysicsHandler::getClassType()))
        {
            _FoundHandlers.push_back(dynamic_cast<const PhysicsHandler*>(MapItor->second));
        }

        //Check for Physics Worlds
        if(MapItor->second->getType().isDerivedFrom(PhysicsWorld::getClassType()))
        {
            _FoundWorlds.push_back(dynamic_cast<const PhysicsWorld*>(MapItor->second));
        }

        //Check for Physics Geoms
        if(MapItor->second->getType().isDerivedFrom(PhysicsGeom::getClassType()))
        {
            _FoundGeoms.push_back(dynamic_cast<const PhysicsGeom*>(MapItor->second));
        }

        //Check for Physics Spaces
        if(MapItor->second->getType().isDerivedFrom(PhysicsSpace::getClassType()))
        {
            _FoundSpaces.push_back(dynamic_cast<const PhysicsSpace*>(MapItor->second));
        }

        //Check for Physics Bodies
        if(MapItor->second->getType().isDerivedFrom(PhysicsBody::getClassType()))
        {
            _FoundBodies.push_back(dynamic_cast<const PhysicsBody*>(MapItor->second));

            //Get the Physics Joints
            std::vector<PhysicsJointUnrecPtr> Joints(dynamic_cast<PhysicsBody*>(MapItor->second)->getJoints());
            for(UInt32 i(0) ; i<Joints.size() ; ++i)
            {
                _FoundJoints.push_back(Joints[i].get());
            }
        }
    }

    return Action::Continue;        
}

const std::vector<const PhysicsHandler*>&  PhysicsAttachmentsFinder::getFoundHandlers(void) const
{
    return _FoundHandlers;        
}

const std::vector<const PhysicsWorld*>&    PhysicsAttachmentsFinder::getFoundWorlds(void) const
{
    return _FoundWorlds;        
}

const std::vector<const PhysicsGeom*>&     PhysicsAttachmentsFinder::getFoundGeoms(void) const
{
    return _FoundGeoms;        
}

const std::vector<const PhysicsSpace*>&    PhysicsAttachmentsFinder::getFoundSpaces(void) const
{
    return _FoundSpaces;        
}

const std::vector<const PhysicsBody*>&     PhysicsAttachmentsFinder::getFoundBodies(void) const
{
    return _FoundBodies;        
}

const std::vector<const PhysicsJoint*>&    PhysicsAttachmentsFinder::getFoundJoints(void) const
{
    return _FoundJoints;        
}


Vec3f calcMinGeometryBounds(GeometryUnrecPtr geo)
{
    if(geo == NULL ||
       geo->getPositions() == NULL ||
       geo->getPositions()->size() == 0)
    {
        return Vec3f();
    }

    GeoVectorProperty* Positions(geo->getPositions());

    Pnt3f Min(Positions->getValue<Pnt3f>(0)), 
        Max(Positions->getValue<Pnt3f>(0));


    for(UInt32 i(1) ; i<Positions->size(); ++i)
    {
        Min[0] = osgMin(Min[0], Positions->getValue<Pnt3f>(i)[0]);
        Min[1] = osgMin(Min[1], Positions->getValue<Pnt3f>(i)[1]);
        Min[2] = osgMin(Min[2], Positions->getValue<Pnt3f>(i)[2]);

        Max[0] = osgMax(Max[0], Positions->getValue<Pnt3f>(i)[0]);
        Max[1] = osgMax(Max[1], Positions->getValue<Pnt3f>(i)[1]);
        Max[2] = osgMax(Max[2], Positions->getValue<Pnt3f>(i)[2]);
    }

    return Max-Min;
}

Pnt3f calcGeometryCenter(GeometryUnrecPtr geo)
{
    if(geo == NULL ||
       geo->getPositions() == NULL ||
       geo->getPositions()->size() == 0)
    {
        return Pnt3f();
    }

    GeoVectorProperty* Positions(geo->getPositions());

    Pnt3f Sum;


    for(UInt32 i(1) ; i<Positions->size(); ++i)
    {
        Sum = Sum + Vec3f(Positions->getValue<Pnt3f>(i));
    }

    return Sum * (1.0f/static_cast<Real32>(Positions->size()));
}

OSG_END_NAMESPACE
