/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGFIELDANIMATION_H_
#define _OSGFIELDANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldAnimationBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FieldAnimation class. See \ref
           PageDynamicsFieldAnimation for a description.
*/

class OSG_TBANIMATION_DLLMAPPING FieldAnimation : public FieldAnimationBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum InterpolationType {LINEAR_INTERPOLATION=1, CUBIC_INTERPOLATION=2, STEP_INTERPOLATION=4, LINEAR_NORMAL_INTERPOLATION=8};
    enum ValueReplacementPolicy {OVERWRITE=1, ADDITIVE_ABSOLUTE=2, ADDITIVE_SINCE_LAST=4};

    typedef FieldAnimationBase Inherited;
    typedef FieldAnimation     Self;

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

	void setAnimatedField(FieldContainerUnrecPtr TheContainer, const std::string& FieldName);
	void setAnimatedField(FieldContainerUnrecPtr TheContainer, UInt32 FieldID);
    
	void setAnimatedMultiField(FieldContainerUnrecPtr TheContainer, const std::string& FieldName, UInt32 Index);
	void setAnimatedMultiField(FieldContainerUnrecPtr TheContainer, UInt32 FieldID, UInt32 Index);

    virtual Real32 getUnclippedCycleLength(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FieldAnimationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldAnimation(void);
    FieldAnimation(const FieldAnimation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldAnimation(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    virtual void internalUpdate(Real32 t, const Real32 prev_t);

    void updateAttachedContainer(std::string FieldName);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldAnimationBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FieldAnimation &source);
};

typedef FieldAnimation *FieldAnimationP;

OSG_END_NAMESPACE

#include "OSGAnimator.h"

#include "OSGFieldAnimationBase.inl"
#include "OSGFieldAnimation.inl"

#endif /* _OSGFIELDANIMATION_H_ */
