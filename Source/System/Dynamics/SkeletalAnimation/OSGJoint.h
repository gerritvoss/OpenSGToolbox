/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#ifndef _OSGJOINT_H_
#define _OSGJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Joint class. See \ref
           PageDynamicsJoint for a description.
*/

class OSG_TBANIMATION_DLLMAPPING Joint : public JointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef JointBase Inherited;
    typedef Joint     Self;

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
    /*! \name                     Transform                                */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrixr &result);

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
    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in JointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Joint(void);
    Joint(const Joint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Joint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Transform                                */
    /*! \{                                                                 */

    virtual void adjustVolume(Volume &volume);

    /*! \}                                                                 */

    Matrix _RelativeDifferenceTransformation;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class JointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Joint &source);
};

typedef Joint *JointP;

OSG_END_NAMESPACE

#include "OSGJointBase.inl"
#include "OSGJoint.inl"

#endif /* _OSGJOINT_H_ */
