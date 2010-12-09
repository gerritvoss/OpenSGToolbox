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
    Vec3f PosX(1.0f,0.0f,0.0f),
          PosY(0.0f,1.0f,0.0f),
          PosZ(0.0f,0.0f,1.0f);
    
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

    m.mult(PosX,PosX);
    m.mult(PosY,PosY);
    m.mult(PosZ,PosZ);
    Vec3f NegX(-PosX),
          NegY(-PosY),
          NegZ(-PosZ);

    glBegin(GL_QUADS);
        // Front Face
        glNormal3fv(NegZ.getValues());
        glVertex3fv(p110.getValues());
        glVertex3fv(p100.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p010.getValues());

        // Back Face
        glNormal3fv(PosZ.getValues());
        glVertex3fv(p111.getValues());
        glVertex3fv(p011.getValues());
        glVertex3fv(p001.getValues());
        glVertex3fv(p101.getValues());

        // Top Face
        glNormal3fv(NegY.getValues());
        glVertex3fv(p101.getValues());
        glVertex3fv(p001.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p100.getValues());
        
        // Bottom Face
        glNormal3fv(PosY.getValues());
        glVertex3fv(p111.getValues());
        glVertex3fv(p110.getValues());
        glVertex3fv(p010.getValues());
        glVertex3fv(p011.getValues());

        // Right face
        glNormal3fv(NegX.getValues());
        glVertex3fv(p011.getValues());
        glVertex3fv(p010.getValues());
        glVertex3fv(p000.getValues());
        glVertex3fv(p001.getValues());

        // Left Face
        glNormal3fv(PosX.getValues());
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
    Real32 r(geom->getRadius());
    Real32 lats(12.0f);
    Real32 longs(12.0f);

    Real32 i, j;
    Vec3f Norm1, Norm0;
    Pnt3f Pos0, Pos1;
    Pnt3f p;
    for(i = 0.0f; i <= lats; ++i)
    {
        p.setValues(0.0f,0.0f,0.0f);
        if(i>lats/2.0f) p[2] += HalfLength;
        else  p[2] -= HalfLength;

        Real32 lat0 = M_PI * (-0.5f + (i - 1.0f) / lats);
        Norm0[2]  = osgSin(lat0);
        Real32 zr0 =  osgCos(lat0);

        Real32 lat1 = M_PI * (-0.5f + i / lats);
        Norm1[2]  = osgSin(lat1);
        Real32 zr1 = osgCos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0.0f; j <= longs; ++j)
        {
            Real32 lng = 2.0f * M_PI * (j - 1.0f) / longs;
            Real32 CosLng = osgCos(lng);
            Real32 SinLng = osgSin(lng);
            Norm0[0] = CosLng * zr0;
            Norm0[1] = SinLng * zr0;
            Norm1[0] = CosLng * zr1;
            Norm1[1] = SinLng * zr1;
            Pos0 = p + (Norm0 * r);
            Pos1 = p + (Norm1 * r);

            glNormal3fv(Norm1.getValues());
            glVertex3fv(Pos1.getValues());

            glNormal3fv(Norm0.getValues());
            glVertex3fv(Pos0.getValues());
        }
        glEnd();
    }
    
    glPopMatrix();
}

void drawPhysicsGeom(const PhysicsPlaneGeomUnrecPtr geom)
{
    Vec3f n(geom->getParameters().x(),geom->getParameters().y(), geom->getParameters().z());
    Pnt3f p(Pnt3f(0.0f,0.0f,0.0f) + n*geom->getParameters().w());

    //Calculate vectors that are perpendicular to the planes normal
    Vec3f t(1.0f,0.0f,0.0f);
    if(n.dot(t) < 0.001f)
    {
        t.setValues(0.0f,1.0f,0.0f);
    }

    Vec3f b(n.cross(t));
    t = b.cross(n);

    Real32 Length(100000.0f);

    t *= Length;
    b *= Length;

    Pnt3f p1(p + t + b),
          p2(p - t + b),
          p3(p - t - b),
          p4(p + t - b);
    
    glBegin(GL_QUADS);
        //Front Side
        glNormal3fv(n.getValues());
        glVertex3fv(p1.getValues());
        glVertex3fv(p2.getValues());
        glVertex3fv(p3.getValues());
        glVertex3fv(p4.getValues());

        //Back side
        glNormal3f(-n.x(), -n.y(), -n.z());
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
    Real32 r(geom->getRadius());
    Real32 lats(12.0f);
    Real32 longs(12.0f);

    Real32 i, j;
    Vec3f Norm1, Norm0;
    Pnt3f Pos0, Pos1;
    for(i = 0.0f; i <= lats; i++)
    {
        Real32 lat0 = M_PI * (-0.5f + (i - 1.0f) / lats);
        Norm0[2]  = osgSin(lat0);
        Real32 zr0 =  osgCos(lat0);

        Real32 lat1 = M_PI * (-0.5f + i / lats);
        Norm1[2]  = osgSin(lat1);
        Real32 zr1 = osgCos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0.0f; j <= longs; j++)
        {
            Real32 lng = 2.0f * M_PI * (j - 1.0f) / longs;
            Real32 CosLng = osgCos(lng);
            Real32 SinLng = osgSin(lng);
            Norm0[0] = CosLng * zr0;
            Norm0[1] = SinLng * zr0;
            Norm1[0] = CosLng * zr1;
            Norm1[1] = SinLng * zr1;
            Pos0 = p + (Norm0 * r);
            Pos1 = p + (Norm1 * r);

            glNormal3fv(Norm1.getValues());
            glVertex3fv(Pos1.getValues());

            glNormal3fv(Norm0.getValues());
            glVertex3fv(Pos0.getValues());
        }
        glEnd();
    }

}

void drawPhysicsGeom(const PhysicsTriMeshGeomUnrecPtr geom)
{

    UInt32 TriCount(geom->getTriangleCount());
    Vec3f v1,v2,v3;

    Vec3f Norm;
    glBegin(GL_TRIANGLES);
        for(UInt32 i(0) ; i<TriCount ; ++i)
        {
            //The Tris returned are already in world-space
            geom->getTriangle(i,v1,v2,v3);
            Norm = (v1-v2).cross(v1-v3);
            Norm.normalize();
            glNormal3fv(Norm.getValues());
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
            //_mat = getDefaultUnlitMaterial();
            _mat = getDefaultMaterial();
        }
    }
    
    ~PhysicsGeomDrawWrapper()
    {}

    static void drop(RenderAction* action,const PhysicsGeomUnrecPtr geom, const Color4f& col, MaterialUnrecPtr mat)
    {
        PhysicsGeomDrawWrapper * vdw = new PhysicsGeomDrawWrapper(geom, col, mat);

        DrawEnv::DrawFunctor func;
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
