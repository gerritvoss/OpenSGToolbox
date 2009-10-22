#include "OSGPhysicsGeomDrawFuncs.h"
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGRenderAction.h>
#include "ODE/OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsGeom(const PhysicsBoxGeomPtr geom)
{
    Pnt3f p1(geom->getLengths() * 0.5),
          p2(-p1);
    
    //Transform by the bodies position and rotation
    Matrix m(geom->getBody()->getTransformation());
    
    m.mult(p1);
    m.mult(p2);

    //TODO: Implement Draw as quads
    glBegin(GL_LINE_LOOP);
        glVertex3f(p1[0], p1[1], p1[2]);   
        glVertex3f(p2[0], p1[1], p1[2]);   
        glVertex3f(p2[0], p2[1], p1[2]);   
        glVertex3f(p1[0], p2[1], p1[2]);   
        glVertex3f(p1[0], p1[1], p1[2]);   
        glVertex3f(p1[0], p1[1], p2[2]);   
        glVertex3f(p2[0], p1[1], p2[2]);   
        glVertex3f(p2[0], p2[1], p2[2]);   
        glVertex3f(p1[0], p2[1], p2[2]);   
        glVertex3f(p1[0], p1[1], p2[2]);   
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(p1[0], p2[1], p1[2]);   
        glVertex3f(p1[0], p2[1], p2[2]);   
        glVertex3f(p2[0], p2[1], p1[2]);   
        glVertex3f(p2[0], p2[1], p2[2]);   
        glVertex3f(p2[0], p1[1], p1[2]);   
        glVertex3f(p2[0], p1[1], p2[2]);   
    glEnd();
}

void drawPhysicsGeom(const PhysicsCapsuleGeomPtr geom)
{
    //TODO: Implement
}

void drawPhysicsGeom(const PhysicsPlaneGeomPtr geom)
{
    Vec3f n(geom->getParameters().x(),geom->getParameters().y(), geom->getParameters().z());
    Pnt3f p(Pnt3f(0.0,0.0,0.0) + n*geom->getParameters().w());

    //Calculate vectors that are perpendicular to the planes normal
    Vec3f t(1.0,0.0,0.0);
    if(n.dot(t) < 0.001)
    {
        t.setValues(0.0,1.0,0.0);
    }

    Vec3f b(n.cross(t));
    t = b.cross(n);

    Real32 Length(100000.0);

    t *= Length;
    b *= Length;

    Pnt3f p1(p + t + b),
          p2(p - t + b),
          p3(p - t - b),
          p4(p + t - b);
    
    //Front Side
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3fv(p1.getValues());
        glVertex3fv(p2.getValues());
        glVertex3fv(p3.getValues());
        glVertex3fv(p4.getValues());
    glEnd();

    //Back side
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3fv(p1.getValues());
        glVertex3fv(p4.getValues());
        glVertex3fv(p3.getValues());
        glVertex3fv(p2.getValues());
    glEnd();
}

void drawPhysicsGeom(const PhysicsRayGeomPtr geom)
{
    Pnt3f p1(geom->getPosition());
    Pnt3f p2(p1 + Vec3f(0.0,0.0,geom->getLength()));

    //Transform by the bodies position and rotation
    Matrix m(geom->getBody()->getTransformation());
    
    m.mult(p1);
    m.mult(p2);

    
    glBegin(GL_LINES);
        glVertex3fv(p1.getValues());   
        glVertex3fv(p2.getValues());
    glEnd();
}

void drawPhysicsGeom(const PhysicsSphereGeomPtr geom)
{
    //TODO: Implement
}

void drawPhysicsGeom(const PhysicsTriMeshGeomPtr geom)
{
    //TODO: Implement
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
class PhysicsGeomDrawWrapper
{
  public:
    PhysicsGeomDrawWrapper(const PhysicsGeomPtr geom, Color4f col, MaterialPtr mat) : 
        _geom(geom), _col(col), _mat(mat)
    {
        if(_mat == NullFC)
        {
            _mat = getDefaultUnlitMaterial();
        }
    }
    
    ~PhysicsGeomDrawWrapper()
    {}

    static void drop(DrawActionBase* action,const PhysicsGeomPtr geom, const Color4f& col, MaterialPtr mat)
    {
        PhysicsGeomDrawWrapper * vdw = new PhysicsGeomDrawWrapper(geom, col, mat);

        Material::DrawFunctor func;
        func = osgTypedMethodFunctor1ObjPtr(vdw, &PhysicsGeomDrawWrapper::draw);
    
        RenderAction *ra = dynamic_cast<RenderAction*>(action);
        
        ra->dropFunctor(func, getCPtr(vdw->_mat));
    }
    
  private:
  
    Action::ResultE draw(DrawActionBase *)
    {
        glColor4fv(_col.getValuesRGBA());
        
        if(_geom->getType() == PhysicsBoxGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsBoxGeom::Ptr::dcast(_geom));
        }
        else if(_geom->getType() == PhysicsCapsuleGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsCapsuleGeom::Ptr::dcast(_geom));
        }
        else if(_geom->getType() == PhysicsPlaneGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsPlaneGeom::Ptr::dcast(_geom));
        }
        else if(_geom->getType() == PhysicsRayGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsRayGeom::Ptr::dcast(_geom));
        }
        else if(_geom->getType() == PhysicsSphereGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsSphereGeom::Ptr::dcast(_geom));
        }
        else if(_geom->getType() == PhysicsTriMeshGeom::getClassType())
        {
            drawPhysicsGeom(PhysicsTriMeshGeom::Ptr::dcast(_geom));
        }
        
        // self-destruct
        delete this;
        
        return Action::Continue;
    }

    PhysicsGeomPtr _geom;
    Color4f _col; 
    MaterialPtr _mat; 
};

void dropPhysicsGeom(DrawActionBase* action,const PhysicsGeomPtr geom, const Color4f& col, MaterialPtr mat)
{
    PhysicsGeomDrawWrapper::drop(action, geom, col, mat);
}

OSG_END_NAMESPACE
