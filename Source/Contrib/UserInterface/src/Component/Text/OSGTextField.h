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

#ifndef _OSGTEXTFIELD_H_
#define _OSGTEXTFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextFieldBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextField class. See \ref
           PageContribUserInterfaceTextField for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TextField : public TextFieldBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextFieldBase Inherited;
    typedef TextField     Self;

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

	Vec2f getContentRequestedSize(void) const;

	virtual void keyTyped(KeyEventDetails* const e);

	virtual void mouseClicked(MouseEventDetails* const e);
	virtual void mousePressed(MouseEventDetails* const e);
	
	virtual void focusGained(FocusEventDetails* const e);
	virtual void focusLost(FocusEventDetails* const e);

	virtual std::string getDrawnText(void) const;

    virtual void detachFromEventProducer(void);
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextFieldBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextField(void);
    TextField(const TextField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextField(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
	void calculateTextBounds(const UInt32 StartIndex, const UInt32 EndIndex, Pnt2f& TopLeft, Pnt2f& BottomRight);
	
    virtual void produceActionPerformed(void);
	
	Time _CurrentCaretBlinkElps;
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
    friend class TextFieldBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextField &source);
};

typedef TextField *TextFieldP;

OSG_END_NAMESPACE

#include "OSGTextFieldBase.inl"
#include "OSGTextField.inl"

#endif /* _OSGTEXTFIELD_H_ */
