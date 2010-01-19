/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGDrawable.h>

#include "OSGPointParticleSystemDrawer.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PointParticleSystemDrawer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PointParticleSystemDrawer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE PointParticleSystemDrawer::draw(DrawActionBase *action, ParticleSystemPtr System, const MFUInt32& Sort)
{
	bool isSorted(Sort.getSize() > 0);
	UInt32 NumParticles;
	if(isSorted)
	{
		NumParticles = Sort.getSize();
	}
	else
	{
		NumParticles = System->getNumParticles();
	}
	action->getStatistics()->getElem(ParticleSystem::statNParticles)->add(NumParticles);
	if(NumParticles != 0)
	{

		bool SeparateColors(System->getNumColors() > 1);
		bool SeparateSizes(System->getNumSizes() > 1 && getForcePerParticleSizing());
		bool SeparateNormals(System->getNumNormals() > 1);

        GLfloat PointSizeRange[2];
        glGetFloatv(GL_POINT_SIZE_RANGE, PointSizeRange);

		UInt32 Index;
		glBegin(GL_POINTS);
			if(isSorted)
			{
				Index = Sort[0];
			}
			else
			{
				Index = 0;
			}

			if(!SeparateColors)
			{
				glColor4fv(System->getColor(Index).getValuesRGBA());
			}
			//Sizes
			if(!SeparateSizes && getForcePerParticleSizing())
			{
                glPointSize(osgClamp<Real32>(PointSizeRange[0], System->getSize(Index).x(), PointSizeRange[1]));
			}
			//Normals
			if(!SeparateNormals)
			{
				glNormal3fv(System->getNormal(Index).getValues());
			}
			for(UInt32 i(0) ; i<NumParticles ; ++i)
			{
				if(isSorted)
				{
					Index = Sort[i];
				}
				else
				{
					Index = i;
				}
				//Colors
				if(SeparateColors)
				{
					glColor4fv(System->getColor(Index).getValuesRGBA());
				}
				//Sizes
				if(SeparateSizes)
				{
                    glEnd();
		            
                    glPointSize(osgClamp<Real32>(PointSizeRange[0], System->getSize(Index).x(), PointSizeRange[1]));
                    
                    glBegin(GL_POINTS);
				}
				//Normals
				if(SeparateNormals)
				{
					glNormal3fv(System->getNormal(Index).getValues());
				}
				//Positions
				glVertex3fv(System->getPosition(Index).getValues());
			}
		glEnd();
	}

    action->getStatistics()->getElem(Drawable::statNPoints)->add(NumParticles);
    action->getStatistics()->getElem(Drawable::statNVertices)->add(NumParticles);
    action->getStatistics()->getElem(Drawable::statNPrimitives)->add(NumParticles);

    return Action::Continue;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PointParticleSystemDrawer::PointParticleSystemDrawer(void) :
    Inherited()
{
}

PointParticleSystemDrawer::PointParticleSystemDrawer(const PointParticleSystemDrawer &source) :
    Inherited(source)
{
}

PointParticleSystemDrawer::~PointParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PointParticleSystemDrawer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PointParticleSystemDrawer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PointParticleSystemDrawer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPOINTPARTICLESYSTEMDRAWERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPOINTPARTICLESYSTEMDRAWERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPOINTPARTICLESYSTEMDRAWERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

