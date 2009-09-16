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

#ifndef _OSGDIALOGWINDOW_H_
#define _OSGDIALOGWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDialogWindowBase.h"
#include "Event/OSGDialogListener.h"
#include <set>
#include <OpenSG/Toolbox/OSGEventListener.h>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief DialogWindow class. See \ref 
           PageUserInterfaceDialogWindow for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DialogWindow : public DialogWindowBase
{
  private:

    typedef DialogWindowBase Inherited;
    friend class DialogFactory;

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

    EventConnection addDialogListener(DialogListenerPtr Listener);
	bool isDialogListenerAttached(DialogListenerPtr Listener) const;
    void removeDialogListener(DialogListenerPtr Listener);

    EventConnection addEventListener(EventListenerPtr Listener);
	bool isEventListenerAttached(EventListenerPtr Listener) const;
    void removeEventListener(EventListenerPtr Listener);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DialogWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogWindow(void);
    DialogWindow(const DialogWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogWindow(void); 

    /*! \}                                                                 */
	typedef std::set<DialogListenerPtr> DialogListenerSet;
    typedef DialogListenerSet::iterator DialogListenerSetItor;
    typedef DialogListenerSet::const_iterator DialogListenerSetConstItor;
	
    DialogListenerSet       _DialogListeners;
	
    virtual void produceDialogInput(const DialogEvent& e);
    
	typedef std::set<EventListenerPtr> EventListenerSet;
    typedef EventListenerSet::iterator EventListenerSetItor;
    typedef EventListenerSet::const_iterator EventListenerSetConstItor;
	
    EventListenerSet       _EventListeners;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogWindow &source);
};

typedef DialogWindow *DialogWindowP;

OSG_END_NAMESPACE

#include "OSGDialogWindowBase.inl"
#include "OSGDialogWindow.inl"

#define OSGDIALOGWINDOW_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOGWINDOW_H_ */
