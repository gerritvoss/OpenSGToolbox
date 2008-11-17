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

#include "OSGKeyframeSequenceTime.h"
#include "Interpolation/OSGKeyframeInterpolations.h"
#include "Interpolation/OSGInterpolationFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequenceTime

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequenceTime::initMethod (void)
{
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::STEP_INTERPOLATION, osg::SFTime::getClassType(), osg::KeyframeSequenceTime::stepFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::SFTime::getClassType(), osg::KeyframeSequenceTime::linearFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::CUBIC_INTERPOLATION, osg::SFTime::getClassType(), osg::KeyframeSequenceTime::cubicFieldInterpolation);
}

bool KeyframeSequenceTime::linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   osg::Time CurValue;
   osg::lerp(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFTime&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFTime&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      osg::Time PrevValue;
      osg::lerp(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFTime&>(Result).getValue() += (CurValue - PrevValue);
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceTime::cubicFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   osg::Time CurValue;
   osg::spline(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFTime&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFTime&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      osg::Time PrevValue;
      osg::spline(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFTime&>(Result).getValue() += (CurValue - PrevValue);
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceTime::stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   osg::Time CurValue;
   bool ReturnValue = osg::step(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFTime&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFTime&>(Result).getValue() += CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      osg::Time PrevValue;
      osg::step(osg::KeyframeSequenceTimePtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFTime&>(Result).getValue() += (CurValue - PrevValue);
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

KeyframeSequenceTime::KeyframeSequenceTime(void) :
    Inherited()
{
}

KeyframeSequenceTime::KeyframeSequenceTime(const KeyframeSequenceTime &source) :
    Inherited(source)
{
}

KeyframeSequenceTime::~KeyframeSequenceTime(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequenceTime::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequenceTime::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequenceTime NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCETIMEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCETIMEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCETIMEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

