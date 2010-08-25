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

#ifndef _OSGANIMATIONEVENTDETAILS_H_
#define _OSGANIMATIONEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimationEventDetails class. See \ref
           PageDynamicsAnimationEventDetails for a description.
*/

class OSG_TBANIMATION_DLLMAPPING AnimationEventDetails : public AnimationEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimationEventDetailsBase Inherited;
    typedef AnimationEventDetails     Self;

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

    static  AnimationEventDetailsTransitPtr      create( FieldContainer* const Source,
                                                         Time TimeStamp); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AnimationEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationEventDetails(void);
    AnimationEventDetails(const AnimationEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AnimationEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AnimationEventDetails &source);
};

typedef AnimationEventDetails *AnimationEventDetailsP;

OSG_END_NAMESPACE

#include "OSGAnimationEventDetailsBase.inl"
#include "OSGAnimationEventDetails.inl"

#endif /* _OSGANIMATIONEVENTDETAILS_H_ */
