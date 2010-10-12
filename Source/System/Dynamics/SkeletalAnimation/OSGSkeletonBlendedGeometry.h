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
#include "OSGNode.h"
#include "OSGSkeletonEventDetails.h"
#include "OSGGeoIntegralProperty.h"
#include "OSGGeoVectorProperty.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonBlendedGeometry class. See \ref
           PageDynamicsSkeletonBlendedGeometry for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonBlendedGeometry : public SkeletonBlendedGeometryBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
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
    /*---------------------------------------------------------------------*/
    /*! \name               calc the inverse matrix                        */
    /*! \{                                                                 */

    void initMatrix(const Matrixr        &mToWorld);

    void calcMatrix(const Matrixr        &mToWorld,
                          Matrixr        &mResult);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void accumulateMatrix(Matrixr &result);

    /*! \}                                                                 */
    
    /**************************************************************************//**
     * @fn	void addJointBlending(const UInt32& PositionIndex,
     * 		const NodeUnrecPtr TheJoint, const Real32& BlendAmount)
     * 
     * @brief	Attaches a point in the mesh to a joint with the given blend weight
     * 
     * @param	PositionIndex	Index of the point to be attached.
     * @param	TheJoint		The joint to which the point is being attached.
     * @param	BlendAmount		The blend weight.
    *****************************************************************************/
    void addJointBlending(UInt32 VertexIndex,
                          Node* const TheJoint,
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
     * @fn	void skeletonUpdated(void)
     * 
     * @brief	Skeleton updated.
    *****************************************************************************/
    void skeletonUpdated(void);

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

    Int32 getJointIndex(Node* theJoint) const;
    Int32 getJointParentIndex(UInt32 index) const;

    UInt32 getNumJoints       (void                    ) const;
    Node* getJoint           (UInt32 index            ) const;
    Matrix getJointInvBind    (UInt32 index            ) const; //Locaal space to Joint space
    void   pushToJoints       (Node* const jointValue,
                               const Matrix& invBind  );
    void   removeFromJoints   (UInt32 uiIndex         );
    void   removeObjFromJoints(Node* const jointValue);
    void   clearJoints        (void                   );

    virtual void            drawPrimitives      (DrawEnv        *pEnv  );
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Volume                                  */
    /*! \{                                                                 */

    virtual void adjustVolume    (Volume &volume);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Draw & Intersect & Render                       */
    /*! \{                                                                 */

#ifndef OSG_EMBEDDED
    Action::ResultE intersectEnter(Action *action);
    Action::ResultE intersectLeave(Action *action);
#endif

    Action::ResultE renderEnter   (Action *action);
    Action::ResultE renderLeave   (Action *action);

    /*! \}                                                                 */
	/**************************************************************************//**
	 * @fn	void calculatePositions(void)
	 * 
	 * @brief	Calculates the positions of the attached meshes based on the
	 *			current positions of the attached skeletons.
	*****************************************************************************/
	void calculatePositions(void);

	void calculateJointTransform(void);

    std::vector<Matrix>       _JointPoseTransforms;
    bool                      _NeedRecalc;

    /**************************************************************************//**
     * @fn	void produceChangedEvent(void)
     * 
     * @brief	Tells all of the skeleton's listeners that an event has occurred. 
    *****************************************************************************/
	void produceSkeletonChanged(void);
    /*==========================  PRIVATE  ================================*/

  private:

    Matrixr _invWorld;

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
