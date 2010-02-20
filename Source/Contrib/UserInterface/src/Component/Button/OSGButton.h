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
#include "OSGActionListener.h"
#include "OSGMouseAdapter.h"
#include "OSGUpdateListener.h"

#include "OSGEventConnection.h"

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

	virtual void mouseClicked(const MouseEventUnrecPtr e);
    virtual void mouseEntered(const MouseEventUnrecPtr e);
    virtual void mouseExited(const MouseEventUnrecPtr e);
    virtual void mousePressed(const MouseEventUnrecPtr e);
    virtual void mouseReleased(const MouseEventUnrecPtr e);

    EventConnection addActionListener(ActionListenerPtr Listener);
	bool isActionListenerAttached(ActionListenerPtr Listener) const;
    void removeActionListener(ActionListenerPtr Listener);

    EventConnection addMousePressedActionListener(ActionListenerPtr Listener);
	bool isMousePressedActionListenerAttached(ActionListenerPtr Listener) const;
    void removeMousePressedActionListener(ActionListenerPtr Listener);

    void setTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledTexture(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    void setImage(ImageRefPtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(ImageRefPtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(ImageRefPtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(ImageRefPtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(ImageRefPtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    
    void setImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));

	void getTextBounds(Pnt2f& TextTopLeft, Pnt2f& TextBottomRight) const;

    bool getActive(void) const;
    void setActive(bool Value);

	virtual void setBorders(BorderRefPtr TheBorder);

	virtual void setBackgrounds(LayerRefPtr TheBackground);
    
	virtual void setForegrounds(LayerRefPtr TheForeground);
    
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

    virtual void actionPreformed(const ActionEventUnrecPtr e);
    virtual void mousePressedActionPreformed(const ActionEventUnrecPtr e);

	virtual void drawInternal(const GraphicsWeakPtr TheGraphics, Real32 Opacity = 1.0f) const;
	virtual void drawText(const GraphicsWeakPtr TheGraphics, const Pnt2f& TopLeft, Real32 Opacity = 1.0f) const;

    virtual Color4f getDrawnTextColor(void) const;
    virtual BorderRefPtr getDrawnBorder(void) const;
    virtual LayerRefPtr getDrawnBackground(void) const;
    virtual LayerRefPtr getDrawnForeground(void) const;
    virtual UIDrawObjectCanvasRefPtr getDrawnDrawObject(void) const;
	virtual UIDrawObjectCanvasRefPtr getBaseDrawObject(void) const;
    virtual Vec2f getDrawnOffset(void) const;
    
	class ButtonArmedListener : public MouseAdapter,public UpdateListener
	{
	public :
		ButtonArmedListener(ButtonRefPtr TheButton);
		
		virtual void mouseReleased(const MouseEventUnrecPtr e);
        virtual void update(const UpdateEventUnrecPtr e);
        void reset(void);
	protected :
		ButtonRefPtr _Button;
	    Time _ActionFireElps;
	};

	friend class ButtonArmedListener;

	ButtonArmedListener _ButtonArmedListener;
    bool _Armed;
    
    static UIDrawObjectCanvasRefPtr createTexturedDrawObjectCanvas(TextureObjChunkRefPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    bool _Active;
    EventConnection   _ArmedUpdateEventConnection;
    EventConnection   _ArmedMouseEventConnection;
	
	typedef std::set<ActionListenerPtr> ActionListenerSet;
    typedef ActionListenerSet::iterator ActionListenerSetItor;
    typedef ActionListenerSet::const_iterator ActionListenerSetConstItor;
	
    ActionListenerSet       _ActionListeners;
    ActionListenerSet       _MousePressedActionListeners;
	
    virtual void produceActionPerformed(const ActionEventUnrecPtr e);
    virtual void produceMousePressedActionPerformed(const ActionEventUnrecPtr e);
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
