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

#ifndef _OSGCELLEDITOR_H_
#define _OSGCELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGCellEditorBase.h"
#include <OpenSG/Toolbox/OSGEvent.h>
#include "OSGCellEditorListener.h"
#include <boost/any.hpp>
#include "Component/OSGComponentFields.h"
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief CellEditor class. See \ref 
           PageUserInterfaceCellEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING CellEditor : public CellEditorBase
{
  private:

    typedef CellEditorBase Inherited;

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
    virtual EventConnection addCellEditorListener(CellEditorListenerPtr l) = 0;
	virtual bool isCellEditorListenerAttached(CellEditorListenerPtr l) const = 0;

    //Removes a listener from the list that's notified
    virtual void removeCellEditorListener(CellEditorListenerPtr l) = 0;

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void) = 0;

    //Returns the value contained in the editor.
    virtual boost::any getCellEditorValue(void) const = 0;

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(const Event& anEvent) const = 0;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(const Event& anEvent) const = 0;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void) = 0;
    
    //Get the Editor Component
    virtual ComponentPtr getCellEditor(const boost::any& Value, bool IsSelected) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CellEditor(void);
    CellEditor(const CellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CellEditor(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CellEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CellEditor &source);
};

typedef CellEditor *CellEditorP;

OSG_END_NAMESPACE

#include "OSGCellEditorBase.inl"
#include "OSGCellEditor.inl"

#define OSGCELLEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCELLEDITOR_H_ */
