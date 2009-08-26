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

#ifndef _OSGEDITABLETEXTCOMPONENT_H_
#define _OSGEDITABLETEXTCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGEditableTextComponentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief EditableTextComponent class. See \ref 
           PageUserInterfaceEditableTextComponent for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING EditableTextComponent : public EditableTextComponentBase
{
  private:

    typedef EditableTextComponentBase Inherited;

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
	virtual void keyPressed(const KeyEvent& e);
	virtual void keyReleased(const KeyEvent& e);
	virtual void keyTyped(const KeyEvent& e);

    void moveCursor(Int32 delta);
    void moveCursorToEnd(void);
    void moveCursorToBegin(void);

    void write(const std::string& Text);
    void overwriteSelection(const std::string& Text);
    void deleteSelectedText(void);
    void deleteRange(UInt32 Start, UInt32 End);
    void insert(const std::string& Text, UInt32 Position);

    bool hasSelection(void) const;
    void selectRange(UInt32 Start, UInt32 End);
    void selectAll(void);
    std::string getSelection(void) const;

    void cut(void);
    void copy(void) const;
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
    virtual LayerPtr getDrawnBackground(void) const;
    virtual LayerPtr getDrawnForeground(void) const;
    virtual BorderPtr getDrawnBorder(void) const;

    void setupCursor(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class EditableTextComponentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const EditableTextComponent &source);
};

typedef EditableTextComponent *EditableTextComponentP;

OSG_END_NAMESPACE

#include "OSGEditableTextComponentBase.inl"
#include "OSGEditableTextComponent.inl"

#define OSGEDITABLETEXTCOMPONENT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGEDITABLETEXTCOMPONENT_H_ */
