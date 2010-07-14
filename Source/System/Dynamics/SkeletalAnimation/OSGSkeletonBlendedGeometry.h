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

#include "OSGSkeletonBlendedGeometryBase.h"
#include "OSGJoint.h"
#include "OSGSkeletonListener.h"
#include "OSGEventConnection.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGGeoVectorProperty.h"
#include <set>
#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonBlendedGeometry class. See \ref
           PageDynamicsSkeletonBlendedGeometry for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonBlendedGeometry : public SkeletonBlendedGeometryBase
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
    void addJointBlending(UInt32 VertexIndex,
                          Joint* const TheJoint,
                          Real32 BlendAmount);

    void addJointBlending(UInt32 VertexIndex,
                          UInt32 JointIndex,
                          Real32 BlendAmount);

    void addJointBlending(UInt32 VertexIndex,
                          UInt32 JointIndex,
                          UInt32 WeightIndex);

   GeoVectorProperty*   getWeights      (void) const;
   GeoIntegralProperty* getWeightIndexes(void) const;

   void setWeights      (GeoVectorProperty*   const weights);
   void setWeightIndexes(GeoIntegralProperty* const indexes);

    /**************************************************************************//**
     * @fn	EventConnection addSkeletonListener(SkeletonListenerPtr Listener)
     * 
     * @brief	Adds a skeleton listener to this instance. 
     * 
     * @param	Listener	The listener to add. 
     * 
     * @return	EventConnection
    *****************************************************************************/
    EventConnection addSkeletonListener(SkeletonListenerPtr Listener);

    /**************************************************************************//**
     * @fn	bool isSkeletonListenerAttached(SkeletonListenerPtr Listener) const
     * 
     * @brief	Query if skeleton listener 'Listener' is attached to this instance. 
     * 
     * @param	Listener	The listener. 
     * 
     * @return	true if skeleton listener attached, false if not. 
    *****************************************************************************/
    bool isSkeletonListenerAttached(SkeletonListenerPtr Listener) const;

    /**************************************************************************//**
     * @fn	void removeSkeletonListener(SkeletonListenerPtr Listener)
     * 
     * @brief	Removes the skeleton listener 'Listener'. 
     * 
     * @param	Listener	 The listener to remove. 
    *****************************************************************************/
    void removeSkeletonListener(SkeletonListenerPtr Listener);

    /**************************************************************************//**
     * @fn	void skeletonUpdated(void)
     * 
     * @brief	Skeleton updated.
    *****************************************************************************/
    void skeletonUpdated(void);

    /**************************************************************************//**
     * @fn	void updateJointTransformations(void)
     * 
     * @brief	Updates the transformations of all joints in this skeleton. 
    *****************************************************************************/
    void updateJointTransformations(void);
    

    /**************************************************************************//**
     * @fn	Matrix getAbsoluteTransformation(UInt32 index) const
     * 
     * @brief	Gets the absolute transformation of the joint in its current
     *			position.
     * 
     * @return	The joint's absolute transformation matrix. 
    *****************************************************************************/
    Matrix getAbsoluteTransformation(UInt32 index) const;

    /**************************************************************************//**
     * @fn	Matrix getAbsoluteBindTransformation(UInt32 index) const
     * 
     * @brief	Gets the bind pose absolute transformation of the joint in its current
     *			position.
     * 
     * @return	The joint's bind pose absolute transformation matrix. 
    *****************************************************************************/
    Matrix getAbsoluteBindTransformation(UInt32 index) const;

    Matrix getBindTransformationDiff(UInt32 index) const;
    Int32 getJointIndex(Joint* theJoint) const;
    Int32 getJointParentIndex(UInt32 index) const;

    UInt32 getNumJoints       (void                    ) const;
    Joint* getJoint           (UInt32 index            ) const;
    Matrix getJointInvBind    (UInt32 index            ) const; //Locaal space to Joint space
    void   pushToJoints       (Joint* const jointValue,
                               const Matrix& invBind  );
    void   removeFromJoints   (UInt32 uiIndex         );
    void   removeObjFromJoints(Joint* const jointValue);
    void   clearJoints        (void                   );
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

	typedef std::set<SkeletonListenerPtr> SkeletonListenerSet;
    typedef SkeletonListenerSet::iterator SkeletonListenerSetItor;
    typedef SkeletonListenerSet::const_iterator SkeletonListenerSetConstItor;
	
    SkeletonListenerSet       _SkeletonListeners;

    /**************************************************************************//**
     * @fn	void produceChangedEvent(void)
     * 
     * @brief	Tells all of the skeleton's listeners that an event has occurred. 
    *****************************************************************************/
	void produceChangedEvent(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonBlendedGeometryBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonBlendedGeometry &source);
};

typedef SkeletonBlendedGeometry *SkeletonBlendedGeometryP;

OSG_END_NAMESPACE

#include "OSGSkeletonBlendedGeometryBase.inl"
#include "OSGSkeletonBlendedGeometry.inl"

#endif /* _OSGSKELETONBLENDEDGEOMETRY_H_ */
