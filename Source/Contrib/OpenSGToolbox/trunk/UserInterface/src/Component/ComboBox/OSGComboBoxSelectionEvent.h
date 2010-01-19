/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGCOMBOBOXSELECTIONEVENT_H_
#define _OSGCOMBOBOXSELECTIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGComboBoxSelectionEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxSelectionEvent class. See \ref 
           PageUserInterfaceComboBoxSelectionEvent for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComboBoxSelectionEvent : public ComboBoxSelectionEventBase
{
  private:

    typedef ComboBoxSelectionEventBase Inherited;

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

    static  ComboBoxSelectionEventPtr      create(  FieldContainerPtr Source,
                                                    Time TimeStamp,
                                                    Int32 CurrentIndex,
                                                    Int32 PreviousIndex); 

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComboBoxSelectionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComboBoxSelectionEvent(void);
    ComboBoxSelectionEvent(const ComboBoxSelectionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComboBoxSelectionEvent(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComboBoxSelectionEventBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComboBoxSelectionEvent &source);
};

typedef ComboBoxSelectionEvent *ComboBoxSelectionEventP;

OSG_END_NAMESPACE

#include "OSGComboBoxSelectionEventBase.inl"
#include "OSGComboBoxSelectionEvent.inl"

#endif /* _OSGCOMBOBOXSELECTIONEVENT_H_ */
