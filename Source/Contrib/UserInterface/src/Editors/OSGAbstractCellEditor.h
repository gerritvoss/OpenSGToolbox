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

#ifndef _OSGABSTRACTCELLEDITOR_H_
#define _OSGABSTRACTCELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractCellEditorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractCellEditor class. See \ref
           PageContribUserInterfaceAbstractCellEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractCellEditor : public AbstractCellEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractCellEditorBase Inherited;
    typedef AbstractCellEditor     Self;

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

    //Tells the editor to cancel editing and not accept any partially edited value.
    virtual void cancelCellEditing(void);

    //Asks the editor if it can start editing using anEvent.
    virtual bool isCellEditable(EventDetails* const anEvent) const;

    //Returns true if the editing cell should be selected, false otherwise.
    virtual bool shouldSelectCell(EventDetails* const anEvent) const;

    //Tells the editor to stop editing and accept any partially edited value as the value of the editor.
    virtual bool stopCellEditing(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractCellEditor(void);
    AbstractCellEditor(const AbstractCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractCellEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	void produceEditingCanceled(void);
	void produceEditingStopped(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractCellEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractCellEditor &source);
};

typedef AbstractCellEditor *AbstractCellEditorP;

OSG_END_NAMESPACE

#include "OSGAbstractCellEditorBase.inl"
#include "OSGAbstractCellEditor.inl"

#endif /* _OSGABSTRACTCELLEDITOR_H_ */
