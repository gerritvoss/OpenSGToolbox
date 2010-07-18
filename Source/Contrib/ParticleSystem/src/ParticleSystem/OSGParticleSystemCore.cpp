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

void ParticleSystemCore::drawPrimitives (DrawEnv *pEnv)
{
    //If I have a Drawer tell it to draw the particles
    if(getDrawer() != NULL && getSystem() != NULL)
    {
        //Sorting particles
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
}

std::vector<UInt32> ParticleSystemCore::intersectLine(const Line& Ray, Real32 IntersectionDistance) const
{
    return getSystem()->intersect(Ray,IntersectionDistance,-1, getParents().front());
}

void ParticleSystemCore::checkAndInitializeSort(void)
{

	if(getMFSort()->size() != getSystem()->getNumParticles() && getSortingMode() != NONE)
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

	UInt32 numParticles = getSystem()->getNumParticles();
	if(getSystem() != NULL && getSortingMode() != NONE && getMFSort()->size() > 0)
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
		doRadixSort();	
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ParticleSystemCore::doRadixSort()
{
	if(getMFHistogram()->size() == 0)
	{ // only initialize histograms if needed. should happen once only
		editMFHistogram()->resize(256*4);
		editMFOffset()->resize(256);
	}

	UInt32* input = (UInt32*)&editDistances(0);
	UInt32 numParticles = getSystem()->getNumParticles();
	// Resize lists if needed
	if(numParticles != getPreviousSize())							
	{ 											
		if(getPreviousSize() < numParticles) 
		{ // only expand if needed
			editMFSort()->resize(numParticles);
			editMFSort2()->resize(numParticles);
		}
		else 
		{	// reset indices
			for(UInt32 i=0;i < numParticles;i++)	
            {
				editSort(i) = i;
            }
		}
		setPreviousSize(numParticles);							
	}

	
	// Clear counters 			
	memset(&editHistogram(0), 0,256*4*sizeof(UInt32));	
													
	// Prepare for temporal coherence 		
	Real32 PrevVal = getDistances(getSort(0));		
	bool AlreadySorted = true;	// Optimism... 
	UInt32* Indices = &editSort(0);
													
	/* Prepare to count */							
	UChar8* p = (UChar8*)input;						
	UChar8* pe = &p[numParticles*4];							
	UInt32* h0= &editHistogram(0);	/* Histogram for first pass (LSB)*/		
	UInt32* h1= &editHistogram(256);	/* Histogram for second pass*/		
	UInt32* h2= &editHistogram(512);	/* Histogram for third pass*/		
	UInt32* h3= &editHistogram(768);	/* Histogram for last pass (MSB)*/	
																		
	while(p!=pe)														
	{																	
		// Read input buffer in previous sorted order 				
		Real32 Val = getDistances(*Indices++);							
		// Check whether already sorted or not x					
		if(Val<PrevVal)	 // Early out
		{ 
			AlreadySorted = false; 
			break; 
		} 
		// Update for next iteration 			
		PrevVal = Val;									
														
		// Create histograms 					
		h0[*p++]++;	
		h1[*p++]++;	
		h2[*p++]++; 
		h3[*p++]++;	
	}													
														
	/* If all input values are already sorted, we just have to return and leave the 
	 * previous list unchanged. That way the routine may take advantage of temporal 	
	 * coherence, for example when used to sort transparent faces.
	 */					
	if(AlreadySorted) return;										
																						
	// Else there has been an early out and we must finish computing the histograms 
	while(p!=pe)												
	{															
		// Continue to create histograms from where we left off	
		h0[*p++]++;	
		h1[*p++]++;	
		h2[*p++]++;	
		h3[*p++]++;			
	}

	
	// Compute #negative values involved if needed
	UInt32 NbNegativeValues = 0;
	// An efficient way to compute the number of negatives values we'll have to deal with is simply to sum the 128
	// last values of the last histogram. Last histogram because that's the one for the Most Significant Byte,
	// responsible for the sign. 128 last values because the 128 first ones are related to positive numbers.
	h3= &editHistogram(768);
	for(UInt32 i=128;i<256;i++)	NbNegativeValues += h3[i];	// 768 for last histogram, 128 for negative part

	// we index from these alternating arrays each pass, and they must be swapped each time. To avoid
	// having to copy all of the elements each pass, we just use pointers to handle this
	UInt32 * sortPtr = &editSort(0);
	UInt32 * sort2Ptr = &editSort2(0);

	// Radix sort, j is the pass number (0=LSB, 3=MSB)
	for(UInt32 j=0;j<4;j++)
	{
		// Should we care about negative values?
		if(j!=3)
		{
			// Here we deal with positive values only
			// Shortcut to current counters 						
			UInt32* CurCount = &editHistogram(j<<8);					
																		
			// Reset flag. The sorting pass is supposed to be performed. (default)
			bool PerformPass = true;					
																						
			// Get first byte 								
			UChar8 UniqueVal = *(((UChar8*)input)+j);			
																	
			// Check that byte's counter 	
			if(CurCount[UniqueVal]==numParticles)	
				PerformPass=false;	

			if(PerformPass)
			{
				// Create offsets
				editOffset(0) = 0;
				for(UInt32 i=1;i<256;i++) 
                {
					editOffset(i) = getOffset(i-1) + CurCount[i-1];
                }

				// Perform Radix Sort
				UChar8* InputBytes = (UChar8*)input;
				UInt32* Indices	= sortPtr;
				UInt32* IndicesEnd = &sortPtr[numParticles];
				InputBytes += j;
				while(Indices!=IndicesEnd)
				{
					UInt32 id = *Indices++;
					sort2Ptr[editOffset(InputBytes[id<<2])++] = id;
				}

				// Swap pointers for next pass. Valid indices - the most recent ones - are in sortPtr after the swap.
				UInt32* Tmp = sortPtr;	
				sortPtr = sort2Ptr; 
				sort2Ptr = Tmp;
			}
		}
		else
		{
			// This is a special case to correctly handle negative values
			/* Shortcut to current counters */						
			UInt32* CurCount = &editHistogram(j<<8);				
																						
			/* Get first byte */									
			UChar8 UniqueVal = *(((UChar8*)input)+j);			
																
			if(!(CurCount[UniqueVal]==numParticles))
			{
				// Create biased offsets, in order for negative numbers to be sorted as well
				editOffset(0) = NbNegativeValues; // First positive number takes place after the negative ones
				for(UInt32 i=1;i<128;i++)	editOffset(i) = getOffset(i-1) + CurCount[i-1];	// 1 to 128 for positive numbers

				// We must reverse the sorting order for negative numbers!
				editOffset(255) = 0;
				for(UInt32 i=0;i<127;i++) 
					editOffset(254-i) = getOffset(255-i) + CurCount[255-i]; // Fixing the wrong order for negative values
				for(UInt32 i=128;i<256;i++) 
					editOffset(i) += CurCount[i];	// Fixing the wrong place for negative values

				// Perform Radix Sort
				for(UInt32 i=0;i<numParticles;i++)
				{
					UInt32 Radix = input[sortPtr[i]]>>24;	// Radix byte, same as above. AND is useless here (UInt32).
					if(Radix<128) 
						sort2Ptr[editOffset(Radix)++] = sortPtr[i]; // Number is positive, same as above
					else 
						sort2Ptr[--editOffset(Radix)] = sortPtr[i]; // Number is negative, flip the sorting order
				}
				// Swap pointers for next pass. Valid indices - the most recent ones - are in sortPtr after the swap.
				UInt32* Tmp = sortPtr;	
				sortPtr = sort2Ptr; 
				sort2Ptr = Tmp;
			}
			else
			{
				// The pass is useless, yet we still have to reverse the order of current list if all values are negative.
				if(UniqueVal >= 128)
				{
					for(UInt32 i=0; i < numParticles; i++)	
						sort2Ptr[i] = sortPtr[numParticles-i-1];

					// Swap pointers for next pass. Valid indices - the most recent ones - are in sortPtr after the swap.
				UInt32* Tmp = sortPtr;	
				sortPtr = sort2Ptr; 
				sort2Ptr = Tmp;
				}
			}
		} //end if (j!=3)
	} // end for (j<4...)
}// end of doRadixSort()

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemCore::ParticleSystemCore(void) :
    Inherited(),
    _SystemUpdateListener(this)
{
}

ParticleSystemCore::ParticleSystemCore(const ParticleSystemCore &source) :
    Inherited(source),
    _SystemUpdateListener(this)
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
    if(getSortingMode() != NONE)
    {
        editMFSort()->push_back(getMFSort()->size());
		editMFDistances()->push_back(0.0f);
    }
}

void ParticleSystemCore::handleParticleKilled(const ParticleEventUnrecPtr e)
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

void ParticleSystemCore::handleParticleStolen(const ParticleEventUnrecPtr e)
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

OSG_END_NAMESPACE
