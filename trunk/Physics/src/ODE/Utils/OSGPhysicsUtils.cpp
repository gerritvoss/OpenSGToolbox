#include "OSGPhysicsUtils.h"

OSG_USING_NAMESPACE

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
