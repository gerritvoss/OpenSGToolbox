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

#ifndef _OSGCOMBOBOXEDITOR_H_
#define _OSGCOMBOBOXEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComboBoxEditorBase.h"
#include "OSGActionListener.h"
#include "OSGComponent.h"
#include "OSGComponent.h"

#include <boost/any.hpp>

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxEditor class. See \ref
           PageContribUserInterfaceComboBoxEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComboBoxEditor : public ComboBoxEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComboBoxEditorBase Inherited;
    typedef ComboBoxEditor     Self;

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
	
	//Add an ActionListener.
	virtual EventConnection addActionListener(ActionListenerPtr Listener) = 0;
	virtual bool isActionListenerAttached(ActionListenerPtr Listener) const = 0;

	//Remove an ActionListener
	virtual void removeActionListener(ActionListenerPtr Listener) = 0;

	//Return the component that should be added to the tree hierarchy for this editor
	virtual ComponentRefPtr getEditorComponent(void) = 0;

	//Return the edited item
	virtual boost::any getItem(void) = 0;

	//Ask the editor to start editing and to select everything
	virtual void selectAll(void) = 0;

	//Set the item that should be edited.
	virtual void setItem(const boost::any& anObject) = 0;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComboBoxEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComboBoxEditor &source);
};

typedef ComboBoxEditor *ComboBoxEditorP;

OSG_END_NAMESPACE

#include "OSGComboBoxEditorBase.inl"
#include "OSGComboBoxEditor.inl"

#endif /* _OSGCOMBOBOXEDITOR_H_ */
