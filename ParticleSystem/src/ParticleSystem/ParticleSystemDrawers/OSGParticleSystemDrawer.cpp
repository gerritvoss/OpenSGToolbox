/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include "OSGParticleSystemDrawer.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystemDrawer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemDrawer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystemDrawer::adjustVolume(ParticleSystemPtr System, Volume & volume)
{
	UInt32 NumParticles(System->getNumParticles());

	for(UInt32 i(0) ;i < NumParticles ; ++i)
	{
		volume.extendBy(System->getPosition(i));
	}

    volume.setValid();
    volume.setEmpty();

    Vec3f p;
    Real32 s;

    for(UInt32 i = 0; i < NumParticles; i++)
    {
        p = System->getPosition(i);
        // make the size bigger to accomodate rotations
        s=System->getSize(i)[0]*Sqrt2;

        p[0]+=s/2;
        p[1]+=s/2;
        p[2]+=s/2;
        volume.extendBy(p);
        p[0]-=s;
        volume.extendBy(p);
        p[1]-=s;
        volume.extendBy(p);
        p[0]+=s;
        volume.extendBy(p);
        p[2]-=s;
        volume.extendBy(p);
        p[0]-=s;
        volume.extendBy(p);
        p[1]+=s;
        volume.extendBy(p);
        p[0]+=s;
        volume.extendBy(p);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemDrawer::ParticleSystemDrawer(void) :
    Inherited()
{
}

ParticleSystemDrawer::ParticleSystemDrawer(const ParticleSystemDrawer &source) :
    Inherited(source)
{
}

ParticleSystemDrawer::~ParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemDrawer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleSystemDrawer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemDrawer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPARTICLESYSTEMDRAWERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLESYSTEMDRAWERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLESYSTEMDRAWERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

