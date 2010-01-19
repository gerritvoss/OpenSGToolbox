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

#ifndef _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_
#define _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsCharacteristicsDrawableBase.h"
#include "OSGAction.h"
#include "OSGMaterial.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsCharacteristicsDrawable class. See \ref
           PageContribPhysicsPhysicsCharacteristicsDrawable for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsCharacteristicsDrawable : public PhysicsCharacteristicsDrawableBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsCharacteristicsDrawableBase Inherited;
    typedef PhysicsCharacteristicsDrawable     Self;

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

    Action::ResultE renderActionEnterHandler(Action  *action);
    Action::ResultE renderActionLeaveHandler(Action  *action);

    Action::ResultE enter(Node*& node);

    MaterialUnrecPtr getDefaultMaterial(void) const;

    virtual void fill(DrawableStatsAttachment *pStat);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsCharacteristicsDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsCharacteristicsDrawable(void);
    PhysicsCharacteristicsDrawable(const PhysicsCharacteristicsDrawable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsCharacteristicsDrawable(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void    adjustVolume(Volume & volume);
    /*==========================  PRIVATE  ================================*/

  private:
    static MaterialUnrecPtr _DefaultMaterial;

    friend class FieldContainer;
    friend class PhysicsCharacteristicsDrawableBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsCharacteristicsDrawable &source);
    RenderAction *_DrawAction;
};

typedef PhysicsCharacteristicsDrawable *PhysicsCharacteristicsDrawableP;

OSG_END_NAMESPACE

#include "OSGPhysicsCharacteristicsDrawableBase.inl"
#include "OSGPhysicsCharacteristicsDrawable.inl"

#endif /* _OSGPHYSICSCHARACTERISTICSDRAWABLE_H_ */
