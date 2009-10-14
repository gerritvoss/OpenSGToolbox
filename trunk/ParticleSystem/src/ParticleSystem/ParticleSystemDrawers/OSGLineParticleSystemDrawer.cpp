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

#include "OSGLineParticleSystemDrawer.h"
#include "ParticleSystem/OSGParticleSystem.h"
#include <OpenSG/OSGDrawable.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LineParticleSystemDrawer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LineParticleSystemDrawer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE LineParticleSystemDrawer::draw(DrawActionBase *action, ParticleSystemPtr System, const MFUInt32& Sort)
{
 	UInt32 NumParticles(System->getNumParticles());
	action->getStatistics()->getElem(ParticleSystem::statNParticles)->add(NumParticles);

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
    action->getStatistics()->getElem(Drawable::statNLines)->add(NumParticles);
    action->getStatistics()->getElem(Drawable::statNVertices)->add(2*NumParticles);
    action->getStatistics()->getElem(Drawable::statNPrimitives)->add(NumParticles);


    return Action::Continue;
}

void LineParticleSystemDrawer::adjustVolume(ParticleSystemPtr System, Volume & volume)
{
    Inherited::adjustVolume(System, volume);
    //TODO: Implements this to take the SecPosition into account
}

Pnt3f LineParticleSystemDrawer::getLineEndpoint(ParticleSystemPtr System, UInt32 Index)
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
	case LENGTH_STATIC:
		default:
		LineLength = getLineLength();   ///could not find anything, line length field
		break;
		}
		
	return System->getPosition(Index)+(LineLength*Direction);

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

void LineParticleSystemDrawer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LineParticleSystemDrawer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LineParticleSystemDrawer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLINEPARTICLESYSTEMDRAWERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLINEPARTICLESYSTEMDRAWERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLINEPARTICLESYSTEMDRAWERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

