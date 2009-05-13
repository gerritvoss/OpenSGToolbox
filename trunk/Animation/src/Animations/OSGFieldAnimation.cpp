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

Real32 FieldAnimation::getLength(void) const
{
    return getAnimator()->getLength();
}

void FieldAnimation::setAnimatedField(FieldContainerPtr TheContainer, const std::string& FieldName)
{
	if(TheContainer != NullFC)
	{
		FieldDescription * f = TheContainer->getType().findFieldDescription(FieldName.c_str());
		if( f == NULL )
		{
			SWARNING << "Could not find Field "<< FieldName << " in Field Container " << TheContainer->getTypeName()  << std::endl;
			return;
		}
		else
		{
			setAnimatedField(TheContainer, f->getFieldId());
		}
	}
	else
	{
         SWARNING << "There is no Field Container defined to Animate"  << std::endl;
         return;
	}
}

void FieldAnimation::setAnimatedField(FieldContainerPtr TheContainer, UInt32 FieldID)
{
	if(TheContainer != NullFC)
	{
		  FieldDescription * f = TheContainer->getType().getFieldDescription(FieldID);
		  if( f == NULL )
		  {
			SWARNING << "Could not find Field ID"<< FieldID << " in Field Container " << TheContainer->getTypeName()  << std::endl;
			return;
		  }
		  else
		  {
			   Field& TheField(*TheContainer->getField( FieldID ));

			   //Check if it's the right type
			   if(TheField.getContentType() != getAnimator()->getDataType())
			   {
					 SWARNING << "The data type of the field connected to this animation, " << TheField.getContentType().getCName() << ", is not the same data type that the animator works on, " << getAnimator()->getDataType().getCName() << "."  << std::endl;
					 return;
			   }
			   else
			   {
				  beginEditCP(FieldAnimationPtr(this), FieldIdFieldMask | ContainerFieldMask);
					 setFieldId( f->getFieldId() );
					 setContainer( TheContainer );
				  endEditCP(FieldAnimationPtr(this), FieldIdFieldMask | ContainerFieldMask);
			   }
		  }
	}
	else
	{
         SWARNING << "There is no Field Container defined to Animate"  << std::endl;
         return;
	}
}

void FieldAnimation::internalUpdate(const Real32& t, const Real32 prev_t)
{
	if(getContainer() == NullFC || getFieldId() == 0)
	{
        SWARNING << "There is no Field Container defined to Animate"  << std::endl;
		return;
	}
   Field& TheField(*getContainer()->getField( getFieldId() ));

   //Check if it's the right type
   if(TheField.getContentType() != getAnimator()->getDataType())
   {
         SWARNING << "The data type of the field connected to this animation, " << TheField.getContentType().getCName() << ", is not the same data type that the animator works on, " << getAnimator()->getDataType().getCName() << "."  << std::endl;
         return;
   }

   //Update the Field Container
   osg::beginEditCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask() );
   
   if( osg::KeyframeAnimatorPtr::dcast( getAnimator() )->animate(
               static_cast<osg::InterpolationType>(getInterpolationType()), 
               static_cast<osg::ValueReplacementPolicy>(getReplacementPolicy()),
               getCycling(), 
               t,
               prev_t,
               TheField) )
   {
      osg::endEditCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask());
   }
   else
   {
      osg::endEditNotChangedCP(getContainer(), getContainer()->getType().getFieldDescription(getFieldId())->getFieldMask());
   }
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

