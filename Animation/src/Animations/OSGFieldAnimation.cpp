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



#include <OpenSG/OSGConfig.h>

#include "OSGFieldAnimation.h"
#include "Animators/OSGKeyframeAnimator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FieldAnimation
Field Animation Class. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldAnimation::initMethod (void)
{
}


bool FieldAnimation::update(const AnimationAdvancerPtr& advancer)
{
   if(getFieldId() == 0)
   {
      if(getContainer() == osg::NullFC)
      {
         SWARNING << "There is no Field Container defined to Animate"  << std::endl;
         return true;
      }
      FieldDescription * f = getContainer()->getType().findFieldDescription(getFieldName().c_str());
      if( f == NULL )
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
         return true;
      }
      beginEditCP(FieldAnimationPtr(this), FieldIdFieldMask);
         setFieldId( f->getFieldId() );
      endEditCP(FieldAnimationPtr(this), FieldIdFieldMask);
      if(getFieldId() == 0)
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
         return true;
      }
   }
   
   //Check if the Animation Time is past the end
   if(advancer->getValue() >= getAnimator()->getLength())
   {
      //Update the number of cycles completed
      beginEditCP(FieldAnimationPtr(this), CyclesFieldMask);
         setCycles( getAnimator()->numCyclesCompleted( advancer->getValue() ) );
      endEditCP(FieldAnimationPtr(this), CyclesFieldMask);
      
      //Check if the Animation has completed it's number of cycles
      if(getCycling() > 0 && getCycles() >= getCycling())
      {
         //Time = getAnimator()->getLength();
         //PrevTime = getAnimator()->getLength();
      }
   }

   //Update the Field Container
   osg::beginEditCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask() );
   
   if( osg::KeyframeAnimatorPtr::dcast( getAnimator() )->animate(
               static_cast<osg::InterpolationType>(getInterpolationType()), 
               static_cast<osg::ValueReplacementPolicy>(getReplacementPolicy()),
               getCycling(), 
               advancer->getValue(),
               advancer->getPrevValue(),
               *getContainer()->getField( getFieldId() )) )
   {
      osg::endEditCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask());
   }
   else
   {
      osg::endEditNotChangedCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask());
   }
   
   //Return true if the animation has completed its number of cycles, false otherwise
   return (getCycling() > 0 && getCycles() >= getCycling());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldAnimation::FieldAnimation(void) :
    Inherited()
{
}

FieldAnimation::FieldAnimation(const FieldAnimation &source) :
    Inherited(source)
{
}

FieldAnimation::~FieldAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldAnimation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FieldAnimation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FieldAnimation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFIELDANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFIELDANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFIELDANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

