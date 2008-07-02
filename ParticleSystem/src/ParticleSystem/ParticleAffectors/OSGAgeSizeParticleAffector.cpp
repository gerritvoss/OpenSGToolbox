/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>


#include "OSGAgeSizeParticleAffector.h"

#include "ParticleSystem/OSGParticleSystem.h"
#include <OpenSG/Toolbox/OSGInterpolations.h>
#include <OpenSG/ParticleSystem/OSGAgeSizeParticleAffectorBase.h>
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AgeSizeParticleAffector

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AgeSizeParticleAffector::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AgeSizeParticleAffector::affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps)
{
	//TODO: Implement
	
	
	if(getAges().size()!=getSizes().size())
	{
		return false;
	}
	else
	{
		Real32 time;
		UInt32 i(0);
		time = (System->getAge(ParticleIndex))/(System->getLifespan(ParticleIndex));
		for( ;i<getAges().size() && time>getAges(i);++i)
		{
			
		}

		if(i == 0)
		{
			System->setSize(getSizes().front(),ParticleIndex);
		}

		else if(i == getAges().size())
		{
			System->setSize(getSizes().back(),ParticleIndex);
		}

		else
		{
			Vec3f size;
			//{
				time = (time - getAges(i-1))/(getAges(i)-getAges(i-1));

				lerp<Vec3f>(getSizes(i-1),getSizes(i),time,size);
				System->setSize(size,ParticleIndex);
			//}
		}


	}
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AgeSizeParticleAffector::AgeSizeParticleAffector(void) :
    Inherited()
{
}

AgeSizeParticleAffector::AgeSizeParticleAffector(const AgeSizeParticleAffector &source) :
    Inherited(source)
{
}

AgeSizeParticleAffector::~AgeSizeParticleAffector(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AgeSizeParticleAffector::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AgeSizeParticleAffector::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AgeSizeParticleAffector NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGAGESIZEPARTICLEAFFECTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGAGESIZEPARTICLEAFFECTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGAGESIZEPARTICLEAFFECTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

