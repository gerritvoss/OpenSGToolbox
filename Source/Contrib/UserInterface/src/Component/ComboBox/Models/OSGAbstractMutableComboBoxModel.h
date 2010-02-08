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

#ifndef _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_
#define _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractMutableComboBoxModelBase.h"
#include <set>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractMutableComboBoxModel class. See \ref 
           PageUserInterfaceAbstractMutableComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractMutableComboBoxModel : public AbstractMutableComboBoxModelBase
{
  private:

    typedef AbstractMutableComboBoxModelBase Inherited;

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
	
    
	typedef std::set<ListDataListenerPtr> ListDataListenerSet;
	typedef ListDataListenerSet::iterator ListDataListenerSetIter;
	typedef ListDataListenerSet::const_iterator ListDataListenerSetConstIter;
	ListDataListenerSet _DataListeners;

	void produceListDataContentsChanged(FieldContainerPtr Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalAdded(FieldContainerPtr Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalRemoved(FieldContainerPtr Source, UInt32 index0, UInt32 index1);

	typedef std::set<ComboBoxSelectionListenerPtr> ComboBoxSelectionListenerSet;
	typedef ComboBoxSelectionListenerSet::iterator ComboBoxSelectionListenerSetIter;
	typedef ComboBoxSelectionListenerSet::const_iterator ComboBoxSelectionListenerSetConstIter;
	ComboBoxSelectionListenerSet _SelectionListeners;

	void produceSelectionChanged(FieldContainerPtr Source, const Int32& CurrentIndex, const Int32& PreviousIndex);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractMutableComboBoxModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractMutableComboBoxModel &source);
};

typedef AbstractMutableComboBoxModel *AbstractMutableComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGAbstractMutableComboBoxModelBase.inl"
#include "OSGAbstractMutableComboBoxModel.inl"

#define OSGABSTRACTMUTABLECOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTMUTABLECOMBOBOXMODEL_H_ */
