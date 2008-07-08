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

#ifndef _OSGDISTANCEATTRACTREPELPARTICLEAFFECTOR_H_
#define _OSGDISTANCEATTRACTREPELPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDistanceAttractRepelParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DistanceAttractRepelParticleAffector class. See \ref 
           PageParticleSystemDistanceAttractRepelParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING DistanceAttractRepelParticleAffector : public DistanceAttractRepelParticleAffectorBase
{
  private:

    typedef DistanceAttractRepelParticleAffectorBase Inherited;

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

    // Variables should all be in DistanceAttractRepelParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DistanceAttractRepelParticleAffector(void);
    DistanceAttractRepelParticleAffector(const DistanceAttractRepelParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistanceAttractRepelParticleAffector(void); 

    /*! \}                                                                 */
    virtual bool affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DistanceAttractRepelParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DistanceAttractRepelParticleAffector &source);
};

typedef DistanceAttractRepelParticleAffector *DistanceAttractRepelParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGDistanceAttractRepelParticleAffectorBase.inl"
#include "OSGDistanceAttractRepelParticleAffector.inl"

#define OSGDISTANCEATTRACTREPELPARTICLEAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDISTANCEATTRACTREPELPARTICLEAFFECTOR_H_ */
