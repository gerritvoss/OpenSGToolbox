/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGCOLLISIONEVENT_H_
#define _OSGCOLLISIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGCollisionEventBase.h"

OSG_BEGIN_NAMESPACE

class CollisionEvent : public CollisionEventBase
{
  private:

    typedef CollisionEventBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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
    static  CollisionEventPtr      create(  FieldContainerPtr Source,
                                            Time TimeStamp,
                                            const Pnt3f& Position,
                                            const Vec3f& Normal,
                                            PhysicsGeomPtr Geom1,
                                            PhysicsGeomPtr Geom2,
                                            const Vec3f& Velocity1,
                                            const Vec3f& Velocity2,
                                            const Real32& ProjectedNormalSpeed); 
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CollisionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionEvent(void);
    CollisionEvent(const CollisionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CollisionEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CollisionEvent &source);
};

typedef CollisionEvent *CollisionEventP;

OSG_END_NAMESPACE

#include "OSGCollisionEventBase.inl"
#include "OSGCollisionEvent.inl"

#endif /* _OSGCOLLISIONEVENT_H_ */
