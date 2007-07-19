/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGCOMPONENT_H_
#define _OSGCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComponentBase.h"
#include "Graphics/OSGGraphics.h"

#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseWheelListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>

#include <set>

//#include <OpenSG/Input/OSGKeyEventProducer.h>
//#include <OpenSG/Input/OSGMouseEventProducer.h>
//#include <OpenSG/Input/OSGMouseWheelEventProducer.h>
//#include <OpenSG/Input/OSGMouseMotionEventProducer.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Component : public ComponentBase
{
  private:

    typedef ComponentBase Inherited;

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
	virtual void draw(const GraphicsPtr Graphics) const;

    virtual void getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const;
	virtual void getClipBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const;
    virtual void getInsideBorderBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const;
    virtual void getBoundsRenderingSurfaceSpace(Pnt2s& TopLeft, Pnt2s& BottomRight) const;
    virtual void updateContainerLayout(void);
	virtual void updateClipBounds(void);
	
	//Mouse Events
    virtual void mouseClicked(const MouseEvent& e);
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

	//Mouse Motion Events
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);

	//Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEvent& e);

	//Key Events
	virtual void keyPressed(const KeyEvent& e);
	virtual void keyReleased(const KeyEvent& e);
	virtual void keyTyped(const KeyEvent& e);
	
    void addMouseMotionListener(MouseMotionListenerPtr Listener);
    void removeMouseMotionListener(MouseMotionListenerPtr Listener);
    void addMouseWheelListener(MouseWheelListenerPtr Listener);
    void removeMouseWheelListener(MouseWheelListenerPtr Listener);
    void addMouseListener(MouseListenerPtr Listener);
    void removeMouseListener(MouseListenerPtr Listener);
    void addKeyListener(KeyListenerPtr Listener);
    void removeKeyListener(KeyListenerPtr Listener);

	void setMouseContained(bool Value);
	bool getMouseContained(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Component(void);
    Component(const Component &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Component(void); 

    /*! \}                                                                 */

    virtual void drawBorder(const GraphicsPtr TheGraphics) const;
    virtual void drawBackground(const GraphicsPtr TheGraphics) const;
    
	virtual void drawInternal(const GraphicsPtr Graphics) const = 0;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComponentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Component &source);
	
	typedef std::set<MouseMotionListenerPtr> MouseMotionListenerSet;
    typedef MouseMotionListenerSet::iterator MouseMotionListenerSetItor;
    typedef MouseMotionListenerSet::const_iterator MouseMotionListenerSetConstItor;
	
    MouseMotionListenerSet       _MouseMotionListeners;
	
    virtual void produceMouseMoved(const MouseEvent& e);
    virtual void produceMouseDragged(const MouseEvent& e);

	typedef std::set<MouseWheelListenerPtr> MouseWheelListenerSet;
    typedef MouseWheelListenerSet::iterator MouseWheelListenerSetItor;
    typedef MouseWheelListenerSet::const_iterator MouseWheelListenerSetConstItor;
	
    MouseWheelListenerSet       _MouseWheelListeners;
	
    void produceMouseWheelMoved(const MouseWheelEvent& e);
	
	typedef std::set<MouseListenerPtr> MouseListenerSet;
    typedef MouseListenerSet::iterator MouseListenerSetItor;
    typedef MouseListenerSet::const_iterator MouseListenerSetConstItor;
	
    MouseListenerSet       _MouseListeners;
	
    void produceMouseClicked(const MouseEvent& e);
    void produceMouseEntered(const MouseEvent& e);
    void produceMouseExited(const MouseEvent& e);
    void produceMousePressed(const MouseEvent& e);
    void produceMouseReleased(const MouseEvent& e);
	
	typedef std::set<KeyListenerPtr> KeyListenerSet;
    typedef KeyListenerSet::iterator KeyListenerSetItor;
    typedef KeyListenerSet::const_iterator KeyListenerSetConstItor;
	
    KeyListenerSet       _KeyListeners;
	
    void produceKeyPressed(const KeyEvent& e);
    void produceKeyReleased(const KeyEvent& e);
    void produceKeyTyped(const KeyEvent& e);
	
	bool _MouseInComponentLastMouse;
};

typedef Component *ComponentP;

OSG_END_NAMESPACE

#include "OSGComponentBase.inl"
#include "OSGComponent.inl"

#define OSGCOMPONENT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMPONENT_H_ */
