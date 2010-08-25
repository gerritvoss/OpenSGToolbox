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

#ifndef _OSGABSTRACTTABLEMODEL_H_
#define _OSGABSTRACTTABLEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractTableModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTableModel class. See \ref
           PageContribUserInterfaceAbstractTableModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractTableModel : public AbstractTableModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractTableModelBase Inherited;
    typedef AbstractTableModel     Self;

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

    //Returns true if the cell at rowIndex and columnIndex is editable.
    virtual bool isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const;
    
    //Sets the value in the cell at columnIndex and rowIndex to aValue.
    virtual void setValueAt(const boost::any& aValue, UInt32 rowIndex, UInt32 columnIndex);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractTableModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractTableModel(void);
    AbstractTableModel(const AbstractTableModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractTableModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void produceContentsHeaderRowChanged(UInt32 FirstColumn, UInt32 LastColumn);
	void produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractTableModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractTableModel &source);
};

typedef AbstractTableModel *AbstractTableModelP;

OSG_END_NAMESPACE

#include "OSGAbstractTableModelBase.inl"
#include "OSGAbstractTableModel.inl"

#endif /* _OSGABSTRACTTABLEMODEL_H_ */
