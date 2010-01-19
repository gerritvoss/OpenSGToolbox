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

#ifndef _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTOR_H_
#define _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAttributeAttractRepelParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AttributeAttractRepelParticleAffector class. See \ref 
           PageParticleSystemAttributeAttractRepelParticleAffector for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING AttributeAttractRepelParticleAffector : public AttributeAttractRepelParticleAffectorBase
{
  private:

    typedef AttributeAttractRepelParticleAffectorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  enum ParticleAttributes{POSITION_ATTRIBUTE, VELOCITY_ATTRIBUTE};

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

    // Variables should all be in AttributeAttractRepelParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AttributeAttractRepelParticleAffector(void);
    AttributeAttractRepelParticleAffector(const AttributeAttractRepelParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AttributeAttractRepelParticleAffector(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AttributeAttractRepelParticleAffectorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AttributeAttractRepelParticleAffector &source);
};

typedef AttributeAttractRepelParticleAffector *AttributeAttractRepelParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGAttributeAttractRepelParticleAffectorBase.inl"
#include "OSGAttributeAttractRepelParticleAffector.inl"

#define OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTOR_H_ */
