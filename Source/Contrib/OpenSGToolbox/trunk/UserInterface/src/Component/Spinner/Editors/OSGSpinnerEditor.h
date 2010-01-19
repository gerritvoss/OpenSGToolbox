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

#ifndef _OSGSPINNEREDITOR_H_
#define _OSGSPINNEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGSpinnerEditorBase.h"
#include "Component/Spinner/OSGSpinnerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpinnerEditor class. See \ref 
           PageUserInterfaceSpinnerEditor for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING SpinnerEditor : public SpinnerEditorBase
{
  private:

    typedef SpinnerEditorBase Inherited;

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
	
    //Pushes the currently edited value to the SpinnerModel.
    virtual void commitEdit(void) = 0;

    //Cancels the current edits and returns the editor to the previous value
    virtual void cancelEdit(void) = 0;

    //Disconnect this editor from the specified JSpinner.
    virtual void dismiss(SpinnerPtr spinner) = 0;

	//Set whether or not this Editor is Editable
	virtual void setEditable(bool Editable) = 0;

	//Get whether or not this Editor is Editable
	virtual bool getEditable(void) const = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SpinnerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpinnerEditor(void);
    SpinnerEditor(const SpinnerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpinnerEditor(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SpinnerEditorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SpinnerEditor &source);
};

typedef SpinnerEditor *SpinnerEditorP;

OSG_END_NAMESPACE

#include "OSGSpinnerEditorBase.inl"
#include "OSGSpinnerEditor.inl"

#define OSGSPINNEREDITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSPINNEREDITOR_H_ */
