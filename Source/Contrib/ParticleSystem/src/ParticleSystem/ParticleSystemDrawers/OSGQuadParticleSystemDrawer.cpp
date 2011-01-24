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

#include "OSGQuadParticleSystemDrawer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGQuadParticleSystemDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGQuadParticleSystemDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void QuadParticleSystemDrawer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE QuadParticleSystemDrawer::draw(DrawEnv *pEnv, ParticleSystemUnrecPtr System, const MFUInt32& Sort)
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
    Pnt3f P1,P2,P3,P4;
    UInt32 Index;

    glBegin(GL_QUADS);
        for(UInt32 i(0); i<NumParticles;++i)
        {
            if(isSorted)
            {
                Index = Sort[i];
            }
            else
            {
                Index = i;
            }
            //Loop through all particles
            //Get The Normal of the Particle
            Vec3f Normal = getQuadNormal(pEnv,System, Index);


            //Calculate the Binormal as the cross between Normal and Up
            Vec3f Binormal = getQuadUpDir(pEnv,  System, Index).cross(Normal);

            //Get the Up Direction of the Particle
            Vec3f Up = Normal.cross(Binormal);

            //Determine Local Space of the Particle
            //This is where error occurs
            Pnt3f Position = System->getPosition(Index);

            //Determine the Width and Height of the quad
            Real32 Width = System->getSize(Index).x()*getQuadSizeScaling().x(),Height =System->getSize(Index).y()*getQuadSizeScaling().y();

            //Calculate Quads positions
            P1 = Position + (Width/2.0f)*Binormal + (Height/2.0f)*Up;
            P2 = Position + (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P3 = Position - (Width/2.0f)*Binormal - (Height/2.0f)*Up;
            P4 = Position - (Width/2.0f)*Binormal + (Height/2.0f)*Up;

            //Draw the Quad
            glNormal3fv(Normal.getValues());

            glColor4fv(System->getColor(Index).getValuesRGBA());
            glTexCoord2f(1.0, 1.0);
            glVertex3fv(P1.getValues());


            glTexCoord2f(0.0, 1.0);
            glVertex3fv(P4.getValues());


            glTexCoord2f(0.0, 0.0);
            glVertex3fv(P3.getValues());

            glTexCoord2f(1.0, 0.0);
            glVertex3fv(P2.getValues());
        }
        glColor4f(1.0f,1.0f,1.0f,1.0f);
    glEnd();

    //Generate a local space for the particle
    return Action::Continue;
}

bool QuadParticleSystemDrawer::setNormalAndUpSource(UInt32 NormalSource, UInt32 UpSource, Vec3f Normal, Vec3f Up)
{
    // set the values for the static normal and up vectors, since they won't necessarily be used
    setNormal(Normal);
    setUp(Up);

    bool defaultsUsed = false;
    // need to determine if the normal source and up direction source are compatible
    // this checks all possible valid combinations we have decided to allow
    if(	(NormalSource == NORMAL_VELOCITY && 
         (UpSource ==UP_POSITION_CHANGE || UpSource == UP_VELOCITY_CHANGE)) ||

        (UpSource == UP_VELOCITY && 
         (NormalSource ==  NORMAL_POSITION_CHANGE || NormalSource ==
          NORMAL_VELOCITY_CHANGE || NormalSource == NORMAL_VIEW_DIRECTION )) ||

        (UpSource == UP_VIEW_DIRECTION && 
         (NormalSource == NORMAL_VIEW_DIRECTION || NormalSource == NORMAL_VIEW_POSITION )) ||

        (NormalSource == NORMAL_STATIC) || (UpSource == UP_STATIC))
    {
        // this is a valid combination, so use it!
        setNormalSource(NormalSource);
        setUpSource(UpSource);

    }
    else
    {
        // the combination of up and normal sources is incompatible, use defaults
        setNormalSource(NORMAL_STATIC);
        setUpSource(UP_STATIC);
        defaultsUsed = true;
    }

    return !defaultsUsed;
}


void QuadParticleSystemDrawer::adjustVolume(ParticleSystemUnrecPtr System, Volume & volume)
{
    //Get The Volume of the Particle System
    Pnt3f MinVolPoint,MaxVolPoint;
    System->getVolume().getBounds(MinVolPoint,MaxVolPoint);

    Real32 Width, Height, Max(0.0f);

    Vec3f MaxSize(System->getMaxParticleSize() * 0.5f);

    volume.extendBy( MinVolPoint - MaxSize );
    volume.extendBy( MaxVolPoint + MaxSize );

}

void QuadParticleSystemDrawer::fill(DrawableStatsAttachment *pStat,
                                    ParticleSystemUnrecPtr System,
                                    const MFUInt32& Sort)
{
    if(pStat == NULL)
    {
        FINFO(("QuadParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "No attachment given.\n"));

        return;
    }
    if(System == NULL)
    {
        FINFO(("QuadParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
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

    pStat->setVertices(4*NumParticles);
    pStat->setTriangles(2*NumParticles);
    pStat->setValid(true);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void QuadParticleSystemDrawer::getQuadWidthHeight(ParticleSystemUnrecPtr System, UInt32 Index, Real32& Width, Real32& Height)
{
	Width = System->getSize(Index).x();
	Height = System->getSize(Index).y();
}

Vec3f QuadParticleSystemDrawer::getQuadNormal(DrawEnv *pEnv, ParticleSystemUnrecPtr System, UInt32 Index)
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
            Matrix ModelView(pEnv->getCameraViewing()); 
			Pnt3f Position(ModelView[0][3],ModelView[1][3],ModelView[2][3]);
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
            Matrix ModelView(pEnv->getCameraViewing()); 
            ModelView.mult(pEnv->getObjectToWorld());
			Direction.setValues(ModelView[0][2],ModelView[1][2],ModelView[2][2]);
		break;
		}
	}
	return Direction;
}

Vec3f QuadParticleSystemDrawer::getQuadUpDir(DrawEnv *pEnv, ParticleSystemUnrecPtr System, UInt32 Index)
{
	Vec3f Direction;
	
	switch(getUpSource())
	{
	case UP_POSITION_CHANGE:
		Direction = System->getPositionChange(Index);
        Direction.normalize();
		break;
	case UP_VELOCITY_CHANGE:
		Direction = System->getVelocityChange(Index);
        Direction.normalize();
		break;
	case UP_VELOCITY:
		Direction = System->getVelocity(Index);
        Direction.normalize();
		break;
	case UP_ACCELERATION:
		Direction = System->getAcceleration(Index);
        Direction.normalize();
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
            Matrix ModelView(pEnv->getCameraViewing()); 
            ModelView.mult(pEnv->getObjectToWorld());
			Direction.setValues(ModelView[0][1],ModelView[1][1],ModelView[2][1]);
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

void QuadParticleSystemDrawer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void QuadParticleSystemDrawer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump QuadParticleSystemDrawer NI" << std::endl;
}

OSG_END_NAMESPACE
