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

#ifndef _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_
#define _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGCollectiveGravityParticleSystemAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollectiveGravityParticleSystemAffector class. See \ref 
           PageParticleSystemCollectiveGravityParticleSystemAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING CollectiveGravityParticleSystemAffector : public CollectiveGravityParticleSystemAffectorBase
{
  private:

    typedef CollectiveGravityParticleSystemAffectorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum MassSource {MASS_STATIC=0, MASS_SIZE_X=1, MASS_SIZE_Y=2, MASS_SIZE_Z=3};

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CollectiveGravityParticleSystemAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollectiveGravityParticleSystemAffector(void);
    CollectiveGravityParticleSystemAffector(const CollectiveGravityParticleSystemAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollectiveGravityParticleSystemAffector(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CollectiveGravityParticleSystemAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CollectiveGravityParticleSystemAffector &source);
};

typedef CollectiveGravityParticleSystemAffector *CollectiveGravityParticleSystemAffectorP;

OSG_END_NAMESPACE

#include "OSGCollectiveGravityParticleSystemAffectorBase.inl"
#include "OSGCollectiveGravityParticleSystemAffector.inl"

#define OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_ */
