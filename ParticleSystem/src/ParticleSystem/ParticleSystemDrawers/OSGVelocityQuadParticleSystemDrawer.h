/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGVELOCITYQUADPARTICLESYSTEMDRAWER_H_
#define _OSGVELOCITYQUADPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGVelocityQuadParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VelocityQuadParticleSystemDrawer class. See \ref 
           PageParticleSystemVelocityQuadParticleSystemDrawer for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING VelocityQuadParticleSystemDrawer : public VelocityQuadParticleSystemDrawerBase
{
  private:

    typedef VelocityQuadParticleSystemDrawerBase Inherited;

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

    // Variables should all be in VelocityQuadParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VelocityQuadParticleSystemDrawer(void);
    VelocityQuadParticleSystemDrawer(const VelocityQuadParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VelocityQuadParticleSystemDrawer(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class VelocityQuadParticleSystemDrawerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const VelocityQuadParticleSystemDrawer &source);
};

typedef VelocityQuadParticleSystemDrawer *VelocityQuadParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGVelocityQuadParticleSystemDrawerBase.inl"
#include "OSGVelocityQuadParticleSystemDrawer.inl"

#define OSGVELOCITYQUADPARTICLESYSTEMDRAWER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGVELOCITYQUADPARTICLESYSTEMDRAWER_H_ */
