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

#ifndef _OSGDEFAULTLISTSELECTIONMODEL_H_
#define _OSGDEFAULTLISTSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGListSelectionModel.h"
#include <set>
#include <list>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListSelectionModel class. See \ref 
           PageUserInterfaceDefaultListSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultListSelectionModel : public ListSelectionModel
{
    /*==========================  PUBLIC  =================================*/
  public:
   enum SelectionMode {SINGLE_SELECTION, SINGLE_INTERVAL_SELECTION, MULTIPLE_INTERVAL_SELECTION};

   virtual void 	addListSelectionListener(ListSelectionListenerPtr x);

   virtual void 	addSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	clearSelection(void);
   
   virtual UInt32 	getAnchorSelectionIndex(void) const;
   
   virtual UInt32 	getLeadSelectionIndex(void) const;
   
   virtual UInt32 	getMaxSelectionIndex(void) const;
   
   virtual UInt32 	getMinSelectionIndex(void) const;
   
   virtual UInt32 	getSelectionMode(void) const;
   
   virtual bool 	getValueIsAdjusting(void) const;
   
   virtual void 	insertIndexInterval(UInt32 index, UInt32 length, bool before);
   
   virtual bool 	isSelectedIndex(UInt32 index) const;
   
   virtual bool 	isSelectionEmpty(void) const;
   
   virtual void 	removeIndexInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	removeListSelectionListener(ListSelectionListenerPtr x);
   
   virtual void 	removeSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	setAnchorSelectionIndex(UInt32 index);
   
   virtual void 	setLeadSelectionIndex(UInt32 index);
   
   virtual void 	setSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	setSelectionMode(UInt32 selectionMode);
   
   virtual void 	setValueIsAdjusting(bool valueIsAdjusting);
   
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultListSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultListSelectionModel(void); 

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultListSelectionModelBase.

	typedef std::set<ListSelectionListenerPtr> ListSelectionListenerSet;
    typedef ListSelectionListenerSet::iterator ListSelectionListenerSetItor;
    typedef ListSelectionListenerSet::const_iterator ListSelectionListenerSetConstItor;
	
    ListSelectionListenerSet       _ListSelectionListeners;
	
    virtual void produceSelectionChanged(const ListSelectionEvent& e);

	struct IndexRange{  //Inclusive
		IndexRange(UInt32 start, UInt32 end)
		{
			StartIndex = start;
			EndIndex = end;
		}
		bool operator== (const IndexRange& right) const
		{
			return StartIndex == right.StartIndex && EndIndex == right.EndIndex;
		}
		bool operator!= (const IndexRange& right) const
		{
			return StartIndex != right.StartIndex || EndIndex != right.EndIndex;
		}
		UInt32 StartIndex;
		UInt32 EndIndex;
	};

	IndexRange getMinMaxSelection(const IndexRange& range);
	static IndexRange getMinMaxSelection(const IndexRange& range1, const IndexRange& range2);
	void updateMinMax(void);

	typedef std::list<IndexRange> RangeSelectionList;
	typedef RangeSelectionList::iterator RangeSelectionListItor;
	typedef RangeSelectionList::const_iterator RangeSelectionListConstItor;

	RangeSelectionList _RangeSelectionList;

	// These are used to help with setting the Selection Intervals

   SelectionMode _SelectionMode;
   UInt32 	_AnchorSelectionIndex;
   UInt32 	_LeadSelectionIndex;
   UInt32 	_MaxSelectionIndex;
   UInt32 	_MinSelectionIndex;
   bool 	_ValueIsAdjusting;
    
    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultListSelectionModel *DefaultListSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultListSelectionModel.inl"

#endif /* _OSGDEFAULTLISTSELECTIONMODEL_H_ */
