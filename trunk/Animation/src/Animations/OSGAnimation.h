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
/*---------------------------------------------------------------------------*\``
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

#ifndef _OSGANIMATION_H_
#define _OSGANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGAnimationBase.h"
#include "Animations/Advancers/OSGAnimationAdvancer.h"
#include "Events/OSGAnimationListener.h"
#include <set>
#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief Animation class. See \ref 
           PageSystemAnimation for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING Animation : public AnimationBase
{
  private:

    typedef AnimationBase Inherited;

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
    
    virtual void start(void);

    virtual void pause(void);
    virtual void unpause(void);
    virtual void pauseToggle(void);
    virtual bool isPaused(void);
    virtual bool isRunning(void);
    
    virtual void stop(void);
    
    virtual bool update(const AnimationAdvancerPtr& advancer);

    EventConnection addAnimationListener(AnimationListenerPtr Listener);
    bool isAnimationListenerAttached(AnimationListenerPtr Listener) const;

    void removeAnimationListener(AnimationListenerPtr Listener);

    virtual Real32 getLength(void) const = 0;
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AnimationBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Animation(void);
    Animation(const Animation &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Animation(void); 

    /*! \}                                                                 */
    
   void produceAnimationStarted(void);
   void produceAnimationStopped(void);
   void produceAnimationPaused(void);
   void produceAnimationUnpaused(void);
   void produceAnimationEnded(void);
   void produceAnimationCycled(void);

   bool _IsPaused;
   bool _IsRunning;

    virtual void internalUpdate(const Real32& t, const Real32 prev_t)=0;

    /*==========================  PRIVATE  ================================*/
  private:

	typedef std::set<AnimationListenerPtr> AnimationListenerSet;
    typedef AnimationListenerSet::iterator AnimationListenerSetItor;
    typedef AnimationListenerSet::const_iterator AnimationListenerSetConstItor;
	
    AnimationListenerSet       _AnimationListeners;

    friend class FieldContainer;
    friend class AnimationBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Animation &source);
};

typedef Animation *AnimationP;

OSG_END_NAMESPACE

#include "OSGAnimationBase.inl"
#include "OSGAnimation.inl"

#define OSGANIMATION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGANIMATION_H_ */
