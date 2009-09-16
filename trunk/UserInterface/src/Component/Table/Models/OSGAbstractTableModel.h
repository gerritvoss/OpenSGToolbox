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

#ifndef _OSGABSTRACTTABLEMODEL_H_
#define _OSGABSTRACTTABLEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <set>

#include "OSGAbstractTableModelBase.h"

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTableModel class. See \ref 
           PageUserInterfaceAbstractTableModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTableModel : public AbstractTableModelBase
{
  private:

    typedef AbstractTableModelBase Inherited;

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
    //Adds a listener to the list that is notified each time a change to the data model occurs.
    virtual EventConnection addTableModelListener(TableModelListenerPtr l);
	virtual bool isTableModelListenerAttached(TableModelListenerPtr l) const;
    
    //Removes a listener from the list that is notified each time a change to the data model occurs.
    virtual void removeTableModelListener(TableModelListenerPtr l);

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
	typedef std::set<TableModelListenerPtr> TableModelListenerSet;
    typedef TableModelListenerSet::iterator TableModelListenerSetItor;
    typedef TableModelListenerSet::const_iterator TableModelListenerSetConstItor;
	TableModelListenerSet _ModelListeners;

	void produceContentsHeaderRowChanged(UInt32 FirstColumn, UInt32 LastColumn);
	void produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
	void produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractTableModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractTableModel &source);
};

typedef AbstractTableModel *AbstractTableModelP;

OSG_END_NAMESPACE

#include "OSGAbstractTableModelBase.inl"
#include "OSGAbstractTableModel.inl"

#define OSGABSTRACTTABLEMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTABLEMODEL_H_ */
