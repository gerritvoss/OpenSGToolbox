/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

    void addChild(BonePtr TheBone);
    void removeChild(BonePtr TheBone);
    void removeChild(UInt32 Index);
    UInt32 getNumChildren(void) const;
    BonePtr getChild(UInt32 Index) const;

    BonePtr getParent(void) const;
    const Matrix              &getRelativeTransformation(void) const;
    const Matrix              &getAbsoluteTransformation(void) const;//get the absolute transformation of a parent


    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in BoneBase.

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

	void updateTransformation(void);
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
