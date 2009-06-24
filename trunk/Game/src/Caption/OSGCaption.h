/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Game                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, Eric Langkamp                    *
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

#ifndef _OSGCAPTION_H_
#define _OSGCAPTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGCaptionBase.h"
#include "Event/OSGCaptionListener.h"
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>

#include <OpenSG/Input/OSGEventConnection.h>
#include <OpenSG/Input/OSGWindowUtils.h>
#include "OSGDefaultCaptionComponentGenerator.h"
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundManager.h>

#include <set>


OSG_BEGIN_NAMESPACE

/*! \brief Caption class. See \ref 
           PageGameCaption for a description.
*/

class OSG_GAMELIB_DLLMAPPING Caption : public CaptionBase
{
  private:

    typedef CaptionBase Inherited;

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
     * @fn	void captionSegment(std::string s, Real32 start, Real32 end)
     * 
     * @brief	Adds a segment of text to the caption object with a given start and end.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	s		The string to be added to the caption object. 
     * @param	start	The time in which string s should start being displayed(in seconds). 
     * @param	end		The time in which string s should stop being displayed(in seconds). 
     *****************************************************************************/
    void captionSegment(std::string s, Real32 start, Real32 end);

    /**************************************************************************//**
     * @fn	EventConnection addCaptionListener(CaptionListenerPtr Listener)
     * 
     * @brief	Simply adds a caption listener to the given caption object.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The pointer of the caption listener to be add. 
     * 
     * @return	. 
     *****************************************************************************/
    EventConnection addCaptionListener(CaptionListenerPtr Listener);

	/**************************************************************************//**
	 * @fn	bool isCaptionListenerAttached(CaptionListenerPtr Listener) const
	 * 
	 * @brief	Verifies whether or not a given CaptionListener is attached.
	 * 
	 * @author	Langkamp. 
	 * @date	6/24/2009. 
	 * 
	 * @param	Listener	The CaptionListenerPtr to be verified. 
	 * 
	 * @return	returns true if the listener given is attached. 
	 *****************************************************************************/
	bool isCaptionListenerAttached(CaptionListenerPtr Listener) const;

    /**************************************************************************//**
     * @fn	void removeCaptionListener(CaptionListenerPtr Listener)
     * 
     * @brief	Removes a given Caption Listener.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The CaptionListnerPtr of the Caption Listener to be removed. 
     *****************************************************************************/
    void removeCaptionListener(CaptionListenerPtr Listener);

    /**************************************************************************//**
     * @fn	void attachWindowEventProducer(WindowEventProducerPtr TheEventProducer)
     * 
     * 
     * @brief	Adds a window event producer to handle the events the caption object gives off.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	TheEventProducer	The Event Producer to be add. 
     *****************************************************************************/
    void attachWindowEventProducer(WindowEventProducerPtr TheEventProducer);

    /**************************************************************************//**
     * @fn	void setupCaption()
     * 
     * @brief	Helper method for internal functions with the caption object.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void setupCaption();

    /**************************************************************************//**
     * @fn	void stop()
     * 
     * @brief	Helper method to stop the caption when the sound is stoped.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void stop();

    /**************************************************************************//**
     * @fn	void pause()
     * 
     * @brief	Helper method to pause the caption when the sound is paused.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void pause();
    void attachSoundListener();


    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CaptionBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Caption(void);
    Caption(const Caption &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    bool _start;
    bool _captionEndedCheck;

    virtual ~Caption(void); 

    virtual void actionPreformed(const CaptionEvent& e);

    /*! \}                                                                 */

    typedef std::set<CaptionListenerPtr> CaptionListenerSet;
    typedef CaptionListenerSet::iterator CaptionListenerSetItor;
    typedef CaptionListenerSet::const_iterator CaptionListenerSetConstItor;
    
    void update(const UpdateEvent& e);

    class CaptionListener : public UpdateListener, public SoundListener
	{
	public :
		CaptionListener(CaptionPtr TheCaption);
		
		virtual void update(const UpdateEvent& e);
        virtual void soundPlayed(const SoundEvent& e);

        virtual void soundStopped(const SoundEvent& e);

        virtual void soundPaused(const SoundEvent& e);

        virtual void soundUnpaused(const SoundEvent& e);

        virtual void soundLooped(const SoundEvent& e);

        virtual void soundEnded(const SoundEvent& e);
	protected :
		CaptionPtr _Caption;
	};

    CaptionListenerSet       _CaptionListeners;

    CaptionListener          _CaptionListener;

    virtual void produceSegmentActivated(const CaptionEvent& e);
    virtual void produceCaptionStarted(const CaptionEvent& e);
    virtual void produceCaptionEnded(const CaptionEvent& e);
    
    void start(UInt32 SoundChannelID);
    UInt32 _SoundChannelID;


    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CaptionBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Caption &source);

    
};

typedef Caption *CaptionP;

OSG_END_NAMESPACE

#include "OSGCaptionBase.inl"
#include "OSGCaption.inl"

#define OSGCAPTION_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCAPTION_H_ */
