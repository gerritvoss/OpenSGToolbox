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

#ifndef _OSGDISTANCEFADEPARTICLEAFFECTOR_H_
#define _OSGDISTANCEFADEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGDistanceFadeParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DistanceFadeParticleAffector class. See \ref 
           PageParticleSystemDistanceFadeParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING DistanceFadeParticleAffector : public DistanceFadeParticleAffectorBase
{
  private:

    typedef DistanceFadeParticleAffectorBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DistanceFadeParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DistanceFadeParticleAffector(void);
    DistanceFadeParticleAffector(const DistanceFadeParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistanceFadeParticleAffector(void); 

    /*! \}                                                                 */
    virtual bool affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Real32& DistanceSqrd);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DistanceFadeParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DistanceFadeParticleAffector &source);
};

typedef DistanceFadeParticleAffector *DistanceFadeParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGDistanceFadeParticleAffectorBase.inl"
#include "OSGDistanceFadeParticleAffector.inl"

#define OSGDISTANCEFADEPARTICLEAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDISTANCEFADEPARTICLEAFFECTOR_H_ */
