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

#ifndef _OSGLISTGENERATEDPOPUPMENU_H_
#define _OSGLISTGENERATEDPOPUPMENU_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGListGeneratedPopupMenuBase.h"
#include "OSGListModel.h"
#include "OSGComponentGenerator.h"
#include "OSGPopupMenu.h"

OSG_BEGIN_NAMESPACE

/*! \brief ListGeneratedPopupMenu class. See \ref
           PageContribUserInterfaceListGeneratedPopupMenu for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ListGeneratedPopupMenu : public ListGeneratedPopupMenuBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ListGeneratedPopupMenuBase Inherited;
    typedef ListGeneratedPopupMenu     Self;

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

    virtual void addItem(MenuItem* const Item);
    virtual void addItem(MenuItem* const Item, const UInt32& Index);
    virtual void removeItem(MenuItem* const Item);
    virtual void removeItem(const UInt32& Index);
    virtual void removeAllItems(void);
    virtual MenuItem* getItem(const UInt32& Index);
    virtual UInt32 getNumItems(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ListGeneratedPopupMenuBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ListGeneratedPopupMenu(void);
    ListGeneratedPopupMenu(const ListGeneratedPopupMenu &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ListGeneratedPopupMenu(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void updateMenuItems(void);
    
	//Sent when the contents of the list has changed in a way that's too complex to characterize with the previous methods.
	void handleListContentsChanged(ListDataEventDetails* const e);
	//Sent after the indices in the index0,index1 interval have been inserted in the data model.
	void handleListIntervalAdded(ListDataEventDetails* const e);
	//Sent after the indices in the index0,index1 interval have been removed from the data model.
	void handleListIntervalRemoved(ListDataEventDetails* const e);

    boost::signals2::connection _ListContentsChangedConnection,
                                _ListIntervalAddedConnection,
                                _ListIntervalRemovedConnection;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ListGeneratedPopupMenuBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ListGeneratedPopupMenu &source);
};

typedef ListGeneratedPopupMenu *ListGeneratedPopupMenuP;

OSG_END_NAMESPACE

#include "OSGListGeneratedPopupMenuBase.inl"
#include "OSGListGeneratedPopupMenu.inl"

#endif /* _OSGLISTGENERATEDPOPUPMENU_H_ */
