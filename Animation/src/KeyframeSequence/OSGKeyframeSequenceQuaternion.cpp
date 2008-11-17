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

#include "OSGKeyframeSequenceQuaternion.h"
#include "Interpolation/OSGKeyframeInterpolations.h"
#include "Interpolation/OSGInterpolationFactory.h"
#include <OpenSG/Toolbox/OSGQuatOperations.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequenceQuaternion

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequenceQuaternion::initMethod (void)
{
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::STEP_INTERPOLATION, osg::SFQuaternion::getClassType(), osg::KeyframeSequenceQuaternion::stepFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::SFQuaternion::getClassType(), osg::KeyframeSequenceQuaternion::linearFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::CUBIC_INTERPOLATION, osg::SFQuaternion::getClassType(), osg::KeyframeSequenceQuaternion::cubicFieldInterpolation);
}

bool KeyframeSequenceQuaternion::linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Quaternion CurValue;
   osg::lerp(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFQuaternion&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFQuaternion&>(Result).getValue() *= CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Quaternion PrevValue;
      osg::lerp(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFQuaternion&>(Result).getValue() *= ( CurValue/PrevValue );
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceQuaternion::cubicFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Quaternion CurValue;
   osg::spline(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFQuaternion&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFQuaternion&>(Result).getValue() *= CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Quaternion PrevValue;
      osg::spline(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFQuaternion&>(Result).getValue() *= ( CurValue/PrevValue );
   }
   else
   {
      SWARNING << "No policy defined for Animation value replacement policy: " << ReplacementPolicy << "." << std::endl;
   }
   return true;
}

bool KeyframeSequenceQuaternion::stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
                                                             const osg::MFReal32& Keys,
                                                             const osg::UInt32& Cycling,
                                                             const osg::Real32& Time,
                                                             const osg::Real32& PrevTime,
                                                             const osg::ValueReplacementPolicy& ReplacementPolicy,
                                                             osg::Field& Result)
{
   Quaternion CurValue;
   bool ReturnValue = osg::step(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, Time, CurValue, Cycling != 1);
   if(ReplacementPolicy == OVERWRITE)
   {
      static_cast<osg::SFQuaternion&>(Result).setValue(CurValue);
   }
   else if(ReplacementPolicy == ADDITIVE_ABSOLUTE)
   {
      static_cast<osg::SFQuaternion&>(Result).getValue() *= CurValue;
   }
   else if(ReplacementPolicy == ADDITIVE_SINCE_LAST)
   {
      Quaternion PrevValue;
      osg::step(osg::KeyframeSequenceQuaternionPtr::dcast(KeyValues)->getValues(), Keys, PrevTime, PrevValue, Cycling != 1);
      static_cast<osg::SFQuaternion&>(Result).getValue() *= ( CurValue/PrevValue );
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

KeyframeSequenceQuaternion::KeyframeSequenceQuaternion(void) :
    Inherited()
{
}

KeyframeSequenceQuaternion::KeyframeSequenceQuaternion(const KeyframeSequenceQuaternion &source) :
    Inherited(source)
{
}

KeyframeSequenceQuaternion::~KeyframeSequenceQuaternion(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequenceQuaternion::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequenceQuaternion::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequenceQuaternion NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCEQUATERNIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCEQUATERNIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCEQUATERNIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

