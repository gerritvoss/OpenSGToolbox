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

#include "OSGKeyframeSequenceVec2f.h"
#include "Interpolation/OSGKeyframeInterpolations.h"
#include "Interpolation/OSGInterpolationFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequenceVec2f

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequenceVec2f::initMethod (void)
{
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::STEP_INTERPOLATION, osg::SFVec2f::getClassType(), osg::KeyframeSequenceVec2f::stepFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::SFVec2f::getClassType(), osg::KeyframeSequenceVec2f::linearFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::CUBIC_INTERPOLATION, osg::SFVec2f::getClassType(), osg::KeyframeSequenceVec2f::cubicFieldInterpolation);
}

bool KeyframeSequenceVec2f::linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Vec2f CurValue;
   osg::lerp(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFVec2f&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFVec2f&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Vec2f PrevValue;
      osg::lerp(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFVec2f&>(Result).getValue() += (CurValue - PrevValue);
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceVec2f::cubicFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Vec2f CurValue;
   osg::spline(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFVec2f&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFVec2f&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Vec2f PrevValue;
      osg::spline(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFVec2f&>(Result).getValue() += (CurValue - PrevValue);
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceVec2f::stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Vec2f CurValue;
   bool ReturnValue = osg::step(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFVec2f&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFVec2f&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Vec2f PrevValue;
      osg::step(osg::KeyframeSequenceVec2fPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFVec2f&>(Result).getValue() += (CurValue - PrevValue);
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return ReturnValue;
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeSequenceVec2f::KeyframeSequenceVec2f(void) :
    Inherited()
{
}

KeyframeSequenceVec2f::KeyframeSequenceVec2f(const KeyframeSequenceVec2f &source) :
    Inherited(source)
{
}

KeyframeSequenceVec2f::~KeyframeSequenceVec2f(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequenceVec2f::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequenceVec2f::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequenceVec2f NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCEVEC2FBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCEVEC2FBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCEVEC2FFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

