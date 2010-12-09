#include "OSGPhysicsBodyDrawFuncs.h"
#include "OSGGL.h"
#include "OSGSimpleGeometry.h"
#include "OSGRenderAction.h"
#include "OSGPhysicsBody.h"
#include "OSGMaterial.h"
#include "OSGPrimeMaterial.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsBodyCoordinateSystem(const PhysicsBodyUnrecPtr body, Real32 Length)
{
    Pnt3f origin(0.0f,0.0f,0.0f);
    Pnt3f x_axis(Length,0.0f,0.0f),
          y_axis(0.0f,Length,0.0f),
          z_axis(0.0f,0.0f,Length);

    //Transform by the bodies position and rotation
    Matrix m(body->getTransformation());
    
    m.mult(origin,origin);
    m.mult(x_axis,x_axis);
    m.mult(y_axis,y_axis);
    m.mult(z_axis,z_axis);

    
    glBegin(GL_LINES);
        //X Axis
        glColor3f(1.0,0.0,0.0);
        glVertex3fv(origin.getValues());   
        glVertex3fv(x_axis.getValues());

        //Y Axis
        glColor3f(0.0,1.0,0.0);
        glVertex3fv(origin.getValues());   
        glVertex3fv(y_axis.getValues());

        //Z Axis
        glColor3f(0.0,0.0,1.0);
        glVertex3fv(origin.getValues());   
        glVertex3fv(z_axis.getValues());
    glEnd();
}

void drawPhysicsBodyLinearVelocity(const PhysicsBodyUnrecPtr body, Real32 Length)
{
    if(body->getEnable())
    {
        Pnt3f origin(0.0f,0.0f,0.0f);
        Vec3f vel;
        body->getRelPointVel(Vec3f(0.0f,0.0f,0.0f),vel);
        vel.normalize();
        vel *= Length;
    
        //Transform by the bodies position and rotation
        Matrix m(body->getTransformation());
        
        m.mult(origin,origin);
        
        Pnt3f p2(origin + vel);

        glBegin(GL_LINES);
            //Velocity Direction
            glColor3f(1.0,0.0,1.0);
            glVertex3fv(origin.getValues());   
            glVertex3fv(p2.getValues());
        glEnd();
    }
}

void drawPhysicsBodyAngularVelocity(const PhysicsBodyUnrecPtr body, Real32 Length)
{
}



class PhysicsBodyDrawWrapper
{
  public:
    PhysicsBodyDrawWrapper(const NodeUnrecPtr node, const PhysicsBodyUnrecPtr body, MaterialUnrecPtr mat) : 
        _node(node),_body(body), _mat(mat)
    {
        if(_mat == NULL)
        {
            _mat = getDefaultUnlitMaterial();
        }
    }
    
    ~PhysicsBodyDrawWrapper()
    {
    }

    static void drop(RenderAction* action,const NodeUnrecPtr node, const PhysicsBodyUnrecPtr geom, MaterialUnrecPtr mat)
    {
        PhysicsBodyDrawWrapper * vdw = new PhysicsBodyDrawWrapper(node, geom, mat);

        DrawEnv::DrawFunctor func;
        func = boost::bind(&PhysicsBodyDrawWrapper::draw, vdw, _1);
    
        action->dropFunctor(func, vdw->_mat);
    }
    
  private:
  
    Action::ResultE draw(DrawEnv *)
    {
        BoxVolume vol;
        _node->getWorldVolume(vol);
        Pnt3f Min,Max;
        vol.getBounds(Min,Max);

        Real32 Length(1.05f * (Max-Min).maxValue());
        drawPhysicsBodyCoordinateSystem(_body, Length);
        drawPhysicsBodyLinearVelocity(_body, Length);
        drawPhysicsBodyAngularVelocity(_body, Length);
        
        // self-destruct
        delete this;
        
        return Action::Continue;
    }
    NodeUnrecPtr _node;
    PhysicsBodyUnrecPtr _body;
    MaterialUnrecPtr _mat; 
};

void dropPhysicsBody(RenderAction* action,const NodeUnrecPtr node, MaterialUnrecPtr mat)
{
    //Get the Physics Body object attached to this node, if there is one
    AttachmentUnrecPtr TheBodyAttachment(node->findAttachment(PhysicsBody::getClassType()));

    if(TheBodyAttachment != NULL)
    {
        PhysicsBodyDrawWrapper::drop(action, node, dynamic_pointer_cast<PhysicsBody>(TheBodyAttachment), mat);
    }
}



OSG_END_NAMESPACE
