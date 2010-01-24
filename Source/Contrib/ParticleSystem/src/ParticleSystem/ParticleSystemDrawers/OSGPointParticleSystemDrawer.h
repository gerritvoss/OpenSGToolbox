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

#ifndef _OSGPOINTPARTICLESYSTEMDRAWER_H_
#define _OSGPOINTPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPointParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PointParticleSystemDrawer class. See \ref
           PageContribParticleSystemPointParticleSystemDrawer for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING PointParticleSystemDrawer : public PointParticleSystemDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PointParticleSystemDrawerBase Inherited;
    typedef PointParticleSystemDrawer     Self;

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

	virtual Action::ResultE draw(DrawEnv *pEnv, ParticleSystemUnrecPtr System, const MFUInt32& Sort);

    virtual void fill(DrawableStatsAttachment *pStat,
                      ParticleSystemUnrecPtr System,
                      const MFUInt32& Sort);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PointParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PointParticleSystemDrawer(void);
    PointParticleSystemDrawer(const PointParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PointParticleSystemDrawer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PointParticleSystemDrawerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PointParticleSystemDrawer &source);
};

typedef PointParticleSystemDrawer *PointParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGPointParticleSystemDrawerBase.inl"
#include "OSGPointParticleSystemDrawer.inl"

#endif /* _OSGPOINTPARTICLESYSTEMDRAWER_H_ */
