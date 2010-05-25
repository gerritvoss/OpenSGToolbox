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

#include "OSGDiscParticleSystemDrawer.h"
#include "OSGDrawable.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDiscParticleSystemDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGDiscParticleSystemDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DiscParticleSystemDrawer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE DiscParticleSystemDrawer::draw(DrawEnv *pEnv,
                                               ParticleSystemUnrecPtr System,
                                               const MFUInt32& Sort)
{
    bool isSorted(Sort.size() > 0);
    UInt32 NumParticles;

    Color4f Color;
    bool areFadesSame(getCenterAlpha() == getEdgeAlpha());

    if(isSorted)
    {
        NumParticles = Sort.size();
    }
    else
    {
        NumParticles = System->getNumParticles();
    }

    UInt32 Index;

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

        Pnt3f Position = System->getPosition(Index);

        //Determine the Width and Height of the quad
        Real32 Width = System->getSize(Index).x()*getRadius(),
               Height =System->getSize(Index).y()*getRadius();

        glBegin(GL_TRIANGLE_FAN);
        //Draw the Disc
        glNormal3fv(Normal.getValues());

        //Color for center point
        Color = System->getColor(i);
        glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getCenterAlpha());


        //Center Point
        glTexCoord2f(0.0f,0.0f);
        glVertex3fv(Position.getValues());

        //Color for edges
        if(!areFadesSame)
        {
            glColor4f(Color.red(), Color.green(), Color.blue(), Color.alpha() * getEdgeAlpha());
        }

        //Edge points
        for(UInt32 j(0) ; j<_DiscPoints.size() ; ++j)
        {
            glTexCoord2fv(_DiscPoints[j].getValues());
            glVertex3f(Position.x() + Width*_DiscPoints[j].x()*Binormal.x() + Height*_DiscPoints[j].y()*Up.x(),
                       Position.y() + Width*_DiscPoints[j].x()*Binormal.y() + Height*_DiscPoints[j].y()*Up.y(),
                       Position.z() + Width*_DiscPoints[j].x()*Binormal.z() + Height*_DiscPoints[j].y()*Up.z()
                      );
        }
        glEnd();
    }

    //Generate a local space for the particle
    return Action::Continue;
}

void DiscParticleSystemDrawer::adjustVolume(ParticleSystemUnrecPtr System, Volume & volume)
{
    //Get The Volume of the Particle System
    Pnt3f MinVolPoint,MaxVolPoint;
    System->getVolume().getBounds(MinVolPoint,MaxVolPoint);

    Real32 Width, Height, Max(0.0f);

    //Maximum of Length and Height
    if(System->getNumParticles() > 0)
    {
        Max= osgMax(System->getMaxParticleSize().x()*getRadius(), System->getMaxParticleSize().y()*getRadius());
    }

    volume.extendBy( MinVolPoint - Vec3f(Max) );
    volume.extendBy( MaxVolPoint + Vec3f(Max) );
}

void DiscParticleSystemDrawer::fill(DrawableStatsAttachment *pStat,
                                    ParticleSystemUnrecPtr System,
                                    const MFUInt32& Sort)
{
    if(pStat == NULL)
    {
        FINFO(("DiscParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
               "No attachment given.\n"));

        return;
    }
    if(System == NULL)
    {
        FINFO(("DiscParticleSystemDrawer::fill(DrawableStatsAttachment *, ParticleSystemUnrecPtr , const MFUInt32& ): "
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

    pStat->setVertices((_DiscPoints.size()-1)*3*NumParticles);
    pStat->setTriangles((_DiscPoints.size()-1)*NumParticles);
    pStat->setValid(true);
}

/*-------------------------------------------------------------------------*\
  -  private                                                                 -
  \*-------------------------------------------------------------------------*/

Vec3f DiscParticleSystemDrawer::getQuadNormal(DrawEnv *pEnv,ParticleSystemUnrecPtr System, UInt32 Index)
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

                Pnt3f Position(ModelView[3][0],ModelView[3][1],ModelView[3][2]);
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
                Matrix ModelView(pEnv->getCameraViewing()); 
                ModelView.mult(pEnv->getObjectToWorld());
                Direction.setValues(ModelView[0][2],ModelView[1][2],ModelView[2][2]);
                break;
            }
    }
    return Direction;
}

Vec3f DiscParticleSystemDrawer::getQuadUpDir(DrawEnv *pEnv,ParticleSystemUnrecPtr System, UInt32 Index)
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
                Matrix ModelView(pEnv->getCameraViewing()); 
                ModelView.mult(pEnv->getObjectToWorld());
                Direction.setValues(ModelView[0][1],ModelView[1][1],ModelView[2][1]);
                break;
            }
    }

    return Direction;
}

void DiscParticleSystemDrawer::updateDiscPoints(void)
{
    _DiscPoints.clear();
    const Real32 PI(3.14159f);
    for(UInt32 i(0) ; i<=getSegments() ; ++i)
    {
        _DiscPoints.push_back(
                              Pnt2f(osgCos(static_cast<Real32>(i)/static_cast<Real32>(getSegments()) * 2.0 * PI),
                                    osgSin(static_cast<Real32>(i)/static_cast<Real32>(getSegments()) * 2.0 * PI))
                             );
    }
}

/*----------------------- constructors & destructors ----------------------*/

DiscParticleSystemDrawer::DiscParticleSystemDrawer(void) :
    Inherited()
{
    updateDiscPoints();
}

DiscParticleSystemDrawer::DiscParticleSystemDrawer(const DiscParticleSystemDrawer &source) :
    Inherited(source),
    _DiscPoints(source._DiscPoints)
{
}

DiscParticleSystemDrawer::~DiscParticleSystemDrawer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DiscParticleSystemDrawer::changed(ConstFieldMaskArg whichField, 
                                       UInt32            origin,
                                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SegmentsFieldMask)
    {
        updateDiscPoints();
    }
}

void DiscParticleSystemDrawer::dump(      UInt32    ,
                                          const BitVector ) const
{
    SLOG << "Dump DiscParticleSystemDrawer NI" << std::endl;
}

OSG_END_NAMESPACE
