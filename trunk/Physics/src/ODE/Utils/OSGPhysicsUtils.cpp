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
