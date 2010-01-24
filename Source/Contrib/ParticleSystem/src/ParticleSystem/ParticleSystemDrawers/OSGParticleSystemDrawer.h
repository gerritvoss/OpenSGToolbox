/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGPARTICLESYSTEMDRAWER_H_
#define _OSGPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemDrawerBase.h"
#include "OSGParticleSystem.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGDrawableStatsAttachment.h"
#include "OSGSysMFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemDrawer class. See \ref
           PageContribParticleSystemParticleSystemDrawer for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleSystemDrawer : public ParticleSystemDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleSystemDrawerBase Inherited;
    typedef ParticleSystemDrawer     Self;

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

	virtual Action::ResultE draw(DrawEnv *pEnv,
                                 ParticleSystemUnrecPtr System,
                                 const MFUInt32& Sort) = 0;

	virtual void adjustVolume(ParticleSystemUnrecPtr System, Volume & volume);

    virtual void fill(DrawableStatsAttachment *pStat,
                      ParticleSystemUnrecPtr System,
                      const MFUInt32& Sort) = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemDrawer(void);
    ParticleSystemDrawer(const ParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemDrawer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemDrawerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemDrawer &source);
};

typedef ParticleSystemDrawer *ParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGParticleSystemDrawerBase.inl"
#include "OSGParticleSystemDrawer.inl"

#endif /* _OSGPARTICLESYSTEMDRAWER_H_ */
