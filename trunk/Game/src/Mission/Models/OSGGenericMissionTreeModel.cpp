/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGGenericMissionTreeModel.h"
#include <OpenSG/UserInterface/OSGTreePath.h>
#include "Mission/OSGMission.h"
#include "Mission/OSGDefaultMission.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GenericMissionTreeModel
A GenericMissionTreeModel.  
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GenericMissionTreeModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
boost::any GenericMissionTreeModel::getChild(const boost::any& parent, const UInt32& index) const
{
    //try
    //{
		//NodePtr TheNode = boost::any_cast<NodePtr>(parent);
        //if(TheNode != NullFC &&
           //TheNode->getNChildren() > index)
        //{
            //return boost::any(TheNode->getChild(index));
        //}
        //else
        //{
            //return boost::any();
        //}
    //}
    //catch(boost::bad_any_cast &)
    //{
        //return boost::any();
    //}

	

    return boost::any_cast<MissionPtr>(parent)->getMissions(index);
}

boost::any GenericMissionTreeModel::getParent(const boost::any& node) const
{
    //try
    //{
        //NodePtr TheNode = boost::any_cast<NodePtr>(node);
        //if(TheNode != NullFC &&
            //TheNode != getInternalRoot() &&
            //TheNode->getParent() != NullFC)
        //{
            //return boost::any(TheNode->getParent());
        //}
    //}
    //catch(boost::bad_any_cast &)
    //{
    //}

	if(boost::any_cast<MissionPtr>(node) != NullFC && 
		boost::any_cast<MissionPtr>(node) != boost::any_cast<MissionPtr>(getInternalRoot()) &&
		boost::any_cast<MissionPtr>(node)->getParent() != NullFC)
	{
		return boost::any_cast<MissionPtr>(node)->getParent();
	}

    return boost::any();
}

UInt32 GenericMissionTreeModel::getChildCount(const boost::any& parent) const
{
    //try
    //{
        //NodePtr TheNode = boost::any_cast<NodePtr>(parent);
        //if(TheNode != NullFC)
        //{
            //return TheNode->getNChildren();
        //}
        //else
        //{
            //return 0;
        //}
    //}
    //catch(boost::bad_any_cast &)
    //{
        //return 0;
    //}

    return boost::any_cast<MissionPtr>(parent)->getMissions().getSize();
}

UInt32 GenericMissionTreeModel::getIndexOfChild(const boost::any& parent, const boost::any& child) const
{
    //try
    //{
        //NodePtr ParentNode = boost::any_cast<NodePtr>(parent);
        //NodePtr ChildNode = boost::any_cast<NodePtr>(child);
        //if(ParentNode != NullFC &&
           //ChildNode  != NullFC)
        //{
            //return ParentNode->findChild(ChildNode);
        //}
        //else
        //{
            //return 0;
        //}
    //}
    //catch(boost::bad_any_cast &)
    //{
        //return 0;
    //}

	MissionPtr ParentMission = boost::any_cast<MissionPtr>(parent);
	MissionPtr ChildMission = boost::any_cast<MissionPtr>(child);

	if(ParentMission != NullFC && ChildMission != NullFC)
	{
		for(UInt32 i = 0; i < ParentMission->getMissions().getSize(); i++)
		{
			if(ChildMission == ParentMission->getMissions(i))
			{
				return i;
			}
		}
 	}

    return 0;
}

boost::any GenericMissionTreeModel::getRoot(void) const
{
    return boost::any(getInternalRoot());
}

bool GenericMissionTreeModel::isLeaf(const boost::any& node) const
{
	if(boost::any_cast<MissionPtr>(node)->getMissions().getSize() == 0)
	{
		return true;
	}

    return false;
}

void GenericMissionTreeModel::valueForPathChanged(TreePath path, const boost::any& newValue)
{
    //try
    //{
        //NodePtr NewNode = boost::any_cast<NodePtr>(newValue);
        //NodePtr OldNode = boost::any_cast<NodePtr>(path.getLastPathComponent());
        //if(NewNode != NullFC &&
           //OldNode  != NullFC &&
		   //NewNode != OldNode &&
		   //OldNode->getParent() != NullFC)
        //{
			//NodePtr ParentNode(OldNode->getParent());
			//beginEditCP(ParentNode, Node::ChildrenFieldMask);
				//if(ParentNode->replaceChildBy(OldNode, NewNode))
				//{
					//endEditCP(ParentNode, Node::ChildrenFieldMask);
					//UInt32 ChildIndex(ParentNode->findChild(NewNode));
					//produceTreeStructureChanged(path.getParentPath(),std::vector<UInt32>(1, ChildIndex),std::vector<boost::any>(1, newValue));
				//}
				//else
				//{
					//endEditNotChangedCP(ParentNode, Node::ChildrenFieldMask);
				//}
        //}
    //}
    //catch(boost::bad_any_cast &)
    //{
    //}
}

void GenericMissionTreeModel::setRoot(MissionPtr root)
{
    beginEditCP(GenericMissionTreeModelPtr(this), InternalRootFieldMask);
        setInternalRoot(root);
    endEditCP(GenericMissionTreeModelPtr(this), InternalRootFieldMask);
}

MissionPtr GenericMissionTreeModel::getRootMission(void) const
{
    return getInternalRoot();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GenericMissionTreeModel::GenericMissionTreeModel(void) :
    Inherited()
{
}

GenericMissionTreeModel::GenericMissionTreeModel(const GenericMissionTreeModel &source) :
    Inherited(source)
{
}

GenericMissionTreeModel::~GenericMissionTreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GenericMissionTreeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & InternalRootFieldMask)
    {
        produceTreeStructureChanged(getPath(getInternalRoot()),std::vector<UInt32>(1, 0),std::vector<boost::any>(1, boost::any(getInternalRoot())));
    }
}

void GenericMissionTreeModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GenericMissionTreeModel NI" << std::endl;
}


OSG_END_NAMESPACE

