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

#ifndef _OSGANIMATIONACTIVITY_H_
#define _OSGANIMATIONACTIVITY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAnimationActivityBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AnimationActivity class. See \ref 
           PageAnimationAnimationActivity for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING AnimationActivity : public AnimationActivityBase
{
  private:

    typedef AnimationActivityBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
  enum ActivityType{
    ANIMATION_START       = 1,
    ANIMATION_PAUSE       = 2,
    ANIMATION_UNPAUSE     = 3,
    ANIMATION_PAUSETOGGLE = 4,
    ANIMATION_STOP        = 5
  };

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

    virtual void eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AnimationActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationActivity(void);
    AnimationActivity(const AnimationActivity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationActivity(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AnimationActivityBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AnimationActivity &source);
};

typedef AnimationActivity *AnimationActivityP;

OSG_END_NAMESPACE

#include "OSGAnimationActivityBase.inl"
#include "OSGAnimationActivity.inl"

#endif /* _OSGANIMATIONACTIVITY_H_ */
