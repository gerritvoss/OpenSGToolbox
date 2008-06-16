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

#ifndef _OSGLINEPARTICLESYSTEMDRAWER_H_
#define _OSGLINEPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGLineParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LineParticleSystemDrawer class. See \ref 
           PageParticleSystemLineParticleSystemDrawer for a description.
*/

class OSG_PARTICLESYSTEMLIB_DLLMAPPING LineParticleSystemDrawer : public LineParticleSystemDrawerBase
{
  private:

    typedef LineParticleSystemDrawerBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum LineDirectionSource {POSITION_CHANGE, VELOCITY_CHANGE, VELOCITY, ACCELERATION, NORMAL};

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

    // Variables should all be in LineParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LineParticleSystemDrawer(void);
    LineParticleSystemDrawer(const LineParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineParticleSystemDrawer(void); 

	Pnt3f getLineEndpoint(ParticleSystemPtr System, UInt32 Index);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LineParticleSystemDrawerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LineParticleSystemDrawer &source);
};

typedef LineParticleSystemDrawer *LineParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGLineParticleSystemDrawerBase.inl"
#include "OSGLineParticleSystemDrawer.inl"

#define OSGLINEPARTICLESYSTEMDRAWER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLINEPARTICLESYSTEMDRAWER_H_ */
