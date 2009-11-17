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

#ifndef _OSGANIMATIONGROUP_H_
#define _OSGANIMATIONGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAnimationGroupBase.h"
#include "Animations/Advancers/OSGAnimationAdvancer.h"
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AnimationGroup class. See \ref 
           PageAnimationAnimationGroup for a description.
*/

class OSG_ANIMATIONLIB_DLLMAPPING AnimationGroup : public AnimationGroupBase, public EventListener
{
  private:

    typedef AnimationGroupBase Inherited;

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
    virtual bool update(const AnimationAdvancerPtr& advancer);
    virtual bool update(const Time& ElapsedTime);
    
    virtual void start(const Time& StartTime=0.0f);
    virtual void seek(const Time& SeekTime);
    virtual void pause(bool ShouldPause);
    virtual bool isPaused(void) const;
    virtual bool isPlaying(void) const;
    virtual void stop(bool DisconnectFromEventProducer = true);

    virtual Real32 getLength(void) const;

    void attachUpdateProducer(EventProducerPtr TheProducer);
    virtual void eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId);
    void detachUpdateProducer(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AnimationGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AnimationGroup(void);
    AnimationGroup(const AnimationGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AnimationGroup(void); 

    void produceAnimationsStarted(void);
    void produceAnimationsStopped(void);
    void produceAnimationsPaused(void);
    void produceAnimationsUnpaused(void);
    void produceAnimationsEnded(void);
    void produceAnimationsCycled(void);

    Time _CurrentTime,_PrevTime;
    bool _IsPlaying,_IsPaused;

    EventConnection _UpdateEventConnection;
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AnimationGroupBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AnimationGroup &source);
};

typedef AnimationGroup *AnimationGroupP;

OSG_END_NAMESPACE

#include "OSGAnimationGroupBase.inl"
#include "OSGAnimationGroup.inl"

#endif /* _OSGANIMATIONGROUP_H_ */
