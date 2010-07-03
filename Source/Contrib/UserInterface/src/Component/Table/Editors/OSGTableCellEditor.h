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

#ifndef _OSGTABLECELLEDITOR_H_
#define _OSGTABLECELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableCellEditorBase.h"
#include "OSGTableFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableCellEditor class. See \ref
           PageContribUserInterfaceTableCellEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TableCellEditor : public TableCellEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableCellEditorBase Inherited;
    typedef TableCellEditor     Self;

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

	virtual ComponentTransitPtr getTableCellEditorComponent(Table* const table, const boost::any& value, bool isSelected, UInt32 row, UInt32 column) = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableCellEditor(void);
    TableCellEditor(const TableCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableCellEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableCellEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableCellEditor &source);
};

typedef TableCellEditor *TableCellEditorP;

OSG_END_NAMESPACE

#include "OSGTableCellEditorBase.inl"
#include "OSGTableCellEditor.inl"

#endif /* _OSGTABLECELLEDITOR_H_ */
