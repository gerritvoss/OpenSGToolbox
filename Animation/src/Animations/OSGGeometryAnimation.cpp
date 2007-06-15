/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGGeometry.h>

#include "OSGGeometryAnimation.h"
#include "Animators/OSGKeyframeAnimator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeometryAnimation
Field Animation Class. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeometryAnimation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool GeometryAnimation::update(const AnimationAdvancerPtr& advancer)
{
   if(getFieldId() == 0)
   {
      if(getGeometryCore() == osg::NullFC)
      {
         SWARNING << "There is no Geometry Core defined to Animate"  << std::endl;
         return true;
      }
      FieldDescription * f = getGeometryCore()->getType().findFieldDescription(getFieldName().c_str());
      if( f == NULL )
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getGeometryCore()->getTypeName()  << std::endl;
         return true;
      }
      beginEditCP(GeometryAnimationPtr(this), FieldIdFieldMask);
      setFieldId( f->getFieldId() );
      endEditCP(GeometryAnimationPtr(this), FieldIdFieldMask);
      if(getFieldId() == 0)
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Geometry Core " << getGeometryCore()->getTypeName()  << std::endl;
         return true;
      }
   }
   
   //Check if the Animation Time is past the end
   if(advancer->getValue() >= getAnimator()->getLength())
   {
      //Update the number of cycles completed
      beginEditCP(GeometryAnimationPtr(this), CyclesFieldMask);
      setCycles( getAnimator()->numCyclesCompleted( advancer->getValue() ) );
      endEditCP(GeometryAnimationPtr(this), CyclesFieldMask);
      
      //Check if the Animation has completed it's number of cycles
      if(getCycling() > 0 && getCycles() >= getCycling())
      {
         //Time = getAnimator()->getLength();
         //PrevTime = getAnimator()->getLength();
      }
   }

   //Update the Field Container
   osg::beginEditCP(getGeometryCore(), getGeometryCore()->getType().getFieldDescription(getFieldId())->getFieldMask() | Geometry::DlistCacheFieldMask );
   
   if( osg::KeyframeAnimatorPtr::dcast( getAnimator() )->animate(
       static_cast<osg::InterpolationType>(getInterpolationType()),
   static_cast<osg::ValueReplacementPolicy>(getReplacementPolicy()),
   getCycling(),
   advancer->getValue(),
   advancer->getPrevValue(),
   *getGeometryCore()->getField( getFieldId() )) )
   {
      getGeometryCore()->setDlistCache(false);
      //getGeometryCore()->invalidateDlistCache();
      osg::endEditCP(getGeometryCore(), getGeometryCore()->getType().getFieldDescription(getFieldId())->getFieldMask() | Geometry::DlistCacheFieldMask);
   }
   else
   {
      osg::endEditNotChangedCP(getGeometryCore(), getGeometryCore()->getType().getFieldDescription(getFieldId())->getFieldMask() | Geometry::DlistCacheFieldMask);
   }
   
   //Return true if the animation has completed its number of cycles, false otherwise
   return (getCycling() > 0 && getCycles() >= getCycling());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeometryAnimation::GeometryAnimation(void) :
    Inherited()
{
}

GeometryAnimation::GeometryAnimation(const GeometryAnimation &source) :
    Inherited(source)
{
}

GeometryAnimation::~GeometryAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeometryAnimation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeometryAnimation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeometryAnimation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGEOMETRYANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOMETRYANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOMETRYANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

