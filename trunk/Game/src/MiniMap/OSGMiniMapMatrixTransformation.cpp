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

#include "OSGMiniMapMatrixTransformation.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MiniMapMatrixTransformation
A MiniMapMatrixTransformation. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MiniMapMatrixTransformation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MiniMapMatrixTransformation::transform(Pnt3f& p)
{
	getTransformation().mult(p);
}

void MiniMapMatrixTransformation::transform(Vec3f& v)
{
	getTransformation().mult(v);
}

void MiniMapMatrixTransformation::transform(Quaternion& r)
{
	Matrix RotMat;
	r.getValue(RotMat);
	RotMat.mult(getTransformation());

	Vec3f tempVec;
	Quaternion tempQuat;
	RotMat.getTransform(tempVec,r,tempVec,tempQuat);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MiniMapMatrixTransformation::MiniMapMatrixTransformation(void) :
    Inherited()
{
}

MiniMapMatrixTransformation::MiniMapMatrixTransformation(const MiniMapMatrixTransformation &source) :
    Inherited(source)
{
}

MiniMapMatrixTransformation::~MiniMapMatrixTransformation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MiniMapMatrixTransformation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MiniMapMatrixTransformation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MiniMapMatrixTransformation NI" << std::endl;
}

OSG_END_NAMESPACE

