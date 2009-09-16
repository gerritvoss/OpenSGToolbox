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

#ifndef _OSGABSTRACTCELLEDITOR_H_
#define _OSGABSTRACTCELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractCellEditorBase.h"
#include <set>
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractCellEditor class. See \ref 
           PageUserInterfaceAbstractCellEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractCellEditor : public AbstractCellEditorBase
{
  private:

    typedef AbstractCellEditorBase Inherited;

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
    //Adds a listener to the list that's notified when the editor stops, or cancels editing.
    virtual EventConnection addCellEditorListener(CellEditorListenerPtr l);
	virtual bool isCellEditorListenerAttached(CellEditorListenerPtr l) const;

    //Removes a listener from the list that's notified
    virtual void removeCellEditorListener(CellEditorListenerPtr l);

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AbstractCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractCellEditor(void);
    AbstractCellEditor(const AbstractCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractCellEditor(void); 

    /*! \}                                                                 */
    
	typedef std::set<CellEditorListenerPtr> CellEditorListenerSet;
    typedef CellEditorListenerSet::iterator CellEditorListenerSetItor;
    typedef CellEditorListenerSet::const_iterator CellEditorListenerSetConstItor;
	CellEditorListenerSet _CellEditorListeners;

    
	void produceEditingCanceled(void);
	void produceEditingStopped(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractCellEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractCellEditor &source);
};

typedef AbstractCellEditor *AbstractCellEditorP;

OSG_END_NAMESPACE

#include "OSGAbstractCellEditorBase.inl"
#include "OSGAbstractCellEditor.inl"

#define OSGABSTRACTCELLEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTCELLEDITOR_H_ */
