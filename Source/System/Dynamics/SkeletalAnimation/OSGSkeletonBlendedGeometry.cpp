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

#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"
#include <boost/bind.hpp>

#include "OSGGeoPropertyUtils.h"

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
#ifndef OSG_EMBEDDED
        IntersectAction::registerEnterDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &SkeletonBlendedGeometry::intersectEnter));
        
        IntersectAction::registerLeaveDefault(
            getClassType(),
            reinterpret_cast<Action::Callback>(
                &SkeletonBlendedGeometry::intersectLeave));
#endif

        RenderAction::registerEnterDefault(
            SkeletonBlendedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkeletonBlendedGeometry::renderEnter));
        
        RenderAction::registerLeaveDefault(
            SkeletonBlendedGeometry::getClassType(),
            reinterpret_cast<Action::Callback>(&SkeletonBlendedGeometry::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 SkeletonBlendedGeometry::getNumJoints(void) const
{
    return getMFInternalJoints()->size();
}

Node* SkeletonBlendedGeometry::getJoint(UInt32 index) const
{
    if(index < getMFInternalJoints()->size())
    {
        return (*getMFInternalJoints())[index];
    }
    else
    {
        return NULL;
    }
}

Matrix SkeletonBlendedGeometry::getJointInvBind(UInt32 index) const
{
    if(index < getMFInternalJointInvBindTransformations()->size())
    {
        return (*getMFInternalJointInvBindTransformations())[index];
    }
    else
    {
        return Matrix();
    }
}

void SkeletonBlendedGeometry::pushToJoints(Node* const jointValue,
                           const Matrix& invBind  )
{
    pushToInternalJoints(jointValue);
    editMFInternalJointInvBindTransformations()->push_back(invBind);
}

void SkeletonBlendedGeometry::removeFromJoints(UInt32 uiIndex)
{
    removeFromInternalJoints(uiIndex);
    editMFInternalJointInvBindTransformations()->erase(uiIndex);
}

void SkeletonBlendedGeometry::removeObjFromJoints(Node* const jointValue)
{
    editMFInternalJointInvBindTransformations()->erase(getMFInternalJoints()->findIndex(jointValue));
    removeObjFromInternalJoints(jointValue);
}

void SkeletonBlendedGeometry::clearJoints(void)
{
    clearInternalJoints();
    editMFInternalJointInvBindTransformations()->clear();
}

void SkeletonBlendedGeometry::drawPrimitives(DrawEnv *pEnv)
{
    if(getBaseGeometry())
    {
        calculateJointTransform();
        if(_NeedRecalc)
        {
            calculatePositions();
        }
    }

    Inherited::drawPrimitives(pEnv);
}

void SkeletonBlendedGeometry::skeletonUpdated(void)
{
	produceSkeletonChanged();
    if(getBaseGeometry())
    {
        calculatePositions();
    }
}

Matrix SkeletonBlendedGeometry::getAbsoluteTransformation(UInt32 index) const
{
    return getInternalJoints(index)->getToWorld();
}

Matrix SkeletonBlendedGeometry::getAbsoluteBindTransformation(UInt32 index) const
{
    Matrix Result(getInternalJointInvBindTransformations(index));
    Result.invert();
    return Result;
}

Int32 SkeletonBlendedGeometry::getJointIndex(Node* theJoint) const
{
    return getMFInternalJoints()->findIndex(theJoint);
}

Int32 SkeletonBlendedGeometry::getJointParentIndex(UInt32 index) const
{
    Node* ChildJoint(getJoint(index));

    if(ChildJoint->getParent())
    {
        return getMFInternalJoints()->findIndex(ChildJoint->getParent());
    }
    return -1;
}

void SkeletonBlendedGeometry::addJointBlending(UInt32 VertexIndex, Node* const TheJoint, Real32 BlendAmount)
{
    if(getWeightIndexes() == NULL)
    {
        GeoUInt32PropertyUnrecPtr Indexes = GeoUInt32Property::create();
        setWeightIndexes(Indexes);
    }
    if(getWeights() == NULL)
    {
        GeoVec1fPropertyUnrecPtr Weights = GeoVec1fProperty::create();
        setWeights(Weights);
    }
    
    Int32 JointIndex(getMFInternalJoints()->findIndex(TheJoint));
    if(JointIndex < 0)
    {
        SFATAL << "Cannot add weight for joint, because that joint is not connected." << std::endl;
        return;
    }

    //Vertex Index
    getWeightIndexes()->push_back(VertexIndex);

    //Joint Index
    getWeightIndexes()->push_back(JointIndex);

    //Weight Index
    getWeightIndexes()->push_back(getWeights()->getSize());

    getWeights()->push_back(Pnt1f(BlendAmount));
}

void SkeletonBlendedGeometry::addJointBlending(UInt32 VertexIndex,
                                               UInt32 JointIndex,
                                               Real32 BlendAmount)
{
    if(getWeightIndexes() == NULL)
    {
        GeoUInt32PropertyUnrecPtr Indexes = GeoUInt32Property::create();
        setWeightIndexes(Indexes);
    }
    if(getWeights() == NULL)
    {
        GeoVec1fPropertyUnrecPtr Weights = GeoVec1fProperty::create();
        setWeights(Weights);
    }

    //Vertex Index
    getWeightIndexes()->push_back(VertexIndex);

    //Joint Index
    getWeightIndexes()->push_back(JointIndex);

    //Weight Index
    getWeightIndexes()->push_back(getWeights()->getSize());

    getWeights()->push_back(Pnt1f(BlendAmount));
}

void SkeletonBlendedGeometry::addJointBlending(UInt32 VertexIndex,
                                               UInt32 JointIndex,
                                               UInt32 WeightIndex)
{
    if(getWeightIndexes() == NULL)
    {
        GeoUInt32PropertyUnrecPtr Indexes = GeoUInt32Property::create();
        setWeightIndexes(Indexes);
    }
    if(getWeights() == NULL)
    {
        GeoVec1fPropertyUnrecPtr Weights = GeoVec1fProperty::create();
        setWeights(Weights);
    }

    //Vertex Index
    getWeightIndexes()->push_back(VertexIndex);

    //Joint Index
    getWeightIndexes()->push_back(JointIndex);

    //Weight Index
    getWeightIndexes()->push_back(WeightIndex);
}

void SkeletonBlendedGeometry::calculateJointTransform(void)
{
    //Precalculate the matrix for each joint
    Matrix m;
    for(UInt32 i(0) ; i<getNumJoints() ; ++i)
    {
        m.setValue(getBindTransformation());
        m.multLeft(getInternalJointInvBindTransformations(i));
        m.multLeft(getJoint(i)->getToWorld());

        if( m != _JointPoseTransforms[i])
        {
            _JointPoseTransforms[i].setValue(m);
            _NeedRecalc             = true;
        }
    }
}

void SkeletonBlendedGeometry::calculatePositions(void)
{
	if(getBaseGeometry() == NULL)
	{
		//Error
		SWARNING << "Base Geometry is NULL." << std::endl;
        return;
    }
	if(getPositions() == NULL)
	{
		//Error
		SWARNING << "Positions is NULL." << std::endl;
        return;
	}
	if(getBaseGeometry()->getPositions() == NULL)
	{
		//Error
		SWARNING << "Base Geometry Postions is NULL." << std::endl;
        return;
	}

    Pnt3f CalculatedPoint;
    Pnt3f BasePoint;
    //Vec3f CalculatedNormal;

    //Zero the Position Property
    zeroGeoProperty(getPositions());

    //Update the Positions and Normals
    UInt32 WeightIndex, JointIndex, VertexIndex;
	UInt32 NumWeightIndexTuples(getWeightIndexes()->size()/3);
    for(UInt32 i(0) ; i < NumWeightIndexTuples ; ++i)
    {
        VertexIndex = getWeightIndexes()->getValue<UInt32>( 3 * i     );
        JointIndex  = getWeightIndexes()->getValue<UInt32>((3 * i) + 1);
        WeightIndex = getWeightIndexes()->getValue<UInt32>((3 * i) + 2);

        //v*BSM*IBM*JM*JW
        getBaseGeometry()->getPositions()->getValue<Pnt3f>(BasePoint, VertexIndex);

        _JointPoseTransforms[JointIndex].mult(BasePoint, BasePoint);

        //Add the displacement to the value at this position
        getPositions()->getValue<Pnt3f>(CalculatedPoint, VertexIndex);
        CalculatedPoint += Vec3f(BasePoint) * getWeights()->getValue<Pnt1f>(WeightIndex)[0];
        getPositions()->setValue<Pnt3f>(CalculatedPoint, VertexIndex);
    }

    for(UInt32 i = 0; i < _mfParents.size(); i++)
    {
        _mfParents[i]->invalidateVolume();
    }

    _volumeCache.setValid();
    _volumeCache.setEmpty();

    _NeedRecalc = false;
}

void SkeletonBlendedGeometry::produceSkeletonChanged(void)
{
    SkeletonEventDetailsUnrecPtr Details = SkeletonEventDetails::create(this,getTimeStamp());
   
    Inherited::produceSkeletonChanged(Details);
}

/*------------------------- volume update -------------------------------*/

void SkeletonBlendedGeometry::adjustVolume(Volume &volume)
{
    Inherited::adjustVolume(volume);
    volume.transform(_invWorld);
}

void SkeletonBlendedGeometry::accumulateMatrix(Matrixr &result)
{
    Inherited::accumulateMatrix(result);
    result.mult(_invWorld);
}

/*------------------------- calc matrix ---------------------------------*/

void SkeletonBlendedGeometry::calcMatrix(const Matrixr        &mToWorld,
                                        Matrixr        &mResult)
{
    mResult.invertFrom(mToWorld);

    _invWorld = mResult; 
}

void SkeletonBlendedGeometry::initMatrix(const Matrixr &mToWorld)
{
    _invWorld.invertFrom(mToWorld);
}
/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

/*-------------------------------------------------------------------------*/
/*                            Intersect                                    */

#ifndef OSG_EMBEDDED
Action::ResultE SkeletonBlendedGeometry::intersectEnter(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_invWorld);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Inherited::intersect(action);
}

Action::ResultE SkeletonBlendedGeometry::intersectLeave(Action *action)
{
    IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    Matrix           m(_invWorld);

    Pnt3f pos;
    Vec3f dir;

    m.multFull(ia->getLine().getPosition (), pos);
    m.mult    (ia->getLine().getDirection(), dir);

    ia->setLine(Line(pos, dir), ia->getMaxDist());
    ia->scale(dir.length());

    return Action::Continue;
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Render                                   */

Action::ResultE SkeletonBlendedGeometry::renderEnter(Action *action)
{
    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    Matrixr mMat;    // will be set to World^-1

    calcMatrix(pAction->topMatrix(), mMat);

    pAction->pushVisibility();

    pAction->pushMatrix(mMat);

    Action::ResultE Result(Inherited::renderActionEnterHandler(action));
    if(Result != Action::Continue)
    {
        pAction->popVisibility();
        pAction->popMatrix();
    }
    return Result;
}

Action::ResultE SkeletonBlendedGeometry::renderLeave(Action *action)
{
    Action::ResultE Result(Inherited::renderActionLeaveHandler(action));

    RenderAction *pAction = 
        dynamic_cast<RenderAction *>(action);

    pAction->popVisibility();

    pAction->popMatrix();

    return Action::Continue;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SkeletonBlendedGeometry::SkeletonBlendedGeometry(void) :
    Inherited(),
    _invWorld ()
{
}

SkeletonBlendedGeometry::SkeletonBlendedGeometry(const SkeletonBlendedGeometry &source) :
    Inherited(source),
    _invWorld (source._invWorld)
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

    if(whichField & InternalJointsFieldMask)
    {
        _JointPoseTransforms.resize(getNumJoints());
    }

    if( (whichField & BaseGeometryFieldMask) ||
        (whichField & InternalJointsFieldMask) ||
        (whichField & InternalWeightIndexesFieldMask) ||
        (whichField & InternalWeightsFieldMask) ||
        (whichField & BindTransformationFieldMask))
    {
		if(getNumJoints() > 0)
		{
			_JointPoseTransforms.resize(getNumJoints());
			calculatePositions();
		}
    }
}

void SkeletonBlendedGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SkeletonBlendedGeometry NI" << std::endl;
}

OSG_END_NAMESPACE
