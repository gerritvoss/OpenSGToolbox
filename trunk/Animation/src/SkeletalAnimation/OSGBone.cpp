/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, John Morales                     *
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

#include "OSGBone.h"
#include "OSGSkeleton.h"
#include "OSGSkeletonBlendedGeometry.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Bone

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Bone::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


Matrix Bone::getInternalRelativeTransformation(void)
{
	return _InternalRelativeTransformation;
}

Matrix Bone::getInternalAbsoluteTransformation(void)
{
	return _InternalAbsoluteTransformation;
}

Matrix Bone::getInternalDefaultRelativeTransformation(void)
{
	return _InternalDefaultRelativeTransformation;
}

Matrix Bone::getInternalDefaultAbsoluteTransformation(void)
{
	return _InternalDefaultAbsoluteTransformation;
}

Matrix Bone::getInternalRelativeDifferenceTransformation(void)
{
	Matrix m;
	Vec3f DefaultTranslation(getDefaultTranslation());
	Vec3f Translation(getTranslation());
	if(getInternalParent() != NullFC)
	{
		m = getInternalParent()->getEndInternalRelativeDifferenceTransformation();
		getInternalParent()->getInternalDefaultRelativeTransformation().mult(DefaultTranslation);
		getInternalParent()->getInternalDefaultRelativeTransformation().mult(Translation);
	}

	Matrix Trans;
	Trans.setTranslate(Translation-DefaultTranslation);

	m.mult(Trans);
	return m;
}

Matrix Bone::getInternalAbsoluteDifferenceTransformation(UInt32 BlendMode)
{
	Matrix m;

	if(BlendMode == SkeletonBlendedGeometry::BLEND_SMOOTH)
	{
		//BLEND_SMOOTH
		Vec3f DefaultTranslation(getDefaultTranslation());
		Vec3f Translation(getTranslation());
		if(getInternalParent() != NullFC)
		{
			m = getInternalParent()->getEndInternalAbsoluteDifferenceTransformation();
			getInternalParent()->getInternalDefaultAbsoluteTransformation().mult(DefaultTranslation);
			getInternalParent()->getInternalDefaultAbsoluteTransformation().mult(Translation);
		}

		Matrix Trans;
		Trans.setTranslate(Translation-DefaultTranslation);

		m.mult(Trans);
	}
	else
	{
		//BLEND_RIGID
		m = _InternalAbsoluteDifferenceTransformation;
	}


	
	return m;
}

Matrix Bone::getEndInternalRelativeDifferenceTransformation(void)
{
	//Dif(end) = Current * [Translation(z)*CurrentLength] * ~[Translation(z)*DefaultLength] * ~Default
	
	Matrix EndRelativeDifference;

	//Set up operands
	Matrix CurrentTransformation = getInternalRelativeTransformation();
	
	Matrix TranslationCurrent;
	Vec3f CurrentLength(0.0f, 0.0f, getLength());
	TranslationCurrent.setTranslate(CurrentLength);

	Matrix TranslationDefault;
	Vec3f DefaultLength(0.0f, 0.0f, getDefaultLength());
	TranslationDefault.setTranslate(DefaultLength);
	TranslationDefault.invert();

	Matrix RelativeDefault = getInternalDefaultRelativeTransformation();
	RelativeDefault.invert();

	//Perform calculation
	EndRelativeDifference = CurrentTransformation;
	TranslationDefault.mult(RelativeDefault);
	TranslationCurrent.mult(TranslationDefault);
	EndRelativeDifference.mult(TranslationCurrent);

	return EndRelativeDifference;
}

Matrix Bone::getEndInternalAbsoluteDifferenceTransformation(void)
{
	//Dif(end) = Current * [Translation(z)*CurrentLength] * ~[Translation(z)*DefaultLength] * ~Default
	
	Matrix EndAbsoluteDifference;

	//Set up operands
	Matrix CurrentTransformation = getInternalAbsoluteTransformation();
	
	Matrix TranslationCurrent;
	Vec3f CurrentLength(0.0f, 0.0f, getLength());
	TranslationCurrent.setTranslate(CurrentLength);

	Matrix TranslationDefault;
	Vec3f DefaultLength(0.0f, 0.0f, getDefaultLength());
	TranslationDefault.setTranslate(DefaultLength);
	TranslationDefault.invert();

	Matrix AbsoluteDefault = getInternalDefaultAbsoluteTransformation();
	AbsoluteDefault.invert();

	//Perform calculation
	EndAbsoluteDifference = CurrentTransformation;
	TranslationDefault.mult(AbsoluteDefault);
	TranslationCurrent.mult(TranslationDefault);
	EndAbsoluteDifference.mult(TranslationCurrent);

	return EndAbsoluteDifference;
}


void Bone::addChild(BonePtr TheBone)
{
    //Remove the old parent if the bone has one
    if(TheBone->getParent() != NullFC)
    {
        TheBone->getParent()->removeChild(TheBone);
    }

    beginEditCP(BonePtr(this), Bone::InternalChildrenFieldMask);
		getInternalChildren().push_back(TheBone);
    endEditCP(BonePtr(this), Bone::InternalChildrenFieldMask);

    beginEditCP(TheBone, Bone::InternalParentFieldMask);
        TheBone->setInternalParent(BonePtr(this));
    endEditCP(TheBone, Bone::InternalParentFieldMask);
}

void Bone::removeChild(BonePtr TheBone)
{
    MFBonePtr::iterator SearchItor = getInternalChildren().find(TheBone);

    if(SearchItor != getInternalChildren().end())
    {
        beginEditCP((*SearchItor), Bone::InternalParentFieldMask);
            (*SearchItor)->setInternalParent(NullFC);
        endEditCP((*SearchItor), Bone::InternalParentFieldMask);

		beginEditCP(BonePtr(this), Bone::InternalChildrenFieldMask);
			getInternalChildren().erase(SearchItor);
		endEditCP(BonePtr(this), Bone::InternalChildrenFieldMask);
    }
}

void Bone::removeChild(UInt32 Index)
{
    if(Index < getInternalChildren().size())
    {
        removeChild(getChild(Index));
    }
}

void Bone::setBindPosition()
{
	//Update DefaultRotation, DefaultTranslation, and DefaultLength Field Containers
	beginEditCP(BonePtr(this), DefaultRotationFieldMask | DefaultTranslationFieldMask | DefaultLengthFieldMask);
		setDefaultRotation(getRotation());
		setDefaultTranslation(getTranslation());
		setDefaultLength(getLength());
	endEditCP(BonePtr(this), DefaultRotationFieldMask | DefaultTranslationFieldMask | DefaultLengthFieldMask);
}

void Bone::calculateRelativeTransformation(bool isDefault)
{
	//Calculate Relative Transformation
	Vec3f Translation;
	if(getInternalParent() != NullFC)
	{
		if (isDefault)
		{
			Translation += Vec3f(0.0,0.0,getInternalParent()->getDefaultLength());
		}
		else
		{
			Translation += Vec3f(0.0,0.0,getInternalParent()->getLength());
		}
	}

	if(isDefault)
	{
		Translation += getDefaultTranslation();
		_InternalDefaultRelativeTransformation.setTransform(Translation , getDefaultRotation()); //calculates the the rotation of the bone
	}
	else
	{
		Translation += getTranslation();
		_InternalRelativeTransformation.setTransform(Translation , getRotation()); //calculates the the rotation of the bone
	}	
}

void Bone::calculateAbsoluteTransformation(bool isDefault)
{
	//Calculate Absolute Transformation
	if(isDefault)
	{
		if(getInternalParent() !=NullFC)
		{
			_InternalDefaultAbsoluteTransformation = getInternalParent()->getInternalDefaultAbsoluteTransformation();
			_InternalDefaultAbsoluteTransformation.mult( getInternalDefaultRelativeTransformation() );
		}
		else
		{
			_InternalDefaultAbsoluteTransformation = getInternalDefaultRelativeTransformation();
		}
	}
	else
	{
		if(getInternalParent() !=NullFC)
		{
			_InternalAbsoluteTransformation = getInternalParent()->getInternalAbsoluteTransformation();
			_InternalAbsoluteTransformation.mult( getInternalRelativeTransformation() );
		}
		else
		{
			_InternalAbsoluteTransformation = getInternalRelativeTransformation();
		}
	}
}

void Bone::calculateDifferenceTransformations(void)
{
	_InternalRelativeDifferenceTransformation = getInternalDefaultRelativeTransformation();
	_InternalRelativeDifferenceTransformation.invert();
	_InternalRelativeDifferenceTransformation.multLeft(getInternalRelativeTransformation());

	
	_InternalAbsoluteDifferenceTransformation = getInternalDefaultAbsoluteTransformation();
	_InternalAbsoluteDifferenceTransformation.invert();
	_InternalAbsoluteDifferenceTransformation.multLeft(getInternalAbsoluteTransformation());
}

void Bone::updateTransformation(bool IsRecursiveUpdate = false)
{
	//=====Update relative & absolute transformations=====//
	//Vec3f Translation;
	//if(getInternalParent() != NullFC)
	//{
	//	Translation += Vec3f(0.0,0.0,getInternalParent()->getLength());
	//}
	//Translation += getTranslation();
	//_InternalRelativeTransformation.setTransform(Translation , getRotation()); //calculates the the rotation of the bone
	
	calculateRelativeTransformation(true);
	calculateAbsoluteTransformation(true);

	calculateRelativeTransformation(false);

	//Calculate Absolute Transformation
	/*if(getInternalParent() !=NullFC)
	{
		_InternalAbsoluteTransformation = getInternalParent()->getInternalAbsoluteTransformation();
		_InternalAbsoluteTransformation.mult( getInternalRelativeTransformation() );
	}
	else
	{
		_InternalAbsoluteTransformation = getInternalRelativeTransformation();
	}*/
	
	
	calculateAbsoluteTransformation(false);
	
	/*_InternalRelativeDifferenceTransformation = getInternalDefaultRelativeTransformation();
	_InternalRelativeDifferenceTransformation.invert();
	_InternalRelativeDifferenceTransformation.multLeft(getInternalRelativeTransformation());

	
	_InternalAbsoluteDifferenceTransformation = getInternalDefaultAbsoluteTransformation();
	_InternalAbsoluteDifferenceTransformation.invert();
	_InternalAbsoluteDifferenceTransformation.multLeft(getInternalAbsoluteTransformation());*/

	calculateDifferenceTransformations();
	

	//Tell all children to update Transformations
	for(UInt32 i(0) ; i<getNumChildren() ; ++i)
	{
		getChild(i)->updateTransformation(true);
	}
	

	//Tell skeleton that the bone has changed
	if(!IsRecursiveUpdate && getInternalSkeleton() != NullFC)
	{
		getInternalSkeleton()->Skeleton::skeletonUpdated();
	}	
		
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Bone::Bone(void) :
    Inherited()
{
}

Bone::Bone(const Bone &source) :
    Inherited(source)
{
}

Bone::~Bone(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Bone::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	//if((whichField & DefaultRotationFieldMask) ||
	//	(whichField & DefaultLengthFieldMask) ||
	//	(whichField & DefaultTranslationFieldMask) ||
	//	(whichField & InternalParentFieldMask))
	//{

	//	//=====Set default internal relative & absolute transformations; no need to calculate them again=====//
	//	//Calculate Default Relative Transformation
	//	//Vec3f DefaultTranslation;
	//	//if(getInternalParent() != NullFC)
	//	//{
	//	//	DefaultTranslation += Vec3f(0.0,0.0,getInternalParent()->getDefaultLength());
	//	//}
	//	//DefaultTranslation += getDefaultTranslation();
	//	//_InternalDefaultRelativeTransformation.setTransform(DefaultTranslation , getDefaultRotation()); //calculates the the rotation of the bone
	//	
	//	calculateRelativeTransformation(true);
	//	
	//	//Calculate Default Absolute Transformation
	//	/*if(getInternalParent() !=NullFC)
	//	{
	//		_InternalDefaultAbsoluteTransformation = getInternalParent()->getInternalDefaultAbsoluteTransformation();
	//		_InternalDefaultAbsoluteTransformation.mult( getInternalDefaultRelativeTransformation() );
	//	}
	//	else
	//	{
	//		_InternalDefaultAbsoluteTransformation = getInternalDefaultRelativeTransformation();
	//	}*/
	//	calculateAbsoluteTransformation(true);
	//}

	if((whichField & RotationFieldMask) ||
		(whichField & InternalParentFieldMask) ||
		(whichField & LengthFieldMask) ||
		(whichField & TranslationFieldMask) ||
		(whichField & DefaultRotationFieldMask) ||
		(whichField & DefaultLengthFieldMask) ||
		(whichField & DefaultTranslationFieldMask) ||
		(whichField & InternalSkeletonFieldMask))
	{
		updateTransformation(false);
	}
}

void Bone::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Bone NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBONEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBONEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBONEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

