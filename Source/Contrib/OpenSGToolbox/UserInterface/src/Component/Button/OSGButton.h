/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTextureChunk.h>
#include "OSGUserInterfaceDef.h"

#include "OSGButtonBase.h"
#include "Event/OSGActionListener.h"
#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGUpdateListener.h>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Button : public ButtonBase
{
  private:

    typedef ButtonBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	enum DrawObjectToTextAlignment{ALIGN_DRAW_OBJECT_LEFT_OF_TEXT=0, ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT, ALIGN_DRAW_OBJECT_ABOVE_TEXT, ALIGN_DRAW_OBJECT_BELOW_TEXT};

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    virtual Vec2f getContentRequestedSize(void) const;

	virtual void mouseClicked(const MouseEventPtr e);
    virtual void mouseEntered(const MouseEventPtr e);
    virtual void mouseExited(const MouseEventPtr e);
    virtual void mousePressed(const MouseEventPtr e);
    virtual void mouseReleased(const MouseEventPtr e);

    EventConnection addActionListener(ActionListenerPtr Listener);
	bool isActionListenerAttached(ActionListenerPtr Listener) const;
    void removeActionListener(ActionListenerPtr Listener);

    EventConnection addMousePressedActionListener(ActionListenerPtr Listener);
	bool isMousePressedActionListenerAttached(ActionListenerPtr Listener) const;
    void removeMousePressedActionListener(ActionListenerPtr Listener);

    void setTexture(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveTexture(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedTexture(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverTexture(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledTexture(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    void setImage(ImagePtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(ImagePtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(ImagePtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(ImagePtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(ImagePtr TheImage, Vec2f Size = Vec2f(-1.0f,-1.0f));
    
    void setImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setActiveImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setFocusedImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setRolloverImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));
    void setDisabledImage(const std::string& Path, Vec2f Size = Vec2f(-1.0f,-1.0f));

	void getTextBounds(Pnt2f& TextTopLeft, Pnt2f& TextBottomRight) const;

    bool getActive(void) const;
    void setActive(bool Value);

	virtual void setBorders(BorderPtr TheBorder);

	virtual void setBackgrounds(LayerPtr TheBackground);
    
	virtual void setForegrounds(LayerPtr TheForeground);
    
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

    virtual void actionPreformed(const ActionEventPtr e);
    virtual void mousePressedActionPreformed(const ActionEventPtr e);

	virtual void drawInternal(const GraphicsPtr TheGraphics, Real32 Opacity = 1.0f) const;
	virtual void drawText(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft, Real32 Opacity = 1.0f) const;

    virtual Color4f getDrawnTextColor(void) const;
    virtual BorderPtr getDrawnBorder(void) const;
    virtual LayerPtr getDrawnBackground(void) const;
    virtual LayerPtr getDrawnForeground(void) const;
    virtual UIDrawObjectCanvasPtr getDrawnDrawObject(void) const;
	virtual UIDrawObjectCanvasPtr getBaseDrawObject(void) const;
    virtual Vec2f getDrawnOffset(void) const;
    
	class ButtonArmedListener : public MouseAdapter,public UpdateListener
	{
	public :
		ButtonArmedListener(ButtonPtr TheButton);
		
		virtual void mouseReleased(const MouseEventPtr e);
        virtual void update(const UpdateEventPtr e);
        void reset(void);
	protected :
		ButtonPtr _Button;
	    Time _ActionFireElps;
	};

	friend class ButtonArmedListener;

	ButtonArmedListener _ButtonArmedListener;
    bool _Armed;
    
    static UIDrawObjectCanvasPtr createTexturedDrawObjectCanvas(TextureChunkPtr TheTexture, Vec2f Size = Vec2f(-1.0f,-1.0f));

    bool _Active;
    EventConnection   _ArmedUpdateEventConnection;
    EventConnection   _ArmedMouseEventConnection;
    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ButtonBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Button &source);
	
	
	typedef std::set<ActionListenerPtr> ActionListenerSet;
    typedef ActionListenerSet::iterator ActionListenerSetItor;
    typedef ActionListenerSet::const_iterator ActionListenerSetConstItor;
	
    ActionListenerSet       _ActionListeners;
    ActionListenerSet       _MousePressedActionListeners;
	
    virtual void produceActionPerformed(const ActionEventPtr e);
    virtual void produceMousePressedActionPerformed(const ActionEventPtr e);
};

typedef Button *ButtonP;

OSG_END_NAMESPACE

#include "OSGButtonBase.inl"
#include "OSGButton.inl"

#endif /* _OSGBUTTON_H_ */