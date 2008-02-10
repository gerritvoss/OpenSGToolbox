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

#ifndef _OSGUIVIEWPORT_H_
#define _OSGUIVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGUIViewportBase.h"
#include "Event/OSGChangeListener.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief UIViewport class. See \ref 
           PageUserInterfaceUIViewport for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING UIViewport : public UIViewportBase
{
  private:

    typedef UIViewportBase Inherited;

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
    virtual void updateLayout(void);

	void addChangeListener(ChangeListenerPtr Listener);
	void removeChangeListener(ChangeListenerPtr Listener);
    
    Vec2f getCorrectedViewSize(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in UIViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UIViewport(void);
    UIViewport(const UIViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UIViewport(void); 

    /*! \}                                                                 */
    
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
	
    ChangeListenerSet       _ChangeListeners;
    void produceStateChanged(const ChangeEvent& e);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class UIViewportBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const UIViewport &source);
};

typedef UIViewport *UIViewportP;

OSG_END_NAMESPACE

#include "OSGUIViewportBase.inl"
#include "OSGUIViewport.inl"

#define OSGUIVIEWPORT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGUIVIEWPORT_H_ */
