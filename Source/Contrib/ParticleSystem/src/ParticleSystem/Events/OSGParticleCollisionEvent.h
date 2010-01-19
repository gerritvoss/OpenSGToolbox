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

#ifndef _OSGPARTICLECOLLISIONEVENT_H_
#define _OSGPARTICLECOLLISIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGParticleCollisionEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleCollisionEvent class. See \ref 
           PageParticleSystemParticleCollisionEvent for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleCollisionEvent : public ParticleCollisionEventBase
{
  private:

    typedef ParticleCollisionEventBase Inherited;

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
    static ParticleCollisionEventPtr create(  FieldContainerPtr Source,
                                            Time TimeStamp,
                                            ParticleSystemPtr PrimarySystem,
                                            UInt32 PrimaryIndex,
                                            ParticleSystemPtr SecondarySystem,
                                            UInt32 SecondaryIndex); 
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleCollisionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleCollisionEvent(void);
    ParticleCollisionEvent(const ParticleCollisionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleCollisionEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticleCollisionEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleCollisionEvent &source);
};

typedef ParticleCollisionEvent *ParticleCollisionEventP;

OSG_END_NAMESPACE

#include "OSGParticleCollisionEventBase.inl"
#include "OSGParticleCollisionEvent.inl"

#endif /* _OSGPARTICLECOLLISIONEVENT_H_ */
