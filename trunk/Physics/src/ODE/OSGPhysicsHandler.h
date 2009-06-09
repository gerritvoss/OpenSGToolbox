/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"
#include <ode/ode.h>

#include "OSGPhysicsHandlerBase.h"

#include <OpenSG/OSGStatElemTypes.h>
#include "OSGPhysicsBodyFields.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGUpdateListener.h>


OSG_BEGIN_NAMESPACE

/*! \brief PhysicsHandler class. See \ref 
           PageContribPhysicsHandler for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsHandler : public PhysicsHandlerBase, public UpdateListener
{
  private:

    typedef PhysicsHandlerBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
	/*! \name                   Class Specific Get Field                    */
	/*! \{                                                                 */
	
	/*! \}                                                                 */

	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific Set Field                    */
	/*! \{                                                                 */
	
	/*! \}                                                                 */

      /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;


    void attachUpdateProducer(WindowEventProducerPtr TheProducer);
    virtual void update(const UpdateEvent& e);

    /*! \}                                                                 */
    static StatElemDesc<StatTimeElem   > statCollisionTime;
    static StatElemDesc<StatTimeElem   > statPerStepCollisionTime;
    static StatElemDesc<StatTimeElem   > statSimulationTime;
    static StatElemDesc<StatTimeElem   > statPerStepSimulationTime;
    static StatElemDesc<StatTimeElem   > statPhysicsTime;
    static StatElemDesc<StatIntElem    > statNPhysicsSteps;
    static StatElemDesc<StatIntElem    > statNCollisionTests;
    static StatElemDesc<StatIntElem    > statNCollisions;

    StatCollector* getStatistics(void);
    void setStatistics(StatCollector *stat);

    /*=========================  PROTECTED  ===============================*/
  protected:
    void update(Time ElapsedTime, NodePtr UpdateNode);

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
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    void onCreate(const PhysicsHandler *id = NULL);
    void onDestroy();
    void updateWorld(NodePtr node);

    StatCollector* _statistics;
    bool _ownStat;
    Time _TimeSinceLast;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsHandlerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsHandler &source);
};

typedef PhysicsHandler *PhysicsHandlerP;

OSG_END_NAMESPACE

#include "OSGPhysicsHandlerBase.inl"
#include "OSGPhysicsHandler.inl"

#define OSGPHYSICSHANDLER_HEADER_CVSID "@(#)$Id: OSGPhysicsHandler.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSHANDLER_H_ */
