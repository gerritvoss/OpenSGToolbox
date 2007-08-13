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

#ifndef _OSGTOGGLEBUTTON_H_
#define _OSGTOGGLEBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGToggleButtonBase.h"
#include "Event/OSGButtonSelectedListener.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING ToggleButton : public ToggleButtonBase
{
  private:

    typedef ToggleButtonBase Inherited;

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

    void addButtonSelectedListener(ButtonSelectedListenerPtr Listener);
    void removeButtonSelectedListener(ButtonSelectedListenerPtr Listener);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ToggleButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ToggleButton(void);
    ToggleButton(const ToggleButton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ToggleButton(void); 

    /*! \}                                                                 */
    
    virtual void actionPreformed(const ActionEvent& e);

	typedef std::set<ButtonSelectedListenerPtr> ButtonSelectedListenerSet;
    typedef ButtonSelectedListenerSet::iterator ButtonSelectedListenerSetItor;
    typedef ButtonSelectedListenerSet::const_iterator ButtonSelectedListenerSetConstItor;
	
    ButtonSelectedListenerSet       _ButtonSelectedListeners;
    void produceButtonSelected(const ButtonSelectedEvent& e);
    void produceButtonDeselected(const ButtonSelectedEvent& e);
    
    virtual BorderPtr getDrawnBorder(void) const;
    virtual UIBackgroundPtr getDrawnBackground(void) const;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ToggleButtonBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ToggleButton &source);
};

typedef ToggleButton *ToggleButtonP;

OSG_END_NAMESPACE

#include "OSGToggleButtonBase.inl"
#include "OSGToggleButton.inl"

#define OSGTOGGLEBUTTON_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTOGGLEBUTTON_H_ */
