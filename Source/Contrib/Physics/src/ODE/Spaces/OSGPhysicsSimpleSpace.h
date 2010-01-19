/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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

#ifndef _OSGPHYSICSSIMPLESPACE_H_
#define _OSGPHYSICSSIMPLESPACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsSimpleSpaceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsSimpleSpace class. See \ref
           PageContribPhysicsPhysicsSimpleSpace for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsSimpleSpace : public PhysicsSimpleSpaceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsSimpleSpaceBase Inherited;
    typedef PhysicsSimpleSpace     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsSimpleSpaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsSimpleSpace(void);
    PhysicsSimpleSpace(const PhysicsSimpleSpace &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsSimpleSpace(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsSimpleSpace *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsSimpleSpaceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsSimpleSpace &source);
};

typedef PhysicsSimpleSpace *PhysicsSimpleSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsSimpleSpaceBase.inl"
#include "OSGPhysicsSimpleSpace.inl"

#endif /* _OSGPHYSICSSIMPLESPACE_H_ */
