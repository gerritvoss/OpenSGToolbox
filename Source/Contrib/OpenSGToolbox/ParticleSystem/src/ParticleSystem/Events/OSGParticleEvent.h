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

#ifndef _OSGPARTICLEEVENT_H_
#define _OSGPARTICLEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGParticleEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleEvent class. See \ref 
           PageParticleSystemParticleEvent for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleEvent : public ParticleEventBase
{
  private:

    typedef ParticleEventBase Inherited;

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
    static ParticleEventPtr create( FieldContainerPtr Source,
                                             Time TimeStamp,
                                             Int32 Index,
                                             const Pnt3f& Position,
                                             const Pnt3f& SecPosition,
                                             const Vec3f& Normal,
                                             const Color4f& Color,
                                             const Vec3f& Size,
                                             Real32 Lifespan,
                                             Real32 Age,
                                             const Vec3f& Velocity,
                                             const Vec3f& SecVelocity,
                                             const Vec3f& Acceleration,
                                             const StringToUInt32Map& Attributes);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleEvent(void);
    ParticleEvent(const ParticleEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticleEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleEvent &source);
};

typedef ParticleEvent *ParticleEventP;

OSG_END_NAMESPACE

#include "OSGParticleEventBase.inl"
#include "OSGParticleEvent.inl"

#endif /* _OSGPARTICLEEVENT_H_ */
