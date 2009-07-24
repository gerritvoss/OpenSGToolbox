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

#include "OSGJoint.h"
#include "OSGSkeleton.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Joint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Joint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Matrix Joint::getAbsoluteTransformation(void) const
{
	//if(_AbsoluteTransformation == Matrix().identity())
//	{
//		std::cout << "\nGetting Absolute Transformation:\n" << _AbsoluteTransformation << "\n" << std::endl;
//	}

		Vec3f translate;
		Vec3f dummy1;
		Quaternion dummy2;
		Quaternion dummy3;
		_AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);
		if (_AbsoluteTransformation == Matrix().identity())//translate == Vec3f(0, 0, 0))
		{
			std::cout << "\nGetting Absolute Transformation:\nTranslation: " << translate << "\n" << _AbsoluteTransformation << "\n[3][0]: " << _AbsoluteTransformation[3][0] << "\n" << std::endl;
		}

		_AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);
		if (_AbsoluteTransformation == Matrix().identity())//translate == Vec3f(0, 0, 0))
		{
			std::cout << "\nGetting Absolute Transformation2:\nTranslation: " << translate << "\n" << _AbsoluteTransformation << "\n[3][0]: " << _AbsoluteTransformation[3][0] << "\n" << std::endl;
		}
	
	
	return _AbsoluteTransformation;
	
	
}

Matrix Joint::getBindAbsoluteTransformation(void) const
{
	return _BindAbsoluteTransformation;
}

const Matrix& Joint::getAbsoluteDifferenceTransformation(void) const
{
	return _AbsoluteDifferenceTransformation;
}

const Matrix& Joint::getRelativeDifferenceTransformation(void) const
{
	return _RelativeDifferenceTransformation;
}

void Joint::calculateTransformations(void)
{
	bool rootJoint = false;

	//Absolute transformation
	if(getParentJoint() != NullFC)
	{
		_AbsoluteTransformation = getParentJoint()->getAbsoluteTransformation();
		
		if(!getUseParentTranslation())
		{
			_AbsoluteTransformation.setTranslate(0.0, 0.0, 0.0);
			std::cout << "Don't use parent translation!!!" << std::endl;
		}
		
		
		
		
		Vec3f translate;
		Vec3f dummy1;
		Quaternion dummy2;
		Quaternion dummy3;
		_AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);
		if (_AbsoluteTransformation == Matrix().identity())//translate == Vec3f(0, 0, 0))
		{
			std::cout << "Setting Absolute Transformation:\nTranslation: " << translate << "\n" << _AbsoluteTransformation << "\n[3][0]: " << _AbsoluteTransformation[3][0] << "\n" << std::endl;
		}
		
	}
	else
	{
		_AbsoluteTransformation.setIdentity();
		rootJoint = true;
	}
	_AbsoluteTransformation.mult(getRelativeTransformation());

	//Absolute bind transformation
	if(getParentJoint() != NullFC)
	{
		_BindAbsoluteTransformation = getParentJoint()->getBindAbsoluteTransformation();

		if(!getUseParentTranslation())
		{
			_BindAbsoluteTransformation.setTranslate(0.0, 0.0, 0.0);
		}
	}
	else
	{
		_BindAbsoluteTransformation.setIdentity();
	}
	_BindAbsoluteTransformation.mult(getBindRelativeTransformation());

	//Absolute difference transformation
	_AbsoluteDifferenceTransformation = getBindAbsoluteTransformation();
	_AbsoluteDifferenceTransformation.invert();
	_AbsoluteDifferenceTransformation.multLeft(getAbsoluteTransformation());

	//Relative difference transformation
	_RelativeDifferenceTransformation = getBindRelativeTransformation();
	_RelativeDifferenceTransformation.invert();
	_RelativeDifferenceTransformation.multLeft(getRelativeTransformation());
	
	if (_RelativeDifferenceTransformation != Matrix().identity())
	{
		//std::cout << _RelativeDifferenceTransformation << std::endl;
	}
	
	if (!rootJoint && _AbsoluteTransformation == Matrix().identity()) 
	{
		std::cout << "AbsTrans is 0!!!" << std::endl;
	}
	
	//_RelativeDifferenceTransformation.setTranslate(0, 0, 0);
	//if(rootJoint)// && _RelativeDifferenceTransformation != Matrix().identity())
//	{
//		Vec3f dummy1;
//		Quaternion dummy2;
//		Quaternion dummy3;
//	
//		Vec3f lastTranslate;
//		_lastRootTrans.getTransform(lastTranslate, dummy2, dummy1, dummy3);
//		Vec3f currentTranslate;
//		_RelativeDifferenceTransformation.getTransform(currentTranslate,dummy2, dummy1, dummy3);
//		Vec3f diff = currentTranslate - lastTranslate;
//		
//		double tolerance = .1;
//		if(diff.x() > tolerance || diff.x() < -1*tolerance || diff.y() > tolerance || diff.y() < -1*tolerance || diff.z() > tolerance || diff.z() < -1*tolerance)
//		{
//			std::cout << "Previous:\n" << _lastRootTrans << std::endl;
//			std::cout << "Current:\n" << _RelativeDifferenceTransformation << std::endl;
//		}
//		
//		_lastRootTrans = _RelativeDifferenceTransformation;
//	}
}

void Joint::updateTransformations(bool isRecursive, bool tellSkeleton)
{
	calculateTransformations();

	for (int i(0); i < getChildJoints().size(); ++i)
	{
		getChildJoints(i)->updateTransformations(true);
	}

	if(!isRecursive && getParentSkeleton() != NullFC && tellSkeleton)
	{
		//Tell skeleton joint has been updated
		getParentSkeleton()->skeletonUpdated();
	}
}

Matrix Joint::previewRelativeDifferenceTransformation(Matrix relativeTransformation)
{
	//Relative difference transformation
	Matrix RelDifTrans = getBindRelativeTransformation();
	RelDifTrans.invert();
	RelDifTrans.multLeft(relativeTransformation);

	return RelDifTrans;
}

Matrix Joint::previewRelativeTransformation(Matrix relativeDifferenceTransformation)
{
	Matrix RelTrans = relativeDifferenceTransformation;
	RelTrans.mult(getBindRelativeTransformation());

	return RelTrans;
}



/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Joint::Joint(void) :
    Inherited()
{
}

Joint::Joint(const Joint &source) :
    Inherited(source)
{
}

Joint::~Joint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Joint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	if((whichField & BindRelativeTransformationFieldMask) || (whichField & RelativeTransformationFieldMask) || (whichField & ParentJointFieldMask))
	{
		updateTransformations(false);
	}

	if(whichField & ChildJointsFieldMask)
	{
		for(UInt32 i(0) ; i<getChildJoints().size() ; ++i)
		{
			beginEditCP(getChildJoints(i), ParentJointFieldMask);
				getChildJoints(i)->setParentJoint(JointPtr(this));
			endEditCP(getChildJoints(i), ParentJointFieldMask);
		}
	}
}

void Joint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Joint NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

