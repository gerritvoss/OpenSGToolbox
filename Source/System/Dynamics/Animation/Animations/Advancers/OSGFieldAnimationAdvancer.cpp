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
#include <OpenSG/OSGSFSysTypes.h>

#include "OSGFieldAnimationAdvancer.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FieldAnimationAdvancer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldAnimationAdvancer::initMethod (void)
{
}

osg::Real32 FieldAnimationAdvancer::getValue(void) const
{
   if(getFieldId() == 0)
   {
      //Check if the Field Container is defined
      if(getContainer() == osg::NullFC)
      {
         SWARNING << "There is no Field Container defined to get Field Advancer"  << std::endl;
         return 0.0f;
      }
      //Check if the field in this container is defined
      FieldDescription * f = getContainer()->getType().findFieldDescription(getFieldName().c_str());
      if( f == NULL )
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
         return 0.0f;
      }
      //Found the Field so set my Field Id
      beginEditCP(FieldAnimationAdvancerPtr(this), FieldIdFieldMask);
         const_cast<SFUInt32*>(&_sfFieldId)->setValue(f->getFieldId());
      endEditCP(FieldAnimationAdvancerPtr(this), FieldIdFieldMask);
      //The Field was not found
      if(getFieldId() == 0)
      {
         SWARNING << "Could not find Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName()  << std::endl;
         return 0.0f;
      }
      //Check if the field is a Real32
      if(getContainer()->getField( getFieldId() )->getType() != SFReal32::getClassType())
      {
         SWARNING << "Field "<< getFieldName() << " in Field Container " << getContainer()->getTypeName() << "Is not a SFReal32 Field."  << std::endl;
         return 0.0f;
      }
   }
   
   return static_cast<SFReal32*>(getContainer()->getField( getFieldId() ))->getValue();
}

osg::Real32 FieldAnimationAdvancer::getPrevValue(void) const
{
   return getPrevFieldValue();
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldAnimationAdvancer::FieldAnimationAdvancer(void) :
    Inherited()
{
}

FieldAnimationAdvancer::FieldAnimationAdvancer(const FieldAnimationAdvancer &source) :
    Inherited(source)
{
}

FieldAnimationAdvancer::~FieldAnimationAdvancer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldAnimationAdvancer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FieldAnimationAdvancer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FieldAnimationAdvancer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFIELDANIMATIONADVANCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFIELDANIMATIONADVANCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFIELDANIMATIONADVANCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

