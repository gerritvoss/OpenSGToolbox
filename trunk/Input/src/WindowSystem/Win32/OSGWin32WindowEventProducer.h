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

#ifndef _OSGWIN32WINDOWEVENTPRODUCER_H_
#define _OSGWIN32WINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#ifdef WIN32

#include <map>

#include "OSGWin32WindowEventProducerBase.h"
#include <OpenSG/OSGWin32Window.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING Win32WindowEventProducer : public Win32WindowEventProducerBase
{
  private:

    typedef std::map<HWND, Win32WindowEventProducerPtr> WIN32HWNDToProducerMap;
    typedef Win32WindowEventProducerBase Inherited;
    
    static WIN32HWNDToProducerMap _WIN32HWNDToProducerMap;
    
    LRESULT WndProc(HWND hwnd, UINT uMsg,
                           WPARAM wParam, LPARAM lParam);

    static void WindowEventLoopThread(void* args);
    
    static KeyEvent::Key determineKey(WPARAM key);
    /*==========================  PUBLIC  =================================*/
  public:

    static LRESULT CALLBACK staticWndProc(HWND hwnd, UINT uMsg,
                           WPARAM wParam, LPARAM lParam);
    virtual bool attachWindow(void);

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

    //Get the Window Fullscreen
    virtual bool getFullscreen(void) const;

    virtual void setShowCursor(bool showCursor);

    virtual bool getShowCursor(void) const;
	
	virtual UInt32 getKeyModifiers(void) const;
	virtual KeyEvent::KeyState getKeyState(KeyEvent::Key TheKey) const;
	virtual Pnt2f getMousePosition(void) const;

	virtual std::string getClipboard(void) const;

	virtual void putClipboard(const std::string Value);

    virtual void openWindow(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
    
    virtual void draw(void);
    virtual void update(void);
    
    virtual Vec2f getDesktopSize(void) const;

	virtual std::vector<Path> openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect);

    virtual Path saveFileDialog(const std::string& DialogTitle,
                    const std::vector<FileDialogFilter>& Filters,
                    const Path& InitialFile,
                    const Path& InitialDirectory,
                    bool PromptForOverwrite
                    );
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in Win32WindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Win32WindowEventProducer(void);
    Win32WindowEventProducer(const Win32WindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Win32WindowEventProducer(void); 

    /*! \}                                                                 */
    
	virtual void setCursor(void);
    
    virtual WindowPtr createWindow(void);
    struct WindowEventLoopThreadArguments
    {
        WindowEventLoopThreadArguments(const Pnt2f& ScreenPosition,
                       const Vec2f& Size,
                       const std::string& WindowName,
                       WIN32WindowPtr TheWindow,
                       Win32WindowEventProducerPtr TheEventProducer);

        Pnt2f _ScreenPosition;
        Vec2f _Size;
        std::string _WindowName;
        WIN32WindowPtr _Window;
        Win32WindowEventProducerPtr _EventProducer;
    };

    bool _MouseOverWindow;

    static const UINT WIN32_DRAW_MESSAGE = WM_USER + 1;
    static const UINT WIN32_UPDATE_MESSAGE = WM_USER + 2;

    Pnt2f _PreviousWindowPosition;
    Vec2f _PreviousWindowSize;
    bool _IsFullscreen;
    bool _IsCursorShown;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class Win32WindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Win32WindowEventProducer &source);
};

typedef Win32WindowEventProducer *Win32WindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGWin32WindowEventProducerBase.inl"
#include "OSGWin32WindowEventProducer.inl"

#define OSGWIN32WINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif

#endif /* _OSGWIN32WINDOWEVENTPRODUCER_H_ */


