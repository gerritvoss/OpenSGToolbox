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

#ifndef _OSGSINGLESELECTIONMODEL_H_
#define _OSGSINGLESELECTIONMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSingleSelectionModelBase.h"
#include "OSGSelectionListener.h"
#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief SingleSelectionModel class. See \ref 
           PageUserInterfaceSingleSelectionModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SingleSelectionModel : public SingleSelectionModelBase
{
  private:

    typedef SingleSelectionModelBase Inherited;

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

    //Adds listener as a listener to changes in the model.
    virtual EventConnection addSelectionListener(SelectionListenerPtr listener) = 0;
	virtual bool isSelectionListenerAttached(SelectionListenerPtr listener) const = 0;

    //Clears the selection (to -1).
    virtual void clearSelection(void) = 0;
    
    //Returns the model's selection.
    virtual Int32 getSelectedIndex(void) = 0;
    
    //Returns true if the selection model currently has a selected value.
    virtual bool isSelected(void) = 0;
    
    //Removes listener as a listener to changes in the model.
    virtual void removeSelectionListener(SelectionListenerPtr listener) = 0;
    
    //Sets the model's selected index to index.
    virtual void setSelectedIndex(Int32 index) = 0;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SingleSelectionModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SingleSelectionModel(void);
    SingleSelectionModel(const SingleSelectionModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SingleSelectionModel(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SingleSelectionModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SingleSelectionModel &source);
};

typedef SingleSelectionModel *SingleSelectionModelP;

OSG_END_NAMESPACE

#include "OSGSingleSelectionModelBase.inl"
#include "OSGSingleSelectionModel.inl"

#endif /* _OSGSINGLESELECTIONMODEL_H_ */
