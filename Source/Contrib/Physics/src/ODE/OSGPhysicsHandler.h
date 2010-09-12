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

#ifndef _OSGPHYSICSHANDLER_H_
#define _OSGPHYSICSHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNode.h"
#include "OSGPhysicsHandlerBase.h"
#include <ode/ode.h>
#include "OSGStatElemTypes.h"
#include "OSGPhysicsBodyFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsHandler class. See \ref
           PageContribPhysicsPhysicsHandler for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsHandler : public PhysicsHandlerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsHandlerBase Inherited;
    typedef PhysicsHandler     Self;

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
    void attachUpdateProducer(ReflexiveContainer* const producer);
    void detachUpdateProducer(void);

    static StatElemDesc<StatTimeElem   > statCollisionTime;
    static StatElemDesc<StatTimeElem   > statSimulationTime;
    static StatElemDesc<StatTimeElem   > statTransformUpdateTime;
    static StatElemDesc<StatTimeElem   > statPhysicsTime;
    static StatElemDesc<StatIntElem    > statNPhysicsSteps;
    static StatElemDesc<StatRealElem   > statNCollisionTests;
    static StatElemDesc<StatRealElem   > statNCollisions;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsHandlerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsHandler(void);
    PhysicsHandler(const PhysicsHandler &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void onCreate(const PhysicsHandler *id = NULL);
    void onDestroy();
    void updateWorld(Node* const node);

    Time _TimeSinceLast;
    void attachedUpdate(EventDetails* const details);
    boost::signals2::connection _UpdateEventConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsHandlerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsHandler &source);
};

typedef PhysicsHandler *PhysicsHandlerP;

OSG_END_NAMESPACE

#include "OSGPhysicsWorld.h"
#include "OSGPhysicsSpace.h"

#include "OSGPhysicsHandlerBase.inl"
#include "OSGPhysicsHandler.inl"

#endif /* _OSGPHYSICSHANDLER_H_ */
