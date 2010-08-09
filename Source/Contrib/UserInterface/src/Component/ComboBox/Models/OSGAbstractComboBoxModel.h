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

#ifndef _OSGABSTRACTCOMBOBOXMODEL_H_
#define _OSGABSTRACTCOMBOBOXMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractComboBoxModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractComboBoxModel class. See \ref
           PageContribUserInterfaceAbstractComboBoxModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractComboBoxModel : public AbstractComboBoxModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractComboBoxModelBase Inherited;
    typedef AbstractComboBoxModel     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractComboBoxModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractComboBoxModel(void);
    AbstractComboBoxModel(const AbstractComboBoxModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractComboBoxModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void produceListDataContentsChanged(FieldContainer* const Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalAdded(FieldContainer* const Source, UInt32 index0, UInt32 index1);
	void produceListDataIntervalRemoved(FieldContainer* const Source, UInt32 index0, UInt32 index1);

	void produceSelectionChanged(FieldContainer* const Source, const Int32& CurrentIndex, const Int32& PreviousIndex);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractComboBoxModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractComboBoxModel &source);
};

typedef AbstractComboBoxModel *AbstractComboBoxModelP;

OSG_END_NAMESPACE

#include "OSGAbstractComboBoxModelBase.inl"
#include "OSGAbstractComboBoxModel.inl"

#endif /* _OSGABSTRACTCOMBOBOXMODEL_H_ */
