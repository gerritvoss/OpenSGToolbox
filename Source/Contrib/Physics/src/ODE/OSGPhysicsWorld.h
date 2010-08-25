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

#ifndef _OSGPHYSICSWORLD_H_
#define _OSGPHYSICSWORLD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsWorldBase.h"
#include <ode/ode.h>
#include "OSGPhysicsHandlerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsWorld class. See \ref
           PageContribPhysicsPhysicsWorld for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsWorld : public PhysicsWorldBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsWorldBase Inherited;
    typedef PhysicsWorld     Self;

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
    dWorldID getWorldID(void);
	Vec3f impulseToForce(Real32 stepsize, const Vec3f& Impulse);
	void worldStep(Real32 stepsize);
	void worldQuickStep(Real32 stepsize);
    void initWorld();

    PhysicsHandler* getParentHandler(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsWorldBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsWorld(void);
    PhysicsWorld(const PhysicsWorld &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsWorld(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	void onCreate(const PhysicsWorld *_World = NULL);
	void onDestroy();
	
    static bool odeInitFunc(void);

    static bool odeExitFunc(void);

    //ODE worldID
    dWorldID _World;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsWorldBase;
    friend class PhysicsHandler;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsWorld &source);
};

typedef PhysicsWorld *PhysicsWorldP;

OSG_END_NAMESPACE

#include "OSGPhysicsHandler.h"

#include "OSGPhysicsWorldBase.inl"
#include "OSGPhysicsWorld.inl"

#endif /* _OSGPHYSICSWORLD_H_ */
