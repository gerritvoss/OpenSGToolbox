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

#ifndef _OSGUIDRAWINGSURFACE_H_
#define _OSGUIDRAWINGSURFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGUIDrawingSurfaceBase.h"


#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseWheelListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief UIDrawingSurface class. See \ref 
           PageUserInterfaceUIDrawingSurface for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING UIDrawingSurface : public UIDrawingSurfaceBase,
	public MouseListener,
	public KeyListener,
	public MouseWheelListener,
	public MouseMotionListener
{
  private:

    typedef UIDrawingSurfaceBase Inherited;

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


    void detachFromEventProducer(void);

	//Mouse Events
    virtual void mouseClicked(const MouseEventPtr e);
    virtual void mouseEntered(const MouseEventPtr e);
    virtual void mouseExited(const MouseEventPtr e);
    virtual void mousePressed(const MouseEventPtr e);
    virtual void mouseReleased(const MouseEventPtr e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEventPtr e);
    virtual void mouseDragged(const MouseEventPtr e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventPtr e);

	//Key Events
	virtual void keyPressed(const KeyEventPtr e);
	virtual void keyReleased(const KeyEventPtr e);
	virtual void keyTyped(const KeyEventPtr e);

    virtual Pnt2f getMousePosition(void) const;

	virtual UInt32 getNumWindowLayers(void) const;
	virtual Int32 getWindowLayer(InternalWindowPtr TheWindow) const;
	virtual InternalWindowPtr getWindowAtLayer(const UInt32& Layer) const;
	virtual void setWindowToLayer(InternalWindowPtr TheWindow, const UInt32& Layer);
	virtual void moveWindowUp(InternalWindowPtr TheWindow);
	virtual void moveWindowDown(InternalWindowPtr TheWindow);
	virtual void moveWindowToTop(InternalWindowPtr TheWindow);
	virtual void moveWindowToBottom(InternalWindowPtr TheWindow);

	virtual void openWindow(InternalWindowPtr TheWindow, const Int32 Layer = -1);
	virtual void closeWindow(InternalWindowPtr TheWindow);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in UIDrawingSurfaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIDrawingSurface(void);
    UIDrawingSurface(const UIDrawingSurface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIDrawingSurface(void); 

    /*! \}                                                                 */

    EventConnection   _MouseEventConnection,
                      _MouseMotionEventConnection,
                      _MouseWheelEventConnection,
                      _KeyEventConnection;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class UIDrawingSurfaceBase;

    static void initMethod(void);

	void checkMouseEnterExit(const InputEventPtr e, const Pnt2f& MouseLocation, ViewportPtr TheViewport);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const UIDrawingSurface &source);
	
};

typedef UIDrawingSurface *UIDrawingSurfaceP;

OSG_END_NAMESPACE

#include "OSGUIDrawingSurfaceBase.inl"
#include "OSGUIDrawingSurface.inl"

#define OSGUIDRAWINGSURFACE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGUIDRAWINGSURFACE_H_ */
