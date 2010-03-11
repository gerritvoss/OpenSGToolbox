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

#ifndef _OSGJOINT_H_
#define _OSGJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Joint class. See \ref
           PageDynamicsJoint for a description.
*/

class OSG_TBANIMATION_DLLMAPPING Joint : public JointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef JointBase Inherited;
    typedef Joint     Self;

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
	 * @fn	Matrix getAbsoluteTransformation(void) const
	 * 
	 * @brief	Gets the absolute transformation of the joint in its current
	 *			position.
	 * 
	 * @return	The joint's absolute transformation matrix. 
	*****************************************************************************/
	Matrix getAbsoluteTransformation(void) const;

	/**************************************************************************//**
	 * @fn	Matrix getBindAbsoluteTransformation(void) const
	 * 
	 * @brief	Gets the absolute transformation of the joint in its bind
	 *			position. 
	 * 
	 * @return	The joint's bind absolute transformation matrix. 
	*****************************************************************************/
	Matrix getBindAbsoluteTransformation(void) const;

	/**************************************************************************//**
	 * @fn	const Matrix& getAbsoluteDifferenceTransformation(void) const
	 * 
	 * @brief	Gets the transformation representing the difference between the
	 *			joint's current absolute transformation and its bind absolute
	 *			transformation.
	 * 
	 * @return	The absolute difference transformation. 
	*****************************************************************************/
	const Matrix& getAbsoluteDifferenceTransformation(void) const;

	/**************************************************************************//**
	 * @fn	const Matrix& getRelativeDifferenceTransformation(void) const
	 * 
	 * @brief	Gets the transformation representing the difference between the
	 *			joint's current relative transformation and its bind relative
	 *			transformation. 
	 * 
	 * @return	The relative difference transformation. 
	*****************************************************************************/
	const Matrix& getRelativeDifferenceTransformation(void) const;

	/**************************************************************************//**
	 * @fn	void calculateTransformations(void)
	 * 
	 * @brief	Updates the joint's absolute transformation matrix, bind absolute
	 *			transformation matrix, absolute difference matrix, and relative
	 *			difference matrix.
	*****************************************************************************/
	void calculateTransformations(void);

	/**************************************************************************//**
	 * @fn	void updateTransformations(bool isRecursive)
	 * 
	 * @brief	Same as calculateTransformations() only it will also tell its
	 *			children to update. 
	 * 
	 * @param	isRecursive	-- Set to true to tell skeleton about the update.
	*****************************************************************************/
	void updateTransformations(bool isRecursive, bool tellSkeleton = true);

	/**************************************************************************//**
	 * @fn	Matrix previewRelativeDifferenceTransformation(Matrix relativeTransform
	 * 		ation)
	 * 
	 * @brief	Calculates the difference transformation between the joint's
	 *			relative bind transformation and the given transformation.
	 * 
	 * @param	relativeTransformation	The relative transformation. 
	 * 
	 * @return	The calculated difference transformation.
	*****************************************************************************/
	Matrix previewRelativeDifferenceTransformation(Matrix relativeTransformation);

	/**************************************************************************//**
	 * @fn	Matrix previewRelativeTransformation(Matrix relativeDifferenceTransform
	 * 		ation)
	 * 
	 * @brief	Calculates the what the joint's new relative difference
	 *			transformation would be if the given difference transformation
	 *			were applied to it.
	 * 
	 * @param	relativeDifferenceTransformation	The relative difference
	 * 												transformation to apply. 
	 * 
	 * @return	The relative transformation. 
	*****************************************************************************/
	Matrix previewRelativeTransformation(Matrix relativeDifferenceTransformation);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in JointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Joint(void);
    Joint(const Joint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Joint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    Matrix _AbsoluteTransformation;
    Matrix _BindAbsoluteTransformation;
    Matrix _AbsoluteDifferenceTransformation;
    Matrix _RelativeDifferenceTransformation;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class JointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Joint &source);
};

typedef Joint *JointP;

OSG_END_NAMESPACE

#include "OSGJointBase.inl"
#include "OSGJoint.inl"

#endif /* _OSGJOINT_H_ */
