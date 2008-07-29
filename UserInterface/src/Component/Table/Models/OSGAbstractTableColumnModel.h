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

#ifndef _OSGABSTRACTTABLECOLUMNMODEL_H_
#define _OSGABSTRACTTABLECOLUMNMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractTableColumnModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTableColumnModel class. See \ref 
           PageUserInterfaceAbstractTableColumnModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractTableColumnModel : public AbstractTableColumnModelBase
{
  private:

    typedef AbstractTableColumnModelBase Inherited;

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
    //Adds a listener for table column model events.
    virtual void addColumnModelListener(TableColumnModelListenerPtr l);

    //Removes a listener for table column model events.
    virtual void removeColumnModelListener(TableColumnModelListenerPtr l);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in AbstractTableColumnModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractTableColumnModel(void);
    AbstractTableColumnModel(const AbstractTableColumnModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractTableColumnModel(void); 

    /*! \}                                                                 */
	typedef std::set<TableColumnModelListenerPtr> TableColumnModelListenerSet;
    typedef TableColumnModelListenerSet::iterator TableColumnModelListenerSetItor;
    typedef TableColumnModelListenerSet::const_iterator TableColumnModelListenerSetConstItor;
	TableColumnModelListenerSet _ModelListeners;

    void produceColumnAdded(const UInt32& ToIndex);
    void produceColumnMoved(const UInt32& ToIndex,const UInt32& FromIndex);
    void produceColumnRemoved(const UInt32& FromIndex);
    void produceColumnMarginChanged(void);
    void produceColumnSelectionChanged(const ListSelectionEvent& e);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractTableColumnModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractTableColumnModel &source);
};

typedef AbstractTableColumnModel *AbstractTableColumnModelP;

OSG_END_NAMESPACE

#include "OSGAbstractTableColumnModelBase.inl"
#include "OSGAbstractTableColumnModel.inl"

#define OSGABSTRACTTABLECOLUMNMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTTABLECOLUMNMODEL_H_ */
