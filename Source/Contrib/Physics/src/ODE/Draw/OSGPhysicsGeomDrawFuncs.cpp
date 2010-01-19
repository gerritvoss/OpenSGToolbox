#include "OSGPhysicsGeomDrawFuncs.h"
#include "OSGGL.h"
#include "OSGSimpleGeometry.h"
#include "OSGRenderAction.h"
#include "OSGPhysicsBody.h"
#include "OSGMaterial.h"
#include "OSGPrimeMaterial.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsGeom(const PhysicsBoxGeomUnrecPtr geom)
{
    Pnt3f p111(geom->getLengths() * 0.5),
          p000(-p111),
          p001(p000.x(), p000.y(), p111.z()),
          p010(p000.x(), p111.y(), p000.z()),
          p011(p000.x(), p111.y(), p111.z()),
          p100(p111.x(), p000.y(), p000.z()),
          p101(p111.x(), p000.y(), p111.z()),
          p110(p111.x(), p111.y(), p000.z());
    
    //Transform by the bodies position and rotation
    Matrix m(geom->getTransformation());
    
    m.mult(p000,p000);
    m.mult(p001,p001);
    m.mult(p010,p010);
    m.mult(p011,p011);
    m.mult(p100,p100);
    m.mult(p101,p101);
    m.mult(p110,p110);
    m.mult(p111,p111);

    glBegin(GL_QUADS);
        // Front Face
        glVertex3fv(p110.getValues());
        glVertex3fv(p100.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p010.getValues());

        // Back Face
        glVertex3fv(p111.getValues());
        glVertex3fv(p011.getValues());
        glVertex3fv(p001.getValues());
        glVertex3fv(p101.getValues());

        // Top Face
        glVertex3fv(p101.getValues());
        glVertex3fv(p001.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p100.getValues());
        
        // Bottom Face
        glVertex3fv(p111.getValues());
        glVertex3fv(p110.getValues());
        glVertex3fv(p010.getValues());
        glVertex3fv(p011.getValues());

        // Right face
        glVertex3fv(p011.getValues());
        glVertex3fv(p010.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p001.getValues());

        // Left Face
        glVertex3fv(p111.getValues());
        glVertex3fv(p101.getValues());
        glVertex3fv(p100.getValues());
        glVertex3fv(p110.getValues());
    glEnd();
}

void drawPhysicsGeom(const PhysicsCapsuleGeomUnrecPtr geom)
{
    Real32 Radius(geom->getRadius()),
           HalfLength(geom->getLength()*0.5f);

    Matrix m(geom->getTransformation());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(m.getValues());

    //Draw the Cylendar
    //ODE Capsules are aligned along the z-axis
    //with the center at the point of reference
    UInt32 Segments(16);
    Real32 x,y;
    Real32 TWO_PI(6.28318531f);
    glBegin(GL_TRIANGLE_STRIP);
        for(UInt32 i(0) ; i<=Segments ; ++i)
        {
            x = osgCos(static_cast<Real32>(i)/static_cast<Real32>(Segments) * TWO_PI);
            y = osgSin(static_cast<Real32>(i)/static_cast<Real32>(Segments)* TWO_PI);
            glNormal3f(x, y, 0);
            glVertex3f(Radius * x,Radius * y,HalfLength);
            glVertex3f(Radius * x,Radius * y,-HalfLength);
        }
    glEnd();

    //Draw the Caps
    int lats(12);
    int longs(12);

    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = Radius * sin(lat0);
        if(i>lats/2) z0 += HalfLength;
        else  z0 -= HalfLength;
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = Radius * sin(lat1);
        if(i>lats/2) z1 += HalfLength;
        else  z1 -= HalfLength;
        double zr1 = osgCos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = TWO_PI * (double) (j - 1) / longs;
            double x = Radius * cos(lng);
            double y = Radius * sin(lng);

            glVertex3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr0, y * zr0, z0);
        }
        glEnd();
    }
    
    glPopMatrix();
}

void drawPhysicsGeom(const PhysicsPlaneGeomUnrecPtr geom)
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
    
    glBegin(GL_QUADS);
        //Front Side
        glVertex3fv(p1.getValues());
        glVertex3fv(p2.getValues());
        glVertex3fv(p3.getValues());
        glVertex3fv(p4.getValues());

        //Back side
        glVertex3fv(p1.getValues());
        glVertex3fv(p4.getValues());
        glVertex3fv(p3.getValues());
        glVertex3fv(p2.getValues());
    glEnd();

}

void drawPhysicsGeom(const PhysicsRayGeomUnrecPtr geom)
{
    Pnt3f p1(geom->getPosition());
    Pnt3f p2(p1 + Vec3f(0.0,0.0,geom->getLength()));

    Matrix m(geom->getTransformation());
        
    m.mult(p1,p1);
    m.mult(p2,p2);

    
    glBegin(GL_LINES);
        glVertex3fv(p1.getValues());   
        glVertex3fv(p2.getValues());
    glEnd();
}

void drawPhysicsGeom(const PhysicsSphereGeomUnrecPtr geom)
{
    Pnt3f p(geom->getPosition());

    if(geom->getBody() != NULL)
    {
        //Transform by the bodies position and rotation
        Matrix m(geom->getBody()->getTransformation());
        m.mult(p,p);
    }
    double r(geom->getRadius());
    int lats(12);
    int longs(12);

    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = r * osgSin(lat0);
        double zr0 =  osgCos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = r * osgSin(lat1);
        double zr1 = osgCos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = r * osgCos(lng);
            double y = r * osgSin(lng);

            //glNormal3f(p.x() + x * zr1, p.y() + y * zr1, p.z() + z1);
            //glNormal3f(p.x() + x * zr0, p.y() + y * zr0, p.z() + z0);
            glVertex3f(p.x() + x * zr1, p.y() + y * zr1, p.z() + z1);
            glVertex3f(p.x() + x * zr0, p.y() + y * zr0, p.z() + z0);
        }
        glEnd();
    }

}

void drawPhysicsGeom(const PhysicsTriMeshGeomUnrecPtr geom)
{

    UInt32 TriCount(geom->getTriangleCount());
    Vec3f v1,v2,v3;

    glBegin(GL_TRIANGLES);
        for(UInt32 i(0) ; i<TriCount ; ++i)
        {
            //The Tris returned are already in world-space
            geom->getTriangle(i,v1,v2,v3);
            glVertex3fv(v1.getValues());
            glVertex3fv(v2.getValues());
            glVertex3fv(v3.getValues());
        }
    glEnd();

}

void dropPhysicsGeom(RenderAction* action,const NodeUnrecPtr node, const Color4f& col, MaterialUnrecPtr mat)
{
    //Get the Physics Geom object attached to this node, if there is one
    AttachmentUnrecPtr TheGeomAttachment(NULL);

    //Box
    TheGeomAttachment = node->findAttachment(PhysicsBoxGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }

    //Sphere
    TheGeomAttachment = node->findAttachment(PhysicsSphereGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }

    //Ray
    TheGeomAttachment = node->findAttachment(PhysicsRayGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }

    //Capsule
    TheGeomAttachment = node->findAttachment(PhysicsCapsuleGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }

    //Plane
    TheGeomAttachment = node->findAttachment(PhysicsPlaneGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }

    //TriMesh
    TheGeomAttachment = node->findAttachment(PhysicsTriMeshGeom::getClassType());
    if(TheGeomAttachment != NULL)
    {
        dropPhysicsGeom(action,dynamic_pointer_cast<PhysicsGeom>(TheGeomAttachment),col,mat);
    }
}

class PhysicsGeomDrawWrapper
{
  public:
    PhysicsGeomDrawWrapper(const PhysicsGeomUnrecPtr geom, Color4f col, MaterialUnrecPtr mat) : 
        _geom(geom), _col(col), _mat(mat)
    {
        if(_mat == NULL)
        {
            _mat = getDefaultUnlitMaterial();
        }
    }
    
    ~PhysicsGeomDrawWrapper()
    {}

    static void drop(RenderAction* action,const PhysicsGeomUnrecPtr geom, const Color4f& col, MaterialUnrecPtr mat)
    {
        PhysicsGeomDrawWrapper * vdw = new PhysicsGeomDrawWrapper(geom, col, mat);

        Material::DrawFunctor func;
        func = boost::bind(&PhysicsGeomDrawWrapper::draw, vdw, _1);
    
        action->dropFunctor(func, vdw->_mat);
    }
    
  private:
  
    Action::ResultE draw(DrawEnv *)
    {
        glColor4fv(_col.getValuesRGBA());
        
        if(_geom->getType() == PhysicsBoxGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsBoxGeom>(_geom));
        }
        else if(_geom->getType() == PhysicsCapsuleGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsCapsuleGeom>(_geom));
        }
        else if(_geom->getType() == PhysicsPlaneGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsPlaneGeom>(_geom));
        }
        else if(_geom->getType() == PhysicsRayGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsRayGeom>(_geom));
        }
        else if(_geom->getType() == PhysicsSphereGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsSphereGeom>(_geom));
        }
        else if(_geom->getType() == PhysicsTriMeshGeom::getClassType())
        {
            drawPhysicsGeom(dynamic_pointer_cast<PhysicsTriMeshGeom>(_geom));
        }
        
        // self-destruct
        delete this;
        
        return Action::Continue;
    }

    PhysicsGeomUnrecPtr _geom;
    Color4f _col; 
    MaterialUnrecPtr _mat; 
};

void dropPhysicsGeom(RenderAction* action,const PhysicsGeomUnrecPtr geom, const Color4f& col, MaterialUnrecPtr mat)
{
    PhysicsGeomDrawWrapper::drop(action, geom, col, mat);
}

OSG_END_NAMESPACE
