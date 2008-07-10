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

#ifndef _OSGQUADPARTICLESYSTEMDRAWER_H_
#define _OSGQUADPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGQuadParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief QuadParticleSystemDrawer class. See \ref 
           PageParticleSystemQuadParticleSystemDrawer for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING QuadParticleSystemDrawer : public QuadParticleSystemDrawerBase
{
  private:

    typedef QuadParticleSystemDrawerBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum NormalSource {NORMAL_POSITION_CHANGE, NORMAL_VELOCITY_CHANGE, NORMAL_VELOCITY, NORMAL_ACCELERATION, NORMAL_PARTICLE_NORMAL, NORMAL_VIEW_DIRECTION, NORMAL_VIEW_POSITION, NORMAL_STATIC};
      enum UpSource {UP_POSITION_CHANGE, UP_VELOCITY_CHANGE, UP_VELOCITY, UP_ACCELERATION, UP_PARTICLE_NORMAL, UP_VIEW_DIRECTION, UP_STATIC};

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
	virtual Action::ResultE draw(DrawActionBase *action, ParticleSystemPtr System, const MFUInt32& Sort);
	virtual void adjustVolume(ParticleSystemPtr System, Volume & volume);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in QuadParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    QuadParticleSystemDrawer(void);
    QuadParticleSystemDrawer(const QuadParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QuadParticleSystemDrawer(void); 

    /*! \}                                                                 */
	Vec3f getQuadNormal(DrawActionBase *action,ParticleSystemPtr System, UInt32 Index);
	Vec3f getQuadUpDir(DrawActionBase *action,ParticleSystemPtr System, UInt32 Index);
	void getQuadWidthHeight(ParticleSystemPtr System, UInt32 Index, Real32& Width, Real32& Height);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class QuadParticleSystemDrawerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const QuadParticleSystemDrawer &source);
};

typedef QuadParticleSystemDrawer *QuadParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGQuadParticleSystemDrawerBase.inl"
#include "OSGQuadParticleSystemDrawer.inl"

#define OSGQUADPARTICLESYSTEMDRAWER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGQUADPARTICLESYSTEMDRAWER_H_ */
