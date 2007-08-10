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

#ifndef _OSGGLUTWINDOWEVENTPRODUCER_H_
#define _OSGGLUTWINDOWEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <map>

#include "OSGGLUTWindowEventProducerBase.h"
#include <OpenSG/OSGGLUTWindow.h>

OSG_BEGIN_NAMESPACE


class OSG_INPUTLIB_DLLMAPPING GLUTWindowEventProducer : public GLUTWindowEventProducerBase
{
  private:

    typedef GLUTWindowEventProducerBase Inherited;

    typedef std::map<Int32, GLUTWindowEventProducerPtr> GLUTWindowToProducerMap;

    static GLUTWindowToProducerMap _GLUTWindowToProducerMap;
    
    static void GLUTWindowEventProducerDisplayFunction(void);
    static void GLUTWindowEventProducerReshapeFunction(int width,int height);
    static void GLUTWindowEventProducerOverlayDisplayFunction(void);
    static void GLUTWindowEventProducerKeyboardFunction(unsigned char key, int x,int y);
    static void GLUTWindowEventProducerKeyboardUpFunction(unsigned char key, int x,int y);
    static void GLUTWindowEventProducerMouseFunction(int button, int state, int x, int y);
    static void GLUTWindowEventProducerMotionFunction(int x, int y);
    static void GLUTWindowEventProducerPassiveMotionFunction(int x, int y);
    static void GLUTWindowEventProducerVisibilityFunction(int state);
    static void GLUTWindowEventProducerEntryFunction(int state);
    static void GLUTWindowEventProducerSpecialFunction(int key, int x, int y);
    static void GLUTWindowEventProducerSpecialUpFunction(int key, int x, int y);
    static void GLUTWindowEventProducerIdleFunction(void);
    static void GLUTWindowEventProducerMenuStatusFunction(int status, int x, int y);

    void glutDisplay(void);
    void glutReshape(Vec2s Size);
    void glutKeyboard(UChar8 key, Pnt2s MousePos);
    void glutKeyboardUp(UChar8 key, Pnt2s MousePos);
    void glutSpecial(UChar8 key, Pnt2s MousePos);
    void glutSpecialUp(UChar8 key, Pnt2s MousePos);
    void glutMouse(Int32 Button, Int32 State, Pnt2s MousePos);
    void glutMotion(Pnt2s MousePos);
    void glutPassiveMotion(Pnt2s MousePos);
    void glutEntry(Int32 State);
    void glutIdle(void);

    static KeyEvent::Key determineKey(UChar8 key);
    static KeyEvent::Key determineSpecialKey(UChar8 key);

    static void WindowEventLoopThread(void* args);
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
    
    virtual bool attachWindow(void);

	virtual UInt32 getKeyModifiers(void) const;
	virtual Pnt2s getMousePosition(void) const;
	
	virtual std::string getClipboard(void) const;

	virtual void putClipboard(const std::string Value);

    virtual void openWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName);
    
    virtual void closeWindow(void);
    
    virtual void draw(void);
    virtual void update(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GLUTWindowEventProducerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GLUTWindowEventProducer(void);
    GLUTWindowEventProducer(const GLUTWindowEventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLUTWindowEventProducer(void); 

    /*! \}                                                                 */
    
	virtual void setCursor(void);
    virtual WindowPtr createWindow(void);
    
    struct WindowEventLoopThreadArguments
    {
        WindowEventLoopThreadArguments(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       GLUTWindowPtr TheWindow,
                       GLUTWindowEventProducerPtr TheEventProducer,
                       Barrier *syncBarrier);

        Pnt2s _ScreenPosition;
        Vec2s _Size;
        std::string _WindowName;
        GLUTWindowPtr _Window;
        GLUTWindowEventProducerPtr _EventProducer;
        Barrier *_SyncBarrier;
    };
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GLUTWindowEventProducerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GLUTWindowEventProducer &source);
};

typedef GLUTWindowEventProducer *GLUTWindowEventProducerP;

OSG_END_NAMESPACE

#include "OSGGLUTWindowEventProducerBase.inl"
#include "OSGGLUTWindowEventProducer.inl"

#define OSGGLUTWINDOWEVENTPRODUCER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGLUTWINDOWEVENTPRODUCER_H_ */
