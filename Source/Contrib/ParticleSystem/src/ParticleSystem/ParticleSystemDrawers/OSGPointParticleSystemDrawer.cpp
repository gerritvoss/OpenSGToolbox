/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGPointParticleSystemDrawer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPointParticleSystemDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGPointParticleSystemDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PointParticleSystemDrawer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE PointParticleSystemDrawer::draw(DrawEnv *pEnv,
                                               ParticleSystemUnrecPtr System,
                                               const MFUInt32& Sort)
{
	bool isSorted(Sort.size() > 0);
	UInt32 NumParticles;
	if(isSorted)
	{
		NumParticles = Sort.size();
	}
	else
	{
		NumParticles = System->getNumParticles();
	}
	if(NumParticles != 0)
	{

		bool SeparateColors(System->getNumColors() > 1);
		bool SeparateSizes(System->getNumSizes() > 1 && getForcePerParticleSizing());
		bool SeparateNormals(System->getNumNormals() > 1);

        GLfloat PointSizeRange[2];
        glGetFloatv(GL_POINT_SIZE_RANGE, PointSizeRange);

        //Sizes
        if(getForcePerParticleSizing())
        {
            glPointSize(osgClamp<Real32>(PointSizeRange[0], System->getSize(0).x(), PointSizeRange[1]));
        }
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

    return Action::Continue;
}

void PointParticleSystemDrawer::fill(DrawableStatsAttachment *pStat,
                                    ParticleSystemUnrecPtr System,
                                    const MFUInt32& Sort)
{
    if(pStat == NULL)
    {
        FINFO(("PointParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "No attachment given.\n"));

        return;
    }
    if(System == NULL)
    {
        FINFO(("PointParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "Particle System is NULL.\n"));

        return;
    }

    UInt32 NumParticles;

    if(Sort.size() > 0)
    {
        NumParticles = Sort.size();
    }
    else
    {
        NumParticles = System->getNumParticles();
    }

    pStat->setVertices(NumParticles);
    pStat->setPoints(NumParticles);
    pStat->setValid(true);
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

void PointParticleSystemDrawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PointParticleSystemDrawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PointParticleSystemDrawer NI" << std::endl;
}

OSG_END_NAMESPACE
