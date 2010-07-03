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

#ifndef _OSGCOLORFIELDEDITOR_H_
#define _OSGCOLORFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGColorFieldEditorBase.h"
#include "OSGButton.h"
#include "OSGColorSelectionModel.h"
#include "OSGDialogWindowListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief ColorFieldEditor class. See \ref
           PageContribFieldContainerEditorColorFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING ColorFieldEditor : public ColorFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ColorFieldEditorBase Inherited;
    typedef ColorFieldEditor     Self;

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
    virtual const std::vector<const DataType*>& getEditableTypes(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ColorFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ColorFieldEditor(void);
    ColorFieldEditor(const ColorFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ColorFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ColorFieldEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    virtual void internalFieldChanged (void);
    virtual void internalStartEditing (void);
    virtual void internalStopEditing  (void);
    virtual void internalCancelEditing(void);
    virtual void updateLayout         (void);
    void         runCommand           (void);

    static std::vector<const DataType*> _EditableTypes;
    ButtonRefPtr _EditingButton;
    ColorSelectionModelPtr _ColorModel;
    
    class ButtonListener : public ActionListener
    {
      public :
           ButtonListener(ColorFieldEditor * const ptr);
           virtual void actionPerformed(const ActionEventUnrecPtr e);

      protected :
        ColorFieldEditor* _ColorFieldEditor ;
    };

    friend class ButtonListener;

    ButtonListener _ButtonListener;
    
    class DialogListener : public DialogWindowListener
    {
      public :
          DialogListener(ColorFieldEditor * const ptr);
          virtual void dialogClosing(const DialogWindowEventUnrecPtr e);
          virtual void dialogClosed(const DialogWindowEventUnrecPtr e);

      protected :
        ColorFieldEditor* _ColorFieldEditor ;
    };

    friend class DialogListener;

    DialogListener _DialogListener;

    Color4f getValueAsColor4f(void) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ColorFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ColorFieldEditor &source);
};

typedef ColorFieldEditor *ColorFieldEditorP;

OSG_END_NAMESPACE

#include "OSGColorFieldEditorBase.inl"
#include "OSGColorFieldEditor.inl"

#endif /* _OSGCOLORFIELDEDITOR_H_ */
