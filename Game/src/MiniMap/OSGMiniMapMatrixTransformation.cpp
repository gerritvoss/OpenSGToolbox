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

	r.setValue(RotMat);
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
    static Char8 cvsid_hpp       [] = OSGMINIMAPMATRIXTRANSFORMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMINIMAPMATRIXTRANSFORMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMINIMAPMATRIXTRANSFORMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

