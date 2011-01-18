/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),                            *
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

#include "OSGMorphGeometry.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"
#include "OSGGeoPropertyUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMorphGeometryBase.cpp file.
// To modify it, please change the .fcd file (OSGMorphGeometry.fcd) and
// regenerate the base file.

/*!\fn void addMorphTarget(Geometry * const Target, Real32 Weight)
 * \brief Add a target geometry and weight
 *
 * \param[in] Target The OSG::Geometry to add
 * \param[in] Weight The weight of the target geometry
 */

/*!\fn void clearMorphTargets(void)
 * \brief Remove all target geometries 
 */

/*!\fn void setMorphTarget(UInt32 Index, Geometry * const Target)
 * \brief Replace the target geometry at the given index
 *
 * \param[in] Index The index of the target geometry to replace
 * \param[in] Target The OSG::Geometry to replace with
 */

/*!\fn void setMorphTargetWeight(UInt32 Index, Real32 Weight)
 * \brief Set the weight of a target geometry at a given index
 *
 * \param[in] Index The index of the target geometry
 * \param[in] Weight The weight to assign this target geometry
 */

/*!\fn UInt32 getNumMorphTargets(void) const
 * \brief Get the number of geometry targets
 *
 * \returns The number of geometry targets
 */

/*!\fn Geometry* getMorphTarget(UInt32 Index) const
 * \brief Get the target geometry at the given index
 *
 * \param[in] Index The index of the target geometry
 */

/*!\fn Int32 getMorphTargetIndex(Geometry * const Target) const
 * \brief Get the index of the given target geometry
 *
 * \param[in] Target
 *
 * \returns The index of the given target geometry.  Returns -1 if the given
 * geometry does not exist. 
 */

/*!\fn Real32 getMorphTargetWeight(UInt32 Index) const
 * \brief Get the weight of the target geometry at the given index
 *
 * \param[in] Index The index of the target geometry
 *
 * \returns The weight
 */

/*!\fn Real32 getMorphTargetWeight(Geometry * const Target) const
 * \brief Get the weight of the target geometry
 *
 * \param[in] Target
 *
 * \returns The weight
 */

/*!\fn GeoVectorProperty*   getWeights      (void) const
 * \brief Get the property of the Weights field
 *
 * \returns Pointer to the Weights field
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MorphGeometry::initMethod(InitPhase ePhase)
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
void MorphGeometry::addMorphTarget(Geometry * const Target, Real32 Weight)
{
    pushToInternalTargetGeometries(Target);
    getInternalWeights()->addValue<Vec1f>(Vec1f(Weight));
}

//void MorphGeometry::removeMorphTarget(Geometry * const Target)
//{
    //Int32 Index(getMorphTargetIndex(Target));
    //if(Index >= 0)
    //{
        //removeFromInternalTargetGeometries(Index);
        //getInternalWeights()->addValue<Vec1f>(Vec1f(Weight));
    //}
//}

//void MorphGeometry::removeMorphTarget(UInt32 Index)
//{
//}

void MorphGeometry::clearMorphTargets(void)
{
    clearInternalTargetGeometries();
    getInternalWeights()->clear();
}

void MorphGeometry::setMorphTarget(UInt32 Index, Geometry * const Target)
{
    if(Index < getNumMorphTargets())
    {
        (*editMFInternalTargetGeometries())[Index] = Target;
    }
}

void MorphGeometry::setMorphTargetWeight(UInt32 Index, Real32 Weight)
{
    if(Index < getNumMorphTargets())
    {
        getInternalWeights()->setValue<Vec1f>(Vec1f(Weight),Index);
    }
}

UInt32 MorphGeometry::getNumMorphTargets(void) const
{
    return getMFInternalTargetGeometries()->size();
}

Geometry* MorphGeometry::getMorphTarget(UInt32 Index) const
{
    return getInternalTargetGeometries(Index);
}

Int32 MorphGeometry::getMorphTargetIndex(Geometry * const Target) const
{
    return getMFInternalTargetGeometries()->findIndex(Target);
}

Real32 MorphGeometry::getMorphTargetWeight(UInt32 Index) const
{
    return getInternalWeights()->getValue<Vec1f>(Index)[0];
}

Real32 MorphGeometry::getMorphTargetWeight(Geometry * const Target) const
{
    Int32 Index(getMorphTargetIndex(Target));
    assert(Index >= 0);

    return getMorphTargetWeight(Index);
}

void MorphGeometry::updateMorph(void)
{
    if(!getBaseGeometry())
    {
        SWARNING << "No Base Geometry" << std::endl;
        return;
    }

    for(UInt32 i(0) ; i<getMFMorphProperties()->size() ; ++i)
    {
        GeoVectorProperty* BaseProp(getBaseGeometry()->getProperty(getMorphProperties(i)));

        //Reset the property
        GeoVectorPropertyUnrecPtr Prop(dynamic_pointer_cast<GeoVectorProperty>(getBaseGeometry()->getProperty(getMorphProperties(i))->clone()));
        setProperty(Prop, getMorphProperties(i));

        //GeoVectorProperty* Prop(getProperty(getMorphProperties(i)));
        //assert( Prop->size() == BaseProp->size() &&
                //Prop->getDimension() == BaseProp->getDimension()&&
                //Prop->getFormat() == BaseProp->getFormat());
        //UInt32 NumBytesToCopy(Prop->getFormatSize() * BaseProp->size() * BaseProp->getDimension());
        //memcpy(Prop->editData(), BaseProp->getData(), NumBytesToCopy);


        //Loop through all morph targets
        Geometry* Target;
        GeoVectorProperty* TargetProp;
        Real32 Weight;
        for(UInt32 j(0) ; j < getNumMorphTargets() ; ++j)
        {
            //If the Weight is really small then don't apply it
            Weight = osgAbs(getMorphTargetWeight(j));
            if(Weight < 0.000001f)
            {
                continue;
            }

            Target = getMorphTarget(j);
            TargetProp = Target->getProperty(getMorphProperties(i));

            //Call the morph property with the given property format
            morphGeoProperty(BaseProp, TargetProp, Prop, Weight);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MorphGeometry::onCreate(const MorphGeometry *Id)
{
	Inherited::onCreate(Id);
    
    if(Id != NULL)
    {
        editMFMorphProperties()->clear();
        editMFMorphProperties()->push_back(Geometry::PositionsIndex);

        GeoVectorPropertyRecPtr Weights = GeoVec1fProperty::create();
        setInternalWeights(Weights);
        //editMFMorphProperties()->push_back(Geometry::NormalsIndex);
    }
}

void MorphGeometry::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

MorphGeometry::MorphGeometry(void) :
    Inherited()
{
}

MorphGeometry::MorphGeometry(const MorphGeometry &source) :
    Inherited(source)
{
}

MorphGeometry::~MorphGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MorphGeometry::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & BaseGeometryFieldMask)
    {
        if(getBaseGeometry() != NULL)
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
                setPositions(getBaseGeometry()->getPositions());
            }
            if(getBaseGeometry()->getNormals() != NULL)
            {
                setNormals(getBaseGeometry()->getNormals());
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
        else
        {
            setTypes(NULL);
            setLengths(NULL);
            setPositions(NULL);
            setNormals(NULL);
            setColors(NULL);
            setSecondaryColors(NULL);
            setTexCoords(NULL);
            setTexCoords1(NULL);
            setTexCoords2(NULL);
            setTexCoords3(NULL);
            setTexCoords4(NULL);
            setTexCoords5(NULL);
            setTexCoords6(NULL);
            setTexCoords7(NULL);
            setIndices(NULL);
            setMaterial(NULL);
        }
    }

    if((whichField & InternalWeightsFieldMask)  ||
        (whichField & InternalTargetGeometriesFieldMask)  ||
        (whichField & BaseGeometryFieldMask)  ||
        (whichField & MorphPropertiesFieldMask))
    {
        updateMorph();
    }
}

void MorphGeometry::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MorphGeometry NI" << std::endl;
}

OSG_END_NAMESPACE
