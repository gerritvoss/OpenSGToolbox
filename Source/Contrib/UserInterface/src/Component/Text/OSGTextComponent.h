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

#ifndef _OSGTEXTCOMPONENT_H_
#define _OSGTEXTCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextComponentBase.h"
#include "OSGUIFont.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextComponent class. See \ref
           PageContribUserInterfaceTextComponent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TextComponent : public TextComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextComponentBase Inherited;
    typedef TextComponent     Self;

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
	
	virtual void keyTyped(KeyEventDetails* const e);

    bool hasSelection(void) const;
	virtual void select(const UInt32& Start,
						const UInt32& End);
	virtual void selectAll(void);
	virtual void setSelectionStart(const UInt32& index);
	virtual void setSelectionEnd(const UInt32& index);
	virtual std::string getSelectedText(void)const;
    
    void clear(void);
    void deleteSelectedText(void);
    void deleteRange(UInt32 Start, UInt32 End);
    void insert(const std::string& Text, UInt32 Position);
    

    void moveCaret(Int32 delta);
    void moveCaretToEnd(void);
    void moveCaretToBegin(void);

    static const OSG::BitVector TextColorsFieldMask;
	virtual void setTextColors(const Color4f& TheColor);
    

    void copy(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextComponent(void);
    TextComponent(const TextComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	UInt32 _TextSelectionStart;
	UInt32 _TextSelectionEnd;

    void produceTextValueChanged(void);

    void produceCaretChanged(void);

    virtual Color4f getDrawnTextColor(void) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextComponent &source);
};

typedef TextComponent *TextComponentP;

OSG_END_NAMESPACE

#include "OSGTextComponentBase.inl"
#include "OSGTextComponent.inl"

#endif /* _OSGTEXTCOMPONENT_H_ */
