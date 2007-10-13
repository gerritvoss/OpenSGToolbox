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

#include "OSGParticleSystemCore.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystemCore

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemCore::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE ParticleSystemCore::drawPrimitives (DrawActionBase *action)
{
    //TODO:Implement
    //If I have a Drawer tell it to draw the particles
    if(getDrawer() != NullFC && getSystem() != NullFC)
    {
        //getDrawer->draw(action, getSystem(), SortedParticleList);
    }
    else
    {
        if(getDrawer() == NullFC)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystemDrawer is Null."));
        }
        if(getSystem() == NullFC)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystem is Null."));
        }
    }

    return Action::Continue;
}

void ParticleSystemCore::adjustVolume(Volume & volume)
{
    //TODO: Implement
    //The adjusted volume is dependent on the Particle System as well as the 
    //Particle Drawer
}

void ParticleSystemCore::sortParticles(void)
{
    //This should be called if the ParticleSystem has
    //just finished an update

    //TODO: Implement
    if(getSystem() != NullFC && getSortingMode() != NONE)
    {
        switch(getSortingMode())
        {
        case FRONT_TO_BACK:
            //Use the FrontToBack Comparitor
            break;
        case BACK_TO_FRONT:
            //Use the BackToFront Comparitor
            break;
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemCore::ParticleSystemCore(void) :
    Inherited()
{
}

ParticleSystemCore::ParticleSystemCore(const ParticleSystemCore &source) :
    Inherited(source)
{
}

ParticleSystemCore::~ParticleSystemCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemCore::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleSystemCore::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemCore NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPARTICLESYSTEMCOREBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLESYSTEMCOREBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLESYSTEMCOREFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

