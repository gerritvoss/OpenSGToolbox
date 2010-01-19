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

#ifndef _OSGABSTRACTCOMBOBOXMODEL_H_
#define _OSGABSTRACTCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractComboBoxModelBase.h"
#include <set>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief AbstractComboBoxModel class. See \ref 
           PageUserInterfaceAbstractComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractComboBoxModel : public AbstractComboBoxModelBase
{
  private:

    typedef AbstractComboBoxModelBase Inherited;

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

    // Variables should all be in AbstractComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractComboBoxModel(void);
    AbstractComboBoxModel(const AbstractComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractComboBoxModel(void); 

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
    friend class AbstractComboBoxModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractComboBoxModel &source);
};

typedef AbstractComboBoxModel *AbstractComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGAbstractComboBoxModelBase.inl"
#include "OSGAbstractComboBoxModel.inl"

#define OSGABSTRACTCOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTCOMBOBOXMODEL_H_ */
