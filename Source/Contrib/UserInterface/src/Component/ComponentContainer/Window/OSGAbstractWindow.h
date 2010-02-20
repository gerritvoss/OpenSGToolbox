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

#ifndef _OSGABSTRACTWINDOW_H_
#define _OSGABSTRACTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractWindowBase.h"

#include "OSGMouseAdapter.h"
#include "OSGMouseMotionAdapter.h"
#include "OSGKeyAdapter.h"

#include "OSGWindowListener.h"

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractWindow class. See \ref
           PageContribUserInterfaceAbstractWindow for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractWindow : public AbstractWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractWindowBase Inherited;
    typedef AbstractWindow     Self;

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

    EventConnection addWindowListener(WindowListenerPtr Listener);
	bool isWindowListenerAttached(WindowListenerPtr Listener) const;
    void removeWindowListener(WindowListenerPtr Listener);

	virtual bool isAlignableInDrawingSurface(void) const;
	virtual bool isScalableInDrawingSurface(void) const;
	
    virtual void updateContainerLayout(void);
	virtual void updateClipBounds(void);
	
    virtual void mouseEntered(const MouseEventUnrecPtr e);
    virtual void mouseExited(const MouseEventUnrecPtr e);

	//Focus Events
	virtual void focusGained(const FocusEventUnrecPtr e);
	virtual void focusLost(const FocusEventUnrecPtr e);

	void vetoWindowClose(void);

	virtual void open(void) = 0;

	virtual void close(void) = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractWindow(void);
    AbstractWindow(const AbstractWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    virtual BorderRefPtr getDrawnBorder(void) const;
    virtual LayerRefPtr getDrawnBackground(void) const;
    virtual LayerRefPtr getDrawnForeground(void) const;
	
	typedef std::set<WindowListenerPtr> WindowListenerSet;
    typedef WindowListenerSet::iterator WindowListenerSetItor;
    typedef WindowListenerSet::const_iterator WindowListenerSetConstItor;
	
    WindowListenerSet       _WindowListeners;
	
    void produceWindowOpened     ( void);
    void produceWindowClosing    ( void);
    void produceWindowClosed     ( void);
    void produceWindowIconified  ( void);
    void produceWindowDeiconified( void);
    void produceWindowActivated  ( void);
    void produceWindowDeactivated( void);
    void produceWindowEntered    ( void);
    void produceWindowExited     ( void);

	bool _VetoWindowClose;

    Pnt2f _PreviousPosition;
    Vec2f _PreviousSize;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractWindow &source);
};

typedef AbstractWindow *AbstractWindowP;

OSG_END_NAMESPACE

#include "OSGUIDrawObjectCanvas.h"
#include "OSGUIDrawingSurface.h"

#include "OSGAbstractWindowBase.inl"
#include "OSGAbstractWindow.inl"

#endif /* _OSGABSTRACTWINDOW_H_ */
