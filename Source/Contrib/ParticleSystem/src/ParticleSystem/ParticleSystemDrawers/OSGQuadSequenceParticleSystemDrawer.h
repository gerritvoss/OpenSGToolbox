/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)*
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

#ifndef _OSGQUADSEQUENCEPARTICLESYSTEMDRAWER_H_
#define _OSGQUADSEQUENCEPARTICLESYSTEMDRAWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQuadSequenceParticleSystemDrawerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief QuadSequenceParticleSystemDrawer class. See \ref
           PageContribParticleSystemQuadSequenceParticleSystemDrawer for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING QuadSequenceParticleSystemDrawer : public QuadSequenceParticleSystemDrawerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef QuadSequenceParticleSystemDrawerBase Inherited;
    typedef QuadSequenceParticleSystemDrawer     Self;

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

	virtual Action::ResultE draw(DrawEnv *pEnv, ParticleSystemUnrecPtr System, const MFUInt32& Sort);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in QuadSequenceParticleSystemDrawerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    QuadSequenceParticleSystemDrawer(void);
    QuadSequenceParticleSystemDrawer(const QuadSequenceParticleSystemDrawer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QuadSequenceParticleSystemDrawer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

	void calcTexCoords(UInt32 SequenceIndex);
	Vec2f _texCoords [4];

  private:

    friend class FieldContainer;
    friend class QuadSequenceParticleSystemDrawerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const QuadSequenceParticleSystemDrawer &source);
};

typedef QuadSequenceParticleSystemDrawer *QuadSequenceParticleSystemDrawerP;

OSG_END_NAMESPACE
#include "OSGParticleFunction.h"
#include "OSGQuadSequenceParticleSystemDrawerBase.inl"
#include "OSGQuadSequenceParticleSystemDrawer.inl"

#endif /* _OSGQUADSEQUENCEPARTICLESYSTEMDRAWER_H_ */
