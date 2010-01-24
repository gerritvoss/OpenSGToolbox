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

#ifndef _OSGLINEPARTICLESYSTEMDRAWER_H_
#define _OSGLINEPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLineParticleSystemDrawerBase.h"
#include "OSGDrawable.h"

OSG_BEGIN_NAMESPACE

/*! \brief LineParticleSystemDrawer class. See \ref
           PageContribParticleSystemLineParticleSystemDrawer for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING LineParticleSystemDrawer : public LineParticleSystemDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum LineDirectionSource
    {
        DIRECTION_POSITION_CHANGE = 0,
        DIRECTION_VELOCITY_CHANGE = 1,
        DIRECTION_VELOCITY        = 2,
        DIRECTION_ACCELERATION    = 3,
        DIRECTION_NORMAL          = 4,
        DIRECTION_STATIC          = 5
    };

    enum LineLengthSource
    {
        LENGTH_SIZE_X       = 0,
        LENGTH_SIZE_Y       = 1,
        LENGTH_SIZE_Z       = 2,
        LENGTH_STATIC       = 3,
        LENGTH_SPEED        = 4,
        LENGTH_ACCELERATION = 5
    };

    typedef LineParticleSystemDrawerBase Inherited;
    typedef LineParticleSystemDrawer     Self;

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

    virtual void adjustVolume(ParticleSystemUnrecPtr System, Volume & volume);

    virtual void fill(DrawableStatsAttachment *pStat,
                      ParticleSystemUnrecPtr System,
                      const MFUInt32& Sort);
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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	Pnt3f getLineEndpoint(ParticleSystemUnrecPtr System, UInt32 Index) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LineParticleSystemDrawerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LineParticleSystemDrawer &source);
};

typedef LineParticleSystemDrawer *LineParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGLineParticleSystemDrawerBase.inl"
#include "OSGLineParticleSystemDrawer.inl"

#endif /* _OSGLINEPARTICLESYSTEMDRAWER_H_ */
