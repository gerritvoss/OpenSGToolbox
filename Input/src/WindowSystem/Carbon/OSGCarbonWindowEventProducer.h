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

#ifndef _OSGCARBONWINDOWEVENTPRODUCER_H_
#define _OSGCARBONWINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "OSGCarbonWindowEventProducerBase.h"
#include <OpenSG/OSGCarbonWindow.h>
#include <AGL/agl.h>

#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief CarbonWindowEventProducer class. See \ref 
           PageInputCarbonWindowEventProducer for a description.
*/

class OSG_INPUTLIB_DLLMAPPING CarbonWindowEventProducer : public CarbonWindowEventProducerBase
{
  private:

    typedef CarbonWindowEventProducerBase Inherited;
	
    typedef std::map<UInt32, CarbonWindowEventProducerPtr> CarbonWindowToProducerMap;    
    
	static CarbonWindowToProducerMap _CarbonWindowToProducerMap;
	
	
    static pascal OSStatus eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData);
    
	OSStatus internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData);
	
	UInt32 _WindowId;
	
	static UInt32 getUndefinedWindowId(void);
	
    static void WindowEventLoopThread(void* args);
	
    struct WindowEventLoopThreadArguments
    {
        WindowEventLoopThreadArguments(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       CarbonWindowPtr TheWindow,
                       CarbonWindowEventProducerPtr TheEventProducer);

        Pnt2s _ScreenPosition;
        Vec2s _Size;
        std::string _WindowName;
        CarbonWindowPtr _Window;
        CarbonWindowEventProducerPtr _EventProducer;
    };
	
	friend struct WindowEventLoopThreadArguments;

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
	
	
    //Set the Window Position
    virtual void setPosition(Pnt2s Pos);
    //Set the Window Position
    virtual Pnt2s getPosition(void) const;

    //Set the Window size
    virtual void setSize(Vec2us Size);

    //Get the Window size
    virtual Vec2s getSize(void) const;

    //Focused
    //Set the Window Focus
    virtual void setFocused(bool Focused);

    //Get the Window Focus
    virtual bool getFocused(void) const;

    //Visible / Iconify / Normal
    //Set the Window Visible
    virtual void setVisible(bool Visible);

    //Get the Window Visible
    virtual bool getVisible(void) const;

    //Set the Window Iconify
    virtual void setIconify(bool Iconify);

    //Get the Window Iconify
    virtual bool getIconify(void) const;

    //Fullscreen
    virtual void setFullscreen(bool Fullscreen);

    //Get the Window Fullscreen
    virtual bool getFullscreen(void) const;

    //Set the text on the Title bar of the window
    virtual void setTitle(const std::string& TitleText);

    //Get the text of the Title bar of the window
    virtual std::string getTitle(void);

    //Set the window to allow or not allow Resizing
    virtual void setRisizable(bool IsResizable);

    //Get whether or not the window allows resizing
    virtual bool getRisizable(void);

    //Set the window to draw or not draw it's border
    virtual void setDrawBorder(bool DrawBorder);

    //Get wether or not the window is drawing a border
    virtual bool getDrawBorder(void);
	

    virtual void draw(void);
    virtual void update(void);

    virtual bool attachWindow(void);

	virtual UInt32 getKeyModifiers(void) const;
    
	virtual Pnt2s getMousePosition(void) const;
	

	virtual std::string getClipboard(void) const;

	virtual void putClipboard(const std::string Value);
	
    virtual void openWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CarbonWindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CarbonWindowEventProducer(void);
    CarbonWindowEventProducer(const CarbonWindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CarbonWindowEventProducer(void); 

    /*! \}                                                                 */
	
	virtual void setCursor(void);
    virtual WindowPtr createWindow(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CarbonWindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CarbonWindowEventProducer &source);
};

typedef CarbonWindowEventProducer *CarbonWindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGCarbonWindowEventProducerBase.inl"
#include "OSGCarbonWindowEventProducer.inl"

#define OSGCARBONWINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCARBONWINDOWEVENTPRODUCER_H_ */
