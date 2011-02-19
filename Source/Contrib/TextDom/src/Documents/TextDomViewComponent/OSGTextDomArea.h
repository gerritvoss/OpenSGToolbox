/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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

#ifndef _OSGTEXTDOMAREA_H_
#define _OSGTEXTDOMAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextDomAreaBase.h"
#include "OSGDocumentFields.h"
#include "OSGTextDomViewFields.h"
#include "OSGTextDomLayoutManagerFields.h"
#include "OSGColorLayerFields.h"
#include "OSGUndoManager.h"
#include "OSGCommandManager.h"
#include "OSGDocumentEventDetailsFields.h"
#include "OSGPlainDocumentLeafElementFields.h"
#include <boost/xpressive/xpressive.hpp>



OSG_BEGIN_NAMESPACE

/*! \brief TextDomArea class. See \ref
           PageContribTextDomTextDomArea for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextDomArea : public TextDomAreaBase
{
  public:

    enum
    {
        LEFT           = 0,
        RIGHT          = 1,
        UP             = 2,
        DOWN           = 3,
        HOME           = 4,
        END            = 5,
        HOMEOFNEXTLINE = 6,
        PAGEUP         = 7,
        PAGEDOWN       = 8
    };

    enum directionOfBraceSearch
    {
        BEFORE = 0,
        AFTER  = 1
    };

    typedef TextDomAreaBase Inherited;
    typedef TextDomArea     Self;
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
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    TextDomAreaTransitPtr createDuplicate(void);
    void setText(const std::string& txt);
    std::string getText(void) const;
    std::string getHighlightedString(void) const;
    TextDomLayoutManager* getTheManager(void) const;
    void setupCursor(void);

    virtual void mouseReleased(MouseEventDetails* const details);
    void mouseDragged(MouseEventDetails* const details);
    void mouseDraggedAfterArming(MouseEventDetails* const details);
    void keyTyped(KeyEventDetails* const details);
    virtual void mouseClicked(MouseEventDetails* const details);
    virtual void mousePressed(MouseEventDetails* const details);

    virtual void focusGained(FocusEventDetails* const details);
    virtual void focusLost(FocusEventDetails* const details);

    void loadFile(const BoostPath& pathOfFile);
    void saveFile(const BoostPath& pathOfFile);
    virtual void drawInternal(Graphics * const TheGraphics, Real32 Opacity = 1.0f) const;

    void updatePreferredSize(void);
    virtual Vec2f getContentRequestedSize(void) const;

    virtual Vec2f getPreferredScrollableViewportSize(void);
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft,
                                             const Pnt2f& VisibleRectBottomRight, 
                                             const UInt32& orientation, 
                                             const Int32& direction);

    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, 
                                              const Pnt2f& VisibleRectBottomRight, 
                                              const UInt32& orientation, 
                                              const Int32& direction);
    //Return true if a viewport should always force the height of this
    //Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);
        
    //Return true if a viewport should always force the width of this
    //Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this
    //Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this
    //Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

    void handleDocumentModelChanged(void);
    void handlePastingAString(const std::string& theClipboard);

    /*!
     * \brief Get the line number of the lowest index line that is currently
     * visible.
     *
     * The lines that are visible are determined by the clipping bounds of this
     * component
     */
    UInt32 getMinVisibleLineNumber(void) const;

    /*!
     * \brief Get the line number of the highest index line that is currently
     * visible.
     *
     * The lines that are visible are determined by the clipping bounds of this
     * component
     */
    UInt32 getMaxVisibleLineNumber(void) const;

    /*!
     * \brief Get the number of lines in the OSG::Document.  This does not includes
     * lines that are a result of line wrapping.
     */
    UInt32 getNumDocumentLines(void) const;

    /*!
     * \brief Get the number of lines.  This includes lines that are a result of
     * line wrapping.
     */
    UInt32 getNumLines(void) const;

    /*!
     * \brief Get the document line number that corresponds to the given line
     * number in this TextDomArea
     *
     * \param[in] LineNum The line number
     */
    UInt32 getDocumentLineNum(UInt32 LineNum) const;

    /*!
     * \brief Get the height of the line.
     *
     * \param[in] LineNum The line number to get the height of
     *
     * \returns The height of the line
     */
    Real32 getLineHeight(UInt32 LineNum) const;

    /*!
     * \brief Get the vertical position of a line
     *
     * \param[in] LineNum The line number
     */
    Real32 getLineVerticalPosition(UInt32 LineNum) const;

    /*!
     * \brief Is the given line the result of line wrapping.
     *
     * If a line of text is not wrapped, then the result will be false. If the
     * line of text is wrapped, then the first wrapped line will be false and
     * all subsequent lines will be true
     *
     * \param[in] LineNum The line number
     */
    bool isWrappedLine(UInt32 LineNum) const;

    void tabHandler(bool isShiftPressed);

    bool searchForStringInDocumentUsingRegEx(const std::string& stringToBeLookedFor,
                                             bool isCaseChecked,
                                             bool isWholeWordChecked,
                                             bool searchUp,
                                             bool wrapAround,
                                             bool isUseRegExChecked);

    void replaceAllUsingRegEx(const std::string& theSearchText,
                              const std::string& theReplaceText,
                              bool isCaseChecked,
                              bool isWholeWordChecked,
                              bool isUseRegExChecked);

    void bookmarkAllUsingRegEx(const std::string& stringToBeLookedFor,
                               bool isCaseChecked,
                               bool isWholeWordChecked,
                               bool isUseRegExChecked);

    static std::string initialSearchStringModification(const std::string& stringToBeLookedFor,
                                                       bool isUseRegExChecked);

    void regexCompiling(const std::string& stringToBeLookedFor,
                        boost::xpressive::sregex& rex,
                        bool isCaseChecked,
                        bool isWholeWordChecked);

    void write(const std::string& txt);
    void clear(void);
    /*=========================  PROTECTED  ===============================*/

  protected:
    virtual Layer*  getDrawnBackground(void) const;
    virtual Layer*  getDrawnForeground(void) const;
    virtual Border* getDrawnBorder    (void) const;

    void createDefaultLayer(void);
    bool _IsMousePressed;
    void drawHighlightBG(Graphics * const TheGraphics, Real32 Opacity) const;
    void drawLineHighlight(Graphics * const TheGraphics, Real32 Opacity) const;
    void drawBookmarkHighlight(Graphics * const TheGraphics, Real32 Opacity) const;
    void drawBraceHighlight(Graphics * const TheGraphics, Real32 Opacity) const;
    void drawTheCaret(Graphics * const TheGraphics, Real32 Opacity) const;

    void drawHighlightBGInternal(Graphics * const TheGraphics,
                                 Real32 Opacity,
                                 UInt32 lesserLine,
                                 UInt32 lesserIndex,
                                 UInt32 greaterLine,
                                 UInt32 greaterIndex) const;

    std::string getHighlightedStringInternal(UInt32 lesserLine,
                                             UInt32 lesserIndex,
                                             UInt32 greaterLine,
                                             UInt32 greaterIndex) const;

    void insertCharacterUsingCommandManager(char theCharacter,UInt32 line,UInt32 index);
    void deleteSelectedUsingCommandManager(void);
    void deleteCharacterUsingCommandManager(void);
    void setTextUsingCommandManager(PlainDocumentLeafElement* const theElement,std::string theString);
    void insertStringUsingCommandManager(UInt32 caretPosition,std::string theString);
    void highlightIfNextCharacterIsABrace(void);
    void createDefaultDocument(void);
    //void stringToUpper(std::string& strToConvert);



    CommandManagerPtr	_TheCommandManager;
    UndoManagerPtr	_TheUndoManager;

	mutable Time _CurrentCaretBlinkElps;

	//Gives notification that an attribute or set of attributes changed.
    void handleDocumentChanged(DocumentEventDetails* const details);

	//Gives notification that there was an insert of something into the document.
	void handleDocumentInsert(DocumentEventDetails* const details);

	//Gives notification when something has been removed
	void handleDocumentRemove(DocumentEventDetails* const details);


    boost::signals2::connection _DocumentChangedConnection,
                                _DocumentInsertConnection,
                                _DocumentRemoveConnection;



    void handleCaretUpdate(UpdateEventDetails* const details);

    boost::signals2::connection _CaretUpdateConnection;
    bool _DrawCaret;

    // Variables should all be in TextDomAreaBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextDomArea(void);
    TextDomArea(const TextDomArea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextDomArea(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const TextDomArea *source = NULL);
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextDomAreaBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextDomArea &source);
};

typedef TextDomArea *TextDomAreaP;

OSG_END_NAMESPACE

#include "OSGGlyphView.h"

#include "OSGTextDomAreaBase.inl"
#include "OSGTextDomArea.inl"

#endif /* _OSGTEXTDOMAREA_H_ */
