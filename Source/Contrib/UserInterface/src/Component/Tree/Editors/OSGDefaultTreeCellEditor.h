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

#ifndef _OSGDEFAULTTREECELLEDITOR_H_
#define _OSGDEFAULTTREECELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultTreeCellEditorBase.h"
#include "OSGTextFieldFields.h"
#include "OSGActionEventDetailsFields.h"
#include "OSGFocusEventDetailsFields.h"
#include "OSGKeyEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultTreeCellEditor class. See \ref
           PageContribUserInterfaceDefaultTreeCellEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultTreeCellEditor : public DefaultTreeCellEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultTreeCellEditorBase Inherited;
    typedef DefaultTreeCellEditor     Self;

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
	virtual ComponentTransitPtr getTreeCellEditorComponent(Tree* const TheTree, const boost::any& Value, bool IsSelected, bool IsExpanded, UInt32 row);
    
    virtual ComponentTransitPtr getCellEditor(const boost::any& Value, bool IsSelected);
    
    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Returns the value contained in the editor.
    virtual boost::any getCellEditorValue(void) const;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(EventDetails* const anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(EventDetails* const anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    //Returns a reference to the editor component.
    ComponentTransitPtr getComponent(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultTreeCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultTreeCellEditor(void);
    DefaultTreeCellEditor(const DefaultTreeCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultTreeCellEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void handleEditorAction(ActionEventDetails* const e);
    void handleEditorFocusLost(FocusEventDetails* const e);
    void handleEditorKeyPressed(KeyEventDetails* const e);

    boost::signals2::connection _EditorActionConnection,
                                _EditorFocusLostConnection,
                                _EditorKeyPressedConnection;

    mutable boost::any _EditingValue;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultTreeCellEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultTreeCellEditor &source);
};

typedef DefaultTreeCellEditor *DefaultTreeCellEditorP;

OSG_END_NAMESPACE

#include "OSGDefaultTreeCellEditorBase.inl"
#include "OSGDefaultTreeCellEditor.inl"

#endif /* _OSGDEFAULTTREECELLEDITOR_H_ */
