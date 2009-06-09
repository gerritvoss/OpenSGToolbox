/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
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

#ifndef _OSGPHYSICSSPACE_H_
#define _OSGPHYSICSSPACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"
#include <ode/ode.h>

#include "OSGPhysicsSpaceBase.h"
#include "ODE/OSGPhysicsWorldFields.h"
#include <set>
#include "Events/OSGCollisionListener.h"
#include <OpenSG/Input/OSGEventConnection.h>

#define MAX_PHYS_CONTACTS 32

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsSpace : public PhysicsSpaceBase
{
  private:

    typedef PhysicsSpaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{                                                                 */
	  void onCreate(const PhysicsSpace *id = NULL);
	  void onDestroy();
	  /*! \}                                                                 */
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Get Field                    */
	  /*! \{                                                                 */
      dSpaceID getSpaceID(void) const;
      PhysicsHandlerPtr getParentHandler(void) const;
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Set Field                    */
	  /*! \{                                                                 */
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
      void initSpace();
	  void AddGeom( dGeomID );
	  void RemoveGeom( dGeomID );
	  bool ContainsGeom( dGeomID );
	  void AddSpace( dSpaceID );
	  void RemoveSpace( dSpaceID );
	  bool ContainsSpace( dSpaceID );
	  Int32 GetNumGeoms();
	  dGeomID GetGeom( Int32 i );

	  void Collide( PhysicsWorldPtr w );
      static void collisionCallback (void *data, dGeomID o1, dGeomID o2);

      void addCollisionContactCategory(UInt64 Category1, UInt64 Category2, CollisionContactParametersPtr ContactParams);
      void removeCollisionContactCategory(UInt64 Category1, UInt64 Category2);
      CollisionContactParametersPtr getCollisionContactCategory(UInt64 Category1, UInt64 Category2);
      CollisionContactParametersPtr getCollisionContact(UInt64 Category1, UInt64 Category2);

      
      void addCollisionListenerCategory();


	  /*! \}                                                                 */
    EventConnection addCollisionListener(CollisionListenerPtr Listener, UInt64 Category, Real32 SpeedThreshold);
    bool isCollisionListenerAttached(CollisionListenerPtr Listener) const;
    void removeCollisionListener(CollisionListenerPtr Listener);
      

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

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsSpaceBase.
    dSpaceID _SpaceID;
    dWorldID _CollideWorldID;

    dJointGroupID _ColJointGroupId;
    std::vector<dContact> _ContactJoints;

    void setSpaceID(dSpaceID id);
    CollisionContactParametersPtr createDefaultContactParams(void) const;

    struct CollisionListenParams
    {
        UInt64 _Category;
        Real32 _SpeedThreshold;
        CollisionListenerPtr _Listener;
    };
    std::vector<CollisionListenParams> _CollisionListenParamsVec; 

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsSpace(void);
    PhysicsSpace(const PhysicsSpace &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsSpace(void); 

    void collisionCallback (dGeomID o1, dGeomID o2);
    /*! \}                                                                 */
    
	typedef std::set<CollisionListenerPtr> CollisionListenerSet;
    typedef CollisionListenerSet::iterator CollisionListenerSetItor;
    typedef CollisionListenerSet::const_iterator CollisionListenerSetConstItor;
    CollisionListenerSet       _CollisionListeners;
        
    void produceCollision(CollisionListenerPtr _Listener, const Pnt3f& Position,const Vec3f& Normal, PhysicsGeomPtr Geom1,PhysicsGeomPtr Geom2,const Vec3f& Velocity1,const Vec3f& Velocity2) const;

    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsSpaceBase;
    friend class PhysicsHandler;
    friend class PhysicsGeom;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsSpace &source);
};

typedef PhysicsSpace *PhysicsSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsSpaceBase.inl"
#include "OSGPhysicsSpace.inl"

#define OSGPHYSICSSPACE_HEADER_CVSID "@(#)$Id: OSGPhysicsSpace.h,v 1.2 2006/08/19 00:21:47 dirk Exp $"

#endif /* _OSGPHYSICSSPACE_H_ */
