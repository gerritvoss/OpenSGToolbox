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

#ifndef _OSGANIMATION_H_
#define _OSGANIMATION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAnimationBase.h"

//#include "OSGAnimationAdvancer.h"
#include "OSGAnimationListener.h"
#include <set>
#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief Animation class. See \ref
           PageDynamicsAnimation for a description.
*/

class OSG_DYNAMICS_DLLMAPPING Animation : public AnimationBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AnimationBase Inherited;
    typedef Animation     Self;

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
    //virtual bool update(const AnimationAdvancerPtr& advancer);
    virtual bool update(const Time& ElapsedTime);
    
    virtual void start(const Time& StartTime=0.0f);
    virtual void seek(const Time& SeekTime);
    virtual void pause(bool ShouldPause);
    virtual bool isPaused(void) const;
    virtual bool isPlaying(void) const;
    virtual void stop(bool DisconnectFromEventProducer = true);

    EventConnection addAnimationListener(AnimationListenerPtr Listener);
    bool isAnimationListenerAttached(AnimationListenerPtr Listener) const;

    void removeAnimationListener(AnimationListenerPtr Listener);

    virtual Real32 getLength(void) const;
    virtual Real32 getCycleLength(void) const = 0;

    void attachUpdateProducer(EventProducerPtr TheProducer);
    void detachUpdateProducer(void);
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
   void produceAnimationStarted(void);
   void produceAnimationStopped(void);
   void produceAnimationPaused(void);
   void produceAnimationUnpaused(void);
   void produceAnimationEnded(void);
   void produceAnimationCycled(void);

    virtual void internalUpdate(const Real32& t, const Real32 prev_t)=0;

    class UpdateHandler : public EventListener
    {
        public:
            UpdateHandler(AnimationRefPtr TheAnimation);

            virtual void eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId);
        private:
            AnimationRefPtr _AttachedAnimation;
    };

    UpdateHandler _UpdateHandler;
    EventConnection _UpdateEventConnection;
    /*==========================  PRIVATE  ================================*/

  private:

	typedef std::set<AnimationListenerPtr> AnimationListenerSet;
    typedef AnimationListenerSet::iterator AnimationListenerSetItor;
    typedef AnimationListenerSet::const_iterator AnimationListenerSetConstItor;
	
    AnimationListenerSet       _AnimationListeners;
    Time _CurrentTime,_PrevTime;
    bool _IsPlaying,_IsPaused;

    friend class FieldContainer;
    friend class AnimationBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Animation &source);
};

typedef Animation *AnimationP;

OSG_END_NAMESPACE

#include "OSGAnimationBase.inl"
#include "OSGAnimation.inl"

#endif /* _OSGANIMATION_H_ */
