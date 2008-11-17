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
#include <OpenSG/OSGShaderParameterChunk.h>

#include "OSGShaderAnimation.h"
#include "Animators/OSGKeyframeAnimator.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderAnimation
Field Animation Class. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderAnimation::initMethod (void)
{
}

bool ShaderAnimation::update(const AnimationAdvancerPtr& advancer)
{
   //Check if the Shader Container has been defined
   if(getShaderContainer() == osg::NullFC)
   {
      SWARNING << "There is no Shader Chunk defined."  << std::endl;
      return false;
   }
   //Check if the Parameter has been found
   if(getParameter() == osg::NullFC)
   {
      //Find the parameter by looping through all of the Shaders Parameters
      osg::MFShaderParameterPtr::iterator Iter;
      for(Iter = getShaderContainer()->getParameters().begin() ; Iter != getShaderContainer()->getParameters().end() ; ++Iter)
      {
         //If the Parameters Name matches the one being looked for
         if((*Iter)->getName() == getParameterName())
         {
            beginEditCP(ShaderAnimationPtr(this), ParameterFieldMask);
               setParameter((*Iter));
            endEditCP(ShaderAnimationPtr(this), ParameterFieldMask);
         }
         
      }
      if(getParameter() == osg::NullFC)
      {
         SWARNING << "Could not find Parameter "<< getParameterName() << " in Shader Chunk: " << getShaderContainer()->getTypeName()  << std::endl;
         return true;
      }
      FieldDescription * f = getParameter()->getType().findFieldDescription("value");
      if( f == NULL )
      {
         SWARNING << "Could not find Field "<<"value" << " in Field Container " << getParameter()->getTypeName()  << std::endl;
         return true;
      }
      beginEditCP(ShaderAnimationPtr(this), ParameterFieldIdFieldMask);
         setParameterFieldId( f->getFieldId() );
      endEditCP(ShaderAnimationPtr(this), ParameterFieldIdFieldMask);
      if(getParameterFieldId() == 0)
      {
         SWARNING << "Could not find Field "<< "value" << " in Field Container " << getParameter()->getTypeName()  << std::endl;
         return true;
      }
   }
   
   //Check if the Animation Time is past the end
   if(advancer->getValue() >= getAnimator()->getLength())
   {
      //Update the number of cycles completed
      beginEditCP(ShaderAnimationPtr(this), CyclesFieldMask);
         setCycles( getAnimator()->numCyclesCompleted( advancer->getValue() ) );
      endEditCP(ShaderAnimationPtr(this), CyclesFieldMask);
      
      //Check if the Animation has completed it's number of cycles
      if(getCycling() > 0 && getCycles() >= getCycling())
      {
         //Time = getAnimator()->getLength();
         //PrevTime = getAnimator()->getLength();
      }
   }
   
   //Update the Field Container
   osg::beginEditCP(getShaderContainer(), osg::ShaderParameterChunk::ParametersFieldMask);
   
   osg::beginEditCP(getParameter());
   if( osg::KeyframeAnimatorPtr::dcast( getAnimator() )->animate(
         static_cast<osg::InterpolationType>(getInterpolationType()), 
         static_cast<osg::ValueReplacementPolicy>(getReplacementPolicy()), 
         getCycling(),
         advancer->getValue(),
         advancer->getPrevValue(),
         *getParameter()->getField( getParameterFieldId() )) )
   {
      osg::endEditCP(getParameter());
      osg::endEditCP(getShaderContainer(), osg::ShaderParameterChunk::ParametersFieldMask);
   }
   else
   {
      osg::endEditNotChangedCP(getParameter());
      osg::endEditNotChangedCP(getShaderContainer(), osg::ShaderParameterChunk::ParametersFieldMask);
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

ShaderAnimation::ShaderAnimation(void) :
    Inherited()
{
}

ShaderAnimation::ShaderAnimation(const ShaderAnimation &source) :
    Inherited(source)
{
}

ShaderAnimation::~ShaderAnimation(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderAnimation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderAnimation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderAnimation NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSHADERANIMATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERANIMATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERANIMATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

