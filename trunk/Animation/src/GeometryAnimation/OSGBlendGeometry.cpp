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
#include <vector>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGIntersectActor.h>
#include <OpenSG/OSGQuaternion.h>

#include "OSGBlendGeometry.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BlendGeometry

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BlendGeometry::initMethod (void)
{
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, BlendGeometryPtr,
              CNodePtr, Action *>(&BlendGeometry::drawActionEnterHandler));

    DrawAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, BlendGeometryPtr,
              CNodePtr, Action *>(&BlendGeometry::drawActionLeaveHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, BlendGeometryPtr,
              CNodePtr, Action *>(&BlendGeometry::intersect));

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, BlendGeometryPtr,
              CNodePtr, Action *>(&BlendGeometry::renderActionEnterHandler));

    RenderAction::registerLeaveDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, BlendGeometryPtr,
              CNodePtr, Action *>(&BlendGeometry::renderActionLeaveHandler));
}

BlendGeometryPtr BlendGeometry::create (const GeometryPtr Geo)
{
   BlendGeometryPtr Result = BlendGeometryBase::create();
   Result->setBaseGeometry(Geo);
   return Result;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BlendGeometry::setBaseGeometry(const GeometryPtr Geo)
{
   GeometryPtr BaseGeometryCopy = osg::GeometryPtr::dcast( deepClone(Geo, "Material") );
   
   //Create a clone of the Geometry
   beginEditCP(BlendGeometryPtr(this));
       setPositions( BaseGeometryCopy->getPositions() );
       setNormals( BaseGeometryCopy->getNormals() );
       setTypes( BaseGeometryCopy->getTypes() );
       setLengths( BaseGeometryCopy->getLengths() );
       setColors( BaseGeometryCopy->getColors() );
       setSecondaryColors( BaseGeometryCopy->getSecondaryColors() );
       setIndices( BaseGeometryCopy->getIndices() );
       getIndexMapping() = BaseGeometryCopy->getIndexMapping();
       setTexCoords( BaseGeometryCopy->getTexCoords());
       setTexCoords1( BaseGeometryCopy->getTexCoords1() );
       setTexCoords2( BaseGeometryCopy->getTexCoords2() );
       setTexCoords3( BaseGeometryCopy->getTexCoords3() );
       setTexCoords4( BaseGeometryCopy->getTexCoords4() );
       setTexCoords5( BaseGeometryCopy->getTexCoords5() );
       setTexCoords6( BaseGeometryCopy->getTexCoords6() );
       setTexCoords7( BaseGeometryCopy->getTexCoords7() );
       setMaterial(BaseGeometryCopy->getMaterial());

       //Get cloned copies of the Geometric properties that can be blended
       setBasePositions( osg::GeoPositionsPtr::dcast( deepClone(Geo->getPositions()) ) );
       setBaseNormals( osg::GeoNormalsPtr::dcast( deepClone(Geo->getNormals()) ) );
       setBaseColors( osg::GeoColorsPtr::dcast( deepClone(Geo->getColors()) ) );
       setBaseSecondaryColors( osg::GeoColorsPtr::dcast( deepClone(Geo->getSecondaryColors()) ) );
       setBaseTexCoords( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords()) ) );
       setBaseTexCoords1( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords1()) ) );
       setBaseTexCoords2( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords2()) ) );
       setBaseTexCoords3( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords3()) ) );
       setBaseTexCoords4( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords4()) ) );
       setBaseTexCoords5( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords5()) ) );
       setBaseTexCoords6( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords6()) ) );
       setBaseTexCoords7( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords7()) ) );

       //Clear out all of the Difference Sets
       getGeoPositionDifferenceSets().clear();
       getGeoNormalDifferenceSets().clear();
       getGeoColorDifferenceSets().clear();
       getGeoSecondaryColorDifferenceSets().clear();
       getGeoTexCoordDifferenceSets().clear();
       getGeoTexCoord1DifferenceSets().clear();
       getGeoTexCoord2DifferenceSets().clear();
       getGeoTexCoord3DifferenceSets().clear();
       getGeoTexCoord4DifferenceSets().clear();
       getGeoTexCoord5DifferenceSets().clear();
       getGeoTexCoord6DifferenceSets().clear();
       getGeoTexCoord7DifferenceSets().clear();

       getBlendAmounts().clear();

       setDlistCache(false);
    endEditCP(BlendGeometryPtr(this));
}

void BlendGeometry::addBlendGeometry(const GeometryPtr Geo, Real32 b)
{
    if(Geo != NullFC)
    {
        //Create the difference sets and add them
        beginEditCP(BlendGeometryPtr(this), GeoPositionDifferenceSetsFieldMask |
                                            GeoNormalDifferenceSetsFieldMask |
                                            GeoColorDifferenceSetsFieldMask |
                                            GeoSecondaryColorDifferenceSetsFieldMask |
                                            GeoTexCoordDifferenceSetsFieldMask |
                                            GeoTexCoord1DifferenceSetsFieldMask |
                                            GeoTexCoord2DifferenceSetsFieldMask |
                                            GeoTexCoord3DifferenceSetsFieldMask |
                                            GeoTexCoord4DifferenceSetsFieldMask |
                                            GeoTexCoord5DifferenceSetsFieldMask |
                                            GeoTexCoord6DifferenceSetsFieldMask |
                                            GeoTexCoord7DifferenceSetsFieldMask |
                                            BlendAmountsFieldMask);
            //Positions Difference Set
            GeoPositionDifferenceSetPtr PositionsDiffSet = GeoPositionDifferenceSet::create( getBasePositions(), Geo->getPositions() );
            if(PositionsDiffSet != NullFC)
            {
                getGeoPositionDifferenceSets().push_back(PositionsDiffSet);
            }

            //Normals Difference Set
            GeoNormalDifferenceSetPtr NormalsDiffSet = GeoNormalDifferenceSet::create( getBaseNormals(), Geo->getNormals() );
            if(NormalsDiffSet != NullFC)
            {
                getGeoNormalDifferenceSets().push_back(NormalsDiffSet);
            }

            //Colors Difference Set
            GeoColorDifferenceSetPtr ColorsDiffSet = GeoColorDifferenceSet::create( getBaseColors(), Geo->getColors() );
            if(ColorsDiffSet != NullFC)
            {
                getGeoColorDifferenceSets().push_back(ColorsDiffSet);
            }

            //SecondaryColors Difference Set
            GeoColorDifferenceSetPtr SecColorsDiffSet = GeoColorDifferenceSet::create( getBaseSecondaryColors(), Geo->getSecondaryColors() );
            if(SecColorsDiffSet != NullFC)
            {
                getGeoSecondaryColorDifferenceSets().push_back(SecColorsDiffSet);
            }

            //TexCoords Difference Set
            GeoTexCoordDifferenceSetPtr TexCoordsDiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords(), Geo->getTexCoords() );
            if(TexCoordsDiffSet != NullFC)
            {
                getGeoTexCoordDifferenceSets().push_back(TexCoordsDiffSet);
            }

            //TexCoord1 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord1sDiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords1(), Geo->getTexCoords1() );
            if(TexCoord1sDiffSet != NullFC)
            {
                getGeoTexCoord1DifferenceSets().push_back(TexCoord1sDiffSet);
            }

            //TexCoord2 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord2sDiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords2(), Geo->getTexCoords2() );
            if(TexCoord2sDiffSet != NullFC)
            {
                getGeoTexCoord2DifferenceSets().push_back(TexCoord2sDiffSet);
            }

            //TexCoord3 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord3DiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords3(), Geo->getTexCoords3() );
            if(TexCoord3DiffSet != NullFC)
            {
                getGeoTexCoord3DifferenceSets().push_back(TexCoord3DiffSet);
            }

            //TexCoord4 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord4DiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords4(), Geo->getTexCoords4() );
            if(TexCoord4DiffSet != NullFC)
            {
                getGeoTexCoord4DifferenceSets().push_back(TexCoord4DiffSet);
            }

            //TexCoord5 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord5DiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords5(), Geo->getTexCoords5() );
            if(TexCoord5DiffSet != NullFC)
            {
                getGeoTexCoord5DifferenceSets().push_back(TexCoord5DiffSet);
            }

            //TexCoord6 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord6DiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords6(), Geo->getTexCoords6() );
            if(TexCoord6DiffSet != NullFC)
            {
                getGeoTexCoord6DifferenceSets().push_back(TexCoord6DiffSet);
            }

            //TexCoord7 Difference Set
            GeoTexCoordDifferenceSetPtr TexCoord7DiffSet = GeoTexCoordDifferenceSet::create( getBaseTexCoords7(), Geo->getTexCoords7() );
            if(TexCoord7DiffSet != NullFC)
            {
                getGeoTexCoord7DifferenceSets().push_back(TexCoord7DiffSet);
            }

            getBlendAmounts().push_back(b);

        endEditCP(BlendGeometryPtr(this), GeoPositionDifferenceSetsFieldMask |
                                            GeoNormalDifferenceSetsFieldMask |
                                            GeoColorDifferenceSetsFieldMask |
                                            GeoSecondaryColorDifferenceSetsFieldMask |
                                            GeoTexCoordDifferenceSetsFieldMask |
                                            GeoTexCoord1DifferenceSetsFieldMask |
                                            GeoTexCoord2DifferenceSetsFieldMask |
                                            GeoTexCoord3DifferenceSetsFieldMask |
                                            GeoTexCoord4DifferenceSetsFieldMask |
                                            GeoTexCoord5DifferenceSetsFieldMask |
                                            GeoTexCoord6DifferenceSetsFieldMask |
                                            GeoTexCoord7DifferenceSetsFieldMask |
                                            BlendAmountsFieldMask);
    }
}

void BlendGeometry::removeBlendGeometry(UInt32 GeoIndex)
{
    if(GeoIndex < getNumBlendGeometries())
    {
        beginEditCP(BlendGeometryPtr(this), GeoPositionDifferenceSetsFieldMask |
                                            GeoNormalDifferenceSetsFieldMask |
                                            GeoColorDifferenceSetsFieldMask |
                                            GeoSecondaryColorDifferenceSetsFieldMask |
                                            GeoTexCoordDifferenceSetsFieldMask |
                                            GeoTexCoord1DifferenceSetsFieldMask |
                                            GeoTexCoord2DifferenceSetsFieldMask |
                                            GeoTexCoord3DifferenceSetsFieldMask |
                                            GeoTexCoord4DifferenceSetsFieldMask |
                                            GeoTexCoord5DifferenceSetsFieldMask |
                                            GeoTexCoord6DifferenceSetsFieldMask |
                                            GeoTexCoord7DifferenceSetsFieldMask |
                                            BlendAmountsFieldMask);

        if(GeoIndex < getGeoPositionDifferenceSets().size())
        {
            getGeoPositionDifferenceSets().erase((getGeoPositionDifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoNormalDifferenceSets().size())
        {
            getGeoNormalDifferenceSets().erase((getGeoNormalDifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoColorDifferenceSets().size())
        {
            getGeoColorDifferenceSets().erase((getGeoColorDifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoSecondaryColorDifferenceSets().size())
        {
            getGeoSecondaryColorDifferenceSets().erase((getGeoSecondaryColorDifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoordDifferenceSets().size())
        {
            getGeoTexCoordDifferenceSets().erase((getGeoTexCoordDifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord1DifferenceSets().size())
        {
            getGeoTexCoord1DifferenceSets().erase((getGeoTexCoord1DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord2DifferenceSets().size())
        {
            getGeoTexCoord2DifferenceSets().erase((getGeoTexCoord2DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord3DifferenceSets().size())
        {
            getGeoTexCoord3DifferenceSets().erase((getGeoTexCoord3DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord4DifferenceSets().size())
        {
            getGeoTexCoord4DifferenceSets().erase((getGeoTexCoord4DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord5DifferenceSets().size())
        {
            getGeoTexCoord5DifferenceSets().erase((getGeoTexCoord5DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord6DifferenceSets().size())
        {
            getGeoTexCoord6DifferenceSets().erase((getGeoTexCoord6DifferenceSets().begin() + GeoIndex));
        }
        if(GeoIndex < getGeoTexCoord7DifferenceSets().size())
        {
            getGeoTexCoord7DifferenceSets().erase((getGeoTexCoord7DifferenceSets().begin() + GeoIndex));
        }
        getBlendAmounts().erase((getBlendAmounts().begin() + GeoIndex));

        endEditCP(BlendGeometryPtr(this), GeoPositionDifferenceSetsFieldMask |
                                            GeoNormalDifferenceSetsFieldMask |
                                            GeoColorDifferenceSetsFieldMask |
                                            GeoSecondaryColorDifferenceSetsFieldMask |
                                            GeoTexCoordDifferenceSetsFieldMask |
                                            GeoTexCoord1DifferenceSetsFieldMask |
                                            GeoTexCoord2DifferenceSetsFieldMask |
                                            GeoTexCoord3DifferenceSetsFieldMask |
                                            GeoTexCoord4DifferenceSetsFieldMask |
                                            GeoTexCoord5DifferenceSetsFieldMask |
                                            GeoTexCoord6DifferenceSetsFieldMask |
                                            GeoTexCoord7DifferenceSetsFieldMask |
                                            BlendAmountsFieldMask);

    }
}

UInt32 BlendGeometry::getNumBlendGeometries(void) const
{
    return getBlendAmounts().size();
}

void BlendGeometry::setBlendAmount(UInt32 GeoIndex, Real32 b)
{
    if(GeoIndex < getNumBlendGeometries())
    {
        beginEditCP(BlendGeometryPtr(this), BlendAmountsFieldMask);
            getBlendAmounts()[GeoIndex] = b;
        endEditCP(BlendGeometryPtr(this), BlendAmountsFieldMask);
    }
}

void BlendGeometry::recalculatePositions(void)
{
   UInt32 NumPositions = getBasePositions()->getSize();
   UInt32 NumDiffSets = getGeoPositionDifferenceSets().getSize();

   //Vector for keeping track of each DiffSets Index
   std::vector<UInt32> CurDiffSetIndicies;
   CurDiffSetIndicies.resize(NumDiffSets);
   for(UInt32 j=0 ; j<NumDiffSets ; ++j)
   {
      CurDiffSetIndicies[j] = 0;
   }

   Real32 BlendAmount;
   UInt32 Index ;
   for(UInt32 i=0 ; i<NumPositions ; ++i)
   {
      //Set the Position to the base position
      Pnt3f Result = getBasePositions()->getValue(i);
      for(UInt32 j=0 ; j<NumDiffSets ; ++j)
      {
         //Blend Each DiffSet that has a non-zero blending value
         BlendAmount = getBlendAmounts(j);
         if(BlendAmount != 0.0 && CurDiffSetIndicies[j] < getGeoPositionDifferenceSets()[j]->getIndices()->getSize())
         {
            //Blend each DiffSet that has an alternet Position
            Index = getGeoPositionDifferenceSets()[j]->getIndices()->getValue(CurDiffSetIndicies[j]);
            if( Index == i )
            {
               Result = Result + ( BlendAmount * (getGeoPositionDifferenceSets()[j]->getPositions()->getValue(CurDiffSetIndicies[j]) - getBasePositions()->getValue(i)) );
                ++CurDiffSetIndicies[j];
            }
         }
      }

      //Set the Position Value
      getPositions()->setValue(Result, i);
   }
}

void BlendGeometry::recalculateNormals(void)
{
   UInt32 NumNormals = getBaseNormals()->getSize();
   UInt32 NumDiffSets = getGeoNormalDifferenceSets().getSize();

   //Vector for keeping track of each DiffSets Index
   std::vector<UInt32> CurDiffSetIndicies;
   CurDiffSetIndicies.resize(NumDiffSets);
   for(UInt32 j=0 ; j<NumDiffSets ; ++j)
   {
      CurDiffSetIndicies[j] = 0;
   }

   Quaternion TotalRotation;
   Quaternion Rotation;

   Real32 BlendAmount;
   UInt32 Index;
   for(UInt32 i=0 ; i<NumNormals ; ++i)
   {
      //Set the Normal to the base position
      Vec3f Result;
      TotalRotation.setIdentity();
      for(UInt32 j=0 ; j<NumDiffSets ; ++j)
      {
         //Blend Each DiffSet that has a non-zero blending value
         BlendAmount = getBlendAmounts(j);
         if(BlendAmount != 0.0)
         {
            //Blend each DiffSet that has an alternet Normal
            Index = getGeoNormalDifferenceSets()[j]->getIndices()->getValue(CurDiffSetIndicies[j]);
            if( Index == i )
            {
               Rotation.setValue(getBaseNormals()->getValue(i), getGeoNormalDifferenceSets()[j]->getNormals()->getValue(CurDiffSetIndicies[j]));
               //Scale the angle to t, which is our lerp amount
               Rotation.scaleAngle(BlendAmount);

               TotalRotation.mult(Rotation);
               ++CurDiffSetIndicies[j];
            }
         }
      }

      TotalRotation.multVec(getBaseNormals()->getValue(i), Result);
      //Set the Normal Value
      getNormals()->setValue(Result, i);
   }
}

void BlendGeometry::recalculateColors(void)
{
    //TODO: Implement
}

void BlendGeometry::recalculateSecondaryColors(void)
{
    //TODO: Implement
}

void BlendGeometry::recalculateTexCoords(UInt32 CoordNum)
{
    //TODO: Implement
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BlendGeometry::BlendGeometry(void) :
    Inherited()
{
    getBlendAmounts().clear();
}

BlendGeometry::BlendGeometry(const BlendGeometry &source) :
    Inherited(source)
{
}

BlendGeometry::~BlendGeometry(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BlendGeometry::changed(BitVector whichField, UInt32 origin)
{
   bool shouldRecalculatePositions = false;
   bool shouldRecalculateNormals = false;
   bool shouldRecalculateColors = false;
   bool shouldRecalculateSecondaryColors = false;
   bool shouldRecalculateTexCoords = false;
   bool shouldRecalculateTexCoords1 = false;
   bool shouldRecalculateTexCoords2 = false;
   bool shouldRecalculateTexCoords3 = false;
   bool shouldRecalculateTexCoords4 = false;
   bool shouldRecalculateTexCoords5 = false;
   bool shouldRecalculateTexCoords6 = false;
   bool shouldRecalculateTexCoords7 = false;

   if(whichField & BlendAmountsFieldMask)
   {
      //Recalculate the Blend Geometry
      shouldRecalculatePositions = true;
      shouldRecalculateNormals = true;
      shouldRecalculateColors = true;
      shouldRecalculateSecondaryColors = true;
      shouldRecalculateTexCoords = true;
      shouldRecalculateTexCoords1 = true;
      shouldRecalculateTexCoords2 = true;
      shouldRecalculateTexCoords3 = true;
        shouldRecalculateTexCoords4 = true;
        shouldRecalculateTexCoords5 = true;
        shouldRecalculateTexCoords6 = true;
        shouldRecalculateTexCoords7 = true;
   }
   else
   {
      if(whichField & BasePositionsFieldMask ||
         whichField & GeoPositionDifferenceSetsFieldMask)
      {
         shouldRecalculatePositions = true;
      }
      if(whichField & BaseNormalsFieldMask ||
         whichField & GeoNormalDifferenceSetsFieldMask)
      {
         shouldRecalculateNormals = true;
      }
      if(whichField & BaseColorsFieldMask ||
         whichField & GeoColorDifferenceSetsFieldMask)
      {
         shouldRecalculateColors = true;
      }
      if(whichField & BaseSecondaryColorsFieldMask ||
         whichField & GeoSecondaryColorDifferenceSetsFieldMask)
      {
         shouldRecalculateSecondaryColors = true;
      }
      if(whichField & BaseTexCoordsFieldMask ||
         whichField & GeoTexCoordDifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords = true;
      }
      if(whichField & BaseTexCoords1FieldMask ||
         whichField & GeoTexCoord1DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords1 = true;
      }
      if(whichField & BaseTexCoords2FieldMask ||
         whichField & GeoTexCoord2DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords2 = true;
      }
      if(whichField & BaseTexCoords3FieldMask ||
         whichField & GeoTexCoord3DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords3 = true;
      }
      if(whichField & BaseTexCoords4FieldMask ||
         whichField & GeoTexCoord4DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords4 = true;
      }
      if(whichField & BaseTexCoords5FieldMask ||
         whichField & GeoTexCoord5DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords5 = true;
      }
      if(whichField & BaseTexCoords6FieldMask ||
         whichField & GeoTexCoord6DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords6 = true;
      }
      if(whichField & BaseTexCoords7FieldMask ||
         whichField & GeoTexCoord7DifferenceSetsFieldMask)
      {
         shouldRecalculateTexCoords7 = true;
      }
   }

   //Updating Blended Geometry
   if(shouldRecalculatePositions)
   {
      recalculatePositions();

      //Bounding Box should be updated
      //Tell Parents thier bounding Boxes are invalid
      for(UInt32 i = 0; i < _parents.size(); i++)
      {
         _parents[i]->invalidateVolume();
      }
   }
   if(shouldRecalculateNormals)
   {
      recalculateNormals();
   }
   if(shouldRecalculateColors)
   {
      recalculateColors();
   }
   if(shouldRecalculateSecondaryColors)
   {
      recalculateSecondaryColors();
   }
   if(shouldRecalculateTexCoords)
   {
      recalculateTexCoords(0);
   }
   if(shouldRecalculateTexCoords1)
   {
      recalculateTexCoords(1);
   }
   if(shouldRecalculateTexCoords2)
   {
      recalculateTexCoords(2);
   }
   if(shouldRecalculateTexCoords3)
   {
      recalculateTexCoords(3);
   }
   if(shouldRecalculateTexCoords4)
   {
      recalculateTexCoords(4);
   }
   if(shouldRecalculateTexCoords5)
   {
      recalculateTexCoords(5);
   }
   if(shouldRecalculateTexCoords6)
   {
      recalculateTexCoords(6);
   }
   if(shouldRecalculateTexCoords7)
   {
      recalculateTexCoords(7);
   }

   Inherited::changed(whichField, origin);
}

void BlendGeometry::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BlendGeometry NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGBLENDGEOMETRYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBLENDGEOMETRYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBLENDGEOMETRYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

