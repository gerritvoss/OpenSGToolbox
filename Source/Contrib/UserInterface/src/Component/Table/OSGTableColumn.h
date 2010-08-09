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

#ifndef _OSGTABLECOLUMN_H_
#define _OSGTABLECOLUMN_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableColumnBase.h"
#include "OSGTableCellRenderer.h"
#include "OSGField.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableColumn class. See \ref
           PageContribUserInterfaceTableColumn for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableColumn : public TableColumnBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableColumnBase Inherited;
    typedef TableColumn     Self;

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
    
    //Returns the TableCellRenderer used by the JTable to draw values for this column.
    TableCellRendererPtr getCellRenderer(void) const;
    
    //Returns the TableCellRenderer used to draw the header of the TableColumn.
    TableCellRendererPtr getHeaderRenderer(void) const;
    
    //Returns the Object used as the value for the header renderer.
    boost::any getHeaderValue(void) const;
    
    //Sets the TableCellRenderer used by JTable to draw individual values for this column.
    void setCellRenderer(TableCellRendererPtr cellRenderer);
    
    //Sets the TableCellRenderer used to draw the TableColumn's header to headerRenderer.
    void setHeaderRenderer(TableCellRendererPtr headerRenderer);
    
    //Sets the Object whose string representation will be used as the value for the headerRenderer.
    void setHeaderValue(const boost::any& headerValue);
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    TableCellRendererPtr _TableCellRenderer;
    TableCellRendererPtr _HeaderCellRenderer;

    boost::any _HeaderValue;
    
    virtual void produceFieldChanged(FieldContainer* TheFieldContainer, FieldDescriptionBase* TheDescription);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableColumnBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableColumn &source);
};

typedef TableColumn *TableColumnP;

OSG_END_NAMESPACE

#include "OSGTableCellEditor.h"
#include "OSGTableColumnBase.inl"
#include "OSGTableColumn.inl"

#endif /* _OSGTABLECOLUMN_H_ */
