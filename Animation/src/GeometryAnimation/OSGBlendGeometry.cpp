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
      osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
            CNodePtr, Action *>(&MaterialDrawable::drawActionEnterHandler));
   DrawAction::registerLeaveDefault(getClassType(),
      osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
            CNodePtr, Action *>(&MaterialDrawable::drawActionLeaveHandler));

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
            CNodePtr, Action *>(&MaterialDrawable::renderActionEnterHandler));
   RenderAction::registerLeaveDefault(getClassType(),
      osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
            CNodePtr, Action *>(&MaterialDrawable::renderActionLeaveHandler));
}

BlendGeometryPtr BlendGeometry::create (const GeometryPtr Geo)
{
   BlendGeometryPtr Result = BlendGeometryBase::create();
   GeometryPtr BaseGeometryCopy = osg::GeometryPtr::dcast( deepClone(Geo, "Material") );
   
   //Create a clone of the Geometry
   Result->setPositions( BaseGeometryCopy->getPositions() );
   Result->setNormals( BaseGeometryCopy->getNormals() );
   Result->setTypes( BaseGeometryCopy->getTypes() );
   Result->setLengths( BaseGeometryCopy->getLengths() );
   Result->setColors( BaseGeometryCopy->getColors() );
   Result->setSecondaryColors( BaseGeometryCopy->getSecondaryColors() );
   Result->setIndices( BaseGeometryCopy->getIndices() );
   Result->getIndexMapping() = BaseGeometryCopy->getIndexMapping();
   Result->setTexCoords( BaseGeometryCopy->getTexCoords());
   Result->setTexCoords1( BaseGeometryCopy->getTexCoords1() );
   Result->setTexCoords2( BaseGeometryCopy->getTexCoords2() );
   Result->setTexCoords3( BaseGeometryCopy->getTexCoords3() );
   Result->setMaterial(BaseGeometryCopy->getMaterial());

   //Get cloned copies of the Geometric properties that can be blended
   Result->setBasePositions( osg::GeoPositionsPtr::dcast( deepClone(Geo->getPositions()) ) );
   Result->setBaseNormals( osg::GeoNormalsPtr::dcast( deepClone(Geo->getNormals()) ) );
   Result->setBaseColors( osg::GeoColorsPtr::dcast( deepClone(Geo->getColors()) ) );
   Result->setBaseSecondaryColors( osg::GeoColorsPtr::dcast( deepClone(Geo->getSecondaryColors()) ) );
   Result->setBaseTexCoords( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords()) ) );
   Result->setBaseTexCoords1( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords1()) ) );
   Result->setBaseTexCoords2( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords2()) ) );
   Result->setBaseTexCoords3( osg::GeoTexCoordsPtr::dcast( deepClone(Geo->getTexCoords3()) ) );

   Result->setDlistCache(false);
   
   return Result;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

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
            //while(Index < i && )
            //{
            //    Index = getGeoPositionDifferenceSets()[j]->getIndices()->getValue(CurDiffSetIndicies[j]);
            //} 
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
}

void BlendGeometry::recalculateSecondaryColors(void)
{
}

void BlendGeometry::recalculateTexCoords(void)
{
}

void BlendGeometry::recalculateTexCoords1(void)
{
}

void BlendGeometry::recalculateTexCoords2(void)
{
}

void BlendGeometry::recalculateTexCoords3(void)
{
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
      recalculateTexCoords();
   }
   if(shouldRecalculateTexCoords1)
   {
      recalculateTexCoords1();
   }
   if(shouldRecalculateTexCoords2)
   {
      recalculateTexCoords2();
   }
   if(shouldRecalculateTexCoords3)
   {
      recalculateTexCoords3();
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

