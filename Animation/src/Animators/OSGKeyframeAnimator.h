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

#ifndef _OSGKEYFRAMEANIMATOR_H_
#define _OSGKEYFRAMEANIMATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <map>

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeAnimatorBase.h"
#include <OpenSG/Toolbox/OSGInterpolations.h>
#include "KeyframeSequence/OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyframeAnimator class. See \ref 
           PageSystemKeyframeAnimator for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING KeyframeAnimator : public KeyframeAnimatorBase
{
  private:

    typedef KeyframeAnimatorBase Inherited;

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
    
    bool animate(const osg::InterpolationType& InterpType,
                 const osg::ValueReplacementPolicy& ReplacementPolicy,
                 const osg::UInt32& Cycling,
                 const osg::Real32& Time,
                 const osg::Real32& PrevTime,
                 osg::Field& Result);
    
    virtual UInt32 numCyclesCompleted(const Real32& Time) const;
    
    virtual Real32 getLength(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in KeyframeAnimatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyframeAnimator(void);
    KeyframeAnimator(const KeyframeAnimator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyframeAnimator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
    
    
    
  private:

    friend class FieldContainer;
    friend class KeyframeAnimatorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const KeyframeAnimator &source);
};

typedef KeyframeAnimator *KeyframeAnimatorP;

OSG_END_NAMESPACE

#include "OSGKeyframeAnimatorBase.inl"
#include "OSGKeyframeAnimator.inl"

#define OSGKEYFRAMEANIMATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGKEYFRAMEANIMATOR_H_ */
