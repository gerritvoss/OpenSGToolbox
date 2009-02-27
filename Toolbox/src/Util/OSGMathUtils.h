/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#ifndef _OPENSG_TOOLBOX_MATH_UTILS_H_
#define _OPENSG_TOOLBOX_MATH_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGMatrix.h>

#include <OpenSG/OSGBaseFunctions.h>

OSG_BEGIN_NAMESPACE

//Solves a system of linear equations of: 2 equations and 2 variables
//
//  Equation AX = B
//A = [ A11  A12 ]
//    [ A21  A22 ]
//X = [ R1   R2  ]
//B = [ B1   B2  ]
//
//The function returns -1 if there are an infinite number of solutions,
// 0 for 0 solutions,
// 1 for 1 solution

const Real32 REAL32_COMPARE_ERROR = 0.00000001;

template <class FloatTypeT>
bool isEqual(FloatTypeT Left, FloatTypeT Right, FloatTypeT ERR = REAL32_COMPARE_ERROR)
{
	return osgabs<FloatTypeT>(Left - Right) > ERR;
}

template<class ValueTypeT, class StorageInterfaceT>
Int8 intersectLines(const osg::PointInterface<ValueTypeT, StorageInterfaceT>& p1,
			    const osg::VectorInterface<ValueTypeT, StorageInterfaceT>& v1,
			    const osg::PointInterface<ValueTypeT, StorageInterfaceT>& p2,
			    const osg::VectorInterface<ValueTypeT, StorageInterfaceT>& v2,
				ValueTypeT& t1, ValueTypeT& t2,
				osg::PointInterface<ValueTypeT, StorageInterfaceT>& intersect)
{

	switch( solveLinearSystem2(v1.x(),-v2.x(),v1.y(),-v2.y(),p2.x()-p1.x(),p2.y()-p1.y(),t1,t2) )
	{
	case -1:
		intersect = p1;
		return -1;
		break;
	case 1:
		intersect = p1 + t1*v1;
		return 1;
		break;
	case 0:
    default:
		return 0;
		break;
	}
}

template<class ValueTypeT, class StorageInterfaceT>
osg::VectorInterface<ValueTypeT, StorageInterfaceT> reflect(const osg::VectorInterface<ValueTypeT, StorageInterfaceT>& Vec, const osg::VectorInterface<ValueTypeT, StorageInterfaceT>& Normal)
{
   osg::VectorInterface<ValueTypeT, StorageInterfaceT> Result;

   Result = Vec - (2 * (Vec.dot(Normal)) * Normal);

   return Result;
}

template <class FloatTypeT>
class Matrix22
{
public:
	typedef VectorInterface< Real32, VecStorage2<Real32> > VectorType;
	Matrix22(FloatTypeT a11, FloatTypeT a12, FloatTypeT a21, FloatTypeT a22)
	{
		_Values[0] = a11;
		_Values[1] = a12;
		_Values[2] = a21;
		_Values[3] = a22;
	}

	FloatTypeT det(void) const
	{
		return _Values[0]*_Values[3] - _Values[1]*_Values[2];
	}
	
	Matrix22<FloatTypeT > inverse(void) const
	{
		return Matrix22<FloatTypeT>(_Values[3], -_Values[1], -_Values[2], _Values[0]);
	}
	
	VectorType mult(const VectorType& src) const
	{
		return VectorType(_Values[0]*src[0] + _Values[1]*src[1], _Values[2]*src[0]+_Values[3]*src[1]);
	}

	VectorType operator*(const VectorType& src) const
	{
		return VectorType(_Values[0]*src[0] + _Values[1]*src[1], _Values[2]*src[0]+_Values[3]*src[1]);
	}
private:
	FloatTypeT _Values[4];
};

template <class FloatTypeT>
Int8 solveLinearSystem2(FloatTypeT A11, FloatTypeT A12, FloatTypeT A21, FloatTypeT A22, FloatTypeT B1, FloatTypeT B2, FloatTypeT& X1, FloatTypeT& X2)
{
	//Get the determinant of A
	FloatTypeT DetA= (A11*A22)-(A12*A21);

	if(DetA==0)
	{
		//There is not a unique solution
		if(isEqual(A21/A11,A22/A12) &&
			isEqual(A21/A11,B2/B1))
		{
			//There are an infinite number of solutions
			return -1;
		}
		else
		{
			//There are no solutions
			return 0;
		}
	}
	
	FloatTypeT DetA1= (B1*A22)-(B2*A12);
	
	FloatTypeT DetA2= (A11*B2)-(A21*B1);


	X1 = DetA1/DetA;
	X2 = DetA2/DetA;

	return 1;
}


void OSG_TOOLBOXLIB_DLLMAPPING makeViewFromUVND(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Vec3f& D);

void OSG_TOOLBOXLIB_DLLMAPPING makeViewFromUVNP(Matrix& Result,const Vec3f& U,const Vec3f& V,const Vec3f& N,const Pnt3f& P);

void OSG_TOOLBOXLIB_DLLMAPPING getUVNDFromMat(const Matrix& Mat,Vec3f& U,Vec3f& V,Vec3f& N,Vec3f& D);

void OSG_TOOLBOXLIB_DLLMAPPING getUVNPFromMat(const Matrix& Mat,Vec3f& U,Vec3f& V,Vec3f& N,Pnt3f& P);

void OSG_TOOLBOXLIB_DLLMAPPING getPFromViewMat(Pnt3f& P, const Matrix& Mat);

void OSG_TOOLBOXLIB_DLLMAPPING setViewMatEyePos(Matrix& Result,const Pnt3f& P);

OSG_END_NAMESPACE

#endif
