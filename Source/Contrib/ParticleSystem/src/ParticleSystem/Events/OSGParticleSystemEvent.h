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

#ifndef _OSGPARTICLESYSTEMEVENT_H_
#define _OSGPARTICLESYSTEMEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemEvent class. See \ref
           PageContribParticleSystemParticleSystemEvent for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleSystemEvent : public ParticleSystemEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleSystemEventBase Inherited;
    typedef ParticleSystemEvent     Self;

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
    static ParticleSystemEventTransitPtr create(  FieldContainerRefPtr Source,
                                                  Time TimeStamp); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemEvent(void);
    ParticleSystemEvent(const ParticleSystemEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemEvent &source);
};

typedef ParticleSystemEvent *ParticleSystemEventP;

OSG_END_NAMESPACE

#include "OSGParticleSystemEventBase.inl"
#include "OSGParticleSystemEvent.inl"

#endif /* _OSGPARTICLESYSTEMEVENT_H_ */
