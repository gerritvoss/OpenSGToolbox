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

#include "OSGTreeModelEventDetails.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTreeModelEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGTreeModelEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeModelEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

TreeModelEventDetailsTransitPtr TreeModelEventDetails::create(  FieldContainer* const Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath,
                                           const std::vector<UInt32>& childIndices,
                                           const std::vector<boost::any>& children)
{
    TreeModelEventDetails* TheEventDetails = TreeModelEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->editMFChildIndices()->setValues(childIndices);
    TheEventDetails->_Path     = ThePath;
    TheEventDetails->_Children = children;

    return TreeModelEventDetailsTransitPtr(TheEventDetails);
}

TreeModelEventDetailsTransitPtr TreeModelEventDetails::create(  FieldContainer* const Source,
                                           Time TimeStamp,
                                           const TreePath& ThePath)
{
    TreeModelEventDetails* TheEventDetails = TreeModelEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->_Path     = ThePath;

    return TreeModelEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TreePath TreeModelEventDetails::getChildPath(UInt32 index) const
{
    return TreePath(getPath(), _Children[index]);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeModelEventDetails::TreeModelEventDetails(void) :
    Inherited()
{
}

TreeModelEventDetails::TreeModelEventDetails(const TreeModelEventDetails &source) :
    Inherited(source)
{
}

TreeModelEventDetails::~TreeModelEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeModelEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TreeModelEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TreeModelEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
