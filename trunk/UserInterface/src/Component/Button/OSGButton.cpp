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
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/OSGImageFileHandler.h>

#include "Graphics/UIDrawObjects/OSGTexturedQuadUIDrawObject.h"

#include <boost/bind.hpp>

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

    
void Button::setTextColors( const Color4f &value )
{
    setTextColor(value);
    setDisabledTextColor(value);
    setRolloverTextColor(value);
    setFocusedTextColor(value);
    setActiveTextColor(value);
}

void Button::setBorders(BorderPtr TheBorder)
{
    Inherited::setBorders(TheBorder);
    setActiveBorder(TheBorder);
}

void Button::setBackgrounds(LayerPtr TheBackground)
{
    Inherited::setBackgrounds(TheBackground);
    setActiveBackground(TheBackground);
}

void Button::setForegrounds(LayerPtr TheForeground)
{
    Inherited::setForegrounds(TheForeground);
    setActiveForeground(TheForeground);
}

UIDrawObjectCanvasPtr Button::createTexturedDrawObjectCanvas(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas = UIDrawObjectCanvas::create();
    TexturedQuadUIDrawObjectPtr TextureDrawObject = TexturedQuadUIDrawObject::create();

    Vec2f ImageSize;
    ImageSize.setValues(TheTexture->getImage()->getWidth(), TheTexture->getImage()->getHeight());

	if(Size.x() > 0.0f)
	{
		ImageSize[0] = Size.x();
	}
	if(Size.y() > 0.0f)
	{
		ImageSize[1] = Size.y();
	}
    
    beginEditCP(TextureDrawObject);
        TextureDrawObject->setPoint1(Pnt2f(0,0));
        TextureDrawObject->setPoint2(Pnt2f(ImageSize.x(),0));
        TextureDrawObject->setPoint3(Pnt2f(ImageSize.x(),ImageSize.y()));
        TextureDrawObject->setPoint4(Pnt2f(0,ImageSize.y()));
        
        TextureDrawObject->setTexCoord1(Vec2f(0.0,0.0));
        TextureDrawObject->setTexCoord2(Vec2f(1.0,0.0));
        TextureDrawObject->setTexCoord3(Vec2f(1.0,1.0));
        TextureDrawObject->setTexCoord4(Vec2f(0.0,1.0));

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


EventConnection Button::addActionListener(ActionListenerPtr Listener)
{
   _ActionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Button::isActionListenerAttached, this, Listener),
       boost::bind(&Button::removeActionListener, this, Listener));
}

EventConnection Button::addMousePressedActionListener(ActionListenerPtr Listener)
{
   _MousePressedActionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Button::isMousePressedActionListenerAttached, this, Listener),
       boost::bind(&Button::removeMousePressedActionListener, this, Listener));
}

Vec2f Button::getContentRequestedSize(void) const
{
    Vec2f Result(0.0f,0.0f);
    UIDrawObjectCanvasPtr DrawnDrawObject = getDrawnDrawObject();
    if(getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_LEFT_OF_TEXT ||
       getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT)
    {
        if(getFont() != NullFC)
        {
            Pnt2f TextTopLeft(0.0f,0.0f), TextBottomRight(0.0f,0.0f);
            getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
            Result[0] += (TextBottomRight - TextTopLeft).x();
            Result[1] = osgMax(Result[1],(TextBottomRight - TextTopLeft).y());
        }

        if(DrawnDrawObject != NullFC)
        {
            Pnt2f DrawObjectTopLeft, DrawObjectBottomRight;
            DrawnDrawObject->getDrawObjectBounds(DrawObjectTopLeft, DrawObjectBottomRight);

            Result[0] += (DrawObjectBottomRight - DrawObjectTopLeft).x();
            Result[1] = osgMax(Result[1],(DrawObjectBottomRight - DrawObjectTopLeft).y());
        }

        if(getFont() != NullFC && DrawnDrawObject != NullFC)
        {
            Result[0] += getDrawObjectToTextPadding();
        }
    }
    else if(getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_ABOVE_TEXT ||
       getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_BELOW_TEXT)
    {
        if(getFont() != NullFC)
        {
            Pnt2f TextTopLeft(0.0f,0.0f), TextBottomRight(0.0f,0.0f);
            getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
            Result[1] += (TextBottomRight - TextTopLeft).y();
            Result[0] = osgMax(Result[0],(TextBottomRight - TextTopLeft).x());
        }

        if(DrawnDrawObject != NullFC)
        {
            Pnt2f DrawObjectTopLeft, DrawObjectBottomRight;
            DrawnDrawObject->getDrawObjectBounds(DrawObjectTopLeft, DrawObjectBottomRight);

            Result[1] += (DrawObjectBottomRight - DrawObjectTopLeft).y();
            Result[0] = osgMax(Result[0],(DrawObjectBottomRight - DrawObjectTopLeft).x());
        }

        if(getFont() != NullFC && DrawnDrawObject != NullFC)
        {
            Result[1] += getDrawObjectToTextPadding();
        }
    }

	return Result + Vec2f(2.0,2.0);
}
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

LayerPtr Button::getDrawnBackground(void) const
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
LayerPtr Button::getDrawnForeground(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveForeground();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverForeground();
        }
        else
        {
            return getForeground();
        }
    }
    else
    {
        return getDisabledForeground();
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
   Pnt2f TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   
   //If I have a DrawObject then Draw it
   UIDrawObjectCanvasPtr DrawnDrawObject = getDrawnDrawObject();
   if(DrawnDrawObject != NullFC)
   {
	  //Get the Draw Object Size
      Pnt2f DrawObjectTopLeft, DrawObjectBottomRight;
      DrawnDrawObject->getDrawObjectBounds(DrawObjectTopLeft, DrawObjectBottomRight);

	  if(getText() != "" && getFont() != NullFC)
	  {
		  //Draw both the text and Draw Object

		  //Get the Text Size
		  Pnt2f TextTopLeft, TextBottomRight;
		  getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

		  Vec2f InternalsSize;
		  if(getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_LEFT_OF_TEXT || 
			 getDrawObjectToTextAlignment() == ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT)
		  {
			  InternalsSize.setValues((TextBottomRight.x()-TextTopLeft.x()) + (DrawObjectBottomRight.x()-DrawObjectTopLeft.x()) + getDrawObjectToTextPadding(),
				  osgMax((TextBottomRight.y()-TextTopLeft.y()), (DrawObjectBottomRight.y()-DrawObjectTopLeft.y())));
		  }
		  else
		  {
			  InternalsSize.setValues(osgMax((TextBottomRight.x()-TextTopLeft.x()), (DrawObjectBottomRight.x()-DrawObjectTopLeft.x())),
				  (TextBottomRight.y()-TextTopLeft.y()) + (DrawObjectBottomRight.y()-DrawObjectTopLeft.y()) + getDrawObjectToTextPadding());
		  }

		  Pnt2f InternalAlignment;
          InternalAlignment = calculateAlignment(TopLeft, (BottomRight-TopLeft), InternalsSize,getAlignment().y(), getAlignment().x());

		  //Draw Object Alignment
          Pnt2f DrawObjectAlignedPosition;
		  switch(getDrawObjectToTextAlignment())
		  {
		  case ALIGN_DRAW_OBJECT_LEFT_OF_TEXT:
			  DrawObjectAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (DrawObjectBottomRight - DrawObjectTopLeft),0.5f, 0.0);
			  break;
		  case ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT:
			  DrawObjectAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (DrawObjectBottomRight - DrawObjectTopLeft),0.5f, 1.0);
			  break;
		  case ALIGN_DRAW_OBJECT_ABOVE_TEXT:
			  DrawObjectAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (DrawObjectBottomRight - DrawObjectTopLeft),0.0f, 0.5);
			  break;
		  case ALIGN_DRAW_OBJECT_BELOW_TEXT:
			  DrawObjectAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (DrawObjectBottomRight - DrawObjectTopLeft),1.0f, 0.5);
			  break;
		  }
          //If active then translate the Text by the Active Offset
          DrawObjectAlignedPosition = DrawObjectAlignedPosition + getDrawnOffset();

          beginEditCP(DrawnDrawObject, PositionFieldMask);
			  DrawnDrawObject->setPosition( DrawObjectAlignedPosition );
          endEditCP(DrawnDrawObject, PositionFieldMask);

		  //Text Alignment
          Pnt2f TextAlignedPosition;
		  switch(getDrawObjectToTextAlignment())
		  {
		  case ALIGN_DRAW_OBJECT_LEFT_OF_TEXT:
			  TextAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (TextBottomRight - TextTopLeft),0.5f, 1.0);
			  break;
		  case ALIGN_DRAW_OBJECT_RIGHT_OF_TEXT:
			  TextAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (TextBottomRight - TextTopLeft),0.5f, 0.0);
			  break;
		  case ALIGN_DRAW_OBJECT_ABOVE_TEXT:
			  TextAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (TextBottomRight - TextTopLeft),1.0f, 0.5);
			  break;
		  case ALIGN_DRAW_OBJECT_BELOW_TEXT:
			  TextAlignedPosition = calculateAlignment(InternalAlignment, InternalsSize, (TextBottomRight - TextTopLeft),0.0f, 0.5);
			  break;
		  }

		  drawText(TheGraphics, TextAlignedPosition);
	  }
	  else
	  {
	      //Just Draw the Draw Object
          Pnt2f AlignedPosition;
          AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (DrawObjectBottomRight - DrawObjectTopLeft),getAlignment().y(), getAlignment().x());

          //If active then translate the Text by the Active Offset
          AlignedPosition = AlignedPosition + getDrawnOffset();

          beginEditCP(DrawnDrawObject, PositionFieldMask);
			  DrawnDrawObject->setPosition( AlignedPosition );
          endEditCP(DrawnDrawObject, PositionFieldMask);
	  }

	  //Draw the DrawnDrawObject
      DrawnDrawObject->draw(TheGraphics);

   }
   else if(getText() != "" && getFont() != NullFC)
   {
	   //Just Draw the Text
       Pnt2f AlignedPosition;
       Pnt2f TextTopLeft, TextBottomRight;
       getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

       AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getAlignment().y(), getAlignment().x());

	   drawText(TheGraphics, AlignedPosition);
   }
}

void Button::drawText(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft) const
{
   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NullFC)
   {
      //Calculate Alignment
      Pnt2f Position =  TopLeft + getDrawnOffset();

	  //Draw the Text
      TheGraphics->drawText(Position, getText(), getFont(), getDrawnTextColor(), getOpacity());
   }
}

Vec2f Button::getDrawnOffset(void) const
{
    if(getActive())
    {
        return getActiveOffset();
    }
    else
    {
        return Vec2f(0.0f,0.0f);
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
		    ButtonPtr(this)->setActive(true);
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
			ButtonPtr(this)->setActive(false);
		}
	}

	Component::mouseExited(e);
}

void Button::mousePressed(const MouseEvent& e)
{
	if(getEnabled())
	{
		if(e.getButton()==MouseEvent::BUTTON1){
			ButtonPtr(this)->setActive(true);
			_Armed = true;
	        
			if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
			{
				getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_ButtonArmedListener);
				if(getEnableActionOnMouseDownTime())
				{
					produceMousePressedActionPerformed(ActionEvent(ButtonPtr(this), e.getTimeStamp()));
					_ButtonArmedListener.reset();
					getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_ButtonArmedListener);
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
		   ButtonPtr(this)->setActive(false);
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

void Button::setTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture, Size);
    }

    beginEditCP(ButtonPtr(this), DrawObjectFieldMask);
        setDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), DrawObjectFieldMask);

}

void Button::setActiveTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture, Size);
    }

    beginEditCP(ButtonPtr(this), ActiveDrawObjectFieldMask);
        setActiveDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), ActiveDrawObjectFieldMask);
}

void Button::setFocusedTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture, Size);
    }

    beginEditCP(ButtonPtr(this), FocusedDrawObjectFieldMask);
        setFocusedDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), FocusedDrawObjectFieldMask);
}

void Button::setRolloverTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture, Size);
    }

    beginEditCP(ButtonPtr(this), RolloverDrawObjectFieldMask);
        setRolloverDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), RolloverDrawObjectFieldMask);
}

void Button::setDisabledTexture(TextureChunkPtr TheTexture, Vec2f Size)
{
    UIDrawObjectCanvasPtr DrawObjectCanvas;
    if(TheTexture == NullFC)
    {
        DrawObjectCanvas = NullFC;
    }
    else
    {
        DrawObjectCanvas = createTexturedDrawObjectCanvas(TheTexture, Size);
    }

    beginEditCP(ButtonPtr(this), DisabledDrawObjectFieldMask);
        setDisabledDrawObject(DrawObjectCanvas);
    endEditCP(ButtonPtr(this), DisabledDrawObjectFieldMask);
}

void Button::setImage(ImagePtr TheImage, Vec2f Size)
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

    setTexture(TextureChunk, Size);
}

void Button::setActiveImage(ImagePtr TheImage, Vec2f Size)
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

    setActiveTexture(TextureChunk, Size);
}

void Button::setFocusedImage(ImagePtr TheImage, Vec2f Size)
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

    setFocusedTexture(TextureChunk, Size);
}

void Button::setRolloverImage(ImagePtr TheImage, Vec2f Size)
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

    setRolloverTexture(TextureChunk, Size);
}

void Button::setDisabledImage(ImagePtr TheImage, Vec2f Size)
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

    setDisabledTexture(TextureChunk, Size);
}


void Button::setImage(const std::string& Path, Vec2f Size)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setImage(LoadedImage, Size);
}

void Button::setActiveImage(const std::string& Path, Vec2f Size)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setActiveImage(LoadedImage, Size);
}

void Button::setFocusedImage(const std::string& Path, Vec2f Size)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setFocusedImage(LoadedImage, Size);
}

void Button::setRolloverImage(const std::string& Path, Vec2f Size)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setRolloverImage(LoadedImage, Size);
}

void Button::setDisabledImage(const std::string& Path, Vec2f Size)
{
    ImagePtr LoadedImage = ImageFileHandler::the().read(Path.c_str());
    setDisabledImage(LoadedImage, Size);
}





  
void Button::getTextBounds(Pnt2f& TextTopLeft, Pnt2f& TextBottomRight) const
{
      getFont()->getBounds(ButtonPtr(this)->getText(), TextTopLeft, TextBottomRight);
}

void Button::removeActionListener(ActionListenerPtr Listener)
{
   ActionListenerSetItor EraseIter(_ActionListeners.find(Listener));
   if(EraseIter != _ActionListeners.end())
   {
      _ActionListeners.erase(EraseIter);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Button::Button(void) :
    Inherited(),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false),
        _Active(false)
{
}

Button::Button(const Button &source) :
    Inherited(source),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false),
        _Active(false)
{
}

Button::~Button(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Button::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & DrawObjectFieldMask &&
		getDrawObject() != NullFC)
	{
		beginEditCP(getDrawObject(), SizeFieldMask);
			getDrawObject()->setSize(getDrawObject()->getPreferredSize());
		endEditCP(getDrawObject(), SizeFieldMask);
	}
	
	if(whichField & ActiveDrawObjectFieldMask &&
		getActiveDrawObject() != NullFC)
	{
		beginEditCP(getActiveDrawObject(), SizeFieldMask);
			getActiveDrawObject()->setSize(getActiveDrawObject()->getPreferredSize());
		endEditCP(getActiveDrawObject(), SizeFieldMask);
	}
	
	if(whichField & RolloverDrawObjectFieldMask &&
		getRolloverDrawObject() != NullFC)
	{
		beginEditCP(getRolloverDrawObject(), SizeFieldMask);
			getRolloverDrawObject()->setSize(getRolloverDrawObject()->getPreferredSize());
		endEditCP(getRolloverDrawObject(), SizeFieldMask);
	}
	
	if(whichField & DisabledDrawObjectFieldMask &&
		getDisabledDrawObject() != NullFC)
	{
		beginEditCP(getDisabledDrawObject(), SizeFieldMask);
			getDisabledDrawObject()->setSize(getDisabledDrawObject()->getPreferredSize());
		endEditCP(getDisabledDrawObject(), SizeFieldMask);
	}
	
	if(whichField & FocusedDrawObjectFieldMask &&
		getFocusedDrawObject() != NullFC)
	{
		beginEditCP(getFocusedDrawObject(), SizeFieldMask);
			getFocusedDrawObject()->setSize(getFocusedDrawObject()->getPreferredSize());
		endEditCP(getFocusedDrawObject(), SizeFieldMask);
	}
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
		Pnt2f MousePos = ViewportToDrawingSurface(e.getLocation(), _Button->getParentWindow()->getDrawingSurface(), e.getViewport());
        //If the Mouse is not within the button
        if(!_Button->isContained(MousePos))
        {
            //Then Disarm the button
            _Button->_Armed = false;
        }

		//Remove myself from the listener
        if(_Button->getParentWindow() != NullFC &&
            _Button->getParentWindow()->getDrawingSurface() != NullFC &&
            _Button->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
        {
            _Button->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
            if(_Button->getEnableActionOnMouseDownTime())
            {
                _Button->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
            }
        }
	}
}

void Button::ButtonArmedListener::update(const UpdateEvent& e)
{
    if(_Button->isContained(_Button->getParentWindow()->getDrawingSurface()->getMousePosition()))
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

