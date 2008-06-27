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

#ifndef _OSGDISTANCEPARTICLEAFFECTOR_H_
#define _OSGDISTANCEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDistanceParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DistanceParticleAffector class. See \ref 
           PageParticleSystemDistanceParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING DistanceParticleAffector : public DistanceParticleAffectorBase
{
  private:

    typedef DistanceParticleAffectorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  enum DistanceSource {DISTANCE_FROM_CAMERA=0, DISTANCE_FROM_NODE};

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
    virtual bool affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DistanceParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DistanceParticleAffector(void);
    DistanceParticleAffector(const DistanceParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistanceParticleAffector(void); 

    /*! \}                                                                 */
    virtual bool affect(ParticleSystemPtr System, Int32 ParticleIndex, const Time& elps, const Real32& Distance) = 0;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DistanceParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DistanceParticleAffector &source);
};

typedef DistanceParticleAffector *DistanceParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGDistanceParticleAffectorBase.inl"
#include "OSGDistanceParticleAffector.inl"

#define OSGDISTANCEPARTICLEAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDISTANCEPARTICLEAFFECTOR_H_ */
