/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_
#define _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include <set>
#include "ParticleSystem/Events/OSGParticleCollisionListener.h"

#include "OSGCollisionParticleSystemAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollisionParticleSystemAffector class. See \ref 
           PageParticleSystemCollisionParticleSystemAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING CollisionParticleSystemAffector : public CollisionParticleSystemAffectorBase
{
  private:

    typedef CollisionParticleSystemAffectorBase Inherited;

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
    virtual void affect(ParticleSystemPtr System, const Time& elps);
    EventConnection addParticleCollisionListener(ParticleCollisionListenerPtr Listener);
    bool isParticleCollisionListenerAttached(ParticleCollisionListenerPtr Listener) const;
    void removeParticleCollisionListener(ParticleCollisionListenerPtr Listener);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CollisionParticleSystemAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionParticleSystemAffector(void);
    CollisionParticleSystemAffector(const CollisionParticleSystemAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionParticleSystemAffector(void); 

    /*! \}                                                                 */
	typedef std::set<ParticleCollisionListenerPtr> ParticleCollisionListenerSet;
    typedef ParticleCollisionListenerSet::iterator ParticleCollisionListenerSetItor;

    ParticleCollisionListenerSet       _ParticleCollisionListeners;

    void produceCollision(const ParticleCollisionEventPtr Event);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CollisionParticleSystemAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CollisionParticleSystemAffector &source);
};

typedef CollisionParticleSystemAffector *CollisionParticleSystemAffectorP;

OSG_END_NAMESPACE

#include "OSGCollisionParticleSystemAffectorBase.inl"
#include "OSGCollisionParticleSystemAffector.inl"

#endif /* _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_ */
