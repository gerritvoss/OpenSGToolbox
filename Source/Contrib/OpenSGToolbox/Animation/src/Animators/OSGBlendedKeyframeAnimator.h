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

#ifndef _OSGBLENDEDKEYFRAMEANIMATOR_H_
#define _OSGBLENDEDKEYFRAMEANIMATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGBlendedKeyframeAnimatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief BlendedKeyframeAnimator class. See \ref 
           PageAnimationBlendedKeyframeAnimator for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING BlendedKeyframeAnimator : public BlendedKeyframeAnimatorBase
{
  private:

    typedef BlendedKeyframeAnimatorBase Inherited;

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
    virtual bool animate(const osg::InterpolationType& InterpType,
                 const osg::ValueReplacementPolicy& ReplacementPolicy,
                 bool Cycling,
                 const osg::Real32& time,
                 const osg::Real32& prevTime,
                 osg::Field& Result,
                 UInt32 Index = 0);
    
    virtual Real32 getLength(void) const;

    virtual const DataType &getDataType(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in BlendedKeyframeAnimatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BlendedKeyframeAnimator(void);
    BlendedKeyframeAnimator(const BlendedKeyframeAnimator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BlendedKeyframeAnimator(void); 

    /*! \}                                                                 */
    bool checkSequencesValidity(void) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class BlendedKeyframeAnimatorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const BlendedKeyframeAnimator &source);
};

typedef BlendedKeyframeAnimator *BlendedKeyframeAnimatorP;

OSG_END_NAMESPACE

#include "OSGBlendedKeyframeAnimatorBase.inl"
#include "OSGBlendedKeyframeAnimator.inl"

#endif /* _OSGBLENDEDKEYFRAMEANIMATOR_H_ */
