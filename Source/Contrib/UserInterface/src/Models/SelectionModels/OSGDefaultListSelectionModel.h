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

#ifndef _OSGDEFAULTLISTSELECTIONMODEL_H_
#define _OSGDEFAULTLISTSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultListSelectionModelBase.h"
#include <list>

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListSelectionModel class. See \ref
           PageContribUserInterfaceDefaultListSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultListSelectionModel : public DefaultListSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultListSelectionModelBase Inherited;
    typedef DefaultListSelectionModel     Self;

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

   virtual void 	addSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	clearSelection(void);
   
   virtual Int32 	getAnchorSelectionIndex(void) const;
   
   virtual Int32 	getLeadSelectionIndex(void) const;
   
   virtual Int32 	getMaxSelectionIndex(void) const;
   
   virtual Int32 	getMinSelectionIndex(void) const;
   
   virtual bool 	getValueIsAdjusting(void) const;
   
   virtual void 	insertIndexInterval(UInt32 index, UInt32 length, bool before);
   
   virtual bool 	isSelectedIndex(UInt32 index) const;
   
   virtual bool 	isSelectionEmpty(void) const;
   
   virtual void 	removeIndexInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	removeSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	setAnchorSelectionIndex(UInt32 index);
   
   virtual void 	setLeadSelectionIndex(UInt32 index);
   
   virtual void 	setSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	setValueIsAdjusting(bool valueIsAdjusting);

   virtual void incrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToIncrement);

   virtual void decrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToDecrement);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultListSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultListSelectionModel(void);
    DefaultListSelectionModel(const DefaultListSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultListSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	struct IndexRange{  //Inclusive
		IndexRange(UInt32 start, UInt32 end);
		bool operator== (const IndexRange& right) const;
		bool operator!= (const IndexRange& right) const;
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

   Int32 	_AnchorSelectionIndex;
   Int32 	_LeadSelectionIndex;
   Int32 	_MaxSelectionIndex;
   Int32 	_MinSelectionIndex;
   bool 	_ValueIsAdjusting;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultListSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultListSelectionModel &source);
};

typedef DefaultListSelectionModel *DefaultListSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultListSelectionModelBase.inl"
#include "OSGDefaultListSelectionModel.inl"

#endif /* _OSGDEFAULTLISTSELECTIONMODEL_H_ */
