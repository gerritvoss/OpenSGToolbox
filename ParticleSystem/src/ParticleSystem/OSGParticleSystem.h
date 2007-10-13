/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGPARTICLESYSTEM_H_
#define _OSGPARTICLESYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGParticleSystemBase.h"
#include <OpenSG/Input/OSGUpdateListener.h>

#include <set>
#include "ParticleSystem/Events/OSGParticleSystemListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystem class. See \ref 
           PageParticleSystemParticleSystem for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleSystem : public ParticleSystemBase
{
  private:

    typedef ParticleSystemBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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
    
    void addParticleSystemListener(ParticleSystemListenerPtr Listener);
    void removeParticleSystemListener(ParticleSystemListenerPtr Listener);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleSystemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystem(void);
    ParticleSystem(const ParticleSystem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystem(void); 

    /*! \}                                                                 */
    
	typedef std::set<ParticleSystemListenerPtr> ParticleSystemListenerSet;
    typedef ParticleSystemListenerSet::iterator ParticleSystemListenerSetItor;

    ParticleSystemListenerSet       _ParticleSystemListeners;

    void produceSystemUpdated(void);
    void produceParticleGenerated(void);
    void produceParticleKilled(void);
    void produceParticleStolen(void);

	class SystemUpdateListener : public UpdateListener
	{
	public:
		SystemUpdateListener(ParticleSystem* TheSystem);
        virtual void update(const UpdateEvent& e);
	private:
		ParticleSystem* _System;
	};

	friend class SystemUpdateListener;

	SystemUpdateListener _SystemUpdateListener;
    
    void update(const Time& elps);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticleSystemBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleSystem &source);
};

typedef ParticleSystem *ParticleSystemP;

OSG_END_NAMESPACE

#include "OSGParticleSystemBase.inl"
#include "OSGParticleSystem.inl"

#define OSGPARTICLESYSTEM_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPARTICLESYSTEM_H_ */
