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

#include "OSGBone.h"

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

void Bone::updateTransformation(void)
{
	//Calculate Relative Transformation
	Matrix m; //a matrix called m
	m.setTransform(Vec3f(getTranslation()), getRotation()); //calculates the the rotation of the bone
	beginEditCP(BonePtr(this), Bone::InternalRelativeTransformationFieldMask);
		setInternalRelativeTransformation(m); //field container
	endEditCP(BonePtr(this), Bone::InternalRelativeTransformationFieldMask);

	//Calculate Absolute Transformation
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

	if((whichField & RotationFieldMask) ||
		(whichField & InternalParentFieldMask) ||
		(whichField & LengthFieldMask) ||
		(whichField & TranslationFieldMask))
	{
		updateTransformation();
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

