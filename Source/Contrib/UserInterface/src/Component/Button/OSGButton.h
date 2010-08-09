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

#ifndef _OSGBUTTON_H_
#define _OSGBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGButtonBase.h"
#include "OSGBorder.h"
#include "OSGLayer.h"
#include "OSGUIFont.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTextureObjChunk.h"

OSG_BEGIN_NAMESPACE

/*! \brief Button class. See \ref
           PageContribUserInterfaceButton for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Button : public ButtonBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum DrawObjectToTextAlignment
    {
        ALIGN_DRAW_OBJECT_LEFT_OF_TEXT  = 0,
        ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT = 1,
        ALIGN_DRAW_OBJECT_ABOVE_TEXT    = 2,
        ALIGN_DRAW_OBJECT_BELOW_TEXT    = 3
    };

    typedef ButtonBase Inherited;
    typedef Button     Self;

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
    virtual Vec2f getContentRequestedSize(void) const;

	virtual void mouseClicked(MouseEventDetails* const e);
    virtual void mouseEntered(MouseEventDetails* const e);
    virtual void mouseExited(MouseEventDetails* const e);
    virtual void mousePressed(MouseEventDetails* const e);
    virtual void mouseReleased(MouseEventDetails* const e);

    void setTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledTexture(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    void setImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(Image* const TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    
    void setImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));

	void getTextBounds(Pnt2f& TextTopLeft, Pnt2f& TextBottomRight) const;

    bool getActive(void) const;
    void setActive(bool Value);

	virtual void setBorders(Border* const TheBorder);

	virtual void setBackgrounds(Layer* const TheBackground);
    
	virtual void setForegrounds(Layer* const TheForeground);
    
    virtual void setTextColors( const Color4f &value );

    virtual void detachFromEventProducer(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Button(void);
    Button(const Button &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Button(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    static UIDrawObjectCanvasTransitPtr createTexturedDrawObjectCanvas(TextureObjChunk* const TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    virtual void actionPreformed(ActionEventDetails* const e);
    virtual void mousePressedActionPreformed(ActionEventDetails* const e);

	virtual void drawInternal(Graphics* const TheGraphics, Real32 Opacity = 1.0f) const;
	virtual void drawText(Graphics* const TheGraphics, const Pnt2f& TopLeft, Real32 Opacity = 1.0f) const;

    virtual Color4f getDrawnTextColor(void) const;
    virtual Border* getDrawnBorder(void) const;
    virtual Layer* getDrawnBackground(void) const;
    virtual Layer* getDrawnForeground(void) const;
    virtual UIDrawObjectCanvas* getDrawnDrawObject(void) const;
	virtual UIDrawObjectCanvas* getBaseDrawObject(void) const;
    virtual Vec2f getDrawnOffset(void) const;
    
		
	void handleArmedMouseReleased(MouseEventDetails* const e);
    void resetArmed(void);
    void handleArmedUpdate(UpdateEventDetails* const e);
    boost::signals2::connection   _ArmedUpdateEventConnection;
    boost::signals2::connection   _ArmedMouseReleasedConnection;

    Time _ActionFireElps;
    bool _Armed;
    bool _Active;
	
    virtual void produceActionPerformed(void);
    virtual void produceMousePressedActionPerformed(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ButtonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Button &source);
};

typedef Button *ButtonP;

OSG_END_NAMESPACE

#include "OSGButtonBase.inl"
#include "OSGButton.inl"

#endif /* _OSGBUTTON_H_ */
