/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGTEXTDOMLAYOUTMANAGER_H_
#define _OSGTEXTDOMLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextDomLayoutManagerBase.h"
#include "OSGElementFields.h"
#include "OSGTextDomAreaFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextDomLayoutManager class. See \ref
           PageContribTextDomTextDomLayoutManager for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextDomLayoutManager : public TextDomLayoutManagerBase
{
	public:
	
	

  protected:

    /*==========================  PUBLIC  =================================*/


	

  public:

    typedef TextDomLayoutManagerBase Inherited;
    typedef TextDomLayoutManager     Self;

		
	virtual Vec2f getContentRequestedSize(void) const = 0;
	virtual void updateViews(void) = 0;
	virtual void printDebugInformation(void) const = 0;

	//used - related to DOM
	virtual void initializeRootElement() = 0;
	virtual void deleteSelected(void) = 0;
	virtual void deleteCharacters(UInt32 HSL,UInt32 HSI,UInt32 HEL,UInt32 HEI) = 0;
	virtual void populateCache(void) = 0;

	//used - related to Layout
	virtual UInt32 getTopmostVisibleLineNumber(void) const = 0;
	virtual UInt32 getLinesToBeDisplayed(void) const = 0;
	virtual void calculatePreferredSize(void) = 0;
	virtual void updateSize(void) = 0;
	virtual bool isLastCharacterOfDocument(void) const = 0;
	virtual void calculateLineHeight(void) = 0;
	virtual UInt32 calculateCaretPosition(Pnt2f PointOnComponent,bool isDragging) = 0;
	virtual void checkCaretVisibility(UInt32 dir) = 0;
	virtual bool isCaretVisible(void) = 0;
	virtual void makeCaretVisible(UInt32 dir) = 0;
	virtual bool isSomethingSelected(void) = 0;
	virtual bool isStartLocationBeforeEndLocation(void) const = 0;
	virtual void moveCaretEnd(bool isControlPressed) = 0;
	virtual void moveCaretHome(bool isControlPressed) = 0;
	virtual void moveCaretUp(void) = 0;
	virtual void moveCaretDown(void) = 0;
	virtual void moveCaretLeft(void) = 0;
	virtual void moveCaretRight(void) = 0;
	virtual void moveTheCaret(UInt32 dir,bool isShiftPressed,bool isControlPressed) = 0;
	virtual void moveAndHighlightWord(UInt32 dir) = 0;
	virtual void recalculateCaretPositions(void) = 0;
	virtual void DoIfLineLongerThanPreferredSize(void) const = 0;
	virtual UInt32 getCaretIndex(void) const = 0;
	virtual UInt32 getCaretLine(void) const = 0;
	virtual void setHighlight(UInt32 startline,UInt32 startindex,UInt32 endline,UInt32 endindex) = 0;
	virtual Real32 getHeightOfLine(void) = 0;
	virtual void doubleClickHandler(void) = 0;
	virtual void selectAll(void) = 0;
	virtual bool isLastCharacter(void) = 0;
	virtual void setTheClipBounds(Pnt2f topLeft,Pnt2f bottomRight) = 0;
	virtual void setStartingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine) = 0;
	virtual void setEndingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine) = 0;
	virtual char oppositeBrace(char val) = 0;
	virtual void findBrace(char theChar,UInt32 direction) = 0;
	virtual void removeBracesHighlightIndices(void) = 0;
	virtual bool isStartingBraces(char value) = 0;
	virtual bool isEndingBraces(char value) = 0;
	virtual UInt32 getNumberOfLeadingSpaces(UInt32 line) = 0;
	virtual Real32 getCaretXPosition(void) = 0;
	virtual Real32 getCaretYPosition(void) = 0;
	virtual Element* getRootElement(void) = 0;
	virtual UInt32 getHEI(void) = 0;
	virtual UInt32 getHEL(void) = 0;
	virtual UInt32 getHSI(void) = 0;
	virtual UInt32 getHSL(void) = 0;
	virtual void setHEI(UInt32) = 0;
	virtual void setHEL(UInt32) = 0;
	virtual void setHSI(UInt32) = 0;
	virtual void setHSL(UInt32) = 0;
	virtual Real32 getPreferredWidth(void) = 0;
	virtual bool getBracesHighlightFlag(void) = 0;
	virtual UInt32 getStartingBraceLine(void) = 0;
	virtual UInt32 getStartingBraceIndex(void) = 0;
	virtual UInt32 getEndingBraceLine(void) = 0;
	virtual UInt32 getEndingBraceIndex(void) = 0;
	virtual Pnt2f getEndXYPosition(UInt32 lineNumber) const = 0;
	virtual Pnt2f getStartXYPosition(UInt32 lineNumber) const = 0;
	virtual Pnt2f getXYPosition(UInt32 lineNumber,UInt32 index,bool isBeginning) const = 0;
	virtual Real32 getGutterSpace(void) = 0;
	virtual Real32 getGutterSeparation(void) = 0;
	virtual UInt32 CaretLineAndIndexToCaretOffsetInDOM(UInt32 CaretLine,UInt32 CaretIndex) = 0;
	virtual void setCaretIndexAndLine(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine) = 0;
	virtual char getNextCharacter(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine) = 0;
	virtual bool isLastCharacterOfLine(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine) = 0;

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

    /*! \}                                                                 */;

    TextDomArea* getParentTextDomArea(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextDomLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextDomLayoutManager(void);
    TextDomLayoutManager(const TextDomLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextDomLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextDomLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextDomLayoutManager &source);
};

typedef TextDomLayoutManager *TextDomLayoutManagerP;

OSG_END_NAMESPACE

#include "OSGTextDomLayoutManagerBase.inl"
#include "OSGTextDomLayoutManager.inl"

#endif /* _OSGTEXTDOMLAYOUTMANAGER_H_ */
