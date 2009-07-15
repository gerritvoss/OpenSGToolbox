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

#ifndef _OSGPARTICLESYSTEMCORE_H_
#define _OSGPARTICLESYSTEMCORE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGParticleSystemCoreBase.h"
#include "ParticleSystem/Events/OSGParticleSystemListener.h"
#include <OpenSG/OSGStatElemTypes.h>

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemCore class. See \ref 
           PageParticleSystemParticleSystemCore for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleSystemCore : public ParticleSystemCoreBase
{
  private:

    typedef ParticleSystemCoreBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum ParticleSortingMode {NONE=0, FRONT_TO_BACK, BACK_TO_FRONT};

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    Action::ResultE drawPrimitives (DrawActionBase *action);
    Action::ResultE drawActionHandler( Action* action );
    Action::ResultE renderActionHandler( Action* action );
    Action::ResultE intersect( Action* action );

    /*! \}*/

	// used for sorting particles
	struct ParticleSortByViewPosition
	{
	public:
		
		ParticleSystemPtr _System;
		Pnt3f _CameraPos;
		bool _SortByMinimum;
		ParticleSortByViewPosition(ParticleSystemPtr TheSystem, Pnt3f TheCameraPos, bool SortByMinimum);
		ParticleSortByViewPosition();
		bool operator()(UInt32 ParticleIndexLeft, UInt32 ParticleIndexRight);
	};
	static ParticleSortByViewPosition TheSorter;

    static StatElemDesc<StatTimeElem    > statParticleSortTime;
	
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleSystemCoreBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemCore(void);
    ParticleSystemCore(const ParticleSystemCore &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemCore(void); 

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                NodeCore Specific                             */
    /*! \{                                                                 */

    void    adjustVolume(Volume & volume);

	class SystemUpdateListener : public ParticleSystemListener
	{
	public:
		SystemUpdateListener(ParticleSystemCorePtr TheCore);
       virtual void systemUpdated(const ParticleSystemEvent& e);
       virtual void particleGenerated(const ParticleEvent& e);
       virtual void particleKilled(const ParticleEvent& e);
       virtual void particleStolen(const ParticleEvent& e);
	   	// used for sorting particles 

	private:
		ParticleSystemCorePtr _Core;
	};

	friend class SystemUpdateListener;

	SystemUpdateListener _SystemUpdateListener;
	
    void sortParticles(DrawActionBase *action);
	void checkAndInitializeSort(void);
	void handleParticleGenerated(const ParticleEvent& e);
	void handleParticleKilled(const ParticleEvent& e);
	void handleParticleStolen(const ParticleEvent& e);
	
	UInt32 comparisons;
	



	friend struct ParticleSortByViewPosition;


    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticleSystemCoreBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleSystemCore &source);
	
};

// fwd declaration, this function is used for qsort in sortParticles(DrawActionBase *action)
int qSortComp(const void * a, const void * b);


typedef ParticleSystemCore *ParticleSystemCoreP;

OSG_END_NAMESPACE

#include "OSGParticleSystemCoreBase.inl"
#include "OSGParticleSystemCore.inl"

#define OSGPARTICLESYSTEMCORE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPARTICLESYSTEMCORE_H_ */
