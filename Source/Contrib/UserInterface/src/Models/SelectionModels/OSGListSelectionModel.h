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

#ifndef _OSGLISTSELECTIONMODEL_H_
#define _OSGLISTSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGListSelectionModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ListSelectionModel class. See \ref
           PageContribUserInterfaceListSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ListSelectionModel : public ListSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ListSelectionModelBase Inherited;
    typedef ListSelectionModel     Self;

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
   enum ListSelectionMode
   {
       MULTIPLE_INTERVAL_SELECTION = 0, 
       SINGLE_INTERVAL_SELECTION = 1, 
       SINGLE_SELECTION = 2
   };

   //Change the selection to be the set union of the current selection and the indices between index0 and index1 inclusive.
   virtual void addSelectionInterval(UInt32 index0, UInt32 index1) = 0;
   
   //Change the selection to the empty set.
   virtual void clearSelection(void) = 0;
   
   //Return the first index argument from the most recent call to setSelectionInterval(), addSelectionInterval() or removeSelectionInterval().
   virtual Int32 getAnchorSelectionIndex(void) const = 0;
   
   //Return the second index argument from the most recent call to setSelectionInterval(), addSelectionInterval() or removeSelectionInterval().
   virtual Int32 getLeadSelectionIndex(void) const = 0;
   
   //Returns the last selected index or -1 if the selection is empty.
   virtual Int32 getMaxSelectionIndex(void) const = 0;
   
   //Returns the first selected index or -1 if the selection is empty.
   virtual Int32 getMinSelectionIndex(void) const = 0;
   
   //Returns true if the value is undergoing a series of changes.
   virtual bool getValueIsAdjusting(void) const = 0;
   
   //Insert length indices beginning before/after index.
   virtual void insertIndexInterval(UInt32 index, UInt32 length, bool before) = 0;
   
   //Returns true if the specified index is selected.
   virtual bool isSelectedIndex(UInt32 index) const = 0;
   
   //Returns true if no indices are selected.
   virtual bool isSelectionEmpty(void) const = 0;
   
   //Remove the indices in the interval index0,index1 (inclusive) from the selection model.
   virtual void removeIndexInterval(UInt32 index0, UInt32 index1) = 0;
   
   //Change the selection to be the set difference of the current selection and the indices between index0 and index1 inclusive.
   virtual void removeSelectionInterval(UInt32 index0, UInt32 index1) = 0;
   
   //Set the anchor selection index.
   virtual void setAnchorSelectionIndex(UInt32 index) = 0;
   
   //Set the lead selection index.
   virtual void setLeadSelectionIndex(UInt32 index) = 0;
   
   //Change the selection to be between index0 and index1 inclusive.
   virtual void setSelectionInterval(UInt32 index0, UInt32 index1) = 0;
   
   //This property is true if upcoming changes to the value of the model should be considered a single event.
   virtual void setValueIsAdjusting(bool valueIsAdjusting) = 0;

   virtual void incrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToIncrement) = 0;
   virtual void decrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToDecrement) = 0;

   std::vector<UInt32> getSelectedIndexes(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ListSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ListSelectionModel(void);
    ListSelectionModel(const ListSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ListSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ListSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ListSelectionModel &source);
};

typedef ListSelectionModel *ListSelectionModelP;

OSG_END_NAMESPACE

#include "OSGListSelectionModelBase.inl"
#include "OSGListSelectionModel.inl"

#endif /* _OSGLISTSELECTIONMODEL_H_ */
