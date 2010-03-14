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

#ifndef _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_
#define _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractMutableComboBoxModelBase.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractMutableComboBoxModel class. See \ref
           PageContribUserInterfaceAbstractMutableComboBoxModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractMutableComboBoxModel : public AbstractMutableComboBoxModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractMutableComboBoxModelBase Inherited;
    typedef AbstractMutableComboBoxModel     Self;

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
	virtual EventConnection addListDataListener(ListDataListenerPtr l);
	virtual bool isListDataListenerAttached(ListDataListenerPtr l) const;
	virtual void removeListDataListener(ListDataListenerPtr l);
	
	virtual EventConnection addSelectionListener(ComboBoxSelectionListenerPtr l);
	virtual bool isSelectionListenerAttached(ComboBoxSelectionListenerPtr l) const;
	virtual void removeSelectionListener(ComboBoxSelectionListenerPtr l);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractMutableComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractMutableComboBoxModel(void);
    AbstractMutableComboBoxModel(const AbstractMutableComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractMutableComboBoxModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	typedef std::set<ListDataListenerPtr> ListDataListenerSet;
	typedef ListDataListenerSet::iterator ListDataListenerSetIter;
	typedef ListDataListenerSet::const_iterator ListDataListenerSetConstIter;
	ListDataListenerSet _DataListeners;

	void produceListDataContentsChanged(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalAdded(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalRemoved(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1);

	typedef std::set<ComboBoxSelectionListenerPtr> ComboBoxSelectionListenerSet;
	typedef ComboBoxSelectionListenerSet::iterator ComboBoxSelectionListenerSetIter;
	typedef ComboBoxSelectionListenerSet::const_iterator ComboBoxSelectionListenerSetConstIter;
	ComboBoxSelectionListenerSet _SelectionListeners;

	void produceSelectionChanged(FieldContainerRefPtr Source, const Int32& CurrentIndex, const Int32& PreviousIndex);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractMutableComboBoxModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractMutableComboBoxModel &source);
};

typedef AbstractMutableComboBoxModel *AbstractMutableComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGAbstractMutableComboBoxModelBase.inl"
#include "OSGAbstractMutableComboBoxModel.inl"

#endif /* _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_ */
