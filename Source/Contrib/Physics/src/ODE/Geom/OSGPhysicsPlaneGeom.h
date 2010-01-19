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

#ifndef _OSGPHYSICSPLANEGEOM_H_
#define _OSGPHYSICSPLANEGEOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsPlaneGeomBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPlaneGeom class. See \ref
           PageContribPhysicsPhysicsPlaneGeom for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsPlaneGeom : public PhysicsPlaneGeomBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsPlaneGeomBase Inherited;
    typedef PhysicsPlaneGeom     Self;

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
    /*! \name                   Class Specific                             */
    /*! \{																*/
    Real32 getPointDepth(const Vec3f& p) const;
    virtual bool isPlaceable(void) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsPlaneGeomBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPlaneGeom(void);
    PhysicsPlaneGeom(const PhysicsPlaneGeom &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPlaneGeom(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsPlaneGeom *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsPlaneGeomBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsPlaneGeom &source);
};

typedef PhysicsPlaneGeom *PhysicsPlaneGeomP;

OSG_END_NAMESPACE

#include "OSGPhysicsPlaneGeomBase.inl"
#include "OSGPhysicsPlaneGeom.inl"

#endif /* _OSGPHYSICSPLANEGEOM_H_ */
