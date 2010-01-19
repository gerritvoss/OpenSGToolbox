/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),                            *
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

#ifndef _OSGCOLLISIONCONTACTPARAMETERS_H_
#define _OSGCOLLISIONCONTACTPARAMETERS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCollisionContactParametersBase.h"
#include <ode/ode.h>

OSG_BEGIN_NAMESPACE

/*! \brief CollisionContactParameters class. See \ref
           PageContribPhysicsCollisionContactParameters for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING CollisionContactParameters : public CollisionContactParametersBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CollisionContactParametersBase Inherited;
    typedef CollisionContactParameters     Self;

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

    void updateODEContactJoint(dContact &d) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CollisionContactParametersBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionContactParameters(void);
    CollisionContactParameters(const CollisionContactParameters &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionContactParameters(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CollisionContactParametersBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollisionContactParameters &source);
};

typedef CollisionContactParameters *CollisionContactParametersP;

OSG_END_NAMESPACE

#include "OSGCollisionContactParametersBase.inl"
#include "OSGCollisionContactParameters.inl"

#endif /* _OSGCOLLISIONCONTACTPARAMETERS_H_ */
