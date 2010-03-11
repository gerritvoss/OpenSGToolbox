/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#ifndef _OSGSKELETONBLENDEDGEOMETRY_H_
#define _OSGSKELETONBLENDEDGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkeleton.h"
#include "OSGJoint.h"
#include "OSGSkeletonBlendedGeometryBase.h"
#include "OSGSkeletonListener.h"
#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonBlendedGeometry class. See \ref
           PageDynamicsSkeletonBlendedGeometry for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonBlendedGeometry : public SkeletonBlendedGeometryBase, public SkeletonListener
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum BlendMode{BLEND_RIGID =0, BLEND_SMOOTH =1};

    typedef SkeletonBlendedGeometryBase Inherited;
    typedef SkeletonBlendedGeometry     Self;

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
    /**************************************************************************//**
     * @fn	void addJointBlending(const UInt32& PositionIndex,
     * 		const JointUnrecPtr TheJoint, const Real32& BlendAmount)
     * 
     * @brief	Attaches a point in the mesh to a joint with the given blend weight
     * 
     * @param	PositionIndex	Index of the point to be attached.
     * @param	TheJoint		The joint to which the point is being attached.
     * @param	BlendAmount		The blend weight.
    *****************************************************************************/
    void addJointBlending(const UInt32& PositionIndex, const JointUnrecPtr TheJoint, const Real32& BlendAmount);

   /**************************************************************************//**
    * @fn	virtual void skeletonChanged(const SkeletonEvent& e)
    * 
    * @brief	Called when the skeleton changes. Tells all attached geometries
	*			to update their positions.
    * 
    * @param	e	The SkeletonEvent. 
   *****************************************************************************/
   virtual void skeletonChanged(const SkeletonEventUnrecPtr e);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonBlendedGeometryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonBlendedGeometry(void);
    SkeletonBlendedGeometry(const SkeletonBlendedGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonBlendedGeometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/**************************************************************************//**
	 * @fn	void calculatePositions(void)
	 * 
	 * @brief	Calculates the positions of the attached meshes based on the
	 *			current positions of the attached skeletons.
	*****************************************************************************/
	void calculatePositions(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonBlendedGeometryBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonBlendedGeometry &source);

	std::vector<EventConnection> _SkeletonListenerConnections;
};

typedef SkeletonBlendedGeometry *SkeletonBlendedGeometryP;

OSG_END_NAMESPACE

#include "OSGSkeletonBlendedGeometryBase.inl"
#include "OSGSkeletonBlendedGeometry.inl"

#endif /* _OSGSKELETONBLENDEDGEOMETRY_H_ */
