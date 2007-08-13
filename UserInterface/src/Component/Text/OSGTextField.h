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

#ifndef _OSGTEXTFIELD_H_
#define _OSGTEXTFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTextFieldBase.h"
#include "Event/OSGActionListener.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGUpdateListener.h>


OSG_BEGIN_NAMESPACE

/*! \brief TextField class. See \ref 
           PageUserInterfaceTextField for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TextField : public TextFieldBase, public UpdateListener

{
  private:

    typedef TextFieldBase Inherited;

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

    /*! \}*/

	virtual void keyTyped(const KeyEvent& e);

	virtual void mouseClicked(const MouseEvent& e);
	virtual void mousePressed(const MouseEvent& e);
	virtual void mouseDragged(const MouseEvent& e);
    virtual void update(const UpdateEvent& e);
	
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

    void addActionListener(ActionListenerPtr Listener);
    void removeActionListener(ActionListenerPtr Listener);


    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TextFieldBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextField(void);
    TextField(const TextField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextField(void); 

    /*! \}                                                                 */
    
	virtual void drawInternal(const GraphicsPtr Graphics) const;

	typedef std::set<ActionListenerPtr> ActionListenerSet;
    typedef ActionListenerSet::iterator ActionListenerSetItor;
    typedef ActionListenerSet::const_iterator ActionListenerSetConstItor;
	
    ActionListenerSet       _ActionListeners;
	
    virtual void produceActionPerformed(const ActionEvent& e);
	
	Time _CurrentCaretBlinkElps;

	/*class CaretUpdateListener : public UpdateListener
	{
	public:
		CaretUpdateListener(TextFieldPtr TheTextField);
        virtual void update(const UpdateEvent& e);
	private:
		TextFieldPtr _TextField;
	};
	CaretUpdateListener _CaretUpdateListener;*/
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TextFieldBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextField &source);
};

typedef TextField *TextFieldP;

OSG_END_NAMESPACE

#include "OSGTextFieldBase.inl"
#include "OSGTextField.inl"

#define OSGTEXTFIELD_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTEXTFIELD_H_ */
