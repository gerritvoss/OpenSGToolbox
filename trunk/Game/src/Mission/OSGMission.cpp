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

#include "OSGMission.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Mission
A Inventory. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Mission::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Mission::setParentOnChild()
{
	for(UInt32 i = 0; i < getMissions().getSize(); i++)
	{
		beginEditCP(getMissions(i), Mission::ParentFieldMask);
			getMissions(i)->setParent(MissionPtr(this));
		endEditCP(getMissions(i), Mission::ParentFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Mission::Mission(void) :
    Inherited()
{
}

Mission::Mission(const Mission &source) :
    Inherited(source)
{
}

Mission::~Mission(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Mission::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	if(whichField & MissionsFieldMask)
	{
		setParentOnChild();
	}
}

void Mission::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Mission NI" << std::endl;
}


OSG_END_NAMESPACE

