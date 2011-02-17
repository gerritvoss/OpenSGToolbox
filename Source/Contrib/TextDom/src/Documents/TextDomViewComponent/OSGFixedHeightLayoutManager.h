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

#ifndef _OSGFIXEDHEIGHTLAYOUTMANAGER_H_
#define _OSGFIXEDHEIGHTLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFixedHeightLayoutManagerBase.h"
#include "OSGUIFont.h"

#include "OSGDocumentFields.h"
#include "OSGElementFields.h"
#include "OSGTextDomViewFields.h"
#include "OSGGlyphViewFields.h"
#include "OSGTextDomAreaFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief FixedHeightLayoutManager class. See \ref
           PageContribTextDomFixedHeightLayoutManager for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING FixedHeightLayoutManager : public FixedHeightLayoutManagerBase
{
  protected:


	enum {LEFT,RIGHT,UP,DOWN,HOME,END,HOMEOFNEXTLINE,PAGEUP,PAGEDOWN};
	enum directionOfBraceSearch{BEFORE,AFTER};
	bool _BracesHighlightFlag;
	UInt32 _StartingBraceIndex;
	UInt32 _StartingBraceLine;
	UInt32 _EndingBraceIndex;
	UInt32 _EndingBraceLine;

	// would be used for word wrapped data
	std::vector<UInt32> linesToElements;
	UInt32 getFirstLineOfElement(UInt32 lineNumber);
	UInt32 totalNumberOfLines(void);
	UInt32 getNumberOfLines(UInt32 lineNumber);
	////

	Element* defaultRoot;
	Element* rootElement;
	Real32 _preferredHeight;
	Real32 _preferredWidth; 
	Real32 heightOfLine;
	Real32 calculateWidthOfLongestLine(Element* const rootElement) const;
	bool insideGutterRegion(Real32 PointOnComponentX)const;
	bool isCaretInWidthRange(void);
	UInt32 _CaretLine;
	UInt32 _CaretIndex;
	Real32 _CaretXPosition;
	Real32 _CaretYPosition;
	UInt32 _HighlightStartLine;
	UInt32 _HighlightStartIndex;
	UInt32 _HighlightEndLine;
	UInt32 _HighlightEndIndex;
	Pnt2f _TheClipBoundsTopLeft;
	Pnt2f _TheClipBoundsBottomRight;
	
	Real32 _GutterSpace;
	Real32 _GutterSeparation;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FixedHeightLayoutManagerBase Inherited;
    typedef FixedHeightLayoutManager     Self;
	
	
	virtual void printDebugInformation(void) const;
	virtual void populateCache(void);

	//used - related to DOM
	virtual void initializeRootElement();
	virtual void deleteSelected(void);
	virtual void deleteCharacters(UInt32 HSL,UInt32 HSI,UInt32 HEL,UInt32 HEI);

	//used - related to Layout
	virtual UInt32 getTopmostVisibleLineNumber(void) const;
	virtual UInt32 getLinesToBeDisplayed(void) const;
	virtual void calculatePreferredSize(void);
	virtual void updateSize(void);
	virtual void updateViews(void);
	virtual bool isLastCharacterOfDocument(void) const;
	virtual Vec2f getContentRequestedSize(void) const;
	virtual void calculateLineHeight(void);
	virtual UInt32 calculateCaretPosition(Pnt2f PointOnComponent,bool isDragging);
	virtual void checkCaretVisibility(void);
	virtual bool isCaretVisible(void);
	virtual void makeCaretVisible(void);
	virtual bool isSomethingSelected(void);
	virtual bool isStartLocationBeforeEndLocation(void) const;
	virtual void moveCaretEnd(bool isControlPressed);
	virtual void moveCaretHome(bool isControlPressed);
	virtual void moveCaretUp(void);
	virtual void moveCaretDown(void);
	virtual void moveCaretLeft(void);
	virtual void moveCaretRight(void);
	virtual void moveTheCaret(UInt32 dir,bool isShiftPressed,bool isControlPressed);
	virtual void moveAndHighlightWord(UInt32 dir);
	virtual void recalculateCaretPositions(void);
	virtual void DoIfLineLongerThanPreferredSize(void);
	virtual UInt32 getCaretIndex(void) const;
	virtual UInt32 getCaretLine(void) const;
	virtual void setCaretIndex(UInt32);
	virtual void setCaretLine(UInt32);
	virtual void setHighlight(UInt32 startline,UInt32 startindex,UInt32 endline,UInt32 endindex);
	virtual Real32 getHeightOfLine(void);
	virtual void doubleClickHandler(void);
	virtual void selectAll(void);
	virtual bool isLastCharacter(void);
	virtual void setTheClipBounds(Pnt2f topLeft,Pnt2f bottomRight);
	virtual void setStartingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine,bool isNewCharacter);
	virtual void setEndingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine);
	virtual char oppositeBrace(char val);
	virtual void findBrace(char theChar,UInt32 direction,bool isNewCharacter);
	virtual void removeBracesHighlightIndices(void);
	virtual bool isStartingBraces(char value);
	virtual bool isEndingBraces(char value);
	virtual UInt32 getNumberOfLeadingSpaces(UInt32 line);
	virtual Real32 getCaretXPosition(void);
	virtual Real32 getCaretYPosition(void);
	virtual Element* getRootElement(void);
	virtual UInt32 getHEI(void);
	virtual UInt32 getHEL(void);
	virtual UInt32 getHSI(void);
	virtual UInt32 getHSL(void);
	virtual void setHEI(UInt32);
	virtual void setHEL(UInt32);
	virtual void setHSI(UInt32);
	virtual void setHSL(UInt32);
	virtual Real32 getPreferredWidth(void);
	virtual bool getBracesHighlightFlag(void);
	virtual UInt32 getStartingBraceLine(void);
	virtual UInt32 getStartingBraceIndex(void);
	virtual UInt32 getEndingBraceLine(void);
	virtual UInt32 getEndingBraceIndex(void);
	virtual Pnt2f getEndXYPosition(UInt32 lineNumber) const;
	virtual Pnt2f getStartXYPosition(UInt32 lineNumber) const;
	virtual Pnt2f getXYPosition(UInt32 lineNumber,UInt32 index,bool isBeginning) const;
	virtual Real32 getGutterSpace(void);
	virtual Real32 getGutterSeparation(void);
	virtual UInt32 CaretLineAndIndexToCaretOffsetInDOM(UInt32 CaretLine,UInt32 CaretIndex);
	virtual void setCaretIndexAndLine(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine);
	virtual char getNextCharacter(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine);
	virtual bool isLastCharacterOfLine(UInt32 _theOriginalCaretIndex,UInt32 _theOriginalCaretLine);
	virtual void highlightString(UInt32 _theOriginalCaretLine,UInt32 _theOriginalCaretIndex,std::string _StringToBeInserted);

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FixedHeightLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FixedHeightLayoutManager(void);
    FixedHeightLayoutManager(const FixedHeightLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FixedHeightLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FixedHeightLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FixedHeightLayoutManager &source);
};

typedef FixedHeightLayoutManager *FixedHeightLayoutManagerP;

OSG_END_NAMESPACE
#include "OSGTextDomArea.h"

#include "OSGFixedHeightLayoutManagerBase.inl"
#include "OSGFixedHeightLayoutManager.inl"

#endif /* _OSGFIXEDHEIGHTLAYOUTMANAGER_H_ */
