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

#ifndef _OSGANIMATIONGROUP_H_
#define _OSGANIMATIONGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationGroupBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimationGroup class. See \ref
           PageDynamicsAnimationGroup for a description.
*/

class OSG_TBANIMATION_DLLMAPPING AnimationGroup : public AnimationGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimationGroupBase Inherited;
    typedef AnimationGroup     Self;

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
    virtual bool update(const Time& ElapsedTime);
    
    virtual void start(const Time& StartTime=0.0f);
    virtual void seek(const Time& SeekTime);
    virtual void pause(bool ShouldPause);
    virtual void stop(bool DisconnectFromEventProducer = true);

    virtual Real32 getUnclippedCycleLength(void) const;
    virtual Real32 getUnclippedLength(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimationGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationGroup(void);
    AnimationGroup(const AnimationGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual void internalUpdate(Real32 t, const Real32 prev_t);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimationGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimationGroup &source);
};

typedef AnimationGroup *AnimationGroupP;

OSG_END_NAMESPACE

#include "OSGAnimationGroupBase.inl"
#include "OSGAnimationGroup.inl"

#endif /* _OSGANIMATIONGROUP_H_ */
