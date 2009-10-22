#include "OSGPhysicsDrawFuncs.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsGeom(const PhysicsBoxGeomPtr geom)
{
}

void drawPhysicsGeom(const PhysicsCapsuleGeomPtr geom)
{
}

void drawPhysicsGeom(const PhysicsPlaneGeomPtr geom)
{
}

void drawPhysicsGeom(const PhysicsRayGeomPtr geom)
{
}

void drawPhysicsGeom(const PhysicsSphereGeomPtr geom)
{
}

void drawPhysicsGeom(const PhysicsTriMeshGeomPtr geom)
{
}



void dropPhysicsGeom(DrawActionBase* action,const NodePtr node, const Color4f& col, MaterialPtr mat)
{
    //Get the Physics Geom object attached to this node, if there is one
    AttachmentPtr TheGeomAttachment(node->findAttachment(PhysicsGeom::getClassType()));
    

    if(TheGeomAttachment != NullFC)
    {
        //Call the drop function on this Geom
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }
}

void dropPhysicsGeom(DrawActionBase* action,const PhysicsGeomPtr geom, const Color4f& col, MaterialPtr mat)
{
    if(geom->getType() == PhysicsBoxGeom::getClassType())
    {
        drawPhysicsGeom(PhysicsBoxGeom::Ptr::dcast(geom));
    }
}

OSG_END_NAMESPACE
