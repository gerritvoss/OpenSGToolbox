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

#ifndef _OSGABSTRACTWINDOW_H_
#define _OSGABSTRACTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractWindowBase.h"

#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGMouseMotionAdapter.h>
#include <OpenSG/Input/OSGKeyAdapter.h>

#include <OpenSG/Input/OSGWindowListener.h>

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractWindow class. See \ref 
           PageUserInterfaceAbstractWindow for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractWindow : public AbstractWindowBase
{
  private:

    typedef AbstractWindowBase Inherited;

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

    EventConnection addWindowListener(WindowListenerPtr Listener);
	bool isWindowListenerAttached(WindowListenerPtr Listener) const;
    void removeWindowListener(WindowListenerPtr Listener);

	virtual bool isAlignableInDrawingSurface(void) const;
	virtual bool isScalableInDrawingSurface(void) const;
	
    virtual void updateContainerLayout(void);
	virtual void updateClipBounds(void);
	
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);

	//Focus Events
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

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
    
    virtual BorderPtr getDrawnBorder(void) const;
    virtual LayerPtr getDrawnBackground(void) const;
    virtual LayerPtr getDrawnForeground(void) const;
	
	typedef std::set<WindowListenerPtr> WindowListenerSet;
    typedef WindowListenerSet::iterator WindowListenerSetItor;
    typedef WindowListenerSet::const_iterator WindowListenerSetConstItor;
	
    WindowListenerSet       _WindowListeners;
	
    void produceWindowOpened(void);
    void produceWindowClosing(void);
    void produceWindowClosed(void);
    void produceWindowIconified(void);
    void produceWindowDeiconified(void);
    void produceWindowActivated(void);
    void produceWindowDeactivated(void);
    void produceWindowEntered(void);
    void produceWindowExited(void);

	bool _VetoWindowClose;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractWindow &source);
};

typedef AbstractWindow *AbstractWindowP;

OSG_END_NAMESPACE

#include "OSGAbstractWindowBase.inl"
#include "OSGAbstractWindow.inl"

#define OSGABSTRACTWINDOW_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTWINDOW_H_ */
