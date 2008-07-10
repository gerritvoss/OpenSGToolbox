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
		beginEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
			getParticleNodes().resize(NumParticles, NullFC);
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
			ParticleNode = Node::create();
			beginEditCP(ParticleNode, Node::CoreFieldMask);
				ParticleNode->setCore(getPrototypeNode()->getCore());
			endEditCP(ParticleNode, Node::CoreFieldMask);

			TransformationCore = Transform::create();
			TransformationNode = Node::create();
			beginEditCP(TransformationNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
				TransformationNode->setCore(TransformationCore);
				TransformationNode->addChild(ParticleNode);
			endEditCP(TransformationNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
			
			getParticleNodes().push_back(TransformationNode);
		}
		endEditCP(NodeParticleSystemCorePtr(this), ParticleNodesFieldMask);
	}

	//Update the transformations of the Particle Nodes
	Matrix Transformation;
	Vec3f Scaling;
	for(UInt32 i(0) ; i<NumParticles ; ++i)
	{
		Scaling = getSystem()->getSize(i);
		Scaling.setValues(Scaling.x()*getSizeScaling().x(),
			Scaling.y()*getSizeScaling().y(),
			Scaling.z()*getSizeScaling().z());

		Transformation.setTransform(getSystem()->getPosition(i),
			                        Quaternion(),
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


void NodeParticleSystemCore::SystemUpdateListener::systemUpdated(const ParticleSystemEvent& e)
{
    if(e.getVolumeChanged())
    {
		_Core->updateNodes();
    }
}

void NodeParticleSystemCore::SystemUpdateListener::particleGenerated(const ParticleEvent& e)
{
}

void NodeParticleSystemCore::SystemUpdateListener::particleKilled(const ParticleEvent& e)
{
}

void NodeParticleSystemCore::SystemUpdateListener::particleStolen(const ParticleEvent& e)
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

