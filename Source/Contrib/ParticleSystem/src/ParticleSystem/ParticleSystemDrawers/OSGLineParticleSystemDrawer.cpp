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

#include "OSGLineParticleSystemDrawer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLineParticleSystemDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGLineParticleSystemDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LineParticleSystemDrawer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE LineParticleSystemDrawer::draw(DrawEnv *pEnv,
                                               ParticleSystemUnrecPtr System,
                                               const MFUInt32& Sort)
{
 	UInt32 NumParticles(System->getNumParticles());

	bool areEndpointsFadeSame(getEndPointFading().x() == getEndPointFading().y());
	Color4f Color;

	if(NumParticles != 0)
	{

		bool SeparateColors(System->getNumColors() > 1);
		bool SeparateSizes(System->getNumSizes() > 1);
		bool SeparateNormals(System->getNumNormals() > 1);

		glBegin(GL_LINES);
			//Colors
			if(!SeparateColors && areEndpointsFadeSame)
			{
				Color = System->getColor(0);
				glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEndPointFading().x());
			}
			//Sizes
			if(!SeparateSizes)
			{
				//glColor4fv(System->getColor(0).getValuesRGBA());
			}
			//Normals
			if(!SeparateNormals)
			{
				glNormal3fv(System->getNormal(0).getValues());
			}
			for(UInt32 i(0) ; i<NumParticles ; ++i)
			{
				//Start Color
				if(SeparateColors)
				{
					Color = System->getColor(i);
					glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEndPointFading().x());
				}
				else if(!SeparateColors && !areEndpointsFadeSame)
				{
					Color = System->getColor(0);
					glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEndPointFading().x());
				}
				//Sizes
				if(SeparateSizes)
				{
					//glColor4fv(System->getColor(i).getValuesRGBA());
				}
				//Normals
				if(SeparateNormals)
				{
					glNormal3fv(System->getNormal(i).getValues());
				}
				//Positions
				glVertex3fv(System->getPosition(i).getValues());
				
				//End Color
				if(SeparateColors && !areEndpointsFadeSame)
				{
					Color = System->getColor(i);
					glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEndPointFading().y());
				}
				else if(!SeparateColors && !areEndpointsFadeSame)
				{
					Color = System->getColor(0);
					glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEndPointFading().y());
				}
				glVertex3fv(getLineEndpoint(System, i).getValues());
			}
		glEnd();
	}

    return Action::Continue;
}

void LineParticleSystemDrawer::adjustVolume(ParticleSystemUnrecPtr System, Volume & volume)
{
    UInt32 NumParticles = System->getNumParticles();
    for(UInt32 i(0) ; i<NumParticles ; ++i)
    {
        volume.extendBy(System->getPosition(i));
        volume.extendBy(getLineEndpoint(System, i));
    }
}

Pnt3f LineParticleSystemDrawer::getLineEndpoint(ParticleSystemUnrecPtr System,
                                                UInt32 Index) const
{
	Vec3f Direction;

	//Calculate Direction
	switch(getLineDirectionSource())
	{
	case DIRECTION_POSITION_CHANGE:
		Direction = System->getPositionChange(Index);
		break;
	case DIRECTION_VELOCITY_CHANGE:
		Direction = System->getVelocityChange(Index);
		break;
	case DIRECTION_VELOCITY:
		Direction = System->getVelocity(Index);
		break;
	case DIRECTION_ACCELERATION:
		Direction = System->getAcceleration(Index);
		break;
	case DIRECTION_STATIC:
		Direction = getLineDirection();
		break;
	case DIRECTION_NORMAL:
	default:
		Direction = System->getNormal(Index);
		break;
	}


	//Calculate Length
	Real32 LineLength;

	switch(getLineLengthSource())
	{
	case LENGTH_SIZE_X:
		LineLength = System->getSize(Index).x();
		break;
	case LENGTH_SIZE_Y:
		LineLength = System->getSize(Index).y();
		break;
	case LENGTH_SIZE_Z:
		LineLength = System->getSize(Index).z();
		break;
	case LENGTH_SPEED:
		LineLength = System->getVelocity(Index).length();
		break;
	case LENGTH_ACCELERATION:
		LineLength = System->getAcceleration(Index).length();
		break;
	case LENGTH_STATIC:
		default:
		LineLength = getLineLength();   ///could not find anything, line length field
		break;
		}
    LineLength *= getLineLengthScaling();
		
	return System->getPosition(Index)+(LineLength*Direction);

}

void LineParticleSystemDrawer::fill(DrawableStatsAttachment *pStat,
                                    ParticleSystemUnrecPtr System,
                                    const MFUInt32& Sort)
{
    if(pStat == NULL)
    {
        FINFO(("LineParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "No attachment given.\n"));

        return;
    }
    if(System == NULL)
    {
        FINFO(("LineParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "Particle System is NULL.\n"));

        return;
    }

    UInt32 NumParticles;

    if(Sort.size() > 0)
    {
        NumParticles = Sort.getSize();
    }
    else
    {
        NumParticles = System->getNumParticles();
    }

    pStat->setVertices(2*NumParticles);
    pStat->setLines(NumParticles);
    pStat->setValid(true);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LineParticleSystemDrawer::LineParticleSystemDrawer(void) :
    Inherited()
{
}

LineParticleSystemDrawer::LineParticleSystemDrawer(const LineParticleSystemDrawer &source) :
    Inherited(source)
{
}

LineParticleSystemDrawer::~LineParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LineParticleSystemDrawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LineParticleSystemDrawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LineParticleSystemDrawer NI" << std::endl;
}

OSG_END_NAMESPACE
