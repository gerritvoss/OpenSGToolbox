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

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeleton.h"
#include "OSGBone.h"
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGIntersectActor.h>

#include <set>

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
#if OSG_VERSION == 0x010801

    // DrawAction
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionEnterHandler));
    
    DrawAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionLeaveHandler));

    // IntersectAction
    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, GeometryPtr,
              CNodePtr, Action *>(&Geometry::intersect));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            GeometryPtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&Geometry::intersectActor),
        getClassType());

    // RenderAction
    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionEnterHandler));
    
    RenderAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionLeaveHandler));
#else
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, GeometryPtr,
              CNodePtr, Action *>(&Geometry::intersect));

    IntersectActor::regClassEnter(
        osgTypedMethodFunctor2BaseCPtr<
            NewActionTypes::ResultE,
            GeometryPtr,
            NodeCorePtr,
            ActorBase::FunctorArgumentType &>(&Geometry::intersectActor),
        getClassType());

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
#endif
    
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SkeletonBlendedGeometry::addSkeleton(SkeletonPtr TheSkeleton)
{
    if(TheSkeleton != NullFC && getSkeletons().find(TheSkeleton) == getSkeletons().end())
    {
        beginEditCP(TheSkeleton, Skeleton::AttachedGeometriesFieldMask);
            TheSkeleton->getAttachedGeometries().push_back(SkeletonBlendedGeometryPtr(this));
        endEditCP(TheSkeleton, Skeleton::AttachedGeometriesFieldMask);

        
        beginEditCP(SkeletonBlendedGeometryPtr(this), SkeletonsFieldMask);
            getSkeletons().push_back(TheSkeleton);
        endEditCP(SkeletonBlendedGeometryPtr(this), SkeletonsFieldMask);
    }
}

void SkeletonBlendedGeometry::subSkeleton(SkeletonPtr TheSkeleton)
{
    if(TheSkeleton != NullFC)
    {
        MFSkeletonPtr::iterator SearchItor(getSkeletons().find(TheSkeleton));
        if(SearchItor != getSkeletons().end())
        {
            MFSkeletonBlendedGeometryPtr::iterator GeoSearchItor((*SearchItor)->getAttachedGeometries().find(SkeletonBlendedGeometryPtr(this)));
            if(GeoSearchItor != (*SearchItor)->getAttachedGeometries().end())
            {
                beginEditCP((*SearchItor), Skeleton::AttachedGeometriesFieldMask);
                    (*SearchItor)->getAttachedGeometries().erase(GeoSearchItor);
                endEditCP((*SearchItor), Skeleton::AttachedGeometriesFieldMask);
            }

            
            beginEditCP(SkeletonBlendedGeometryPtr(this), SkeletonsFieldMask);
                getSkeletons().erase(SearchItor);
            endEditCP(SkeletonBlendedGeometryPtr(this), SkeletonsFieldMask);
        }
    }
}

UInt32 SkeletonBlendedGeometry::numSkeletons(void) const
{
    return getSkeletons().size();
}

void SkeletonBlendedGeometry::subSkeleton(UInt32 Index)
{
    if(Index < getSkeletons().size())
    {
        subSkeleton(getSkeletons(Index));
    }
}

void SkeletonBlendedGeometry::addBoneBlending(const UInt32& PositionIndex, const BonePtr TheBone, const Real32& BlendAmount,  bool AttachedToEnd)
{
	beginEditCP(SkeletonBlendedGeometryPtr(this), BonesFieldMask | PositionIndexesFieldMask | BlendAmountsFieldMask | AttachedToEndFieldMask);
		getPositionIndexes().push_back(PositionIndex);
		getBones().push_back(TheBone);
		getBlendAmounts().push_back(BlendAmount);
		getAttachedToEnd().push_back(AttachedToEnd);
	endEditCP(SkeletonBlendedGeometryPtr(this), BonesFieldMask | PositionIndexesFieldMask | BlendAmountsFieldMask | AttachedToEndFieldMask);
}

void SkeletonBlendedGeometry::calculatePositions(void)
{
	if(getBaseGeometry() != NullFC &&
		getPositions() != NullFC &&
        getBaseGeometry()->getPositions() != NullFC &&
		(getPositionIndexes().size() == getBones().size() &&
		getPositionIndexes().size() == getBlendAmounts().size()))
	{
		Pnt3f CalculatedPoint;
		//Update the Positions and Normals
		std::set<UInt32> VisitedIndicies;

		//UInt32 VertexesTransformations[n];
		for(UInt32 i(0) ; i < getPositionIndexes().size() ; ++i)
		{
			if(getAttachedToEnd(i))
			{
				Matrix temp = getBones(i)->getEndInternalAbsoluteDifferenceTransformation();
				temp.scale(getBlendAmounts(i));
				temp.mult(getBaseGeometry()->getPositions()->getValue(getPositionIndexes(i)), CalculatedPoint);

			}
			else
			{
				Matrix temp = getBones(i)->getInternalAbsoluteDifferenceTransformation(getBlendMode());
				temp.scale(getBlendAmounts(i));
				temp.mult(getBaseGeometry()->getPositions()->getValue(getPositionIndexes(i)), CalculatedPoint);
			}


			if(VisitedIndicies.find(getPositionIndexes(i)) == VisitedIndicies.end())
			{
				//Overwrite
				VisitedIndicies.insert(getPositionIndexes(i));
			}
			else
			{
				//Add
				CalculatedPoint += getPositions()->getValue(getPositionIndexes(i));
			}
			getPositions()->setValue(CalculatedPoint, getPositionIndexes(i));
		}

		for(UInt32 i = 0; i < _parents.size(); i++)
		{
			_parents[i]->invalidateVolume();
		}
	}
	else
	{
		//Error
	}


}

void SkeletonBlendedGeometry::skeletonUpdated(void)
{
    calculatePositions();
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

	if((whichField & BaseGeometryFieldMask) &&
		getBaseGeometry() != NullFC)
	{
		if(getBaseGeometry()->getTypes() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TypesFieldMask);
                setTypes(getBaseGeometry()->getTypes());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TypesFieldMask);
		}
		if(getBaseGeometry()->getLengths() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::LengthsFieldMask);
                setLengths(getBaseGeometry()->getLengths());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::LengthsFieldMask);
		}
		if(getBaseGeometry()->getPositions() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::PositionsFieldMask);
			setPositions(getBaseGeometry()->getPositions()->clone());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::PositionsFieldMask);
		}
		if(getBaseGeometry()->getNormals() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::NormalsFieldMask);
                setNormals(getBaseGeometry()->getNormals()->clone());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::NormalsFieldMask);
		}
		if(getBaseGeometry()->getColors() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::ColorsFieldMask);
                setColors(getBaseGeometry()->getColors());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::ColorsFieldMask);
		}
		if(getBaseGeometry()->getSecondaryColors() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::SecondaryColorsFieldMask);
                setSecondaryColors(getBaseGeometry()->getSecondaryColors());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::SecondaryColorsFieldMask);
		}
		if(getBaseGeometry()->getTexCoords() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoordsFieldMask);
                setTexCoords(getBaseGeometry()->getTexCoords());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoordsFieldMask);
		}
		if(getBaseGeometry()->getTexCoords1() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords1FieldMask);
                setTexCoords1(getBaseGeometry()->getTexCoords1());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords1FieldMask);
		}
		if(getBaseGeometry()->getTexCoords2() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords2FieldMask);
                setTexCoords2(getBaseGeometry()->getTexCoords2());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords2FieldMask);
		}
		if(getBaseGeometry()->getTexCoords3() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords3FieldMask);
                setTexCoords3(getBaseGeometry()->getTexCoords3());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords3FieldMask);
		}
		if(getBaseGeometry()->getTexCoords4() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords4FieldMask);
                setTexCoords4(getBaseGeometry()->getTexCoords4());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords4FieldMask);
		}
		if(getBaseGeometry()->getTexCoords5() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords5FieldMask);
                setTexCoords5(getBaseGeometry()->getTexCoords5());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords5FieldMask);
		}
		if(getBaseGeometry()->getTexCoords6() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords6FieldMask);
                setTexCoords6(getBaseGeometry()->getTexCoords6());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords6FieldMask);
		}
		if(getBaseGeometry()->getTexCoords7() != NullFC)
		{
            beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords7FieldMask);
                setTexCoords7(getBaseGeometry()->getTexCoords7());
            endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::TexCoords7FieldMask);
		}
        beginEditCP(SkeletonBlendedGeometryPtr(this), Geometry::DlistCacheFieldMask | Geometry::MaterialFieldMask | Geometry::HighindicesFieldMask | Geometry::LowindicesFieldMask | Geometry::MaxindexFieldMask | Geometry::MinindexFieldMask | Geometry::IndexMappingFieldMask);
            getIndexMapping().setValues(getBaseGeometry()->getIndexMapping());
	        setMinindex(getBaseGeometry()->getMinindex());
	        setMaxindex(getBaseGeometry()->getMaxindex());
	        getLowindices().setValues(getBaseGeometry()->getLowindices());
	        getHighindices().setValues(getBaseGeometry()->getHighindices());
	        setMaterial(getBaseGeometry()->getMaterial());
	        setDlistCache(false);
	    endEditCP(SkeletonBlendedGeometryPtr(this), Geometry::DlistCacheFieldMask | Geometry::MaterialFieldMask | Geometry::HighindicesFieldMask | Geometry::LowindicesFieldMask | Geometry::MaxindexFieldMask | Geometry::MinindexFieldMask | Geometry::IndexMappingFieldMask);
    }

	if((whichField & BonesFieldMask) ||
		(whichField & PositionIndexesFieldMask) ||
		(whichField & BlendAmountsFieldMask))
	{
		calculatePositions();
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

