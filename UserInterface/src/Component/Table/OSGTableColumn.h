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

#ifndef _OSGTABLECOLUMN_H_
#define _OSGTABLECOLUMN_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTableColumnBase.h"

#include "OSGTableCellRenderer.h"
#include "OSGTableCellEditor.h"
#include <OpenSG/OSGField.h>

#include <OpenSG/Input/OSGFieldChangeListener.h>
#include <OpenSG/Input/OSGFieldChangeEvent.h>

OSG_BEGIN_NAMESPACE

/*! \brief TableColumn class. See \ref 
           PageUserInterfaceTableColumn for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TableColumn : public TableColumnBase
{
  private:

    typedef TableColumnBase Inherited;

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
    
    void addFieldChangeListener(FieldChangeListenerPtr Listener);
    
    void removeFieldChangeListener(FieldChangeListenerPtr Listener);
    
    //Returns the TableCellEditor used by the JTable to edit values for this column.
    TableCellEditor* getCellEditor(void) const;
    
    //Returns the TableCellRenderer used by the JTable to draw values for this column.
    TableCellRenderer* getCellRenderer(void) const;
    
    //Returns the TableCellRenderer used to draw the header of the TableColumn.
    TableCellRenderer* getHeaderRenderer(void) const;
    
    //Returns the Object used as the value for the header renderer.
    Field* getHeaderValue(void) const;
    
    //Sets the editor to used by when a cell in this column is edited.
    void setCellEditor(TableCellEditor* cellEditor);
    
    //Sets the TableCellRenderer used by JTable to draw individual values for this column.
    void setCellRenderer(TableCellRenderer* cellRenderer);
    
    //Sets the TableCellRenderer used to draw the TableColumn's header to headerRenderer.
    void setHeaderRenderer(TableCellRenderer* headerRenderer);
    
    //Sets the Object whose string representation will be used as the value for the headerRenderer.
    void setHeaderValue(Field* headerValue);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TableColumnBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableColumn(void);
    TableColumn(const TableColumn &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableColumn(void); 

    /*! \}                                                                 */
    
    TableCellEditor* _TableCellEditor;
    TableCellRenderer* _TableCellRenderer;
    TableCellRenderer* _HeaderCellRenderer;

    Field* _HeaderValue;
    
	typedef std::set<FieldChangeListenerPtr> FieldChangeListenerSet;
    typedef FieldChangeListenerSet::iterator FieldChangeListenerSetItor;
    typedef FieldChangeListenerSet::const_iterator FieldChangeListenerSetConstItor;
	
    FieldChangeListenerSet       _FieldChangeListeners;
    
    virtual void produceFieldChanged(Field* TheField, FieldDescription* TheDescription);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TableColumnBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TableColumn &source);
};

typedef TableColumn *TableColumnP;

OSG_END_NAMESPACE

#include "OSGTableColumnBase.inl"
#include "OSGTableColumn.inl"

#define OSGTABLECOLUMN_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTABLECOLUMN_H_ */
