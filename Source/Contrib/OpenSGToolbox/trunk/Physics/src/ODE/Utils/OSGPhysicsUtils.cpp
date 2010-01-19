#include "OSGPhysicsUtils.h"

OSG_BEGIN_NAMESPACE

PhysicsHandlerFinder::PhysicsHandlerFinder(void) :
    _found()
{
}

PhysicsHandlerPtr PhysicsHandlerFinder::operator() (NodePtr root)
{
    _found=NullFC;

    traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef(
        this, 
        &PhysicsHandlerFinder::check));

    return _found;
}

PhysicsHandlerPtr PhysicsHandlerFinder::find(NodePtr root)
{
    PhysicsHandlerFinder f;      

    return f(root);
}

Action::ResultE PhysicsHandlerFinder::check(NodePtr& node)
{
    AttachmentPtr a = node->findAttachment(PhysicsHandler::getClassType());
    if(a!=NullFC)
    {
        _found = PhysicsHandlerPtr::dcast(a);
        return Action::Quit;
    }
    return Action::Continue;        
}

// ------------------------------------------------

PhysicsGeometryFinder::PhysicsGeometryFinder(void) :
    _found()
{
}

NodePtr PhysicsGeometryFinder::operator() (NodePtr root)
{
    _found=NullFC;

    traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef(
        this, 
        &PhysicsGeometryFinder::check));

    return _found;
}

NodePtr PhysicsGeometryFinder::find(NodePtr root)
{
    PhysicsGeometryFinder f;      

    return f(root);
}

Action::ResultE PhysicsGeometryFinder::check(NodePtr& node)
{
    GeometryPtr triGeo = GeometryPtr::dcast(node->getCore()); 
    if(triGeo!=NullFC)
    {
        _found = node;
        return Action::Quit;
    }
    return Action::Continue;        
}

// ------------------------------------------------

PhysicsAttachmentsFinder::PhysicsAttachmentsFinder(void){
}

void PhysicsAttachmentsFinder::traverse(NodePtr root)
{
    _FoundHandlers.clear();
    _FoundWorlds.clear();
    _FoundGeoms.clear();
    _FoundSpaces.clear();
    _FoundBodies.clear();
    _FoundJoints.clear();

    osg::traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef(
        this, 
        &PhysicsAttachmentsFinder::check));
}

Action::ResultE PhysicsAttachmentsFinder::check(NodePtr& node)
{
    AttachmentPtr Att;
    //Loop through all of the attachments on this node
    for(AttachmentMap::iterator MapItor(node->getSFAttachments()->getValue().begin())
            ; MapItor != node->getSFAttachments()->getValue().end()
            ; ++MapItor)
    {
        //Check for Physics Handlers
        if(MapItor->second->getType().isDerivedFrom(PhysicsHandler::getClassType()))
        {
            _FoundHandlers.push_back(PhysicsHandlerPtr::dcast(MapItor->second));
        }

        //Check for Physics Worlds
        if(MapItor->second->getType().isDerivedFrom(PhysicsWorld::getClassType()))
        {
            _FoundWorlds.push_back(PhysicsWorldPtr::dcast(MapItor->second));
        }

        //Check for Physics Geoms
        if(MapItor->second->getType().isDerivedFrom(PhysicsGeom::getClassType()))
        {
            _FoundGeoms.push_back(PhysicsGeomPtr::dcast(MapItor->second));
        }

        //Check for Physics Spaces
        if(MapItor->second->getType().isDerivedFrom(PhysicsSpace::getClassType()))
        {
            _FoundSpaces.push_back(PhysicsSpacePtr::dcast(MapItor->second));
        }

        //Check for Physics Bodies
        if(MapItor->second->getType().isDerivedFrom(PhysicsBody::getClassType()))
        {
            _FoundBodies.push_back(PhysicsBodyPtr::dcast(MapItor->second));

            //Get the Physics Joints
            std::vector<PhysicsJointPtr> Joints(PhysicsBodyPtr::dcast(MapItor->second)->getJoints());
            for(UInt32 i(0) ; i<Joints.size() ; ++i)
            {
                _FoundJoints.push_back(Joints[i]);
            }
        }
    }

    return Action::Continue;        
}

const std::vector<PhysicsHandlerPtr>&  PhysicsAttachmentsFinder::getFoundHandlers(void) const
{
    return _FoundHandlers;        
}

const std::vector<PhysicsWorldPtr>&    PhysicsAttachmentsFinder::getFoundWorlds(void) const
{
    return _FoundWorlds;        
}

const std::vector<PhysicsGeomPtr>&     PhysicsAttachmentsFinder::getFoundGeoms(void) const
{
    return _FoundGeoms;        
}

const std::vector<PhysicsSpacePtr>&    PhysicsAttachmentsFinder::getFoundSpaces(void) const
{
    return _FoundSpaces;        
}

const std::vector<PhysicsBodyPtr>&     PhysicsAttachmentsFinder::getFoundBodies(void) const
{
    return _FoundBodies;        
}

const std::vector<PhysicsJointPtr>&    PhysicsAttachmentsFinder::getFoundJoints(void) const
{
    return _FoundJoints;        
}


Vec3f calcMinGeometryBounds(GeometryPtr geo)
{
    if(geo == NullFC ||
       geo->getPositions() == NullFC ||
       geo->getPositions()->size() == 0)
    {
        return Vec3f();
    }

    GeoPositionsPtr Positions(geo->getPositions());

    Pnt3f Min(Positions->getValue(0)), 
        Max(Positions->getValue(0));


    for(UInt32 i(1) ; i<Positions->size(); ++i)
    {
        Min[0] = osgMin(Min[0], Positions->getValue(i)[0]);
        Min[1] = osgMin(Min[1], Positions->getValue(i)[1]);
        Min[2] = osgMin(Min[2], Positions->getValue(i)[2]);

        Max[0] = osgMax(Max[0], Positions->getValue(i)[0]);
        Max[1] = osgMax(Max[1], Positions->getValue(i)[1]);
        Max[2] = osgMax(Max[2], Positions->getValue(i)[2]);
    }

    return Max-Min;
}

Pnt3f calcGeometryCenter(GeometryPtr geo)
{
    if(geo == NullFC ||
       geo->getPositions() == NullFC ||
       geo->getPositions()->size() == 0)
    {
        return Pnt3f();
    }

    GeoPositionsPtr Positions(geo->getPositions());

    Pnt3f Sum;


    for(UInt32 i(1) ; i<Positions->size(); ++i)
    {
        Sum = Sum + Vec3f(Positions->getValue(i));
    }

    return Sum * (1.0f/static_cast<Real32>(Positions->size()));
}

OSG_END_NAMESPACE
