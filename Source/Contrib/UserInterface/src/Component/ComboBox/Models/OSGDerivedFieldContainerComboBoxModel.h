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

#ifndef _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_
#define _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDerivedFieldContainerComboBoxModelBase.h"
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief DerivedFieldContainerComboBoxModel class. See \ref
           PageContribUserInterfaceDerivedFieldContainerComboBoxModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DerivedFieldContainerComboBoxModel : public DerivedFieldContainerComboBoxModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DerivedFieldContainerComboBoxModelBase Inherited;
    typedef DerivedFieldContainerComboBoxModel     Self;

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
	//Returns the selected item
    virtual boost::any getSelectedItem(void) const;

	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index);
	
	//Set the selected item.
	virtual void setSelectedItem(const boost::any& anObject);

	virtual UInt32 getSize(void) const;

    virtual boost::any getElementAt(UInt32 index) const;
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    std::vector<boost::any> _FieldList;
	Int32 _SelectedIndex;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DerivedFieldContainerComboBoxModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DerivedFieldContainerComboBoxModel &source);
};

typedef DerivedFieldContainerComboBoxModel *DerivedFieldContainerComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGDerivedFieldContainerComboBoxModelBase.inl"
#include "OSGDerivedFieldContainerComboBoxModel.inl"

#endif /* _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODEL_H_ */
