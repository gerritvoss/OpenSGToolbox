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

#ifndef _OSGPARTICLESYSTEMEVENTDETAILS_H_
#define _OSGPARTICLESYSTEMEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemEventDetails class. See \ref
           PageContribParticleSystemParticleSystemEventDetails for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleSystemEventDetails : public ParticleSystemEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleSystemEventDetailsBase Inherited;
    typedef ParticleSystemEventDetails     Self;

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
    static ParticleSystemEventDetailsTransitPtr create(  FieldContainer* const Source,
                                                  Time TimeStamp); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemEventDetails(void);
    ParticleSystemEventDetails(const ParticleSystemEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemEventDetails &source);
};

typedef ParticleSystemEventDetails *ParticleSystemEventDetailsP;

OSG_END_NAMESPACE

#include "OSGParticleSystemEventDetailsBase.inl"
#include "OSGParticleSystemEventDetails.inl"

#endif /* _OSGPARTICLESYSTEMEVENTDETAILS_H_ */
