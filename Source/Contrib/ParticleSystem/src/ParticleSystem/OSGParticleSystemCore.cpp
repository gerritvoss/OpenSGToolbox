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

#include "OSGParticleSystemCore.h"
#include "OSGIntersectAction.h"
#include "OSGRenderAction.h"
#include "OSGSimpleGeometry.h"
#include "OSGCamera.h"
#include "OSGMatrix.h"
#include "OSGQuaternion.h"
#include "OSGRadixSort.h"
#include <stdio.h>
#include <vector>
#include <iterator>
#include "OSGParticleSystemEventDetails.h"
#include "OSGParticleEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleSystemCoreBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystemCore.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemCore::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            ParticleSystemCore::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            ParticleSystemCore::getClassType(),
            reinterpret_cast<Action::Callback>(
                &MaterialDrawable::renderActionLeaveHandler));

        IntersectAction::registerEnterDefault(
            ParticleSystemCore::getClassType(),
            reinterpret_cast<Action::Callback>(&ParticleSystemCore::intersect));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystemCore::drawPrimitives (DrawEnv *pEnv)
{
    //If I have a Drawer tell it to draw the particles
    if(getDrawer() != NULL && getSystem() != NULL)
    {
        //If the Sort Time statistic is being tracked then start the timer
        StatTimeElem *SortTimeStatElem = StatCollector::getGlobalElem(ParticleSystem::statParticleSortTime);
        if(SortTimeStatElem)
        {
            SortTimeStatElem->start();
        }

        //Sorting particles
        checkAndInitializeSort();
		sortParticles(pEnv);

        //If the Sort Time statistic is being tracked then stop the timer
        if(SortTimeStatElem)
        {
            SortTimeStatElem->stop();
        }

		getDrawer()->draw(pEnv, getSystem(), *getMFSort());
    }
    else
    {
        if(getDrawer() == NULL)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystemDrawer is Null."));
        }
        if(getSystem() == NULL)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystem is Null."));
        }
    }
}

std::vector<UInt32> ParticleSystemCore::intersectLine(const Line& Ray, Real32 IntersectionDistance) const
{
    return getSystem()->intersect(Ray,IntersectionDistance,-1, getParents().front());
}

void ParticleSystemCore::checkAndInitializeSort(void)
{

	if(getMFSort()->size() != getSystem()->getNumParticles())
	{	// re-init _mfSort if there is a discrepency between number of particles in each
		editMFSort()->resize(getSystem()->getNumParticles(),1);
		editMFDistances()->resize(getSystem()->getNumParticles(), 0.0f);
		//initialize _mfSort
		for(UInt32 i(0); i < getSystem()->getNumParticles(); ++i)
		{
			editSort(i) = i;
			editDistances(i) = 0.0f;
		}
	}

}

void ParticleSystemCore::fill(DrawableStatsAttachment *pStat)
{
    if(getDrawer() == NULL)
    {
        FINFO(("ParticleSystemCore::fill(DrawableStatsAttachment *): "
               "No Drawer Attached.\n"));

        return;
    }
    if(getSystem() == NULL)
    {
        FINFO(("ParticleSystemCore::fill(DrawableStatsAttachment *): "
               "No System Attached.\n"));

        return;
    }

    //Fill the number of Particles
    StatIntElem *statElem = StatCollector::getGlobalElem(ParticleSystem::statNParticles);
    if(statElem)
    {
        statElem->add(getSystem()->getNumParticles());
    }

    getDrawer()->fill(pStat, getSystem(), *getMFSort());
}

Action::ResultE ParticleSystemCore::intersect( Action* action )
{
    return Action::Continue;
}

void ParticleSystemCore::adjustVolume(Volume & volume)
{
    //The adjusted volume is dependent on the Particle System as well as the 
    //Particle Drawer
	Inherited::adjustVolume(volume);

    if(getDrawer() != NULL && getSystem() != NULL)
    {
        getDrawer()->adjustVolume(getSystem(), volume);
    }
}


void ParticleSystemCore::sortParticles(DrawEnv *pEnv)
{
    //This should be called if the ParticleSystem has just finished an update

	UInt32 numParticles = getSystem()->getNumParticles();
	if(getSystem()         != NULL && 
       getSortingMode()    != NONE && 
       getMFSort()->size() >  0)
    {
		//extract camera position
		Pnt3f CameraLocation(0.0,0.0,0.0);
		pEnv->getCameraToWorld().mult(CameraLocation,CameraLocation);

		/* 
		 * Lots of time spent getting the sorting as best as possible
		 * std::qsort averages 3 to 4 ticks w/ 500 particles. Fast enough, but not stable
		 *	std::stable_sort averages 18 to 19 ticks w/ 500 particles, much too slow
		 *	The radix sort we use here avgs. 1 to 2 ticks, and is stable	
		 */
	
		// fill up the array of distances from the particles to the camera
		switch(getSortingMode())
		{
			case BACK_TO_FRONT:
			{
				for(UInt32 i(0); i < numParticles; i++)
				{
					editDistances(i) = -(getSystem()->getPosition(i) - CameraLocation).squareLength();
				}
				break;
			}

			case FRONT_TO_BACK:
			{
				for(UInt32 i(0); i < numParticles; i++)
				{
					editDistances(i) = (getSystem()->getPosition(i) - CameraLocation).squareLength();
				}
				break;
			}
		}
		
		// perform the actual sort
		RadixSort(numParticles ,_mfDistances, _mfSort);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ParticleSystemCore::handleVolumeChanged(ParticleSystemEventDetails* const details)
{
    for(UInt32 i = 0; i < getParents().size(); i++)
    {
        getParents()[i]->invalidateVolume();
    }
}

void ParticleSystemCore::handleParticleGenerated(ParticleEventDetails* const details)
{
    //add particle to _mfSort
    editMFSort()->push_back(getMFSort()->size());
	editMFDistances()->push_back(0.0f);
}

void ParticleSystemCore::handleParticleKilled(ParticleEventDetails* const details)
{
    // remove highest indexed particle from _mfSort
    for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
    {
        if((*theItor) == _mfSort.size() - 1 ) 
        {
            _mfSort.erase(theItor);
			_mfDistances.erase(--_mfDistances.end());
            break;
        }
    }
}

void ParticleSystemCore::handleParticleStolen(ParticleEventDetails* const details)
{
    // remove particle from _mfSort
    for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
    {
        if((int)*theItor == _mfSort.size() - 1 ) 
        {
            _mfSort.erase(theItor);
			_mfDistances.erase(--_mfDistances.end());
            break;
        }
    }
}


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

void ParticleSystemCore::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SystemFieldMask)
    {
        _VolumeChangedConnection.disconnect();
        _ParticleGeneratedConnection.disconnect();
        _ParticleKilledConnection.disconnect();
        _ParticleStolenConnection.disconnect();

        if(getSystem() != NULL)
        {
            _VolumeChangedConnection = getSystem()->connectVolumeChanged(boost::bind(&ParticleSystemCore::handleVolumeChanged, this, _1));
            _ParticleGeneratedConnection = getSystem()->connectParticleGenerated(boost::bind(&ParticleSystemCore::handleParticleGenerated, this, _1));
            _ParticleKilledConnection = getSystem()->connectParticleKilled(boost::bind(&ParticleSystemCore::handleParticleKilled, this, _1));
            _ParticleStolenConnection = getSystem()->connectParticleStolen(boost::bind(&ParticleSystemCore::handleParticleStolen, this, _1));
        }
    }
    if(((whichField & SystemFieldMask) || (whichField & ParentsFieldMask))
       && _mfParents.size() > 0 &&
       getSystem() != NULL)
    {
        getSystem()->setBeacon(dynamic_cast<Node*>(_mfParents.front()));
    }
    if((whichField & ParentsFieldMask)
       && _mfParents.size() > 1)
    {
        SWARNING << "ParticleSystemCore: Cannot have a single instance of"
                    "ParticleSystemCore attached to more than 1 Node." << std::cout;
    }

    if(whichField & SystemFieldMask ||
       whichField & DrawerFieldMask)
    {
        for(UInt32 i = 0; i < _mfParents.size(); i++)
        {
            _mfParents[i]->invalidateVolume();
        }
    }

    if((whichField & SystemFieldMask) || (whichField & SortFieldMask))
    {
        if(getSystem() != NULL)
        {
            if(getMFSort()->size() != getSystem()->getNumParticles())
            {
                editMFSort()->resize(getSystem()->getNumParticles());
                editMFDistances()->resize(getSystem()->getNumParticles());

                //initialize _mfSort
                for(UInt32 i(0); i < getSystem()->getNumParticles(); ++i)
                {
                    editSort(i) = i;
                    editDistances(i) = 0.0f;
                }
            }
        }
        else
        {
            if(getMFSort()->size() != 0)
            {
                editMFSort()->clear();
                editMFDistances()->clear();
            }
        }
    }
}

void ParticleSystemCore::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump ParticleSystemCore NI" << std::endl;
}


OSG_END_NAMESPACE
