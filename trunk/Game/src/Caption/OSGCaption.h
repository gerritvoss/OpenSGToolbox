/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include "OSGCaptionBase.h"
#include "Event/OSGCaptionListener.h"
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>

#include <OpenSG/Input/OSGEventConnection.h>
#include <OpenSG/Input/OSGWindowUtils.h>
#include "OSGDefaultCaptionComponentGenerator.h"

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

    void captionSegment(std::string s, Real32 start, Real32 end);
    void setCaptionDialog(SoundPtr sound);

    EventConnection addCaptionListener(CaptionListenerPtr Listener);
	bool isCaptionListenerAttached(CaptionListenerPtr Listener) const;
    void removeCaptionListener(CaptionListenerPtr Listener);
    void attachWindowEventProducer(WindowEventProducerPtr TheEventProducer);
    void setupCaption();
    void start();
    void stop();
    void pause();


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
    Real32 _timeStamp;

    virtual ~Caption(void); 

    virtual void actionPreformed(const CaptionEvent& e);

    /*! \}                                                                 */

    typedef std::set<CaptionListenerPtr> CaptionListenerSet;
    typedef CaptionListenerSet::iterator CaptionListenerSetItor;
    typedef CaptionListenerSet::const_iterator CaptionListenerSetConstItor;
    
    void update(const UpdateEvent& e);

    class CaptionListener : public UpdateListener
	{
	public :
		CaptionListener(CaptionPtr TheCaption);
		
		virtual void update(const UpdateEvent& e);
	protected :
		CaptionPtr _Caption;
	};

    CaptionListenerSet       _CaptionListeners;

    CaptionListener          _CaptionListener;

    virtual void produceSegmentActivated(const CaptionEvent& e);
    virtual void produceCaptionStarted(const CaptionEvent& e);
    virtual void produceCaptionEnded(const CaptionEvent& e);


    
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
