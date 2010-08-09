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

#ifndef _OSGABSTRACTTABLECOLUMNMODEL_H_
#define _OSGABSTRACTTABLECOLUMNMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractTableColumnModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTableColumnModel class. See \ref
           PageContribUserInterfaceAbstractTableColumnModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractTableColumnModel : public AbstractTableColumnModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractTableColumnModelBase Inherited;
    typedef AbstractTableColumnModel     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void produceColumnAdded(const UInt32& ToIndex);
    void produceColumnMoved(const UInt32& ToIndex,const UInt32& FromIndex);
    void produceColumnRemoved(const UInt32& FromIndex);
    void produceColumnMarginChanged(void);
    void produceColumnSelectionChanged(ListSelectionEventDetails* const e);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractTableColumnModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractTableColumnModel &source);
};

typedef AbstractTableColumnModel *AbstractTableColumnModelP;

OSG_END_NAMESPACE

#include "OSGAbstractTableColumnModelBase.inl"
#include "OSGAbstractTableColumnModel.inl"

#endif /* _OSGABSTRACTTABLECOLUMNMODEL_H_ */
