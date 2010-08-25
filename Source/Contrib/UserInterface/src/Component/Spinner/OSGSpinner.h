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

#ifndef _OSGSPINNER_H_
#define _OSGSPINNER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSpinnerBase.h"
#include "OSGSpinnerModel.h"

#include "OSGTextField.h"
#include "OSGButton.h"

OSG_BEGIN_NAMESPACE

/*! \brief Spinner class. See \ref
           PageContribUserInterfaceSpinner for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Spinner : public SpinnerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef SpinnerBase Inherited;
    typedef Spinner     Self;

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

    virtual void updateLayout(void);
    
    //Commits the currently edited value to the SpinnerModel.
    void commitEdit(void);

    //Returns the SpinnerModel that defines this spinners sequence of values.
    SpinnerModelPtr getModel(void) const;

    //Returns the object in the sequence that comes after the object returned by getValue().
    boost::any getNextValue(void);

    //Returns the object in the sequence that comes before the object returned by getValue().
    boost::any getPreviousValue(void);

    //Returns the current value of the model, typically this value is displayed by the editor.
    boost::any getValue(void);

    //Changes the model that represents the value of this spinner.
    void setModel(SpinnerModelPtr model);

    //Changes current value of the model, typically this value is displayed by the editor.
    void setValue(const boost::any& value);

	//Set whether or not this Editor is Editable
	//This is only relevent when the Editor is a derived class of SpinnerEditor
	void setEditable(bool Editable);

	//Get whether or not this Editor is Editable
	//This is only relevent when the Editor is a derived class of SpinnerEditor
	bool getEditable(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SpinnerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Spinner(void);
    Spinner(const Spinner &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Spinner(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const Spinner *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    SpinnerModelPtr _Model;
    
    //This method is called by the constructors to create the JComponent that displays the current value of the sequence.
    ComponentTransitPtr createEditor(SpinnerModelPtr model);

    //Next Button Action
    void handleNextButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _NextButtonActionConnection;

    //Previous Button Action
    void handlePreviousButtonAction(ActionEventDetails* const e);
    boost::signals2::connection _PreviousButtonActionConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SpinnerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Spinner &source);
};

typedef Spinner *SpinnerP;

OSG_END_NAMESPACE

#include "OSGSpinnerBase.inl"
#include "OSGSpinner.inl"

#endif /* _OSGSPINNER_H_ */
