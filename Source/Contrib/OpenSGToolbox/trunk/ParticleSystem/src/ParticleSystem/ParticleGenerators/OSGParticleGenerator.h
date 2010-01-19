/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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

#ifndef _OSGPARTICLEGENERATOR_H_
#define _OSGPARTICLEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGParticleGeneratorBase.h"
#include "ParticleSystem/OSGParticleSystemFields.h"
#include <OpenSG/Toolbox/OSGStringToUInt32MapType.h>

OSG_BEGIN_NAMESPACE

/*! \brief ParticleGenerator class. See \ref 
           PageParticleSystemParticleGenerator for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING ParticleGenerator : public ParticleGeneratorBase
{
  private:

    typedef ParticleGeneratorBase Inherited;

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

    virtual bool generate(ParticleSystemPtr System, const Time& elps) = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ParticleGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleGenerator(void);
    ParticleGenerator(const ParticleGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleGenerator(void); 

    /*! \}                                                                 */
    
    virtual void generate(ParticleSystemPtr System,
		Pnt3f& PositionReturnValue, 
		Pnt3f& SecPositionReturnValue, 
		Vec3f& NormalReturnValue,
		Color4f& ColorReturnValue,
		Vec3f& SizeReturnValue,
		Time& LifespanReturnValue,
		Time& AgeReturnValue,
		Vec3f& VelocityReturnValue,
		Vec3f& SecVelocityReturnValue,
		Vec3f& AccelerationReturnValue,
        StringToUInt32Map& AttributeReturnValue) const;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ParticleGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ParticleGenerator &source);
};

typedef ParticleGenerator *ParticleGeneratorP;

OSG_END_NAMESPACE

#include "OSGParticleGeneratorBase.inl"
#include "OSGParticleGenerator.inl"

#define OSGPARTICLEGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPARTICLEGENERATOR_H_ */
