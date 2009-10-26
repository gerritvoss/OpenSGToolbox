#include "OSGPhysicsGeomDrawFuncs.h"
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGRenderAction.h>
#include "ODE/OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsGeom(const PhysicsBoxGeomPtr geom)
{
    Pnt3f p111(geom->getLengths() * 0.5),
          p000(-p111),
          p001(p000.x(), p000.y(), p111.z()),
          p010(p000.x(), p111.y(), p000.z()),
          p011(p000.x(), p111.y(), p111.z()),
          p100(p111.x(), p000.y(), p000.z()),
          p101(p111.x(), p000.y(), p111.z()),
          p110(p111.x(), p111.y(), p000.z());

    
    if(geom->getBody() != NullFC)
    {
        //Transform by the bodies position and rotation
        Matrix m(geom->getBody()->getTransformation());
        
        m.mult(p000);
        m.mult(p001);
        m.mult(p010);
        m.mult(p011);
        m.mult(p100);
        m.mult(p101);
        m.mult(p110);
        m.mult(p111);
    }

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

void drawPhysicsGeom(const PhysicsCapsuleGeomPtr geom)
{
    Real32 Radius(geom->getRadius()),
           HalfLength(geom->getLength()*0.5f);

    Matrix m;
    if(geom->getBody() != NullFC)
    {
        //Transform by the bodies position and rotation
        m = geom->getBody()->getTransformation();
    }

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
            x = osgcos(static_cast<Real32>(i)/static_cast<Real32>(Segments) * TWO_PI);
            y = osgsin(static_cast<Real32>(i)/static_cast<Real32>(Segments)* TWO_PI);
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
        double zr1 = cos(lat1);

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

    if(geom->getBody() != NullFC)
    {
        //Transform by the bodies position and rotation
        Matrix m(geom->getBody()->getTransformation());
        
        m.mult(p1);
        m.mult(p2);
    }

    
    glBegin(GL_LINES);
        glVertex3fv(p1.getValues());   
        glVertex3fv(p2.getValues());
    glEnd();
}

void drawPhysicsGeom(const PhysicsSphereGeomPtr geom)
{
    Pnt3f p(geom->getPosition());

    if(geom->getBody() != NullFC)
    {
        //Transform by the bodies position and rotation
        Matrix m(geom->getBody()->getTransformation());
        m.mult(p);
    }
    double r(geom->getRadius());
    int lats(12);
    int longs(12);

    int i, j;
    for(i = 0; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = r * sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = r * sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++)
        {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = r * cos(lng);
            double y = r * sin(lng);

            //glNormal3f(p.x() + x * zr1, p.y() + y * zr1, p.z() + z1);
            //glNormal3f(p.x() + x * zr0, p.y() + y * zr0, p.z() + z0);
            glVertex3f(p.x() + x * zr1, p.y() + y * zr1, p.z() + z1);
            glVertex3f(p.x() + x * zr0, p.y() + y * zr0, p.z() + z0);
        }
        glEnd();
    }

}

void drawPhysicsGeom(const PhysicsTriMeshGeomPtr geom)
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

void dropPhysicsGeom(DrawActionBase* action,const NodePtr node, const Color4f& col, MaterialPtr mat)
{
    //Get the Physics Geom object attached to this node, if there is one
    AttachmentPtr TheGeomAttachment(NullFC);

    //Box
    TheGeomAttachment = node->findAttachment(PhysicsBoxGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }

    //Sphere
    TheGeomAttachment = node->findAttachment(PhysicsSphereGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }

    //Ray
    TheGeomAttachment = node->findAttachment(PhysicsRayGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }

    //Capsule
    TheGeomAttachment = node->findAttachment(PhysicsCapsuleGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }

    //Plane
    TheGeomAttachment = node->findAttachment(PhysicsPlaneGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
        dropPhysicsGeom(action,PhysicsGeom::Ptr::dcast(TheGeomAttachment),col,mat);
    }

    //TriMesh
    TheGeomAttachment = node->findAttachment(PhysicsTriMeshGeom::getClassType());
    if(TheGeomAttachment != NullFC)
    {
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
