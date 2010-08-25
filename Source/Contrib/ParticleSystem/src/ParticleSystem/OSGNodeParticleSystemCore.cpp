/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGNodeParticleSystemCore.h"
#include "OSGTransform.h"
#include "OSGParticleSystemEventDetails.h"
#include "OSGParticleEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNodeParticleSystemCoreBase.cpp file.
// To modify it, please change the .fcd file (OSGNodeParticleSystemCore.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NodeParticleSystemCore::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NodeParticleSystemCore::updateNodes(void)
{
    if(getPrototypeNode() ==NULL)
    {
        return;
    }

    UInt32 NumParticles;
    if(getSystem() == NULL)
    {
        NumParticles = 0;
    }
    else
    {
        NumParticles = getSystem()->getNumParticles();
    }

    //Resize the ParticleNodes MultiField
    if(NumParticles < getMFParticleNodes()->size())
    {
        if(NumParticles == 0)
        {
            clearParticleNodes();
        }
        else
        {
            while(NumParticles < getMFParticleNodes()->size())
            {
                removeFromParticleNodes(getMFParticleNodes()->size()-1);
            }
        }
    }
    else if(NumParticles > getMFParticleNodes()->size())
    {
        NodeRefPtr TransformationNode;
        TransformRefPtr TransformationCore;

        NodeRefPtr ParticleNode;
        while(NumParticles > getMFParticleNodes()->size())
        {
            ParticleNode = cloneTree(getPrototypeNode());

            TransformationCore = Transform::create();
            TransformationNode = Node::create();
            TransformationNode->setCore(TransformationCore);
            TransformationNode->addChild(ParticleNode);

            pushToParticleNodes(TransformationNode);
        }
    }

    //Update the transformations of the Particle Nodes
    Matrix Transformation;
    Vec3f Scaling;
    Matrix Rotation;
    Vec3f Normal,Binormal, Up;
    for(UInt32 i(0) ; i<NumParticles ; ++i)
    {
        Scaling = getSystem()->getSize(i);
        Scaling.setValues(Scaling.x()*getSizeScaling().x(),
                          Scaling.y()*getSizeScaling().y(),
                          Scaling.z()*getSizeScaling().z());

        Normal = getNodeNormal(getSystem(), i);
        Binormal = getNodeUpDir(getSystem(), i).cross(Normal);
        Up = Normal.cross(Binormal);
        Rotation.setValue(Binormal.x(),Up.x(),Normal.x(),0.0,
                          Binormal.y(),Up.y(),Normal.y(),0.0,
                          Binormal.z(),Up.z(),Normal.z(),0.0,
                          0.0,0.0,0.0,1.0);

        if(Normal.isZero() || Up.isZero() || Binormal.isZero()
           || Normal.squareLength() > 1.1)
        {
            /*std::cout << "NumParticles " << NumParticles << std::endl;
              std::cout << "Index " << i << std::endl;
              std::cout << "Up " << Up << std::endl;
              std::cout << "Normal " << Normal << std::endl;
              std::cout << "Binormal " << Binormal << std::endl;*/
        }

        Transformation.setTransform(getSystem()->getPosition(i).subZero(),
                                    Quaternion( Rotation ),
                                    Scaling);

        dynamic_cast<Transform*>(getParticleNodes(i)->getCore())->setMatrix(Transformation);
    }

    //Update My Children
    for(UInt32 j(0) ; j<_mfParents.size() ; ++j)
    {
        if(dynamic_cast<Node*>(_mfParents[j])->getNChildren() != getMFParticleNodes()->size())
        {
            while(dynamic_cast<Node*>(_mfParents[j])->getNChildren() > 0)
            {
                dynamic_cast<Node*>(_mfParents[j])->subChild(dynamic_cast<Node*>(_mfParents[j])->getNChildren()-1);
            }
            for(UInt32 i(0) ; i<getMFParticleNodes()->size() ; ++i)
            {
                dynamic_cast<Node*>(_mfParents[j])->addChild(getParticleNodes(i));
            }
        }
    }
}

Vec3f NodeParticleSystemCore::getNodeNormal(ParticleSystemRefPtr System, UInt32 Index)
{
    Vec3f Direction;

    switch(getNormalSource())
    {
        case NORMAL_POSITION_CHANGE:
            Direction = System->getPositionChange(Index);
            Direction.normalize();
            break;
        case NORMAL_VELOCITY_CHANGE:
            Direction = System->getVelocityChange(Index);
            Direction.normalize();
            break;
        case NORMAL_VELOCITY:
            Direction = System->getVelocity(Index);
            Direction.normalize();
            break;
        case NORMAL_ACCELERATION:
            Direction = System->getAcceleration(Index);
            Direction.normalize();
            break;
        case NORMAL_PARTICLE_NORMAL:
            Direction = System->getNormal(Index);
            break;
        case NORMAL_VIEW_POSITION:
            {
                //TODO: make this more efficient
                //Matrix ModelView = action->getCameraToWorld();
                //Vec3f Position(ModelView[0][3],ModelView[1][3],ModelView[2][3]);
                //Direction = Position - System->getPosition(Index);
                //Direction.normalize();

                break;
            }
        case NORMAL_STATIC:
            Direction = getNormal();
            break;
        case NORMAL_VIEW_DIRECTION:
        default:
            {
                //TODO: make this more efficient
                //Matrix ModelView = action->getCameraToWorld();
                //Direction.setValues(ModelView[2][0],ModelView[2][1],ModelView[2][2]);
                break;
            }
    }
    return Direction;
}

Vec3f NodeParticleSystemCore::getNodeUpDir(ParticleSystemRefPtr System, UInt32 Index)
{
    Vec3f Direction;

    switch(getUpSource())
    {
        case UP_POSITION_CHANGE:
            Direction = System->getPositionChange(Index);
            break;
        case UP_VELOCITY_CHANGE:
            Direction = System->getVelocityChange(Index);
            break;
        case UP_VELOCITY:
            Direction = System->getVelocity(Index);
            break;
        case UP_ACCELERATION:
            Direction = System->getAcceleration(Index);
            break;
        case UP_PARTICLE_NORMAL:
            Direction = System->getNormal(Index);
            break;
        case UP_STATIC:
            Direction = getUp();
            break;
        case UP_VIEW_DIRECTION:
        default:
            {
                //TODO: make this more efficient
                //Matrix ModelView = action->getCameraToWorld();
                //Direction.setValues(ModelView[1][0],ModelView[1][1],ModelView[1][2]);
                break;
            }
    }

    return Direction;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void NodeParticleSystemCore::handleVolumeChanged(ParticleSystemEventDetails* const details)
{
    updateNodes();
}

void NodeParticleSystemCore::handleParticleGenerated(ParticleEventDetails* const details)
{
    updateNodes();
}

void NodeParticleSystemCore::handleParticleKilled(ParticleEventDetails* const details)
{
    updateNodes();
}

void NodeParticleSystemCore::handleParticleStolen(ParticleEventDetails* const details)
{
    updateNodes();
}
/*----------------------- constructors & destructors ----------------------*/

NodeParticleSystemCore::NodeParticleSystemCore(void) :
    Inherited()
{
}

NodeParticleSystemCore::NodeParticleSystemCore(const NodeParticleSystemCore &source) :
    Inherited(source)
{
}

NodeParticleSystemCore::~NodeParticleSystemCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NodeParticleSystemCore::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SystemFieldMask)
    {
        _VolumeChangedConnection.disconnect();
        _ParticleGeneratedConnection.disconnect();
        _ParticleKilledConnection.disconnect();
        _ParticleStolenConnection.disconnect();

        if(getSystem() != NULL)
        {
            _VolumeChangedConnection = getSystem()->connectVolumeChanged(boost::bind(&NodeParticleSystemCore::handleVolumeChanged, this, _1));
            _ParticleGeneratedConnection = getSystem()->connectParticleGenerated(boost::bind(&NodeParticleSystemCore::handleParticleGenerated, this, _1));
            _ParticleKilledConnection = getSystem()->connectParticleKilled(boost::bind(&NodeParticleSystemCore::handleParticleKilled, this, _1));
            _ParticleStolenConnection = getSystem()->connectParticleStolen(boost::bind(&NodeParticleSystemCore::handleParticleStolen, this, _1));
        }
    }
    if((whichField & SystemFieldMask) ||
       (whichField & ParentsFieldMask))
    {
        updateNodes();
    }
}

void NodeParticleSystemCore::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump NodeParticleSystemCore NI" << std::endl;
}

OSG_END_NAMESPACE
