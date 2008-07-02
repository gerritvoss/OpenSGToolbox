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

#ifndef _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_
#define _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDerivedFieldContainerComboBoxModelBase.h"
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief DerivedFieldContainerComboBoxModel class. See \ref 
           PageUserInterfaceDerivedFieldContainerComboBoxModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DerivedFieldContainerComboBoxModel : public DerivedFieldContainerComboBoxModelBase
{
  private:

    typedef DerivedFieldContainerComboBoxModelBase Inherited;

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
	//Returns the selected item
	virtual SharedFieldPtr getSelectedItem(void) const;

	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index);
	
	//Set the selected item.
	virtual void setSelectedItem(SharedFieldPtr anObject);

	virtual UInt32 getSize(void) const;

	virtual SharedFieldPtr getElementAt(UInt32 index) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DerivedFieldContainerComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DerivedFieldContainerComboBoxModel(void);
    DerivedFieldContainerComboBoxModel(const DerivedFieldContainerComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DerivedFieldContainerComboBoxModel(void); 

    /*! \}                                                                 */
	std::vector<SharedFieldPtr> _FieldList;
	Int32 _SelectedIndex;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DerivedFieldContainerComboBoxModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DerivedFieldContainerComboBoxModel &source);
};

typedef DerivedFieldContainerComboBoxModel *DerivedFieldContainerComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGDerivedFieldContainerComboBoxModelBase.inl"
#include "OSGDerivedFieldContainerComboBoxModel.inl"

#define OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_ */
