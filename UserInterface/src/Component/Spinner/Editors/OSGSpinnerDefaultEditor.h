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

#ifndef _OSGSPINNERDEFAULTEDITOR_H_
#define _OSGSPINNERDEFAULTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSpinnerDefaultEditorBase.h"
#include "Event/OSGChangeListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpinnerDefaultEditor class. See \ref 
           PageUserInterfaceSpinnerDefaultEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SpinnerDefaultEditor : public SpinnerDefaultEditorBase,
    public ChangeListener
{
  private:

    typedef SpinnerDefaultEditorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    friend class LookAndFeel;

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
    
    //Pushes the currently edited value to the SpinnerModel.
    virtual void commitEdit(void);

    //Disconnect this editor from the specified JSpinner.
    virtual void dismiss(SpinnerPtr spinner);

    //Called by the JTextField PropertyChangeListener.
    //void propertyChange(PropertyChangeEvent e);

    //This method is called when the spinner's model's state changes.
    virtual void stateChanged(const ChangeEvent& e);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SpinnerDefaultEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpinnerDefaultEditor(void);
    SpinnerDefaultEditor(const SpinnerDefaultEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpinnerDefaultEditor(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SpinnerDefaultEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpinnerDefaultEditor &source);
};

typedef SpinnerDefaultEditor *SpinnerDefaultEditorP;

OSG_END_NAMESPACE

#include "OSGSpinnerDefaultEditorBase.inl"
#include "OSGSpinnerDefaultEditor.inl"

#define OSGSPINNERDEFAULTEDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPINNERDEFAULTEDITOR_H_ */
