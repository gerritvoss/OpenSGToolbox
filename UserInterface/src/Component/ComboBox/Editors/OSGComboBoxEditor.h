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

#ifndef _OSGCOMBOBOXEDITOR_H_
#define _OSGCOMBOBOXEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComboBoxEditorBase.h"
#include "Event/OSGActionListener.h"
#include "Component/OSGComponentFields.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxEditor class. See \ref 
           PageUserInterfaceComboBoxEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComboBoxEditor : public ComboBoxEditorBase
{
  private:

    typedef ComboBoxEditorBase Inherited;

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
	
	//Add an ActionListener.
	virtual void addActionListener(ActionListenerPtr Listener) = 0;

	//Remove an ActionListener
	virtual void removeActionListener(ActionListenerPtr Listener) = 0;

	//Return the component that should be added to the tree hierarchy for this editor
	virtual ComponentPtr getEditorComponent(void) = 0;

	//Return the edited item
	virtual SharedFieldPtr getItem(void) = 0;

	//Ask the editor to start editing and to select everything
	virtual void selectAll(void) = 0;

	//Set the item that should be edited.
	virtual void setItem(SharedFieldPtr anObject) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComboBoxEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComboBoxEditor(void);
    ComboBoxEditor(const ComboBoxEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComboBoxEditor(void); 

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComboBoxEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComboBoxEditor &source);
};

typedef ComboBoxEditor *ComboBoxEditorP;

OSG_END_NAMESPACE

#include "OSGComboBoxEditorBase.inl"
#include "OSGComboBoxEditor.inl"

#define OSGCOMBOBOXEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMBOBOXEDITOR_H_ */
