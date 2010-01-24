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

#ifndef _OSGQUADPARTICLESYSTEMDRAWER_H_
#define _OSGQUADPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQuadParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief QuadParticleSystemDrawer class. See \ref
           PageContribParticleSystemQuadParticleSystemDrawer for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING QuadParticleSystemDrawer : public QuadParticleSystemDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum NormalSource
    {
        NORMAL_POSITION_CHANGE = 0,
        NORMAL_VELOCITY_CHANGE = 1,
        NORMAL_VELOCITY        = 2,
        NORMAL_ACCELERATION    = 3,
        NORMAL_PARTICLE_NORMAL = 4,
        NORMAL_VIEW_DIRECTION  = 5,
        NORMAL_VIEW_POSITION   = 6,
        NORMAL_STATIC          = 7
    };

    enum UpSource
    {
        UP_POSITION_CHANGE = 0,
        UP_VELOCITY_CHANGE = 1,
        UP_VELOCITY        = 2,
        UP_ACCELERATION    = 3,
        UP_PARTICLE_NORMAL = 4,
        UP_VIEW_DIRECTION  = 5,
        UP_STATIC          = 6
    };

    typedef QuadParticleSystemDrawerBase Inherited;
    typedef QuadParticleSystemDrawer     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	Vec3f getQuadNormal(DrawEnv *pEnv, ParticleSystemUnrecPtr System, UInt32 Index);
	Vec3f getQuadUpDir(DrawEnv *pEnv, ParticleSystemUnrecPtr System, UInt32 Index);
	void getQuadWidthHeight(ParticleSystemUnrecPtr System, UInt32 Index, Real32& Width, Real32& Height);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class QuadParticleSystemDrawerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const QuadParticleSystemDrawer &source);
};

typedef QuadParticleSystemDrawer *QuadParticleSystemDrawerP;

OSG_END_NAMESPACE

#include "OSGQuadParticleSystemDrawerBase.inl"
#include "OSGQuadParticleSystemDrawer.inl"

#endif /* _OSGQUADPARTICLESYSTEMDRAWER_H_ */
