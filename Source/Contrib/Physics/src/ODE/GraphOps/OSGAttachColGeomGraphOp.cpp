/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *                   contact: dan.guilliams@gmail.com                        *
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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include "OSGAttachColGeomGraphOp.h"
#include "OSGGraphOpFactory.h"
#include "OSGNameAttachment.h"
#include "OSGPhysicsGeom.h"
#include "OSGPhysicsTriMeshGeom.h"
#include "OSGPhysicsSphereGeom.h"
#include "OSGPhysicsBoxGeom.h"
#include "OSGPhysicsCapsuleGeom.h"
#include "OSGGeometry.h"
#include <string>


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class AttachColGeomGraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
    A class used to change traversal masks of nodes meeting certain criteria.

*/

namespace
{
    //! Register the GraphOp with the factory
    static bool registerOp(void)
    {
        GraphOpRefPtr newOp = AttachColGeomGraphOp::create();

        GraphOpFactory::the()->registerOp(newOp);
        return true;
    }
    
    static StaticInitFuncWrapper registerOpWrapper(registerOp);

} // namespace

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

AttachColGeomGraphOp::AttachColGeomGraphOp() :
	mMatchName(true),
    mMatchWholeName(true),
	mMatchCurTravMask(false),
	mMatchMaskCondition(BIT_EQUAL),
	mMatchCurTravMaskValue(1),
    mCreateGeomType(TRI_MESH_GEOM),
	mNumChanged(0)
{
	mMatchRegex = boost::xpressive::cregex::compile(".*_Col$", boost::xpressive::regex_constants::icase);
}

AttachColGeomGraphOp::~AttachColGeomGraphOp(void)
{
}

void AttachColGeomGraphOp::setCreateGeomType(UInt32 TheGeomType)
{
    mCreateGeomType = TheGeomType;
}

AttachColGeomGraphOpTransitPtr AttachColGeomGraphOp::create()
{
    return AttachColGeomGraphOpTransitPtr(new AttachColGeomGraphOp());
}

GraphOpTransitPtr AttachColGeomGraphOp::clone(void)
{
    return GraphOpTransitPtr(new AttachColGeomGraphOp(*this));
}

bool AttachColGeomGraphOp::traverse(Node *root)
{
    return GraphOp::traverse(root);
}

void AttachColGeomGraphOp::setMatchWholeName(bool value)
{
	mMatchWholeName = value;
}

void AttachColGeomGraphOp::setMatchMaskCondition(UInt8 MatchMaskCondition)
{
	mMatchMaskCondition = MatchMaskCondition;
}

void AttachColGeomGraphOp::setMatchRegex(const std::string& MatchName)
{
	mMatchRegex = boost::xpressive::cregex::compile(MatchName, boost::xpressive::regex_constants::icase);
}

void AttachColGeomGraphOp::setMatchRegex(const boost::xpressive::cregex& MatchRegex)
{
	mMatchRegex = MatchRegex;
}

void AttachColGeomGraphOp::setCurrentTravMaskValue(UInt32 CurrentTraversalMask)
{
	mMatchCurTravMaskValue = CurrentTraversalMask;
}

void AttachColGeomGraphOp::setMatchName(bool MatchName)
{
	mMatchName = MatchName;
}

void AttachColGeomGraphOp::setMatchCurrentTravMask(bool MatchCurMask)
{
	mMatchCurTravMask = MatchCurMask;
}

void AttachColGeomGraphOp::setCollideMask(UInt32 CollideMask)
{
	mCollideMask = CollideMask;
}

void AttachColGeomGraphOp::setCategoryMask(UInt32 CategoryMask)
{
	mCategoryMask = CategoryMask;
}

void AttachColGeomGraphOp::setParams(const std::string params)
{
    ParamSet ps(params);   
    
    ps("CreateGeomType", mCreateGeomType);

    //Name Matching
    ps("MatchName", mMatchName);
    std::string MatchRegex;
	ps("MatchRegex", MatchRegex);
    ps("MatchWholeName", mMatchWholeName);
	mMatchRegex = boost::xpressive::cregex::compile(MatchRegex, boost::xpressive::regex_constants::icase);

    //Mask Matching
	ps("MatchCurTravMask",mMatchCurTravMask);
	ps("MatchCurTravMaskValue",mMatchCurTravMaskValue);
	//ps("MatchMaskCondition",mMatchMaskCondition);
    
    std::string out = ps.getUnusedParams();
    if(out.length())
    {
        FWARNING(("AttachColGeomGraphOp doesn't have parameters '%s'.\n",
                out.c_str()));
    }
}

std::string AttachColGeomGraphOp::usage(void)
{
    return 
    "AttachColGeomGraphOp: Adds physics geoms as atttachments to matching nodes.\n"
    "Params: name (type, default)\n";
    
}

UInt32 AttachColGeomGraphOp::getNumChanged( void )
{
	return mNumChanged;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE AttachColGeomGraphOp::traverseEnter(Node * const node)
{
	bool setMask(false);

    //Name Matching
	if(mMatchName)
	{
        const Char8 * namePtr = OSG::getName(node);
        if(namePtr == NULL)
        {
            namePtr = "";
        }
        if(mMatchWholeName)
        {
            setMask = boost::xpressive::regex_match( namePtr, mMatchRegex );
		}
        else
        {
            setMask = boost::xpressive::regex_search( namePtr, mMatchRegex );
        }
	}

    //Mask Matching
	if(mMatchCurTravMask)
    {
        bool BitTest(false);
        switch(mMatchMaskCondition)
        {
        case BIT_AND:
            BitTest = static_cast<bool>(node->getTravMask() & mMatchCurTravMaskValue);
            break;
        case BIT_OR:
            BitTest = static_cast<bool>(node->getTravMask() | mMatchCurTravMaskValue);
            break;
        case BIT_XOR:
            BitTest = static_cast<bool>(node->getTravMask() ^ mMatchCurTravMaskValue);
            break;
        case BIT_NOT:
        case BIT_NOT_EQUAL:
            BitTest = (node->getTravMask() != mMatchCurTravMaskValue);
            break;
        case BIT_EQUAL:
        default:
            BitTest = (node->getTravMask() == mMatchCurTravMaskValue);
            break;
        }

        if(BitTest)
        {
            setMask = true;
        }
    }

	if(setMask)
	{
        //Apply the new traversal mask
        PhysicsGeomUnrecPtr NewGeom;
        Node* AttachNode(node);
        while(AttachNode != NULL &&
              AttachNode->getNChildren() > 0 &&
              !AttachNode->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
        {
            AttachNode = AttachNode->getChild(0);
        }
        if(AttachNode != NULL &&
           AttachNode->getCore()->getType().isDerivedFrom(Geometry::getClassType()))
        {
            switch(mCreateGeomType)
            {
            case TRI_MESH_GEOM:
                NewGeom = PhysicsTriMeshGeom::create();

                dynamic_pointer_cast<PhysicsTriMeshGeom>(NewGeom)->setGeometryNode(AttachNode);
                break;
            case BOX_GEOM:
                NewGeom = PhysicsBoxGeom::create();

                //Find the Min, and Max vertex
                break;
            case CAPSULE_GEOM:
                NewGeom = PhysicsCapsuleGeom::create();
                break;
            case SPHERE_GEOM:
                NewGeom = PhysicsSphereGeom::create();

                //Find the centroid of the verticies
                //Find the max distance vertex from the centroid
                break;
            }
        }
        if(NewGeom != NULL && AttachNode != NULL)
        {
            NewGeom->setCollideBits(mCollideMask);
            NewGeom->setCategoryBits(mCategoryMask);
            AttachNode->addAttachment(NewGeom);
	        ++mNumChanged;

            return Action::Skip;    
        }
        if(mCreateGeomType != REMOVE_GEOM && AttachNode != NULL)
        {
            Attachment* att = AttachNode->findAttachment(PhysicsGeom::getClassType());
            if(att != NULL)
            {
                AttachNode->subAttachment(att);
            }
        }
    }

    return Action::Continue;    
}

Action::ResultE AttachColGeomGraphOp::traverseLeave(Node * const node, Action::ResultE res)
{
	return res;
}




