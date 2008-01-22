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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGButton.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/OSGImageFileHandler.h>

#include "Graphics/UIDrawObjects/OSGTexturedQuadUIDrawObject.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Button
A UI Button.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Button::initMethod (void)
{
}

UIDrawObjectCanvasPtr Button::createTexturedDrawObjectCanvas(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas = UIDrawObjectCanvas::create();
    TexturedQuadUIDrawObjectPtr TextureDrawObject = TexturedQuadUIDrawObject::create();

    Vec2s ImageSize;
    ImageSize.setValues(TheTexture->getImage()->getWidth(), TheTexture->getImage()->getHeight());
    
    beginEditCP(TextureDrawObject);
        TextureDrawObject->setPoint1(Pnt2s(0,0));
        TextureDrawObject->setPoint2(Pnt2s(ImageSize.x(),0));
        TextureDrawObject->setPoint3(Pnt2s(ImageSize.x(),ImageSize.y()));
        TextureDrawObject->setPoint4(Pnt2s(0,ImageSize.y()));
        
        TextureDrawObject->setTexCoord1(Vec2f(0.0,1.0));
        TextureDrawObject->setTexCoord2(Vec2f(1.0,1.0));
        TextureDrawObject->setTexCoord3(Vec2f(1.0,0.0));
        TextureDrawObject->setTexCoord4(Vec2f(0.0,0.0));

        TextureDrawObject->setTexture(TheTexture);

        TextureDrawObject->setOpacity(1.0);
    endEditCP(TextureDrawObject);
    
    beginEditCP(DrawObjectCanvas, UIDrawObjectCanvas::DrawObjectsFieldMask);
        DrawObjectCanvas->getDrawObjects().push_back(TextureDrawObject);
    endEditCP(DrawObjectCanvas, UIDrawObjectCanvas::DrawObjectsFieldMask);

    return DrawObjectCanvas;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

BorderPtr Button::getDrawnBorder(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveBorder();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBorder();
        }
        else
        {
            return getBorder();
        }
    }
    else
    {
        return getDisabledBorder();
    }
}

UIBackgroundPtr Button::getDrawnBackground(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveBackground();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBackground();
        }
        else
        {
            return getBackground();
        }
    }
    else
    {
        return getDisabledBackground();
    }
}

Color4f Button::getDrawnTextColor(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveTextColor();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverTextColor();
        }
        else
        {
            return getTextColor();
        }
    }
    else
    {
        return getDisabledTextColor();
    }
}

UIDrawObjectCanvasPtr Button::getDrawnDrawObject(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedDrawObject();
        //}
        if(getActive())
        {
            return getActiveDrawObject();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverDrawObject();
        }
        else
        {
            return getDrawObject();
        }
    }
    else
    {
        return getDisabledDrawObject();
    }
}
void Button::drawInternal(const GraphicsPtr TheGraphics) const
{
   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   
   //If I have a DrawObject then Draw it
   UIDrawObjectCanvasPtr DrawnDrawObject = getDrawnDrawObject();
   if(DrawnDrawObject != NullFC)
   {
      //Calculate Alignment
      Pnt2s AlignedPosition;
      Pnt2s DrawObjectTopLeft, DrawObjectBottomRight;
      DrawnDrawObject->getBounds(DrawObjectTopLeft, DrawObjectBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (DrawObjectBottomRight - DrawObjectTopLeft),getVerticalAlignment(), getHorizontalAlignment());

      //If active then translate the Text by the Active Offset
      if(getActive())
      {
          AlignedPosition = AlignedPosition + getActiveOffset();
      }

	  //Draw the DrawnDrawObject
        beginEditCP(DrawnDrawObject, PositionFieldMask);
            DrawnDrawObject->setPosition( AlignedPosition );
        endEditCP(DrawnDrawObject, PositionFieldMask);

        DrawnDrawObject->draw(TheGraphics);

   }

   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NullFC)
   {
      //Calculate Alignment
      Pnt2s AlignedPosition;
      Pnt2s TextTopLeft, TextBottomRight;
      getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getVerticalAlignment(), getHorizontalAlignment());

      //If active then translate the Text by the Active Offset
      if(getActive())
      {
          AlignedPosition = AlignedPosition + getActiveOffset();
      }

	  //Draw the Text
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), getDrawnTextColor(), getOpacity());
   }

}

void Button::actionPreformed(const ActionEvent& e)
{
}

void Button::mousePressedActionPreformed(const ActionEvent& e)
{
}

void Button::mouseClicked(const MouseEvent& e)
{
	Component::mouseClicked(e);
}

void Button::mouseEntered(const MouseEvent& e)
{
	if(getEnabled())
	{
		if(_Armed)
		{
			beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
				ButtonPtr(this)->setActive(true);
			endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		}
	}

	Component::mouseEntered(e);
}

void Button::mouseExited(const MouseEvent& e)
{
	if(getEnabled())
	{
		if(_Armed)
		{
			beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
				ButtonPtr(this)->setActive(false);
			endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		}
	}

	Component::mouseExited(e);
}

void Button::mousePressed(const MouseEvent& e)
{
	if(getEnabled())
	{
		if(e.getButton()==MouseEvent::BUTTON1){
			beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
				ButtonPtr(this)->setActive(true);
			endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
			_Armed = true;
	        
			if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!=NullFC&& getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
			{
				getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseListener(&_ButtonArmedListener);
				if(getEnableActionOnMouseDownTime())
				{
					produceMousePressedActionPerformed(ActionEvent(ButtonPtr(this), e.getTimeStamp()));
					_ButtonArmedListener.reset();
					getParentFrame()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_ButtonArmedListener);
				}
			}
		}
	}
	Component::mousePressed(e);
}

void Button::mouseReleased(const MouseEvent& e)
{	
	if(getEnabled())
	{
		if(e.getButton() == MouseEvent::BUTTON1 && _Armed)
		{
			beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
				ButtonPtr(this)->setActive(false);
			endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		   produceActionPerformed(ActionEvent(ButtonPtr(this), e.getTimeStamp()));
		   _Armed = false;
		}
	}
	Component::mouseReleased(e);
}

void Button::produceActionPerformed(const ActionEvent& e)
{
    actionPreformed(e);
	ActionListenerSet Listeners(_ActionListeners);
    for(ActionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
}

void Button::produceMousePressedActionPerformed(const ActionEvent& e)
{
    mousePressedActionPreformed(e);
    for(ActionListenerSetConstItor SetItor(_MousePressedActionListeners.begin()) ; SetItor != _MousePressedActionListeners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
}

void Button::setTexture(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture);
    }

    beginEditCP(ButtonPtr(this), DrawObjectFieldMask);
        setDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), DrawObjectFieldMask);

}

void Button::setActiveTexture(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture);
    }

    beginEditCP(ButtonPtr(this), ActiveDrawObjectFieldMask);
        setActiveDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), ActiveDrawObjectFieldMask);
}

void Button::setFocusedTexture(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture);
    }

    beginEditCP(ButtonPtr(this), FocusedDrawObjectFieldMask);
        setFocusedDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), FocusedDrawObjectFieldMask);
}

void Button::setRolloverTexture(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture);
    }

    beginEditCP(ButtonPtr(this), RolloverDrawObjectFieldMask);
        setRolloverDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), RolloverDrawObjectFieldMask);
}

void Button::setDisabledTexture(TextureChunkPtr TheTexture)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture);
    }

    beginEditCP(ButtonPtr(this), DisabledDrawObjectFieldMask);
        setDisabledDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), DisabledDrawObjectFieldMask);
}

void Button::setImage(ImagePtr TheImage)
{
    TextureChunkPtr TextureChunk;
    if(TheImage == NullFC)
    {
        TextureChunk = NullFC;
    }
    else
    {
        TextureChunk = TextureChunk::create();
        beginEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
            TextureChunk->setImage(TheImage);
            TextureChunk->setWrapS(GL_CLAMP);
            TextureChunk->setWrapT(GL_CLAMP);
            TextureChunk->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            TextureChunk->setMagFilter(GL_LINEAR);
            TextureChunk->setEnvMode(GL_MODULATE);
        endEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
    }

    setTexture(TextureChunk);
}

void Button::setActiveImage(ImagePtr TheImage)
{
    TextureChunkPtr TextureChunk;
    if(TheImage == NullFC)
    {
        TextureChunk = NullFC;
    }
    else
    {
        TextureChunk = TextureChunk::create();
        beginEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
            TextureChunk->setImage(TheImage);
            TextureChunk->setWrapS(GL_CLAMP);
            TextureChunk->setWrapT(GL_CLAMP);
            TextureChunk->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            TextureChunk->setMagFilter(GL_LINEAR);
            TextureChunk->setEnvMode(GL_MODULATE);
        endEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
    }

    setActiveTexture(TextureChunk);
}

void Button::setFocusedImage(ImagePtr TheImage)
{
    TextureChunkPtr TextureChunk;
    if(TheImage == NullFC)
    {
        TextureChunk = NullFC;
    }
    else
    {
        TextureChunk = TextureChunk::create();
        beginEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
            TextureChunk->setImage(TheImage);
            TextureChunk->setWrapS(GL_CLAMP);
            TextureChunk->setWrapT(GL_CLAMP);
            TextureChunk->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            TextureChunk->setMagFilter(GL_LINEAR);
            TextureChunk->setEnvMode(GL_MODULATE);
        endEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
    }

    setFocusedTexture(TextureChunk);
}

void Button::setRolloverImage(ImagePtr TheImage)
{
    TextureChunkPtr TextureChunk;
    if(TheImage == NullFC)
    {
        TextureChunk = NullFC;
    }
    else
    {
        TextureChunk = TextureChunk::create();
        beginEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
            TextureChunk->setImage(TheImage);
            TextureChunk->setWrapS(GL_CLAMP);
            TextureChunk->setWrapT(GL_CLAMP);
            TextureChunk->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            TextureChunk->setMagFilter(GL_LINEAR);
            TextureChunk->setEnvMode(GL_MODULATE);
        endEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
    }

    setRolloverTexture(TextureChunk);
}

void Button::setDisabledImage(ImagePtr TheImage)
{
    TextureChunkPtr TextureChunk;
    if(TheImage == NullFC)
    {
        TextureChunk = NullFC;
    }
    else
    {
        TextureChunk = TextureChunk::create();
        beginEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
            TextureChunk->setImage(TheImage);
            TextureChunk->setWrapS(GL_CLAMP);
            TextureChunk->setWrapT(GL_CLAMP);
            TextureChunk->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            TextureChunk->setMagFilter(GL_LINEAR);
            TextureChunk->setEnvMode(GL_MODULATE);
        endEditCP(TextureChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::EnvModeFieldMask);
    }

    setDisabledTexture(TextureChunk);
}


void Button::setImage(const std::string& Path)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setImage(LoadedImage);
}

void Button::setActiveImage(const std::string& Path)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setActiveImage(LoadedImage);
}

void Button::setFocusedImage(const std::string& Path)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setFocusedImage(LoadedImage);
}

void Button::setRolloverImage(const std::string& Path)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setRolloverImage(LoadedImage);
}

void Button::setDisabledImage(const std::string& Path)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setDisabledImage(LoadedImage);
}





  
void Button::getTextBounds(Pnt2s& TextTopLeft, Pnt2s& TextBottomRight) const
{
      getFont()->getBounds(ButtonPtr(this)->getText(), TextTopLeft, TextBottomRight);
}


void Button::setPreferredSizeByContents(const int Insets)
{
	  Pnt2s TextTopLeft, TextBottomRight;   
	  // Get the Font bounds
	  getFont()->getBounds(ButtonPtr(this)->getText(), TextTopLeft, TextBottomRight);
	  Pnt2s TopLeft, BottomRight;
	  // Returns boundary required for Border
      getInsideBorderBounds(TopLeft, BottomRight);
	  Pnt2s InsetPnt(Insets, Insets);
	  // Uses these sizes and size Button
	  setPreferredSize(Vec2s(TextBottomRight - TextTopLeft  - BottomRight + TopLeft + Insets));

	};
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Button::Button(void) :
    Inherited(),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false)
{
}

Button::Button(const Button &source) :
    Inherited(source),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false)
{
}

Button::~Button(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Button::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Button::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Button NI" << std::endl;
}

void Button::ButtonArmedListener::mouseReleased(const MouseEvent& e)
{
	if(e.getButton() == MouseEvent::BUTTON1)
	{
		Pnt2s MousePos = ViewportToDrawingSurface(e.getLocation(), _Button->getParentFrame()->getDrawingSurface(), e.getViewport());
        //If the Mouse is not within the button
        if(!_Button->isContained(MousePos))
        {
            //Then Disarm the button
            _Button->_Armed = false;
        }

		//Remove myself from the listener
        _Button->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        if(_Button->getEnableActionOnMouseDownTime())
        {
            _Button->getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
        }
	}
}

void Button::ButtonArmedListener::update(const UpdateEvent& e)
{
    if(_Button->isContained(_Button->getParentFrame()->getDrawingSurface()->getMousePosition()))
    {
        _ActionFireElps += e.getElapsedTime();
    }
    if(_ActionFireElps >= _Button->getActionOnMouseDownRate())
    {
        _Button->produceMousePressedActionPerformed(ActionEvent(_Button, e.getTimeStamp()));
        _ActionFireElps -= static_cast<Int32>(_ActionFireElps/_Button->getActionOnMouseDownRate()) * _Button->getActionOnMouseDownRate();
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

