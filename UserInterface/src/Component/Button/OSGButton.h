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
#include "Util/OSGUIDefines.h"
#include "Event/OSGActionListener.h"
#include <OpenSG/Input/OSGMouseAdapter.h>
#include <OpenSG/Input/OSGUpdateListener.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING Button : public ButtonBase
{
  private:

    typedef ButtonBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

	virtual void mouseClicked(const MouseEvent& e);
    virtual void mouseEntered(const MouseEvent& e);
    virtual void mouseExited(const MouseEvent& e);
    virtual void mousePressed(const MouseEvent& e);
    virtual void mouseReleased(const MouseEvent& e);

    void addActionListener(ActionListenerPtr Listener);
    void removeActionListener(ActionListenerPtr Listener);

    void addMousePressedActionListener(ActionListenerPtr Listener);
    void removeMousePressedActionListener(ActionListenerPtr Listener);

    void setTexture(TextureChunkPtr TheTexture);
    void setActiveTexture(TextureChunkPtr TheTexture);
    void setFocusedTexture(TextureChunkPtr TheTexture);
    void setRolloverTexture(TextureChunkPtr TheTexture);
    void setDisabledTexture(TextureChunkPtr TheTexture);

    void setImage(ImagePtr TheImage);
    void setActiveImage(ImagePtr TheImage);
    void setFocusedImage(ImagePtr TheImage);
    void setRolloverImage(ImagePtr TheImage);
    void setDisabledImage(ImagePtr TheImage);
    
    void setImage(const std::string& Path);
    void setActiveImage(const std::string& Path);
    void setFocusedImage(const std::string& Path);
    void setRolloverImage(const std::string& Path);
    void setDisabledImage(const std::string& Path);

	void getTextBounds(Pnt2f& TextTopLeft, Pnt2f& TextBottomRight) const;
	void setPreferredSizeByContents(const Real32 Insets);

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

    virtual void actionPreformed(const ActionEvent& e);
    virtual void mousePressedActionPreformed(const ActionEvent& e);

	virtual void drawInternal(const GraphicsPtr Graphics) const;
    virtual Color4f getDrawnTextColor(void) const;
    virtual BorderPtr getDrawnBorder(void) const;
    virtual UIBackgroundPtr getDrawnBackground(void) const;
    virtual UIDrawObjectCanvasPtr getDrawnDrawObject(void) const;
    
	class ButtonArmedListener : public MouseAdapter,public UpdateListener
	{
	public :
		ButtonArmedListener(ButtonPtr TheButton);
		
		virtual void mouseReleased(const MouseEvent& e);
        virtual void update(const UpdateEvent& e);
        void reset(void);
	protected :
		ButtonPtr _Button;
	    Time _ActionFireElps;
	};

	friend class ButtonArmedListener;

	ButtonArmedListener _ButtonArmedListener;
    bool _Armed;
    
    static UIDrawObjectCanvasPtr createTexturedDrawObjectCanvas(TextureChunkPtr TheTexture);
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
	
    virtual void produceActionPerformed(const ActionEvent& e);
    virtual void produceMousePressedActionPerformed(const ActionEvent& e);
};

typedef Button *ButtonP;

OSG_END_NAMESPACE

#include "OSGButtonBase.inl"
#include "OSGButton.inl"

#define OSGBUTTON_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGBUTTON_H_ */
