/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
#include <vector>

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGQuaternion.h>

#include "OSGParticleSystemCore.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleSystemCore

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemCore::initMethod (void)
{
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, ParticleSystemCorePtr,
              CNodePtr, Action *>(&ParticleSystemCore::drawActionHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, ParticleSystemCorePtr,
              CNodePtr, Action *>(&ParticleSystemCore::intersect));

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, ParticleSystemCorePtr,
              CNodePtr, Action *>(&ParticleSystemCore::renderActionHandler));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE ParticleSystemCore::drawPrimitives (DrawActionBase *action)
{
    //If I have a Drawer tell it to draw the particles
    if(getDrawer() != NullFC && getSystem() != NullFC)
    {
		sortParticles(action);

		TimeStamp theTime = getTimeStamp();

		getDrawer()->draw(action, getSystem(), getSort() );
		theTime = getTimeStamp() - theTime;
		std::cout << "Draw Time = " <<  getTimeStampMsecs(theTime) << std::endl; // ticks converted to milliseconds
      
    }
    else
    {
        if(getDrawer() == NullFC)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystemDrawer is Null."));
        }
        if(getSystem() == NullFC)
        {
            FWARNING(("ParticleSystemCore::draw: ParticleSystem is Null."));
        }
    }

    return Action::Continue;
}

Action::ResultE ParticleSystemCore::drawActionHandler( Action* action )
{
    DrawAction *a = dynamic_cast<DrawAction*>(action);
    Material::DrawFunctor func;

    func=osgTypedMethodFunctor1ObjPtr(&(*this), 
                                      &ParticleSystemCore::drawPrimitives);

    if(a->getMaterial() != NULL)
    {
        a->getMaterial()->draw(func, a);
    }
    else if ( getMaterial() != NullFC )
    {
        getMaterial()->draw( func, a );
    }
    else
    {
        getDefaultMaterial()->draw( func, a );
        FWARNING(("MaterialDrawable::draw:: no material!\n"));;
    }
    return Action::Continue;
}

Action::ResultE ParticleSystemCore::renderActionHandler( Action* action )
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;
    func = osgTypedMethodFunctor1ObjPtr(this, 
                                        &ParticleSystemCore::drawPrimitives);

    Material* m = a->getMaterial();

    if(m == NULL)
    {
        if(getMaterial() != NullFC)
        {
            m = getMaterial().getCPtr();
        }
        else
        {
            m = getDefaultMaterial().getCPtr();
            FNOTICE(("MaterialDrawable::render: no Material!?!\n"));
        }
    }

    a->dropFunctor(func, m);

    return Action::Continue;
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

    if(getDrawer() != NullFC && getSystem() != NullFC)
    {
        getDrawer()->adjustVolume(getSystem(), volume);
    }
}

void ParticleSystemCore::sortParticles(DrawActionBase *action)
{
    //This should be called if the ParticleSystem has
    //just finished an update
	
	//initialize _mfSort
	static bool firstCall = true;
	if(firstCall){
		//add each particle from the particle system to _mfSort the first time through
		firstCall = false;
		ParticleSystemPtr sys = getSystem();
		for(UInt32 i(0); i < sys->getNumParticles(); ++i)
		{
			_mfSort.push_back(i);
		}
	}

	//extract camera position
	Pnt3f CameraLocation(0.0,0.0,0.0);
	action->getCameraToWorld().mult(CameraLocation);
	
    if(getSystem() != NullFC && getSortingMode() != NONE)
    {
		// initialize sort funcion struct
		ParticleSortByViewPosition TheSortFunction = ParticleSortByViewPosition(getSystem(),CameraLocation,true);
        // get sorting order
		switch(getSortingMode())
        {
			case FRONT_TO_BACK:
				//Use the FrontToBack Comparitor, already initialized above
				break;

			case BACK_TO_FRONT:
				//Use the BackToFront Comparitor, changes sorting order
				TheSortFunction = ParticleSortByViewPosition(getSystem(),CameraLocation,false);
				break;
        }
		
		// mfSort is sorted, keep track of sort time
		TimeStamp theTime = getTimeStamp();
		TheSortFunction._numComparisons = 0;
		std::sort(_mfSort.begin(),_mfSort.end(),TheSortFunction);
		theTime = getTimeStamp() - theTime;

		std::cout << "Sort Time = " <<  getTimeStampMsecs(theTime); // ticks converted to milliseconds
		UInt32 comps = TheSortFunction._numComparisons;
		std::cout << ", Num. Sorted = " << _mfSort.size() << ", Num Comps = " << comps;
		std::cout << ", Comps/Particle = " << comps/_mfSort.size() << std::endl;
    }
}
UInt32 ParticleSystemCore::ParticleSortByViewPosition::_numComparisons=0;

ParticleSystemCore::ParticleSortByViewPosition::ParticleSortByViewPosition(ParticleSystemPtr TheSystem, Pnt3f TheCameraPos, bool SortByMinimum) 
	: _System(TheSystem), _CameraPos(TheCameraPos), _SortByMinimum(SortByMinimum)
{
}


bool ParticleSystemCore::ParticleSortByViewPosition::operator()(UInt32 ParticleIndexLeft, UInt32 ParticleIndexRight)
{
	
	bool retFlag;
	if(_SortByMinimum){
		retFlag = ((Vec3f(_System->getPosition(ParticleIndexLeft)) - _CameraPos).squareLength()) 
			< ((Vec3f(_System->getPosition(ParticleIndexRight)) - _CameraPos).squareLength());

	} else
	{
		retFlag = ((Vec3f(_System->getPosition(ParticleIndexLeft)) - _CameraPos).squareLength()) 
			> ((Vec3f(_System->getPosition(ParticleIndexRight)) - _CameraPos).squareLength());
	}
	++_numComparisons;
	return retFlag;

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemCore::ParticleSystemCore(void) :
    Inherited(),
    _SystemUpdateListener(ParticleSystemCorePtr(this))
{
}

ParticleSystemCore::ParticleSystemCore(const ParticleSystemCore &source) :
    Inherited(source),
    _SystemUpdateListener(ParticleSystemCorePtr(this))
{
}

ParticleSystemCore::~ParticleSystemCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemCore::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & SystemFieldMask &&
        getSystem() != NullFC)
    {
        getSystem()->addParticleSystemListener(&_SystemUpdateListener);
    }

    if(whichField & SystemFieldMask ||
       whichField & DrawerFieldMask)
    {
         for(UInt32 i = 0; i < getParents().size(); i++)
         {
             getParents()[i]->invalidateVolume();
         }
    }
}

void ParticleSystemCore::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemCore NI" << std::endl;
}

void ParticleSystemCore::SystemUpdateListener::systemUpdated(const ParticleSystemEvent& e)
{
    if(e.getVolumeChanged())
    {
         for(UInt32 i = 0; i < _Core->getParents().size(); i++)
         {
             _Core->getParents()[i]->invalidateVolume();
         }
    }
}

void ParticleSystemCore::SystemUpdateListener::particleGenerated(const ParticleEvent& e)
{
	_Core->handleParticleGenerated(e);
}

void ParticleSystemCore::SystemUpdateListener::particleKilled(const ParticleEvent& e)
{
	_Core->handleParticleKilled(e);
}

void ParticleSystemCore::SystemUpdateListener::particleStolen(const ParticleEvent& e)
{
	_Core->handleParticleStolen(e);
}

// TODO: make these more efficient
void ParticleSystemCore::handleParticleGenerated(const ParticleEvent& e)
{
	//add particle to _mfSort
	_mfSort.addValue(e.getIndex());
}

void ParticleSystemCore::handleParticleKilled(const ParticleEvent& e)
{
	// remove highest indexed particle from _mfSort
	for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
	{
		if((int)*theItor == _mfSort.size() - 1 ) 
		{
			_mfSort.erase(theItor);
			break;
		}
	}	
}

void ParticleSystemCore::handleParticleStolen(const ParticleEvent& e)
{
	// remove particle from _mfSort (is this right? stolen particles are just removed from the system?)
	for(MFUInt32::iterator theItor = _mfSort.begin(); theItor != _mfSort.end(); ++theItor)
	{
		if((int)*theItor == _mfSort.size() - 1 ) 
		{
			_mfSort.erase(theItor);
		}
	}
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
    static Char8 cvsid_hpp       [] = OSGPARTICLESYSTEMCOREBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLESYSTEMCOREBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLESYSTEMCOREFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

