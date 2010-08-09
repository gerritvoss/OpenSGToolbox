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

#ifndef _OSGNODEPARTICLESYSTEMCORE_H_
#define _OSGNODEPARTICLESYSTEMCORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNodeParticleSystemCoreBase.h"
#include "OSGParticleSystemEventDetailsFields.h"
#include "OSGParticleEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief NodeParticleSystemCore class. See \ref
           PageContribParticleSystemNodeParticleSystemCore for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING NodeParticleSystemCore : public NodeParticleSystemCoreBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum NormalSource 
    {
        NORMAL_POSITION_CHANGE = 0,
        NORMAL_VELOCITY_CHANGE = 1,
        NORMAL_VELOCITY        = 2,
        NORMAL_ACCELERATION    = 3,
        NORMAL_PARTICLE_NORMAL = 4,
        NORMAL_VIEW_DIRECTION  = 5,
        NORMAL_VIEW_POSITION   = 6,
        NORMAL_STATIC          = 7
    };

    enum UpSource
    {
        UP_POSITION_CHANGE = 0,
        UP_VELOCITY_CHANGE = 1,
        UP_VELOCITY        = 2,
        UP_ACCELERATION    = 3,
        UP_PARTICLE_NORMAL = 4,
        UP_VIEW_DIRECTION  = 5,
        UP_STATIC          = 6
    };

    typedef NodeParticleSystemCoreBase Inherited;
    typedef NodeParticleSystemCore     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    Vec3f getNodeNormal(ParticleSystemRefPtr System, UInt32 Index);
    Vec3f getNodeUpDir(ParticleSystemRefPtr System, UInt32 Index);

	void handleVolumeChanged(ParticleSystemEventDetails* const details);
	void handleParticleGenerated(ParticleEventDetails* const details);
	void handleParticleKilled(ParticleEventDetails* const details);
	void handleParticleStolen(ParticleEventDetails* const details);
    
    boost::signals2::connection _VolumeChangedConnection;
    boost::signals2::connection _ParticleGeneratedConnection;
    boost::signals2::connection _ParticleKilledConnection;
    boost::signals2::connection _ParticleStolenConnection;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class NodeParticleSystemCoreBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const NodeParticleSystemCore &source);
};

typedef NodeParticleSystemCore *NodeParticleSystemCoreP;

OSG_END_NAMESPACE

#include "OSGParticleSystem.h"
#include "OSGNode.h"

#include "OSGNodeParticleSystemCoreBase.inl"
#include "OSGNodeParticleSystemCore.inl"

#endif /* _OSGNODEPARTICLESYSTEMCORE_H_ */
