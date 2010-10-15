/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGSTACKEDTRANSFORM_H_
#define _OSGSTACKEDTRANSFORM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStackedTransformBase.h"

#ifdef OSG_HAVE_ACTION //CHECK
#include "OSGActorBase.h"
#endif

OSG_BEGIN_NAMESPACE

/*! \brief StackedTransform class. See \ref
           PageGroupStackedTransform for a description.
*/

class OSG_GROUP_DLLMAPPING StackedTransform : public StackedTransformBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StackedTransformBase Inherited;
    typedef StackedTransform     Self;

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
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrixr &result);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in StackedTransformBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StackedTransform(void);
    StackedTransform(const StackedTransform &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StackedTransform(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Intersect & Render                              */
    /*! \{                                                                 */

#ifndef OSG_EMBEDDED
    ActionBase::ResultE     intersectEnter(Action    *action);
    ActionBase::ResultE     intersectLeave(Action    *action);
#endif

    ActionBase::ResultE     renderEnter   (Action    *action);
    ActionBase::ResultE     renderLeave   (Action    *action);

#ifdef OSG_HAVE_ACTION //CHECK
    NewActionTypes::ResultE 
        intersectActorEnter(ActorBase::FunctorArgumentType &funcArg);

    NewActionTypes::ResultE 
        intersectActorLeave(ActorBase::FunctorArgumentType &funcArg);
#endif

    void updateTransform(void);
    void invalidateTransform(void);
    /*==========================  PRIVATE  ================================*/

  private:
    Matrix _Transformation;

    friend class FieldContainer;
    friend class StackedTransformBase;
    friend class TransformationElement;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StackedTransform &source);
};

typedef StackedTransform *StackedTransformP;

OSG_END_NAMESPACE

#include "OSGStackedTransformBase.inl"
#include "OSGStackedTransform.inl"

#endif /* _OSGSTACKEDTRANSFORM_H_ */
