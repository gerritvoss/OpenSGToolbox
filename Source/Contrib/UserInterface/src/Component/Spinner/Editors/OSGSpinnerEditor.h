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

#ifndef _OSGSPINNEREDITOR_H_
#define _OSGSPINNEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSpinnerEditorBase.h"
#include "OSGSpinnerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpinnerEditor class. See \ref
           PageContribUserInterfaceSpinnerEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SpinnerEditor : public SpinnerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SpinnerEditorBase Inherited;
    typedef SpinnerEditor     Self;

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
	
    //Pushes the currently edited value to the SpinnerModel.
    virtual void commitEdit(void) = 0;

    //Cancels the current edits and returns the editor to the previous value
    virtual void cancelEdit(void) = 0;

    //Disconnect this editor from the specified JSpinner.
    virtual void dismiss(Spinner* const spinner) = 0;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SpinnerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SpinnerEditor &source);
};

typedef SpinnerEditor *SpinnerEditorP;

OSG_END_NAMESPACE

#include "OSGSpinnerEditorBase.inl"
#include "OSGSpinnerEditor.inl"

#endif /* _OSGSPINNEREDITOR_H_ */
