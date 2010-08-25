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

#ifndef _OSGDEFAULTSINGLESELECTIONMODEL_H_
#define _OSGDEFAULTSINGLESELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultSingleSelectionModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultSingleSelectionModel class. See \ref
           PageContribUserInterfaceDefaultSingleSelectionModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultSingleSelectionModel : public DefaultSingleSelectionModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultSingleSelectionModelBase Inherited;
    typedef DefaultSingleSelectionModel     Self;

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

    //Clears the selection (to -1).
    virtual void clearSelection(void);
    
    //Returns the model's selection.
    virtual Int32 getSelectedIndex(void);
    
    //Returns true if the selection model currently has a selected value.
    virtual bool isSelected(void);
    
    //Sets the model's selected index to index.
    virtual void setSelectedIndex(Int32 index);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultSingleSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultSingleSelectionModel(void);
    DefaultSingleSelectionModel(const DefaultSingleSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultSingleSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    virtual void produceSelectionChanged(const Int32& SelectedIndex, const Int32& PreviouslySelectedIndex);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultSingleSelectionModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultSingleSelectionModel &source);
};

typedef DefaultSingleSelectionModel *DefaultSingleSelectionModelP;

OSG_END_NAMESPACE

#include "OSGDefaultSingleSelectionModelBase.inl"
#include "OSGDefaultSingleSelectionModel.inl"

#endif /* _OSGDEFAULTSINGLESELECTIONMODEL_H_ */
