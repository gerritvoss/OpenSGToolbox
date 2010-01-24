/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGParticleGeneratorBase.h"
#include "OSGParticleSystemFields.h"
#include "OSGStringToUInt32MapType.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleGenerator class. See \ref
           PageContribParticleSystemParticleGenerator for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleGenerator : public ParticleGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleGeneratorBase Inherited;
    typedef ParticleGenerator     Self;

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

    virtual bool generate(ParticleSystemRefPtr System, const Time& elps) = 0;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    virtual void generate(ParticleSystemRefPtr System,
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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleGenerator &source);
};

typedef ParticleGenerator *ParticleGeneratorP;

OSG_END_NAMESPACE

#include "OSGParticleGeneratorBase.inl"
#include "OSGParticleGenerator.inl"

#endif /* _OSGPARTICLEGENERATOR_H_ */
