#include "OSGPhysicsBodyDrawFuncs.h"
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGRenderAction.h>
#include "ODE/OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

void drawPhysicsBodyCoordinateSystem(const PhysicsBodyPtr body, Real32 Length)
{
    Pnt3f origin(0.0f,0.0f,0.0f);
    Pnt3f x_axis(Length,0.0f,0.0f),
          y_axis(0.0f,Length,0.0f),
          z_axis(0.0f,0.0f,Length);

    //Transform by the bodies position and rotation
    Matrix m(body->getTransformation());
    
    m.mult(origin);
    m.mult(x_axis);
    m.mult(y_axis);
    m.mult(z_axis);

    
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

void drawPhysicsBodyLinearVelocity(const PhysicsBodyPtr body, Real32 Length)
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
        
        m.mult(origin);
        
        Pnt3f p2(origin + vel);

        glBegin(GL_LINES);
            //Velocity Direction
            glColor3f(1.0,0.0,1.0);
            glVertex3fv(origin.getValues());   
            glVertex3fv(p2.getValues());
        glEnd();
    }
}

void drawPhysicsBodyAngularVelocity(const PhysicsBodyPtr body, Real32 Length)
{
}



class PhysicsBodyDrawWrapper
{
  public:
    PhysicsBodyDrawWrapper(const NodePtr node, const PhysicsBodyPtr body, MaterialPtr mat) : 
        _node(node),_body(body), _mat(mat)
    {
        if(_mat == NullFC)
        {
            _mat = getDefaultUnlitMaterial();
        }
    }
    
    ~PhysicsBodyDrawWrapper()
    {}

    static void drop(DrawActionBase* action,const NodePtr node, const PhysicsBodyPtr geom, MaterialPtr mat)
    {
        PhysicsBodyDrawWrapper * vdw = new PhysicsBodyDrawWrapper(node, geom, mat);

        Material::DrawFunctor func;
        func = osgTypedMethodFunctor1ObjPtr(vdw, &PhysicsBodyDrawWrapper::draw);
    
        RenderAction *ra = dynamic_cast<RenderAction*>(action);
        
        ra->dropFunctor(func, getCPtr(vdw->_mat));
    }
    
  private:
  
    Action::ResultE draw(DrawActionBase *)
    {
        DynamicVolume vol;
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
    NodePtr _node;
    PhysicsBodyPtr _body;
    MaterialPtr _mat; 
};

void dropPhysicsBody(DrawActionBase* action,const NodePtr node, MaterialPtr mat)
{
    //Get the Physics Body object attached to this node, if there is one
    AttachmentPtr TheBodyAttachment(node->findAttachment(PhysicsBody::getClassType()));

    if(TheBodyAttachment != NullFC)
    {
        PhysicsBodyDrawWrapper::drop(action, node, PhysicsBody::Ptr::dcast(TheBodyAttachment), mat);
    }
}



OSG_END_NAMESPACE
