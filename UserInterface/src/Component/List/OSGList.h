/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGLIST_H_
#define _OSGLIST_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGListBase.h"
#include "Event/OSGFocusListener.h"
#include "OSGListDataListener.h"
#include "OSGListSelectionListener.h"

OSG_BEGIN_NAMESPACE

class ListModel;
class ListCellGenerator;
class ListSelectionModel;

class OSG_USERINTERFACELIB_DLLMAPPING List : public ListBase, public ListSelectionListener, public ListDataListener, public FocusListener
{
  private:

    typedef ListBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	//Focus Events
	virtual void focusGained(const FocusEvent& e);
	virtual void focusLost(const FocusEvent& e);

    //Selection Event
	virtual void selectionChanged(const ListSelectionEvent& e);

	//List Data Events
	virtual void contentsChanged(ListDataEvent e);
	virtual void intervalAdded(ListDataEvent e);
	virtual void intervalRemoved(ListDataEvent e);
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
   
    virtual void updateLayout(void);

    void setModel(ListModel* Model);
    void setCellGenerator(ListCellGenerator* CellGenerator);
    void setSelectionModel(ListSelectionModel* SelectionModel);

    ListModel* getModel(void) const;
    ListCellGenerator* getCellGenerator(void) const;
    ListSelectionModel* getSelectionModel(void) const;
	
    virtual void mousePressed(const MouseEvent& e);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ListBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    List(void);
    List(const List &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~List(void); 

    /*! \}                                                                 */

    ListModel *_Model;
    ListCellGenerator *_CellGenerator;
    ListSelectionModel *_SelectionModel;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ListBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const List &source);
};

typedef List *ListP;

OSG_END_NAMESPACE

#include "OSGListBase.inl"
#include "OSGList.inl"

#define OSGLIST_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLIST_H_ */
