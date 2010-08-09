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

/**************************************************************************//**
 * @defgroup PhysicsSpaces
 *****************************************************************************/

/**************************************************************************//**
 * @class   PhysicsSpace : public PhysicsSpaceBase
 * 
 * @brief	A wapper around the ODE space type. 
 * 
 * @ingroup PhysicsSpaces
 *
 * @see    @htmlonly <A href="http://www.ode.org/">ODE</A> @endhtmlonly
 *****************************************************************************/

#ifndef _OSGPHYSICSSPACE_H_
#define _OSGPHYSICSSPACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsSpaceBase.h"

//#include "rapidxml.h"
//#include "rapidxml_iterators.h"
#include "OSGXMLFCFileType.h"

namespace rapidxml{
template < class T>
class xml_node;

template < class T>
class node_iterator;

class parse_error;
}

#define MAX_PHYS_CONTACTS 32

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsSpace class. See \ref
           PageContribPhysicsPhysicsSpace for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsSpace : public PhysicsSpaceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsSpaceBase Inherited;
    typedef PhysicsSpace     Self;

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
	  /*! \name                   Class Specific Get Field                    */
	  /*! \{                                                                 */
      dSpaceID getSpaceID(void) const;
      PhysicsHandler* getParentHandler(void) const;
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

	  void Collide( PhysicsWorld* const w );
      static void collisionCallback (void *data, dGeomID o1, dGeomID o2);

      void addCollisionContactCategory(UInt64 Category1, UInt64 Category2, CollisionContactParameters* const ContactParams);
      void removeCollisionContactCategory(UInt64 Category1, UInt64 Category2);
      CollisionContactParameters* getCollisionContactCategory(UInt64 Category1, UInt64 Category2);
      CollisionContactParameters* getCollisionContact(UInt64 Category1, UInt64 Category2);

      
      void addCollisionListenerCategory();

      virtual bool isPlaceable(void) const;

      virtual void discardLastCollision(void);


	  /*! \}                                                                 */
      boost::signals2::connection connectCollision(const CollisionEventType::slot_type &listener, 
                                                   UInt64 Category,
                                                   Real32 SpeedThreshold,
                                                   boost::signals2::connect_position at= boost::signals2::at_back);
      boost::signals2::connection connectCollision(const CollisionEventType::group_type &group,
                                                   const CollisionEventType::slot_type &listener, 
                                                   UInt64 Category,
                                                   Real32 SpeedThreshold,
                                                   boost::signals2::connect_position at= boost::signals2::at_back);
        
	  static bool xmlReadHandler (rapidxml::xml_node<char>&, const XMLFCFileType::IDLookupMap&,const FieldContainerUnrecPtr&);
	  static bool xmlWriteHandler (const FieldContainerUnrecPtr&);

      static bool registerXMLHandler(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsSpaceBase.

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{                                                                 */
	  void onCreate(const PhysicsSpace *id = NULL);
	  void onDestroy();
	  /*! \}                                                                 */
    // Variables should all be in PhysicsSpaceBase.
    dSpaceID _SpaceID;
    dWorldID _CollideWorldID;

    dJointGroupID _ColJointGroupId;
    std::vector<dContact> _ContactJoints;

    void setSpaceID(dSpaceID id);
    CollisionContactParametersTransitPtr createDefaultContactParams(void) const;

    struct CollisionListenParams
    {
        UInt64 _Category;
        Real32 _SpeedThreshold;
        const CollisionEventType::slot_type* _Listener;

        CollisionListenParams(UInt64 Category, Real32 SpeedThreshold, const CollisionEventType::slot_type* Listener);
    };
    std::vector<CollisionListenParams> _CollisionListenParamsVec; 

    void collisionCallback (dGeomID o1, dGeomID o2);
        
    void produceCollision(const CollisionEventType::slot_type* Listener, 
                          const Pnt3f& Position,
                          const Vec3f& Normal, 
                          PhysicsGeom* const Geom1,
                          PhysicsGeom* const Geom2,
                          UInt64 Geom1Cat,
                          UInt64 Geom1Col,
                          UInt64 Geom2Cat,
                          UInt64 Geom2Col,
                          const Vec3f& Velocity1,
                          const Vec3f& Velocity2,
                          const Real32& ProjectedNormalSpeed);

    void produceCollision(const Pnt3f& Position,
                            const Vec3f& Normal, 
                            PhysicsGeom* const Geom1,
                            PhysicsGeom* const Geom2,
                            UInt64 Geom1Cat,
                            UInt64 Geom1Col,
                            UInt64 Geom2Cat,
                            UInt64 Geom2Col,
                            const Vec3f& Velocity1,
                            const Vec3f& Velocity2,
                            const Real32& ProjectedNormalSpeed);

    bool _DiscardCollision;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsSpaceBase;
    friend class PhysicsHandler;
    friend class PhysicsGeom;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsSpace &source);
};

typedef PhysicsSpace *PhysicsSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsGeom.h"
#include "OSGCollisionContactParameters.h"
#include "OSGCollisionEventDetails.h"

#include "OSGPhysicsSpaceBase.inl"
#include "OSGPhysicsSpace.inl"

#endif /* _OSGPHYSICSSPACE_H_ */
