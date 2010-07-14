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

#ifndef _OSGSKELETONDRAWABLE_H_
#define _OSGSKELETONDRAWABLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSkeletonDrawableBase.h"
#include "OSGAction.h"
#include "OSGSkeletonBlendedGeometry.h"
#include "OSGJoint.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonDrawable class. See \ref
           PageDynamicsSkeletonDrawable for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonDrawable : public SkeletonDrawableBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkeletonDrawableBase Inherited;
    typedef SkeletonDrawable     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    void     drawPrimitives(DrawEnv *pEnv);

    Action::ResultE     renderActionEnterHandler (Action *action);

    Action::ResultE     renderActionLeaveHandler (Action *action);

    /*! \}                                                                 */

    virtual void fill(DrawableStatsAttachment *pStat);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonDrawableBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonDrawable(void);
    SkeletonDrawable(const SkeletonDrawable &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonDrawable(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                NodeCore Specific                             */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume & volume);

    /*! \}                                                                 */

    Pnt3f _lastEndPoint;
    Pnt3f _lastStartPoint;
    Matrix _lastAbsTrans;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonDrawableBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonDrawable &source);
};

typedef SkeletonDrawable *SkeletonDrawableP;

OSG_END_NAMESPACE

#include "OSGSkeletonDrawableBase.inl"
#include "OSGSkeletonDrawable.inl"

#endif /* _OSGSKELETONDRAWABLE_H_ */
