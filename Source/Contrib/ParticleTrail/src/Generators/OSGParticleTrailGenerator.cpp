/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGParticleTrailGenerator.h"
#include "OSGInterpolations.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleTrailGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleTrailGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleTrailGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ParticleSystemListenerPtr ParticleTrailGenerator::getParticleSystemListener(void)
{
	return &_TrailParticleSystemListener;
}

void ParticleTrailGenerator::TrailParticleSystemListener::systemUpdated(const ParticleSystemEventUnrecPtr e)
{
    ParticleSystemRecPtr system = dynamic_cast<ParticleSystem*>(e->getSource());
    Real64 timeStamp = e->getTimeStamp();
    UInt32 numParticles = system->getNumParticles();
    // check for proper init. of last added value
    if(!_mInitialized) 
    {
        _mLastAdded = timeStamp;

        _mInitialized = true;
    }

    // add new trail sections
    if(_mTrailGenerator->getTrailResolutionMethod() == TIME_SPACING)
    {
        Time start(_mLastAdded);
        while(_mLastAdded + _mTrailGenerator->getTrailResolution() < timeStamp)
        {
            _mLastAdded += _mTrailGenerator->getTrailResolution();
            Time fractionalTime = 1 - (timeStamp - _mLastAdded)/(timeStamp - start);
            for(PTMItor it = _mTrailGenerator->_mTrails.begin(); it != _mTrailGenerator->_mTrails.end(); it++)
            {
                if((*it).second.size() > 0)
                {
                    ParticleTrailGenerator::TrailSection newSection;

                    newSection.pos = lerp((*it).second.back().pos,
                                          system->getPosition((*it).first),fractionalTime);
                    newSection.time = lerp<Time>(_mLastAdded,timeStamp,fractionalTime);
                    newSection.ID = _mTrailGenerator->getNextTSID();
                    (*it).second.push_back(newSection);
                    _mTrailGenerator->internalTrailSectGenerated(newSection, system->getVelocity((*it).first));
                }
            }// end for(numParticles) 
        }// end while(_mLastAdded + ...)
    } else if(_mTrailGenerator->getTrailResolutionMethod() == DISTANCE_SPACING)
    {
        ParticleTrailGenerator::TrailSection newSection;
        Real32 curDist(0.0f), origDist(0.0f);
        for(PTMItor it = _mTrailGenerator->_mTrails.begin(); it != _mTrailGenerator->_mTrails.end(); it++)
        {
            // we continue to add new sections to the trail as long as the 
            // distance between the last added trail section and the current 
            // position is greater than the trail resolution
            if((*it).second.size() > 0)
            {	// get distance between current position and last added section
                origDist = system->getPosition((*it).first).dist((*it).second.back().pos);
                curDist = origDist;
                while(curDist > _mTrailGenerator->getTrailResolution())
                { // generate new trail section
                    ParticleTrailGenerator::TrailSection newSection;
                    Real32 fractionalDistance = 1 - (curDist-_mTrailGenerator->getTrailResolution())/origDist;

                    Pnt3f pos = lerp((*it).second.back().pos,
                                     system->getPosition((*it).first),fractionalDistance);

                    newSection.pos = pos;
                    newSection.time = lerp<Time>((*it).second.back().time,timeStamp,fractionalDistance);
                    newSection.ID = _mTrailGenerator->getNextTSID();
                    (*it).second.push_back(newSection);
                    _mTrailGenerator->internalTrailSectGenerated(newSection, system->getVelocity((*it).first));
                    // update distance
                    curDist = system->getPosition((*it).first).dist(pos);
                }// end while
            }// end if
        }// end for
    } else // 1 trail section/update
    {
        for(PTMItor it = _mTrailGenerator->_mTrails.begin(); it != _mTrailGenerator->_mTrails.end(); it++)
        {
            ParticleTrailGenerator::TrailSection newSection;
            newSection.time = timeStamp;
            newSection.pos = system->getPosition((*it).first);
            newSection.ID = _mTrailGenerator->getNextTSID();
            (*it).second.push_back(newSection);
            _mTrailGenerator->internalTrailSectGenerated(newSection, system->getVelocity((*it).first));
        }
    }

    // remove old/outdated trail sections for active particle trails
    for(PTMItor it = _mTrailGenerator->_mTrails.begin(); it != _mTrailGenerator->_mTrails.end(); it++)
    {
        if(_mTrailGenerator->getTrailLengthMethod() == TIME && (*it).second.size() > 0)
        {	
            while(/*sectionAge > _mTrailGenerator->getTrailLength() &&*/ (*it).second.size() > 0)
            {
                Real64 sectionAge = timeStamp - (*it).second.front().time;
                if(sectionAge > _mTrailGenerator->getTrailLength())
                {
                    _mTrailGenerator->internalTrailSectKilled((*it).second.front());
                    (*it).second.pop_front();
                } else break;
            }
        } else if((*it).second.size() > 0) // getTrailLengthMethod() == NUM_POINTS
        {
            UInt32 trailLength = (UInt32)_mTrailGenerator->getTrailLength();
            while((*it).second.size() > trailLength)
            {
                _mTrailGenerator->internalTrailSectKilled((*it).second.front());
                (*it).second.pop_front();
            }
        }// end if/else if
    }// end for(_mTrails.size())

    // remove old trail sections for killed particles
    for(PTMItor kptItor = _mTrailGenerator->_mKilledParticleTrails.begin(); kptItor != _mTrailGenerator->_mKilledParticleTrails.end(); kptItor++)
    {
        int numKilledTrails = _mTrailGenerator->_mKilledParticleTrails.size();
        if(_mTrailGenerator->getTrailLengthMethod() == TIME)
        {
            int thisSize = (*kptItor).second.size();
            while((*kptItor).second.size() > 0)
            {
                thisSize = (*kptItor).second.size();
                Real64 sectionAge = timeStamp - (*kptItor).second.front().time;
                UInt32 myid = (*kptItor).second.front().ID;
                if(sectionAge > _mTrailGenerator->getTrailLength())
                {
                    _mTrailGenerator->internalTrailSectKilled((*kptItor).second.front());
                    (*kptItor).second.pop_front();
                } else break;

            }
        } else // getTrailLengthMethod() == NUM_POINTS
        { // No more points are being generated, so if these aren't removed, they will stay forever.  
            // So, we just clear the trails. 
            while((*kptItor).second.size() > 0)
            {	
                _mTrailGenerator->internalTrailSectKilled((*kptItor).second.front());
                (*kptItor).second.pop_front();
            }
        }
    } // end for(_mKilledParticleTrails.size())

    // fire off internal update for subclasses of trail generators
    _mTrailGenerator->internalUpdate(e);
} // end ParticleTrailGenerator::TrailParticleSystemListener::systemUpdated()


    void
ParticleTrailGenerator::TrailParticleSystemListener::particleGenerated(const ParticleEventUnrecPtr e)
{
    ParticleTrailGenerator::TrailSection newSection;
    newSection.pos = e->getParticlePosition();
    newSection.time = e->getTimeStamp();
    newSection.ID = _mTrailGenerator->getNextTSID();
    ParticleTrailGenerator::ParticleTrail trail;
    trail.push_back(newSection);
    _mTrailGenerator->_mTrails[e->getParticleIndex()] = trail;
    _mTrailGenerator->internalGenerated(e);
    _mTrailGenerator->internalTrailSectGenerated(newSection, e->getParticleVelocity());
}

void ParticleTrailGenerator::TrailParticleSystemListener::particleKilled(const ParticleEventUnrecPtr e)
{
    if(_mTrailGenerator->_mTrails[e->getParticleIndex()].size() > 0)
    {
        _mTrailGenerator->_mKilledParticleTrails[e->getParticleIndex()] = _mTrailGenerator->_mTrails[e->getParticleIndex()];		
    }
    _mTrailGenerator->_mTrails[e->getParticleIndex()] = _mTrailGenerator->_mTrails[_mTrailGenerator->_mTrails.size()-1];
    _mTrailGenerator->_mTrails.erase(_mTrailGenerator->_mTrails.size()-1);
    _mTrailGenerator->internalKill(e);

}

void ParticleTrailGenerator::TrailParticleSystemListener::particleStolen(const ParticleEventUnrecPtr e)
{
    if(_mTrailGenerator->_mTrails[e->getParticleIndex()].size() > 0)
    {
        _mTrailGenerator->_mKilledParticleTrails[e->getParticleIndex()] =_mTrailGenerator->_mTrails[e->getParticleIndex()];
    }
    _mTrailGenerator->_mTrails[e->getParticleIndex()] = _mTrailGenerator->_mTrails[_mTrailGenerator->_mTrails.size()-1];
    _mTrailGenerator->_mTrails.erase(_mTrailGenerator->_mTrails.size()-1);
    _mTrailGenerator->internalKill(e);
}

void ParticleTrailGenerator::TrailParticleSystemListener::volumeChanged(const ParticleSystemEventUnrecPtr e)
{
    // nothing to do
}

UInt32 ParticleTrailGenerator::getNextTSID(void)
{
    return _mTrailSectIDCntr++;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleTrailGenerator::ParticleTrailGenerator(void) :
    Inherited(),
    _TrailParticleSystemListener(this)
{
}

ParticleTrailGenerator::ParticleTrailGenerator(const ParticleTrailGenerator &source) :
    Inherited(source),
    _TrailParticleSystemListener(this)
{
}

ParticleTrailGenerator::~ParticleTrailGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleTrailGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleTrailGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleTrailGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
