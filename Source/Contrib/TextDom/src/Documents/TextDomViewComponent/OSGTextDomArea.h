/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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
  protected:

	  enum {LEFT,RIGHT,UP,DOWN,HOME,END,HOMEOFNEXTLINE,PAGEUP,PAGEDOWN};

	  UIFontRefPtr _Font;
	  ColorLayerRefPtr tempBackground;
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
                                               UInt32 greaterIndex);

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

  public:

	typedef TextDomAreaBase Inherited;
    typedef TextDomArea     Self;
	
	TextDomAreaTransitPtr createDuplicate(void);
	void setText(std::string txt);
	std::string getText(void);
	std::string getHighlightedString(void);
	TextDomLayoutManager* getTheManager(void);
	void setupCursor(void);

	void  createDefaultFont(void);

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
    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

	void handleDocumentModelChanged();
	void handlePastingAString(const std::string& theClipboard);

	UInt32 getTopmostVisibleLineNumber(void);
	UInt32 getLinesToBeDisplayed(void);
	Real32 getHeightOfLine(void);
	void tabHandler(bool isShiftPressed);
	bool searchForStringInDocumentUsingRegEx(std::string& stringToBeLookedFor,const bool& isCaseChecked,const bool& isWholeWordChecked,const bool &searchUp,const bool &wrapAround,const bool &isUseRegExChecked);
	void replaceAllUsingRegEx(std::string& theSearchText,const std::string& theReplaceText,const bool& isCaseChecked,const bool &isWholeWordChecked,const bool &isUseRegExChecked);
	void bookmarkAllUsingRegEx(std::string& stringToBeLookedFor,const bool& isCaseChecked,const bool& isWholeWordChecked,const bool &isUseRegExChecked);

	void initialSearchStringModification(std::string& stringToBeLookedFor,const bool& isUseRegExChecked);
	void regexCompiling(const std::string& stringToBeLookedFor,boost::xpressive::sregex& rex,const bool& isCaseChecked,const bool& isWholeWordChecked);

	void write(std::string txt);
	void clear(void);
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
    /*=========================  PROTECTED  ===============================*/

  protected:

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

#include "OSGTextDomAreaBase.inl"
#include "OSGTextDomArea.inl"

#endif /* _OSGTEXTDOMAREA_H_ */
