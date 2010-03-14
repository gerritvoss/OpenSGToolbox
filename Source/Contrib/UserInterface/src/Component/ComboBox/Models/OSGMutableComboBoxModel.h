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

#ifndef _OSGMUTABLECOMBOBOXMODEL_H_
#define _OSGMUTABLECOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMutableComboBoxModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MutableComboBoxModel class. See \ref
           PageContribUserInterfaceMutableComboBoxModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MutableComboBoxModel : public MutableComboBoxModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MutableComboBoxModelBase Inherited;
    typedef MutableComboBoxModel     Self;

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
	//Adds an item at the end of the model.
	virtual void addElement(const boost::any& obj) = 0;

	//Adds an item at a specific index.
	virtual void insertElementAt(const boost::any& obj, const UInt32& index) = 0;

	//Removes an item from the model.
	virtual void removeElement(const boost::any& obj) = 0;

	//Removes an item at a specific index.
	virtual void removeElementAt(const UInt32& index) = 0;

	//Removes all elements
	virtual void removeAllElements(void) = 0;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MutableComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MutableComboBoxModel(void);
    MutableComboBoxModel(const MutableComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MutableComboBoxModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MutableComboBoxModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MutableComboBoxModel &source);
};

typedef MutableComboBoxModel *MutableComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGMutableComboBoxModelBase.inl"
#include "OSGMutableComboBoxModel.inl"

#endif /* _OSGMUTABLECOMBOBOXMODEL_H_ */
