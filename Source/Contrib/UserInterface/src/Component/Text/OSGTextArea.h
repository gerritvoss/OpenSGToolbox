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

#ifndef _OSGTEXTAREA_H_
#define _OSGTEXTAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextAreaBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextArea class. See \ref
           PageContribUserInterfaceTextArea for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TextArea : public TextAreaBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextAreaBase Inherited;
    typedef TextArea     Self;

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

	struct TextLine{
		UInt32 _StartPosition;
		UInt32 _EndPosition;
		Real32 _VerticalOffset;
		Real32 _LeftHorizontalOffset;
		Real32 _RightHorizontalOffset;
	};

	virtual void keyTyped(KeyEventDetails* const e);
	virtual void mouseClicked(MouseEventDetails* const e);
	virtual void mousePressed(MouseEventDetails* const e);
	
	virtual void focusGained(FocusEventDetails* const e);
	virtual void focusLost(FocusEventDetails* const e);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one block of rows or columns, depending on the value of orientation.
    virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

    //Components that display logical rows or columns should compute the scroll increment that will completely expose one new row or column, depending on the value of orientation.
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction);

	virtual Int32 getCaretLine(void) const;
	virtual Int32 getCaretColumn(void) const;
	virtual UInt32 numLines(void) const;
	virtual std::string getLine(UInt32 line) const;
	virtual std::string getWrappedLine(UInt32 line) const;

	virtual bool isLineVisible(const UInt32& line) const;
    virtual UInt32 numVisibleLines(void) const;

	virtual void scrollToLine(const UInt32& line);

    
    virtual void moveCaretToEndOfLine(void);
    virtual void moveCaretToBeginOfLine(void);
    
    void moveCaretLine(Int32 delta);

    virtual void detachFromEventProducer(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextAreaBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextArea(void);
    TextArea(const TextArea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextArea(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
    
	mutable Time _CurrentCaretBlinkElps;
	
    void handleCaretUpdate(UpdateEventDetails* const e);
    boost::signals2::connection _CaretUpdateConnection;

    void handleMouseDownKeyTyped(KeyEventDetails* const e);
    void handleMouseDownMouseReleased(MouseEventDetails* const e);
    void handleMouseDownMouseDragged(MouseEventDetails* const e);
    boost::signals2::connection _MouseDownKeyTypedConnection,
                                _MouseDownMouseReleasedConnection,
                                _MouseDownMouseDraggedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextAreaBase;

	Int32 findTextPosition(Pnt2f Input);
    static void initMethod(void);

	std::vector<TextLine> _LineContents;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextArea &source);
};

typedef TextArea *TextAreaP;

OSG_END_NAMESPACE

#include "OSGTextAreaBase.inl"
#include "OSGTextArea.inl"

#endif /* _OSGTEXTAREA_H_ */
