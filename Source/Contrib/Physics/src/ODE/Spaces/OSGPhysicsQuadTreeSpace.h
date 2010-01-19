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

#ifndef _OSGPHYSICSQUADTREESPACE_H_
#define _OSGPHYSICSQUADTREESPACE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsQuadTreeSpaceBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsQuadTreeSpace class. See \ref
           PageContribPhysicsPhysicsQuadTreeSpace for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsQuadTreeSpace : public PhysicsQuadTreeSpaceBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsQuadTreeSpaceBase Inherited;
    typedef PhysicsQuadTreeSpace     Self;

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
	void initQuadTree(dSpaceID space);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsQuadTreeSpaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsQuadTreeSpace(void);
    PhysicsQuadTreeSpace(const PhysicsQuadTreeSpace &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsQuadTreeSpace(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsQuadTreeSpace *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsQuadTreeSpaceBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsQuadTreeSpace &source);
};

typedef PhysicsQuadTreeSpace *PhysicsQuadTreeSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsQuadTreeSpaceBase.inl"
#include "OSGPhysicsQuadTreeSpace.inl"

#endif /* _OSGPHYSICSQUADTREESPACE_H_ */
