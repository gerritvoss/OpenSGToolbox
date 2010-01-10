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

#include "OSGSkeletonBlendedGeometry.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"

#include <set>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSkeletonBlendedGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGSkeletonBlendedGeometry.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SkeletonBlendedGeometry::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(&Geometry::intersect));

        RenderAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionEnterHandler));
                
        RenderAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionLeaveHandler));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void SkeletonBlendedGeometry::addJointBlending(const UInt32& PositionIndex, const JointUnrecPtr TheJoint, const Real32& BlendAmount)
{
    editMFPositionIndexes()->push_back(PositionIndex);
    pushToJoints(TheJoint);
    editMFBlendAmounts()->push_back(BlendAmount);
}

void SkeletonBlendedGeometry::calculatePositions(void)
{
	if(getBaseGeometry() == NULL)
	{
		//Error
		SWARNING << "SkeletonBlendedGeometry::calculatePositions(): Base Geometry is NULL." << std::endl;
        return;
	if(getPositions() == NULL)
	{
		//Error
		SWARNING << "SkeletonBlendedGeometry::calculatePositions(): Positions is NULL." << std::endl;
        return;
	}
	if(getBaseGeometry()->getPositions() == NULL)
	{
		//Error
		SWARNING << "SkeletonBlendedGeometry::calculatePositions(): Base Geometry Postions is NULL." << std::endl;
        return;
	}
	if(getMFPositionIndexes()->size() != getMFJoints()->size())
	{
		//Error
		SWARNING << "SkeletonBlendedGeometry::calculatePositions(): Positions Indexes size is not the same as the affecting Joints size." << std::endl;
        return;
	}
	}
	if(getMFPositionIndexes()->size() != getMFBlendAmounts()->size())
	{
		//Error
		SWARNING << "SkeletonBlendedGeometry::calculatePositions(): Positions Indexes size is not the same as the affecting blend amount size." << std::endl;
        return;
	}

    Pnt3f CalculatedPoint;
    Pnt3f PointTemp;
    Vec3f CalculatedNormal;


    //Set the values of all points to 0
    for (int i(0); i < getPositions()->size(); ++i)
    {
        getPositions()->setValue(Pnt3f(0, 0, 0), i);
    }

    //Update the Positions and Normals
    for(UInt32 i(0) ; i < getMFPositionIndexes()->size() ; ++i)
    {

        Matrix temp = getJoints(i)->getAbsoluteDifferenceTransformation();
        temp.scale(getBlendAmounts(i));
        getBaseGeometry()->getPositions()->getValue<Pnt3f>(PointTemp, getPositionIndexes(i));
        temp.mult(PointTemp, CalculatedPoint);
        //temp.mult(getBaseGeometry()->getNormals()->getValue(getPositionIndexes(i)), CalculatedNormal);
        

        //Add
        CalculatedPoint += PointTemp.subZero();
        getPositions()->setValue<Pnt3f>(CalculatedPoint, getPositionIndexes(i));
    }

    for(UInt32 i = 0; i < _mfParents.size(); i++)
    {
        _mfParents[i]->invalidateVolume();
    }

    _volumeCache.setValid();
    _volumeCache.setEmpty();
}

void SkeletonBlendedGeometry::skeletonChanged(const SkeletonEventUnrecPtr e)
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

void SkeletonBlendedGeometry::changed(ConstFieldMaskArg whichField, 
                                      UInt32            origin,
                                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & BaseGeometryFieldMask) &&
            getBaseGeometry() != NULL)
    {
        if(getBaseGeometry()->getTypes() != NULL)
        {
            setTypes(getBaseGeometry()->getTypes());
        }
        if(getBaseGeometry()->getLengths() != NULL)
        {
            setLengths(getBaseGeometry()->getLengths());
        }
        if(getBaseGeometry()->getPositions() != NULL)
        {
            GeoPropertyUnrecPtr Pos(getBaseGeometry()->getPositions()->clone());
            setPositions(dynamic_pointer_cast<GeoVectorProperty>(Pos));
        }
        if(getBaseGeometry()->getNormals() != NULL)
        {
            GeoPropertyUnrecPtr Norm(getBaseGeometry()->getNormals()->clone());
            setNormals(dynamic_pointer_cast<GeoVectorProperty>(Norm));
        }
        if(getBaseGeometry()->getColors() != NULL)
        {
            setColors(getBaseGeometry()->getColors());
        }
        if(getBaseGeometry()->getSecondaryColors() != NULL)
        {
            setSecondaryColors(getBaseGeometry()->getSecondaryColors());
        }
        if(getBaseGeometry()->getTexCoords() != NULL)
        {
            setTexCoords(getBaseGeometry()->getTexCoords());
        }
        if(getBaseGeometry()->getTexCoords1() != NULL)
        {
            setTexCoords1(getBaseGeometry()->getTexCoords1());
        }
        if(getBaseGeometry()->getTexCoords2() != NULL)
        {
            setTexCoords2(getBaseGeometry()->getTexCoords2());
        }
        if(getBaseGeometry()->getTexCoords3() != NULL)
        {
            setTexCoords3(getBaseGeometry()->getTexCoords3());
        }
        if(getBaseGeometry()->getTexCoords4() != NULL)
        {
            setTexCoords4(getBaseGeometry()->getTexCoords4());
        }
        if(getBaseGeometry()->getTexCoords5() != NULL)
        {
            setTexCoords5(getBaseGeometry()->getTexCoords5());
        }
        if(getBaseGeometry()->getTexCoords6() != NULL)
        {
            setTexCoords6(getBaseGeometry()->getTexCoords6());
        }
        if(getBaseGeometry()->getTexCoords7() != NULL)
        {
            setTexCoords7(getBaseGeometry()->getTexCoords7());
        }
        if(getBaseGeometry()->getIndices() != NULL)
        {
            setIndices(getBaseGeometry()->getIndices());
        }
        setMaterial(getBaseGeometry()->getMaterial());
    }

    if((whichField & JointsFieldMask) ||
        (whichField & PositionIndexesFieldMask) ||
        (whichField & BlendAmountsFieldMask))
    {
        calculatePositions();
    }

    if(whichField & SkeletonsFieldMask)
    {
        for(std::vector<EventConnection>::iterator Itor(_SkeletonListenerConnections.begin()) ; Itor != _SkeletonListenerConnections.end() ; ++Itor)
        {
            Itor->disconnect();
        }

        _SkeletonListenerConnections.clear();

        for(UInt32 i(0) ; i<getMFSkeletons()->size() ; ++i)
        {
            _SkeletonListenerConnections.push_back(getSkeletons(i)->addSkeletonListener(this));
        }
    }
}

void SkeletonBlendedGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonBlendedGeometry NI" << std::endl;
}

OSG_END_NAMESPACE
