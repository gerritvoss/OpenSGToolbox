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

#include "OSGDocument.h"
#include "OSGTextDomView.h"
#include "OSGGlyphView.h"
#include "OSGPlainDocumentBranchElement.h"
#include "OSGPlainDocumentLeafElement.h"
#include "OSGPlainDocument.h"
#include "OSGTextDomArea.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGraphics.h"

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

	ElementRefPtr defaultRoot;
	PlainDocumentBranchElementRefPtr rootElement;
	Real32 _preferredHeight;
	Real32 _preferredWidth; 
	Real32 heightOfLine;
	Real32 calculateWidthOfLongestLine(PlainDocumentBranchElementRefPtr rootElement) const;
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
	void populateCache(void);

	//used - related to DOM
	void initializeRootElement();
	void deleteSelected(void);
	void deleteCharacters(UInt32 HSL,UInt32 HSI,UInt32 HEL,UInt32 HEI);

	//used - related to Layout
	UInt32 getTopmostVisibleLineNumber() const;
	UInt32 getLinesToBeDisplayed() const;
	void calculatePreferredSize(void);
	void updateSize(void);
	virtual void updateViews(void);
	bool isLastCharacterOfDocument() const;
	virtual Vec2f getContentRequestedSize(void) const;
	void calculateLineHeight(void);
	UInt32 calculateCaretPosition(Pnt2f PointOnComponent,bool isDragging);
	void checkCaretVisibility(UInt32 dir);
	bool isCaretVisible(void);
	void makeCaretVisible(UInt32 dir);
	bool isSomethingSelected(void);
	bool isStartLocationBeforeEndLocation(void) const;
	void moveCaretEnd(bool isControlPressed);
	void moveCaretHome(bool isControlPressed);
	void moveCaretUp(void);
	void moveCaretDown(void);
	void moveCaretLeft(void);
	void moveCaretRight(void);
	void moveTheCaret(UInt32 dir,bool isShiftPressed,bool isControlPressed);
	void moveAndHighlightWord(UInt32 dir);
	void recalculateCaretPositions(void);
	void DoIfLineLongerThanPreferredSize() const;
	UInt32 getCaretIndex(void) const;
	UInt32 getCaretLine(void) const;
	void setHighlight(UInt32 startline,UInt32 startindex,UInt32 endline,UInt32 endindex);
	Real32 getHeightOfLine(void);
	void doubleClickHandler(void);
	void selectAll(void);
	void tabHandler(bool isShiftPressed);
	bool isLastCharacter(void);
	void setTheClipBounds(Pnt2f topLeft,Pnt2f bottomRight);
	void setStartingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine);
	void setEndingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine);
	char oppositeBrace(char val);
	void findBrace(char theChar,UInt32 direction);
	void removeBracesHighlightIndices(void);
	bool isStartingBraces(char value);
	bool isEndingBraces(char value);
	UInt32 getNumberOfLeadingSpaces(UInt32 line);
	Real32 getCaretXPosition(void);
	Real32 getCaretYPosition(void);
	PlainDocumentBranchElementRefPtr getRootElement(void);
	UInt32 getHEI(void);
	UInt32 getHEL(void);
	UInt32 getHSI(void);
	UInt32 getHSL(void);
	Real32 getPreferredWidth(void);
	bool getBracesHighlightFlag(void);
	UInt32 getStartingBraceLine(void);
	UInt32 getStartingBraceIndex(void);
	UInt32 getEndingBraceLine(void);
	UInt32 getEndingBraceIndex(void);
	Pnt2f getEndXYPosition(UInt32 lineNumber) const;
	Pnt2f getStartXYPosition(UInt32 lineNumber) const;
	Pnt2f getXYPosition(UInt32 lineNumber,UInt32 index,bool isBeginning) const;
	Real32 getGutterSpace(void);
	Real32 getGutterSeparation(void);


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
