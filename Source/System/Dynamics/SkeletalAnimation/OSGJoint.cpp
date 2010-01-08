/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#include "OSGSkeleton.h"
#include "OSGJoint.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGJointBase.cpp file.
// To modify it, please change the .fcd file (OSGJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Joint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Matrix Joint::getAbsoluteTransformation(void) const
{
    Vec3f translate;
    Vec3f dummy1;
    Quaternion dummy2;
    Quaternion dummy3;
    _AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);

    _AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);

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
    if(getParentJoint() != NULL)
    {
        _AbsoluteTransformation = getParentJoint()->getAbsoluteTransformation();

        if(!getUseParentTranslation())
        {
            _AbsoluteTransformation.setTranslate(0.0, 0.0, 0.0);
        }

        Vec3f translate;
        Vec3f dummy1;
        Quaternion dummy2;
        Quaternion dummy3;
        _AbsoluteTransformation.getTransform(translate,dummy2,dummy1,dummy3);
    }
    else
    {
        _AbsoluteTransformation.setIdentity();
        rootJoint = true;
    }
    _AbsoluteTransformation.mult(getRelativeTransformation());

    //Absolute bind transformation
    if(getParentJoint() != NULL)
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

}

void Joint::updateTransformations(bool isRecursive, bool tellSkeleton)
{
    calculateTransformations();

    for(UInt32 i(0) ; i<getMFChildJoints()->size() ; ++i)
    {
        getChildJoints(i)->updateTransformations(true);
    }

    if(!isRecursive && getParentSkeleton() != NULL && tellSkeleton)
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

void Joint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if((whichField & BindRelativeTransformationFieldMask) || (whichField & RelativeTransformationFieldMask) || (whichField & ParentJointFieldMask))
	{
		updateTransformations(false);
	}

	if(whichField & ChildJointsFieldMask)
	{
		for(UInt32 i(0) ; i<getMFChildJoints()->size() ; ++i)
		{
            getChildJoints(i)->setParentJoint(this);
		}
	}
}

void Joint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Joint NI" << std::endl;
}

OSG_END_NAMESPACE
