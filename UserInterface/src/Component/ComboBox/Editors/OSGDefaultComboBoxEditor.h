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

#ifndef _OSGDEFAULTCOMBOBOXEDITOR_H_
#define _OSGDEFAULTCOMBOBOXEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDefaultComboBoxEditorBase.h"
#include "Event/OSGFocusListener.h"

#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultComboBoxEditor class. See \ref 
           PageUserInterfaceDefaultComboBoxEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultComboBoxEditor : public DefaultComboBoxEditorBase
{
  private:

    typedef DefaultComboBoxEditorBase Inherited;

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

    virtual void dump(      UInt32     uiIndent, 
                      const BitVector  bvFlags ) const;

    /*! \}                                                                 */
	//Add an ActionListener.
	virtual EventConnection addActionListener(ActionListenerPtr Listener);
	virtual bool isActionListenerAttached(ActionListenerPtr Listener) const;

	//Remove an ActionListener
	virtual void removeActionListener(ActionListenerPtr Listener);

	//Return the component that should be added to the tree hierarchy for this editor
	virtual ComponentPtr getEditorComponent(void);

	//Return the edited item
	virtual boost::any getItem(void);

	//Ask the editor to start editing and to select everything
	virtual void selectAll(void);

	//Set the item that should be edited.
	virtual void setItem(const boost::any& anObject);
	
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultComboBoxEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultComboBoxEditor(void);
    DefaultComboBoxEditor(const DefaultComboBoxEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultComboBoxEditor(void); 

    /*! \}                                                                 */
    //Expand Button Action Listener
	class TextFieldListener :public FocusListener
	{
	public:
		TextFieldListener(DefaultComboBoxEditorPtr TheDefaultComboBoxEditor);
        virtual void focusGained(const FocusEvent& e);
        virtual void focusLost(const FocusEvent& e);

	private:
		DefaultComboBoxEditorPtr _DefaultComboBoxEditor;
	};

	friend class TextFieldListener;

	TextFieldListener _TextFieldListener;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultComboBoxEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultComboBoxEditor &source);
};

typedef DefaultComboBoxEditor *DefaultComboBoxEditorP;

OSG_END_NAMESPACE

#include "OSGDefaultComboBoxEditorBase.inl"
#include "OSGDefaultComboBoxEditor.inl"

#define OSGDEFAULTCOMBOBOXEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTCOMBOBOXEDITOR_H_ */
