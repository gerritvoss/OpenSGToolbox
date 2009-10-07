/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGNODEPARTICLESYSTEMCORE_H_
#define _OSGNODEPARTICLESYSTEMCORE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGNodeParticleSystemCoreBase.h"
#include "ParticleSystem/Events/OSGParticleSystemListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief NodeParticleSystemCore class. See \ref 
           PageParticleSystemNodeParticleSystemCore for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING NodeParticleSystemCore : public NodeParticleSystemCoreBase
{
  private:

    typedef NodeParticleSystemCoreBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum NormalSource {NORMAL_POSITION_CHANGE, NORMAL_VELOCITY_CHANGE, NORMAL_VELOCITY, NORMAL_ACCELERATION, NORMAL_PARTICLE_NORMAL, NORMAL_VIEW_DIRECTION, NORMAL_VIEW_POSITION, NORMAL_STATIC};
      enum UpSource {UP_POSITION_CHANGE, UP_VELOCITY_CHANGE, UP_VELOCITY, UP_ACCELERATION, UP_PARTICLE_NORMAL, UP_VIEW_DIRECTION, UP_STATIC};

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
	void updateNodes(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in NodeParticleSystemCoreBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    NodeParticleSystemCore(void);
    NodeParticleSystemCore(const NodeParticleSystemCore &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~NodeParticleSystemCore(void); 

    /*! \}                                                                 */
    
	class SystemUpdateListener : public ParticleSystemListener
	{
	public:
		SystemUpdateListener(NodeParticleSystemCorePtr TheCore);
       virtual void systemUpdated(const ParticleSystemEventPtr e);
       virtual void particleGenerated(const ParticleEventPtr e);
       virtual void particleKilled(const ParticleEventPtr e);
       virtual void particleStolen(const ParticleEventPtr e);
	private:
		NodeParticleSystemCorePtr _Core;
	};

	friend class SystemUpdateListener;

	SystemUpdateListener _SystemUpdateListener;

	Vec3f getNodeNormal(ParticleSystemPtr System, UInt32 Index);
	Vec3f getNodeUpDir(ParticleSystemPtr System, UInt32 Index);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class NodeParticleSystemCoreBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const NodeParticleSystemCore &source);
};

typedef NodeParticleSystemCore *NodeParticleSystemCoreP;

OSG_END_NAMESPACE

#include "OSGNodeParticleSystemCoreBase.inl"
#include "OSGNodeParticleSystemCore.inl"

#define OSGNODEPARTICLESYSTEMCORE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGNODEPARTICLESYSTEMCORE_H_ */
