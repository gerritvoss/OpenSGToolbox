/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTransform.h>

#include "OSGNodeParticleSystemCore.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NodeParticleSystemCore

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NodeParticleSystemCore::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NodeParticleSystemCore::updateNodes(void)
{
	if(getPrototypeNode() ==NullFC)
	{
		return;
	}

	UInt32 NumParticles;
	if(getSystem() == NullFC)
	{
		NumParticles = 0;
	}
	else
	{
		NumParticles = getSystem()->getNumParticles();
	}

	//Resize the ParticleNodes MultiField
	if(NumParticles < getParticleNodes().size())
	{
        for(UInt32 i(NumParticles) ; i<getParticleNodes().size(); ++i)
        {
            subRefCP(getParticleNodes()[i]);
        }

		beginEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
			getParticleNodes().resize(NumParticles);
		endEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
	}
	else if(NumParticles > getParticleNodes().size())
	{
		NodePtr TransformationNode;
		TransformPtr TransformationCore;

		NodePtr ParticleNode;
		beginEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
		while(NumParticles > getParticleNodes().size())
		{
			ParticleNode = cloneTree(getPrototypeNode());

			TransformationCore = Transform::create();
			TransformationNode = Node::create();
			beginEditCP(TransformationNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
				TransformationNode->setCore(TransformationCore);
				TransformationNode->addChild(ParticleNode);
			endEditCP(TransformationNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
			
            addRefCP(TransformationNode);
			getParticleNodes().push_back(TransformationNode);
		}
		endEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
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

		Transformation.setTransform(getSystem()->getPosition(i),
			                        Quaternion( Rotation ),
									Scaling);

		beginEditCP(getParticleNodes()[i]->getCore(), Transform::MatrixFieldMask);
			Transform::Ptr::dcast(getParticleNodes()[i]->getCore())->setMatrix(Transformation);
		endEditCP(getParticleNodes()[i]->getCore(), Transform::MatrixFieldMask);
	}

	//Update My Children
	for(UInt32 j(0) ; j<getParents().size() ; ++j)
	{
		if(getParents()[j]->getNChildren() != getParticleNodes().size())
		{
			beginEditCP(getParents()[j], Node::ChildrenFieldMask);
			while(getParents()[j]->getNChildren() > 0)
			{
				getParents()[j]->subChild(getParents()[j]->getNChildren()-1);
			}
			for(UInt32 i(0) ; i<getParticleNodes().size() ; ++i)
			{
				getParents()[j]->addChild(getParticleNodes()[i]);
			}
			endEditCP(getParents()[j], Node::ChildrenFieldMask);
		}
	}
}

Vec3f NodeParticleSystemCore::getNodeNormal(ParticleSystemPtr System, UInt32 Index)
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

Vec3f NodeParticleSystemCore::getNodeUpDir(ParticleSystemPtr System, UInt32 Index)
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

/*----------------------- constructors & destructors ----------------------*/

NodeParticleSystemCore::NodeParticleSystemCore(void) :
    Inherited(),
    _SystemUpdateListener(NodeParticleSystemCorePtr(this))
{
}

NodeParticleSystemCore::NodeParticleSystemCore(const NodeParticleSystemCore &source) :
    Inherited(source),
    _SystemUpdateListener(NodeParticleSystemCorePtr(this))
{
}

NodeParticleSystemCore::~NodeParticleSystemCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NodeParticleSystemCore::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if(whichField & SystemFieldMask)
    {
		if(getSystem() != NullFC)
		{
			getSystem()->addParticleSystemListener(&_SystemUpdateListener);
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


void NodeParticleSystemCore::SystemUpdateListener::systemUpdated(const ParticleSystemEventPtr e)
{
    //Do nothing
}

void NodeParticleSystemCore::SystemUpdateListener::volumeChanged(const ParticleSystemEventPtr e)
{
    _Core->updateNodes();
}

void NodeParticleSystemCore::SystemUpdateListener::particleGenerated(const ParticleEventPtr e)
{
}

void NodeParticleSystemCore::SystemUpdateListener::particleKilled(const ParticleEventPtr e)
{
}

void NodeParticleSystemCore::SystemUpdateListener::particleStolen(const ParticleEventPtr e)
{
}
/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGNODEPARTICLESYSTEMCOREBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGNODEPARTICLESYSTEMCOREBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGNODEPARTICLESYSTEMCOREFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

