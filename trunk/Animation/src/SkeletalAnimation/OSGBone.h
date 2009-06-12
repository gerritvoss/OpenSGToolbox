/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, John Morales                     *
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

#ifndef _OSGBONE_H_
#define _OSGBONE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGBoneBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Bone class. See \ref 
           PageAnimationBone for a description.
*/

/**************************************************************************//**
 * @class	OSG_ANIMATIONLIB_DLLMAPPING Bone : public BoneBase
 * 
 * @brief	Osg animationlib dllmapping. 
 * 
 * @author	Dtnaylor
 * @date	6/10/2009
*****************************************************************************/
class OSG_ANIMATIONLIB_DLLMAPPING Bone : public BoneBase
{
  private:

    typedef BoneBase Inherited;

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

    /**************************************************************************//**
     * @fn	void addChild(BonePtr TheBone)
     * 
     * @brief	Adds a child to the bone. 
     * 
     * @param	TheBone	the bone. 
    *****************************************************************************/
    void addChild(BonePtr TheBone);

    /**************************************************************************//**
     * @fn	void removeChild(BonePtr TheBone)
     * 
     * @brief	Removes a child from the bone. 
     * 
     * @param	TheBone	The bone to remove. 
    *****************************************************************************/
    void removeChild(BonePtr TheBone);

    /**************************************************************************//**
     * @fn	void removeChild(UInt32 Index)
     * 
     * @brief	Removes a child from the bone. 
     * 
     * @param	Index	Zero-based index of the bone to remove. 
    *****************************************************************************/
    void removeChild(UInt32 Index);

	/**************************************************************************//**
	 * @fn	void setBindPosition()
	 * 
	 * @brief	Sets the bone's current position as its bind (default) position. 
	*****************************************************************************/
	void setBindPosition();

    /**************************************************************************//**
     * @fn	UInt32 getNumChildren(void) const
     * 
     * @brief	Gets the number of children of the bone. 
     * 
     * @return	The number children. 
    *****************************************************************************/
    UInt32 getNumChildren(void) const;

    /**************************************************************************//**
     * @fn	BonePtr getChild(UInt32 Index) const
     * 
     * @brief	Gets a child of the bone. 
     * 
     * @param	Index	Zero-based index of the child. 
     * 
     * @return	The child. 
    *****************************************************************************/
    BonePtr getChild(UInt32 Index) const;

	Matrix getInternalRelativeTransformation(void);
	Matrix getInternalAbsoluteTransformation(void);
	Matrix getInternalDefaultRelativeTransformation(void);
	Matrix getInternalDefaultAbsoluteTransformation(void);
	Matrix getInternalRelativeDifferenceTransformation(void);
	Matrix getInternalAbsoluteDifferenceTransformation(UInt32 BlendMode);
	Matrix getEndInternalRelativeDifferenceTransformation(void);
	Matrix getEndInternalAbsoluteDifferenceTransformation(void);

    BonePtr getParent(void) const;
    const Matrix              &getRelativeTransformation(void) const;
    const Matrix              &getAbsoluteTransformation(void) const;//get the absolute transformation of a parent


    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in BoneBase.
	
	Matrix _InternalRelativeTransformation;
	Matrix _InternalAbsoluteTransformation;
	Matrix _InternalDefaultRelativeTransformation;
	Matrix _InternalDefaultAbsoluteTransformation;
	Matrix _InternalRelativeDifferenceTransformation;
	Matrix _InternalAbsoluteDifferenceTransformation;


    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Bone(void);
    Bone(const Bone &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Bone(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/

	/**************************************************************************//**
	 * @fn	void updateTransformation(bool IsRecursiveUpdate)
	 * 
	 * @brief	Updates the transformation described by IsRecursiveUpdate. 
	 * 
	 * @param	IsRecursiveUpdate	true if is recursive update. 
	*****************************************************************************/
	void updateTransformation(bool IsRecursiveUpdate);

	/**************************************************************************//**
	 * @fn	void calculateRelativeTransformation(bool isDefault)
	 * 
	 * @brief	Calculates the relative transformation. 
	 * 
	 * @param	isDefault	true if is default. 
	*****************************************************************************/
	void calculateRelativeTransformation(bool isDefault);
	void calculateAbsoluteTransformation(bool isDefault);
	void calculateDifferenceTransformations(void);

  private:

    friend class FieldContainer;
    friend class BoneBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Bone &source);
};

typedef Bone *BoneP;

OSG_END_NAMESPACE

#include "OSGBoneBase.inl"
#include "OSGBone.inl"

#define OSGBONE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGBONE_H_ */
