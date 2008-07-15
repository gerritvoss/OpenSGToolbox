/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

#define OSG_COMPILEANIMATIONLIB

#include <OpenSG/OSGConfig.h>

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGBone.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SkeletonBlendedGeometry

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonBlendedGeometry::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SkeletonBlendedGeometry::addBoneBlending(const UInt32& PositionIndex, const BonePtr TheBone, const Real32& BlendAmount)
{
	beginEditCP(SkeletonBlendedGeometryPtr(this), BonesFieldMask | PositionIndexesFieldMask | BlendAmountsFieldMask);
		getPositionIndexes().push_back(PositionIndex);
		getBones().push_back(TheBone);
		getBlendAmounts().push_back(BlendAmount);
	endEditCP(SkeletonBlendedGeometryPtr(this), BonesFieldMask | PositionIndexesFieldMask | BlendAmountsFieldMask);
}

void SkeletonBlendedGeometry::calculatePositions(void)
{
	Matrix BonesTransforms,m;
	std::vector<Matrix> PositionTrans;

	if(getBaseGeometry() != NullFC &&
		getPositionIndexes().size() == getBones().size() == getBlendAmounts().size())
	{
		
		PositionTrans.resize(getBaseGeometry()->getPositions()->size());
		//UInt32 VertexesTransformations[n];
		for(UInt32 i(0) ; i<getPositionIndexes().size() ; ++i)
		{
			BonesTransforms = getBones(i)->getAbsoluteTransformation();
			BonesTransforms.scale(getBlendAmounts(i));
			BonesTransforms.mult(PositionTrans[getPositionIndexes(i)]);
			PositionTrans[getPositionIndexes(i)] = BonesTransforms;


		}
		//Update the Positions and Normals
		setPositions(GeoPositionsPtr::dcast(getBaseGeometry()->getPositions()->shallowCopy()));
		setNormals(GeoNormalsPtr::dcast(getBaseGeometry()->getNormals()->shallowCopy())); 



		Pnt3f CalculatedPoint;
		Vec3f CalculatedVector;
		for(UInt32 i(0) ; i<getPositions()->size() ; ++i)
		{
			//get's the Positions
			PositionTrans[i].multFullMatrixPnt(getPositions()->getValue(i), CalculatedPoint);
			getPositions()->setValue(CalculatedPoint, i);   //P[i]

			//get's the Normals
			PositionTrans[i].multMatrixVec(getNormals()-> getValue(i),CalculatedVector);
			getNormals()->setValue(CalculatedVector,i);
	
		}
	}
	else
	{
		//Error
	}

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonBlendedGeometry::SkeletonBlendedGeometry(void) :
    Inherited()
{
}

SkeletonBlendedGeometry::SkeletonBlendedGeometry(const SkeletonBlendedGeometry &source) :
    Inherited(source)
{
}

SkeletonBlendedGeometry::~SkeletonBlendedGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SkeletonBlendedGeometry::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & BonesFieldMask) ||
		(whichField & PositionIndexesFieldMask) ||
		(whichField & BlendAmountsFieldMask))
	{
		calculatePositions();
	}
	if((whichField & BaseGeometryFieldMask) &&
		getBaseGeometry() != Null)
	{
		if()
		{
		}
	}
}

void SkeletonBlendedGeometry::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SkeletonBlendedGeometry NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSKELETONBLENDEDGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSKELETONBLENDEDGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSKELETONBLENDEDGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

