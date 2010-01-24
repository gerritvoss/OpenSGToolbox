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
#include <stdio.h>
#include <vector>
#include <iterator>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleSystemCoreBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystemCore.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

ParticleSystemCore::ParticleSortByViewPosition ParticleSystemCore::TheSorter = ParticleSystemCore::ParticleSortByViewPosition();

StatElemDesc<StatTimeElem> ParticleSystemCore::statParticleSortTime("ParticleSortTime", 
                                                                    "time for particles to be sorted");

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

Action::ResultE ParticleSystemCore::drawPrimitives (DrawEnv *pEnv)
{
    //If I have a Drawer tell it to draw the particles
    if(getDrawer() != NULL && getSystem() != NULL)
    {
		
		checkAndInitializeSort();
		sortParticles(pEnv);

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

    return Action::Continue;
}

std::vector<UInt32> ParticleSystemCore::intersectLine(const Line& Ray, Real32 IntersectionDistance) const
{
    return getSystem()->intersect(Ray,IntersectionDistance,-1, getParents().front());
}

void ParticleSystemCore::checkAndInitializeSort(void)
{

	if(getMFSort()->size() != getSystem()->getNumParticles() && getSortingMode() != NONE)
	{	// re-init _mfSort if there is a discrepency between number of particles in each
		editMFSort()->resize(getSystem()->getNumParticles());
		//initialize _mfSort
		for(UInt32 i(0); i < getSystem()->getNumParticles(); ++i)
		{
			editSort(i) = i;
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
    //This should be called if the ParticleSystem has
    //just finished an update

	//extract camera position
	Pnt3f CameraLocation(0.0,0.0,0.0);
    pEnv->getCameraToWorld().mult(CameraLocation,CameraLocation);
    if(getSystem() != NULL && getSortingMode() != NONE && _mfSort.size() > 0)
    {
		// initialize sort funcion struct
		TheSorter = ParticleSortByViewPosition(getSystem(),CameraLocation,true);

		// get sorting order
		switch(getSortingMode())
        {
			case FRONT_TO_BACK:
				//Use the FrontToBack Comparitor, already initialized above
				break;

			case BACK_TO_FRONT:
				//Use the BackToFront Comparitor, changes sorting order
				TheSorter = ParticleSortByViewPosition(getSystem(),CameraLocation,false);
				break;
        }
		
		// particles sorted using stdlib's quicksort
		std::qsort(&_mfSort[0],_mfSort.size(), sizeof(MFUInt32::StoredType),qSortComp);
		// sort with std::sort
		//std::sort(getSort().begin(), getSort().end(), TheSorter);
    }
}

ParticleSystemCore::ParticleSortByViewPosition::ParticleSortByViewPosition(const ParticleSystem* TheSystem, Pnt3f TheCameraPos, bool SortByMinimum) 
	: _System(TheSystem), _CameraPos(TheCameraPos.subZero()), _SortByMinimum(SortByMinimum)
{
}

ParticleSystemCore::ParticleSortByViewPosition::ParticleSortByViewPosition() 
	: _System(NULL), _CameraPos(Vec3f(0.0,0.0,0.0)), _SortByMinimum(true)
{
}


/*  
 *	This comparison operator is left here in case we revert to std::sort again
 */
bool ParticleSystemCore::ParticleSortByViewPosition::operator()(UInt32 ParticleIndexLeft, UInt32 ParticleIndexRight)
{
	bool retFlag;
	// relative distances squared are compared
	if(_SortByMinimum){
		retFlag = ((Vec3f(_System->getPosition(ParticleIndexLeft)) - _CameraPos).squareLength()) 
			< ((Vec3f(_System->getPosition(ParticleIndexRight)) - _CameraPos).squareLength());

	} else
	{
		retFlag = ((Vec3f(_System->getPosition(ParticleIndexLeft)) - _CameraPos).squareLength()) 
			> ((Vec3f(_System->getPosition(ParticleIndexRight)) - _CameraPos).squareLength());
	}
	return retFlag;
}

// function used for qsort comparisons
int qSortComp(const void * a, const void * b)
{
	int ret;
	// relative distances squared are compared
	if(ParticleSystemCore::TheSorter._SortByMinimum){
		ret = (Vec3f(ParticleSystemCore::TheSorter._System->getPosition(*(UInt32*)a) - ParticleSystemCore::TheSorter._CameraPos).squareLength()) 
			- ((Vec3f(ParticleSystemCore::TheSorter._System->getPosition(*(UInt32*)b)) - ParticleSystemCore::TheSorter._CameraPos).squareLength());

	} else
	{
		ret = Vec3f(ParticleSystemCore::TheSorter._System->getPosition(*(UInt32*)b) - ParticleSystemCore::TheSorter._CameraPos).squareLength() 
			- Vec3f(ParticleSystemCore::TheSorter._System->getPosition(*(UInt32*)a) - ParticleSystemCore::TheSorter._CameraPos).squareLength();
	}
	return ret;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemCore::ParticleSystemCore(void) :
    Inherited(),
    _SystemUpdateListener(ParticleSystemCoreRefPtr(this))
{
}

ParticleSystemCore::ParticleSystemCore(const ParticleSystemCore &source) :
    Inherited(source),
    _SystemUpdateListener(ParticleSystemCoreRefPtr(this))
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

    if(whichField & SystemFieldMask &&
       getSystem() != NULL)
    {
        getSystem()->addParticleSystemListener(&_SystemUpdateListener);
    }
    if(((whichField & SystemFieldMask) || (whichField & ParentsFieldMask))
       && _mfParents.size() > 0)
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

                //initialize _mfSort
                for(UInt32 i(0); i < getSystem()->getNumParticles(); ++i)
                {
                    editSort(i) = i;
                }
            }
        }
        else
        {
            if(getMFSort()->size() != 0)
            {
                editMFSort()->clear();
            }
        }
    }
}

void ParticleSystemCore::dump(      UInt32    ,
                                    const BitVector ) const
{
    SLOG << "Dump ParticleSystemCore NI" << std::endl;
}

void ParticleSystemCore::SystemUpdateListener::systemUpdated(const ParticleSystemEventUnrecPtr e)
{
    //Do nothing
}

void ParticleSystemCore::SystemUpdateListener::volumeChanged(const ParticleSystemEventUnrecPtr e)
{
    for(UInt32 i = 0; i < _Core->getParents().size(); i++)
    {
        _Core->getParents()[i]->invalidateVolume();
    }
}

void ParticleSystemCore::SystemUpdateListener::particleGenerated(const ParticleEventUnrecPtr e)
{
    _Core->handleParticleGenerated(e);
}

void ParticleSystemCore::SystemUpdateListener::particleKilled(const ParticleEventUnrecPtr e)
{
    _Core->handleParticleKilled(e);
}

void ParticleSystemCore::SystemUpdateListener::particleStolen(const ParticleEventUnrecPtr e)
{
    _Core->handleParticleStolen(e);
}


void ParticleSystemCore::handleParticleGenerated(const ParticleEventUnrecPtr e)
{
    //add particle to _mfSort
    if(getSortingMode() != NONE) editMFSort()->push_back(getMFSort()->size());
}

void ParticleSystemCore::handleParticleKilled(const ParticleEventUnrecPtr e)
{
    // remove highest indexed particle from _mfSort
    for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
    {
        if((*theItor) == _mfSort.size() - 1 ) 
        {
            _mfSort.erase(theItor);
            break;
        }
    }
}

void ParticleSystemCore::handleParticleStolen(const ParticleEventUnrecPtr e)
{
    // remove particle from _mfSort
    for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
    {
        if((int)*theItor == _mfSort.size() - 1 ) 
        {
            _mfSort.erase(theItor);
            break;
        }
    }
}

OSG_END_NAMESPACE
