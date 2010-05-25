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

#ifndef _OSGPARTICLESYSTEMCORE_H_
#define _OSGPARTICLESYSTEMCORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemCoreBase.h"
#include "OSGParticleSystemListener.h"
#include "OSGStatElemTypes.h"
#include "OSGLine.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemCore class. See \ref
           PageContribParticleSystemParticleSystemCore for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleSystemCore : public ParticleSystemCoreBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ParticleSortingMode
    {
        NONE          = 0,
        FRONT_TO_BACK = 1,
        BACK_TO_FRONT = 2
    };

    typedef ParticleSystemCoreBase Inherited;
    typedef ParticleSystemCore     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

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

    void     drawPrimitives(DrawEnv *pEnv);

    /*! \}*/

    Action::ResultE intersect           (Action         *action);

    void    adjustVolume(Volume & volume);

    virtual void fill(DrawableStatsAttachment *pStat);

    // used for sorting particles
    struct ParticleSortByViewPosition
    {
      public:

        const ParticleSystem* _System;
		Vec3f _CameraPos;
        bool _SortByMinimum;
        ParticleSortByViewPosition(const ParticleSystem* TheSystem, Pnt3f TheCameraPos, bool SortByMinimum);
        ParticleSortByViewPosition();
        bool operator()(UInt32 ParticleIndexLeft, UInt32 ParticleIndexRight);
    };
    static ParticleSortByViewPosition TheSorter;

    static StatElemDesc<StatTimeElem    > statParticleSortTime;

    std::vector<UInt32> intersectLine(const Line& Ray, Real32 IntersectionDistance) const;
	
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
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    class SystemUpdateListener : public ParticleSystemListener
    {
      public:
        SystemUpdateListener(ParticleSystemCoreRefPtr TheCore);
        virtual void systemUpdated(const ParticleSystemEventUnrecPtr e);
        virtual void volumeChanged(const ParticleSystemEventUnrecPtr e);
        virtual void particleGenerated(const ParticleEventUnrecPtr e);
        virtual void particleKilled(const ParticleEventUnrecPtr e);
        virtual void particleStolen(const ParticleEventUnrecPtr e);
        // used for sorting particles 

      private:
        ParticleSystemCoreRefPtr _Core;
    };


	SystemUpdateListener _SystemUpdateListener;
	
    void sortParticles(DrawEnv *pEnv);
	void checkAndInitializeSort(void);
	void handleParticleGenerated(const ParticleEventUnrecPtr e);
	void handleParticleKilled(const ParticleEventUnrecPtr e);
	void handleParticleStolen(const ParticleEventUnrecPtr e);
	
	UInt32 comparisons;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemCoreBase;
	friend struct ParticleSortByViewPosition;
	friend class SystemUpdateListener;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemCore &source);
};

int qSortComp(const void * a, const void * b);

typedef ParticleSystemCore *ParticleSystemCoreP;

OSG_END_NAMESPACE

#include "OSGParticleSystemDrawer.h"
#include "OSGParticleSystem.h"

#include "OSGParticleSystemCoreBase.inl"
#include "OSGParticleSystemCore.inl"

#endif /* _OSGPARTICLESYSTEMCORE_H_ */
