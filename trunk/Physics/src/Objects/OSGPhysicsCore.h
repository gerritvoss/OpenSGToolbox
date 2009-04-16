/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGPHYSICSCORE_H_
#define _OSGPHYSICSCORE_H_
#ifdef __sgi
#pragma once
#endif
#include "OSGPhysicsConfig.h"
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGAction.h>

#include "OSGPhysicsCoreBase.h"
#include "Physics/Actors/OSGPhysicsActor.h"

OSG_BEGIN_NAMESPACE

class OSG_PHYSICS_CLASS_API PhysicsCore : public PhysicsCoreBase
{
  private:

    typedef PhysicsCoreBase Inherited;

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

    virtual void update(const Real32& ElpsTime);
    virtual void accumulateMatrix(Matrix &result);
    virtual void adjustVolume(Volume &volume);
    
    NewActionTypes::ResultE physicsActor(	ActorBase::FunctorArgumentType& funcArg );
    
      /*---------------------------------------------------------------------*/
      Action::ResultE drawEnter     (Action *action);
      Action::ResultE drawLeave     (Action *action);
      
      //Action::ResultE intersectEnter(Action *action);
      //Action::ResultE intersectLeave(Action *action);
      
      //NewActionTypes::ResultE intersectEnter(ActorBase::FunctorArgumentType &funcArg);
      //NewActionTypes::ResultE intersectLeave(ActorBase::FunctorArgumentType &funcArg);
      
      Action::ResultE renderEnter   (Action *action);
      Action::ResultE renderLeave   (Action *action);
     
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsCoreBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsCore(void);
    PhysicsCore(const PhysicsCore &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsCore(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsCoreBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsCore &source);
};

typedef PhysicsCore *PhysicsCoreP;

OSG_END_NAMESPACE

#include "OSGPhysicsCoreBase.inl"
#include "OSGPhysicsCore.inl"

#define OSGPHYSICSCORE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPHYSICSCORE_H_ */
