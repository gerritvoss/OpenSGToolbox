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

#ifndef _OSGEDITABLETEXTCOMPONENT_H_
#define _OSGEDITABLETEXTCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGEditableTextComponentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief EditableTextComponent class. See \ref
           PageContribUserInterfaceEditableTextComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING EditableTextComponent : public EditableTextComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef EditableTextComponentBase Inherited;
    typedef EditableTextComponent     Self;

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

	virtual void keyPressed(KeyEventDetails* const e);
	virtual void keyReleased(KeyEventDetails* const e);
	virtual void keyTyped(KeyEventDetails* const e);

    void write(const std::string& Text);
    void overwriteSelection(const std::string& Text);

    void cut(void);
    void paste(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in EditableTextComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EditableTextComponent(void);
    EditableTextComponent(const EditableTextComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EditableTextComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual Layer* getDrawnBackground(void) const;
    virtual Layer* getDrawnForeground(void) const;
    virtual Border* getDrawnBorder(void) const;

    void setupCursor(void);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class EditableTextComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const EditableTextComponent &source);
};

typedef EditableTextComponent *EditableTextComponentP;

OSG_END_NAMESPACE

#include "OSGEditableTextComponentBase.inl"
#include "OSGEditableTextComponent.inl"

#endif /* _OSGEDITABLETEXTCOMPONENT_H_ */
