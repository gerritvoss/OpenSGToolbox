/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGXWINDOWEVENTPRODUCER_H_
#define _OSGXWINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#ifdef __linux

#include "OSGXWindowEventProducerBase.h"
#include <OpenSG/OSGXWindow.h>
#include <OpenSG/OSGThreadManager.h>

OSG_BEGIN_NAMESPACE

/*! \brief XWindowEventProducer class. See \ref 
           PageInputXWindowEventProducer for a description.
*/

class OSG_INPUTLIB_DLLMAPPING XWindowEventProducer : public XWindowEventProducerBase
{
  private:

    typedef XWindowEventProducerBase Inherited;

    static int wait_for_map_notify(Display *, XEvent *event, char *arg);
    static KeyEvent::Key determineKey(const KeySym& XKeySym);
    
    static UInt32 determineKeyModifiers(const unsigned int state);
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

    virtual void dump(      UInt32     uiIndent, 
                      const BitVector  bvFlags ) const;
    
	virtual WindowPtr initWindow(void);

    virtual bool attachWindow(void);

    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
	
    virtual void mainLoop(void);

    //Set the Window Position
    virtual void setPosition(Pnt2f Pos);
    //Set the Window Position
    virtual Pnt2f getPosition(void) const;

    //Set the Window size
    virtual void setSize(Vec2us Size);

    //Get the Window size
    virtual Vec2f getSize(void) const;

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

    virtual void setShowCursor(bool showCursor);

    virtual bool getShowCursor(void) const;

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
    
	 virtual UInt32 getKeyModifiers(void) const;
     
	virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const;
    
	 virtual Pnt2f getMousePosition(void) const;
    
	 virtual std::string getClipboard(void) const;

	 virtual void putClipboard(const std::string Value);
    
    void handleEvent(XEvent& Event);
    
    
    virtual void draw(void);
    virtual void update(void);
    
    virtual Vec2f getDesktopSize(void) const;

	virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect);

    virtual Path saveFileDialog(const std::string& DialogTitle,
                    const std::vector<FileDialogFilter>& Filters,
                    const std::string& InitialFile,
                    const Path& InitialDirectory,
                    bool PromptForOverwrite
                    );
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in XWindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    XWindowEventProducer(void);
    XWindowEventProducer(const XWindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~XWindowEventProducer(void); 

	 virtual void setCursor(void);
    
    virtual WindowPtr createWindow(void);
    
    unsigned int _LastKeyboardMouseButtonMask;
    Pnt2f _LastMousePosition;
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class XWindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const XWindowEventProducer &source);
};

typedef XWindowEventProducer *XWindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGXWindowEventProducerBase.inl"
#include "OSGXWindowEventProducer.inl"

#define OSGXWINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif

#endif /* _OSGXWINDOWEVENTPRODUCER_H_ */


