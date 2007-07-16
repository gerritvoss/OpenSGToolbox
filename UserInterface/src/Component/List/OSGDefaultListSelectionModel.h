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

#ifndef _OSGDEFAULTLISTSELECTIONMODEL_H_
#define _OSGDEFAULTLISTSELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultListSelectionModelBase.h"
#include "OSGListSelectionModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListSelectionModel class. See \ref 
           PageUserInterfaceDefaultListSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultListSelectionModel : public DefaultListSelectionModelBase
   , public ListSelectionModel
{
  private:

    typedef DefaultListSelectionModelBase Inherited;

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
   virtual void 	addListSelectionListener(ListSelectionListenerPtr x);

   virtual void 	addSelectionInterval(UInt32 index0, UInt32 index1);
   
   virtual void 	clearSelection(void);
   
   virtual UInt32 	getAnchorSelectionIndex(void) const;
   
   virtual UInt32 	getLeadSelectionIndex(void) const;
   
   virtual UInt32 	getMaxSelectionIndex(void) const;
   
   virtual UInt32 	getMinSelectionIndex(void) const;
   
   virtual Int32 	getSelectionMode(void) const;
   
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
   
   virtual void 	setSelectionMode(Int32 selectionMode);
   
   virtual void 	setValueIsAdjusting(bool valueIsAdjusting);
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultListSelectionModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultListSelectionModel &source);
};

typedef DefaultListSelectionModel *DefaultListSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultListSelectionModelBase.inl"
#include "OSGDefaultListSelectionModel.inl"

#define OSGDEFAULTLISTSELECTIONMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTLISTSELECTIONMODEL_H_ */
