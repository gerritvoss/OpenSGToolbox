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

#include "OSGTreeModel.h"
#include "OSGTreePath.h"
#include <deque>
#include "OSGBaseFunctions.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TreePath TreeModel::getPath(const boost::any& node) const
{
    std::deque<boost::any> PathVector;

    boost::any RecNode(node);
    while(!RecNode.empty())
    {
        PathVector.push_front(RecNode);
        RecNode = getParent(RecNode);
    }

    return TreePath(PathVector, TreeModelRefPtr(const_cast<TreeModel*>(this)));
}

bool TreeModel::depthFirstLessThan(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));
    return LeftPath.depthFirstLessThan(RightPath);
}

bool TreeModel::breadthFirstLessThan(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));
    return LeftPath.breadthFirstLessThan(RightPath);
}

bool TreeModel::isEqual(const boost::any& left, const boost::any& right) const
{
    TreePath LeftPath(getPath(left)),
             RightPath(getPath(right));

    if(LeftPath.getPathCount() == RightPath.getPathCount())
    {
        for(UInt32 i(0) ; i<osgMin<UInt32>(LeftPath.getPathCount(), RightPath.getPathCount())-1 ; ++i)
        {
            if( getIndexOfChild(LeftPath.getPathComponent(i),LeftPath.getPathComponent(i+1))
                !=
                getIndexOfChild(RightPath.getPathComponent(i),RightPath.getPathComponent(i+1)))
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeModel::TreeModel(void) :
    Inherited()
{
}

TreeModel::TreeModel(const TreeModel &source) :
    Inherited(source)
{
}

TreeModel::~TreeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeModel NI" << std::endl;
}

OSG_END_NAMESPACE
