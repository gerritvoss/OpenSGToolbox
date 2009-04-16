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

#include "OSGQuadParticleSystemDrawer.h"
#include "ParticleSystem/OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::QuadParticleSystemDrawer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void QuadParticleSystemDrawer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE QuadParticleSystemDrawer::draw(DrawActionBase *action, ParticleSystemPtr System, const MFUInt32& Sort)
{
	Pnt3f P1,P2,P3,P4;

glBegin(GL_QUADS);
	for(UInt32 i(0); i<System->getNumParticles();++i)
	{
	//Loop through all particles
		//Get The Normal of the Particle
		Vec3f Normal = getQuadNormal(action,System, i);


	    //Calculate the Binormal as the cross between Normal and Up
	    Vec3f Binormal = getQuadUpDir(action,  System, i).cross(Normal);
		
		//Get the Up Direction of the Particle
		Vec3f Up = Normal.cross(Binormal);

		//Determine Local Space of the Particle
		Pnt3f Position = System->getPosition(i);

		//Determine the Width and Height of the quad
		Real32 Width = System->getSize(i).x()*getQuadSizeScaling().x(),Height =System->getSize(i).y()*getQuadSizeScaling().y();

		//Calculate Quads positions
		P1 = Position + (Width/2.0f)*Binormal + (Height/2.0f)*Up;
		P2 = Position + (Width/2.0f)*Binormal - (Height/2.0f)*Up;
		P3 = Position - (Width/2.0f)*Binormal - (Height/2.0f)*Up;
		P4 = Position - (Width/2.0f)*Binormal + (Height/2.0f)*Up;

	    //Draw the Quad
		glNormal3fv(Normal.getValues());
		
		glColor4fv(System->getColor(i).getValuesRGBA());
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(P1.getValues());
		
		
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(P2.getValues());
	
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(P3.getValues());

		glTexCoord2f(0.0, 1.0);
		glVertex3fv(P4.getValues());
	}
glEnd();
	//Generate a local space for the particle
    return Action::Continue;
}

void QuadParticleSystemDrawer::adjustVolume(ParticleSystemPtr System, Volume & volume)
{
	Pnt3f Position;
	Real32 Width, Height, Max;
	for(UInt32 i(0); i<System->getNumParticles();++i)
	{
	//Loop through all particles

		//Get the Particle Position
		Position = System->getPosition(i);

		//Maximum of Length and Height
		getQuadWidthHeight(System, i, Width, Height);
		Max= osgMax(Width, Height);

		//Calculate Quads positions
		volume.extendBy( Position - Vec3f(Max/2.0f) );
		volume.extendBy( Position + Vec3f(Max/2.0f) );
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void QuadParticleSystemDrawer::getQuadWidthHeight(ParticleSystemPtr System, UInt32 Index, Real32& Width, Real32& Height)
{
	Width = System->getSize(Index).x();
	Height = System->getSize(Index).y();
}

Vec3f QuadParticleSystemDrawer::getQuadNormal(DrawActionBase *action,ParticleSystemPtr System, UInt32 Index)
{
	Vec3f Direction;
	
	switch(getNormalSource())
	{
	case NORMAL_POSITION_CHANGE:
		Direction = System->getPositionChange(Index);
			Direction.normalize();
		break;
	case NORMAL_VELOCITY_CHANGE:
		Direction = System->getVelocityChange(Index);
			Direction.normalize();
		break;
	case NORMAL_VELOCITY:
		Direction = System->getVelocity(Index);
			Direction.normalize();
		break;
	case NORMAL_ACCELERATION:
		Direction = System->getAcceleration(Index);
			Direction.normalize();
		break;
	case NORMAL_PARTICLE_NORMAL:
		Direction = System->getNormal(Index);
		break;
	case NORMAL_VIEW_POSITION:
		{
			//TODO: make this more efficient
			Matrix ModelView = action->getCameraToWorld();
			Vec3f Position(ModelView[0][3],ModelView[1][3],ModelView[2][3]);
			Direction = Position - System->getPosition(Index);
			Direction.normalize();
		
		break;
		}
	case NORMAL_STATIC:
		Direction = getNormal();
			break;
	case NORMAL_VIEW_DIRECTION:
	default:
		{
			//TODO: make this more efficient
			Matrix ModelView = action->getCameraToWorld();
			Direction.setValues(ModelView[2][0],ModelView[2][1],ModelView[2][2]);
		break;
		}
	}
	return Direction;
}

Vec3f QuadParticleSystemDrawer::getQuadUpDir(DrawActionBase *action,ParticleSystemPtr System, UInt32 Index)
{
	Vec3f Direction;
	
	switch(getUpSource())
	{
	case UP_POSITION_CHANGE:
		Direction = System->getPositionChange(Index);
		break;
	case UP_VELOCITY_CHANGE:
		Direction = System->getVelocityChange(Index);
		break;
	case UP_VELOCITY:
		Direction = System->getVelocity(Index);
		break;
	case UP_ACCELERATION:
		Direction = System->getAcceleration(Index);
		break;
	case UP_PARTICLE_NORMAL:
		Direction = System->getNormal(Index);
		break;
	case UP_STATIC:
		Direction = getUp();
		break;
	case UP_VIEW_DIRECTION:
	default:
		{
			//TODO: make this more efficient
			Matrix ModelView = action->getCameraToWorld();
			Direction.setValues(ModelView[1][0],ModelView[1][1],ModelView[1][2]);
		break;
		}
	}

	return Direction;
}

/*----------------------- constructors & destructors ----------------------*/

QuadParticleSystemDrawer::QuadParticleSystemDrawer(void) :
    Inherited()
{
}

QuadParticleSystemDrawer::QuadParticleSystemDrawer(const QuadParticleSystemDrawer &source) :
    Inherited(source)
{
}

QuadParticleSystemDrawer::~QuadParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void QuadParticleSystemDrawer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void QuadParticleSystemDrawer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump QuadParticleSystemDrawer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGQUADPARTICLESYSTEMDRAWERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQUADPARTICLESYSTEMDRAWERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGQUADPARTICLESYSTEMDRAWERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

