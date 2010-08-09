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

#ifndef _OSGCOMBOBOXMODEL_H_
#define _OSGCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComboBoxModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxModel class. See \ref
           PageContribUserInterfaceComboBoxModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComboBoxModel : public ComboBoxModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComboBoxModelBase Inherited;
    typedef ComboBoxModel     Self;

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
    virtual boost::any getSelectedItem(void) const = 0;

	//Returns the selected item Index
	virtual Int32 getSelectedItemIndex(void) const = 0;

	//Set the selected item.
	virtual void setSelectedItem(const Int32& index) = 0;
	
	//Set the selected item.
	virtual void setSelectedItem(const boost::any& anObject) = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComboBoxModel(void);
    ComboBoxModel(const ComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComboBoxModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComboBoxModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComboBoxModel &source);
};

typedef ComboBoxModel *ComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGComboBoxModelBase.inl"
#include "OSGComboBoxModel.inl"

#endif /* _OSGCOMBOBOXMODEL_H_ */
