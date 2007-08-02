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

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTextLayoutParam.h>
#include <OpenSG/OSGTextLayoutResult.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGDepthChunk.h>

#include "OSGGraphics2D.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Graphics2D
A Concrete 2D UI Graphics.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Graphics2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Graphics2D::preDraw()
{
   glPushAttrib(GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
   
	getUIDepth()->activate(getDrawAction());

	//_light = glIsEnabled(GL_LIGHTING);

	//glGetIntegerv(GL_POLYGON_MODE, _fill);
	glPolygonMode(GL_FRONT, GL_FILL);

	//_depth = glIsEnabled(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	//_colmat = glIsEnabled(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);

	if(getEnablePointAntiAliasing())
	{
		glEnable(GL_POINT_SMOOTH);
	}
	if(getEnableLineAntiAliasing())
	{
		glEnable(GL_LINE_SMOOTH);
	}
	if(getEnablePolygonAntiAliasing())
	{
		glEnable(GL_POLYGON_SMOOTH);
	}
}

void Graphics2D::postDraw()
{
	/*if(_depth == GL_TRUE)
	{
		glEnable(GL_DEPTH_TEST);
	}
	if(_light == GL_TRUE)
	{
		glEnable(GL_LIGHTING);
	}
	if(_colmat == GL_TRUE)
	{
		glEnable(GL_COLOR_MATERIAL);
	}
	glPolygonMode(GL_FRONT, _fill[0]);
	glPolygonMode(GL_BACK , _fill[1]);*/
   
	getUIDepth()->deactivate(getDrawAction());
   glPopAttrib();
}

void Graphics2D::drawRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Real32& Opacity) const
{
   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	if(Alpha < 1.0 || getEnablePolygonAntiAliasing())
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	glBegin(GL_QUADS);
      glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
	   glVertex2sv(TopLeft.getValues());
	   glVertex2s(BottomRight.x(), TopLeft.y());
	   glVertex2sv(BottomRight.getValues());
	   glVertex2s(TopLeft.x(), BottomRight.y());
	glEnd();
	
	if(Alpha < 1.0 || getEnablePolygonAntiAliasing())
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawQuad(const Pnt2s& p1, const Pnt2s& p2, const Pnt2s& p3, const Pnt2s& p4, 
						const Color4f& c1, const Color4f& c2, const Color4f& c3, const Color4f& c4,
						const Real32& Opacity) const
{
	Real32 MinAlpha( osgMin(osgMin(c1.alpha(), c2.alpha()), osgMin(c3.alpha(), c4.alpha())) * Opacity * getOpacity());
	if(MinAlpha < 1.0)
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_QUADS);
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex2sv(p1.getValues());
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex2sv(p2.getValues());
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex2sv(p3.getValues());
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex2sv(p4.getValues());
	glEnd();

	if(MinAlpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawQuad(const Pnt2s& p1, const Pnt2s& p2, const Pnt2s& p3, const Pnt2s& p4, 
						const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
						const TextureChunkPtr Texture,
						const Real32& Opacity) const
{
	Real32 Alpha( Opacity * getOpacity());
	if(Alpha < 1.0 || Texture->isTransparent())
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	if(Texture != NullFC)
	{
		Texture->activate(getDrawAction());
	}
	
	glBegin(GL_QUADS);
	   glColor4f(1.0, 1.0, 1.0, Alpha );
	   glTexCoord2fv(t1.getValues());
	   glVertex2sv(p1.getValues());
	   glTexCoord2fv(t2.getValues());
	   glVertex2sv(p2.getValues());
	   glTexCoord2fv(t3.getValues());
	   glVertex2sv(p3.getValues());
	   glTexCoord2fv(t4.getValues());
	   glVertex2sv(p4.getValues());
	glEnd();
	
	if(Texture != NullFC)
	{
		Texture->deactivate(getDrawAction());
	}

	if(Alpha < 1.0 || Texture->isTransparent())
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawQuad(const Pnt2s& p1, const Pnt2s& p2, const Pnt2s& p3, const Pnt2s& p4, 
						const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
						const MaterialPtr Material,
						const Real32& Opacity) const
{
	Real32 Alpha( Opacity * getOpacity());
	if(Alpha < 1.0 || Material->isTransparent())
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

   StatePtr state = NullFC;
	if(Material != NullFC)
	{
      state = Material->makeState();

      addRefCP(state);

      state->activate(getDrawAction());
	}
	
	glBegin(GL_QUADS);
	   glColor4f(1.0, 1.0, 1.0, Alpha );
	   glTexCoord2fv(t1.getValues());
	   glVertex2sv(p1.getValues());
	   glTexCoord2fv(t2.getValues());
	   glVertex2sv(p2.getValues());
	   glTexCoord2fv(t3.getValues());
	   glVertex2sv(p3.getValues());
	   glTexCoord2fv(t4.getValues());
	   glVertex2sv(p4.getValues());
	glEnd();
	
	if(state != NullFC)
	{
		state->deactivate(getDrawAction());
      subRefCP(state);
	}

	if(Alpha < 1.0 || Material->isTransparent())
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawLine(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Real32& Width, const Color4f& Color, const Real32& Opacity) const
{
	GLfloat previousLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &previousLineWidth);
   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	if(Alpha < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glLineWidth(Width);
	glBegin(GL_LINES);
      glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
		glVertex2sv(TopLeft.getValues());
		glVertex2sv(BottomRight.getValues());
	glEnd();
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
	glLineWidth(previousLineWidth);
}

void Graphics2D::drawPolygon(const MFPnt2s Verticies, const Color4f& Color, const Real32& Opacity) const
{
   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	if(Alpha < 1.0)
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_POLYGON);
      glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
	   for(UInt32 i=0 ; i<Verticies.size() ; ++i)
	   {
	      glVertex2sv(Verticies.getValue(i).getValues());
	   }
	glEnd();
	
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawDisc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
{
	Real32 angleNow = StartAngleRad;
	Real32 angleDiff = (EndAngleRad-StartAngleRad)/(static_cast<Real32>(SubDivisions));
	if(EndAngleRad-StartAngleRad > 2*3.1415926535)
		angleDiff = 2*3.1415926535/static_cast<Real32>(SubDivisions);
    if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_TRIANGLE_FAN);
      glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha() * Opacity * getOpacity() );
      glVertex2sv(Center.getValues());
      glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha() * Opacity * getOpacity() );
      for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
      {
			glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgcos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgsin(angleNow));
			angleNow += angleDiff;
		}
	glEnd();

    if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}
void Graphics2D::drawComplexDisc(const Pnt2s& Center, const Int16& InnerRadius, const Int16& OuterRadius, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
{	
	Real32 angleNow = StartAngleRad;
	Real32 angleDiff = (EndAngleRad-StartAngleRad)/(static_cast<Real32>(SubDivisions));
	if(EndAngleRad-StartAngleRad > 2*3.1415926535)
		angleDiff = 2*3.1415926535/static_cast<Real32>(SubDivisions);
	if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glBegin(GL_QUAD_STRIP);
    for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
	{
		glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha());
		glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgcos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgsin(angleNow));
		glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha());
		glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgcos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgsin(angleNow));
		angleNow += angleDiff;
	}
	glEnd();
	if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}

void Graphics2D::drawArc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const
{
	GLfloat previousLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &previousLineWidth);
	Real32 angleNow = StartAngleRad;
	Real32 angleDiff = (EndAngleRad-StartAngleRad)/(static_cast<Real32>(SubDivisions));
	//If andle difference is bigger to a circle, set it to equal to a circle
	if(EndAngleRad-StartAngleRad > 2*3.1415926535)
		angleDiff = 2*3.1415926535/static_cast<Real32>(SubDivisions);
   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	if(Alpha < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glLineWidth(LineWidth);
	glBegin(GL_LINE_STRIP);
      glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
		//draw vertex lines
      for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
      {
			glVertex2f( static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgcos(angleNow ),static_cast<Real32>(Center.y()) +static_cast<Real32>(Height)*osgsin(angleNow));
			//glVertex2s(Center.x() + Width*osgcos(angleNow + angleDiff), Center.y() + Height*osgsin(angleNow+angleDiff));
			angleNow += angleDiff;
		}
	glEnd();

	
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
   glLineWidth(previousLineWidth);
}

void Graphics2D::drawLoweredBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Int16& Width, const Real32& Opacity) const
{
Pnt2s TopRight = Pnt2s(BottomRight.x(), TopLeft.y());
	Pnt2s BottomLeft = Pnt2s(TopLeft.x(), BottomRight.y());
	Color4f LightColor;
	Color4f DarkColor;
	Color4f DarkerColor;
	Real32 hue, sat, val;
	Real32 valdark, valdarker;
	Color.getValuesHSV(hue, sat, val);
	//set value of darker shades
	valdark = .7*val;
	valdarker = .5*val;
	DarkColor.setValuesHSV(hue, sat, valdark);
	DarkerColor.setValuesHSV(hue, sat, valdarker);
	//value is 100 b/c that allows the color to be brighter
	LightColor.setValuesHSV(hue, sat, 100);

	//bottom
	drawLine(Pnt2s(BottomLeft.x(), BottomLeft.y()-(Width/2.0-.5)), Pnt2s(BottomRight.x(), BottomRight.y()-(Width/2.0-0.5)), Width, LightColor,Opacity);
	//right
	drawLine(Pnt2s(TopRight.x()-(Width/2.0-.5), TopRight.y()), Pnt2s(BottomRight.x()-(Width/2.0-.5), BottomRight.y()), Width, LightColor, Opacity);
	if(Width == 1)
	{
		//top
		drawLine(Pnt2s(TopLeft.x()-1, TopLeft.y()), Pnt2s(TopRight.x(),TopRight.y()), 1, DarkerColor, Opacity);

		//left
		drawLine(Pnt2s(TopLeft.x(), TopLeft.x()), Pnt2s(BottomLeft.x(), BottomLeft.y()), 1, DarkerColor, Opacity);
	}
	else if(Width%2 == 1)//Odd still has some work to be done.... so use even sizes only for bevel borders for the time being.
	{
			//Top
		drawLine(Pnt2s(TopLeft.x(), TopLeft.y()+Width/4.0), Pnt2s(TopRight.x(), TopRight.y()+Width/4.0), Width/2.0,DarkerColor, Opacity);
		drawLine(Pnt2s(TopLeft.x() + Width/2.0, TopLeft.y()+3*Width/4.0), Pnt2s(TopRight.x()-Width/2.0, TopRight.y()+3*Width/4.0),Width/2.0,DarkColor, Opacity);
		
		//Left
		drawLine(Pnt2s(BottomLeft.x()+Width/4.0, BottomLeft.y()), Pnt2s(TopLeft.x()+Width/4.0, TopLeft.y()), Width/2.0, DarkerColor, Opacity);
		drawLine(Pnt2s(BottomLeft.x()+3*Width/4.0, BottomLeft.y()-Width/2.0), Pnt2s(TopLeft.x()+3*Width/4.0, TopLeft.y()+Width/2.0), Width/2.0, DarkColor, Opacity);
	}
	else
	{	
		//Top
		drawLine(Pnt2s(TopLeft.x(), TopLeft.y()+Width/4.0), Pnt2s(TopRight.x(), TopRight.y()+Width/4.0), Width/2.0,DarkerColor, Opacity);
		drawLine(Pnt2s(TopLeft.x() + Width/2.0, TopLeft.y()+3*Width/4.0), Pnt2s(TopRight.x()-Width/2.0, TopRight.y()+3*Width/4.0),Width/2.0,DarkColor, Opacity);
		
		//Left
		drawLine(Pnt2s(BottomLeft.x()+Width/4.0, BottomLeft.y()), Pnt2s(TopLeft.x()+Width/4.0, TopLeft.y()), Width/2.0, DarkerColor, Opacity);
		drawLine(Pnt2s(BottomLeft.x()+3*Width/4.0, BottomLeft.y()-Width/2.0), Pnt2s(TopLeft.x()+3*Width/4.0, TopLeft.y()+Width/2.0), Width/2.0, DarkColor, Opacity);
	}
}

void Graphics2D::drawRaisedBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color, const Int16& Width, const Real32& Opacity) const
{
	Pnt2s TopRight = Pnt2s(BottomRight.x(), TopLeft.y());
	Pnt2s BottomLeft = Pnt2s(TopLeft.x(), BottomRight.y());
	Color4f LightColor;
	Color4f DarkColor;
	Color4f DarkerColor;
	Real32 hue;
	Real32 sat;
	Real32 val;
	Real32 valdark, valdarker;
	Color.getValuesHSV(hue, sat, val);
	//set value of darker shades
	valdark = .7*val;
	valdarker = .5*val;
	DarkColor.setValuesHSV(hue, sat, valdark);
	DarkerColor.setValuesHSV(hue, sat, valdarker);
	//value is 100 b/c that allows the color to be brighter
	LightColor.setValuesHSV(hue, sat, 100);

	//top
	drawLine(Pnt2s(TopLeft.x(), TopLeft.y()+(Width/2.0+.5)), Pnt2s(TopRight.x(), TopRight.y()+(Width/2.0+0.5)), Width, LightColor,Opacity);
	//Left
	drawLine(Pnt2s(TopLeft.x()+(Width/2.0+.5), TopLeft.y()), Pnt2s(BottomLeft.x()+(Width/2.0+.5), BottomLeft.y()), Width, LightColor, Opacity);
	if(Width == 1)
	{
		//Bottom
		drawLine(Pnt2s(BottomLeft.x()-1, BottomLeft.y()), Pnt2s(BottomRight.x(),BottomRight.y()), 1, DarkerColor, Opacity);

		//Right
		drawLine(Pnt2s(TopRight.x(), TopRight.x()), Pnt2s(BottomRight.x(), BottomRight.y()), 1, DarkerColor, Opacity);
	}
	else if(Width%2 == 1)//Odd still has some work to be done.... so use even sizes only for bevel borders for the time being.
	{
		//Bottom
		drawLine(Pnt2s(BottomLeft.x(), BottomLeft.y()-Width/4.0), Pnt2s(BottomRight.x(), BottomRight.y()-Width/4.0), Width/2.0,DarkerColor, Opacity);
		drawLine(Pnt2s(BottomLeft.x() + Width/2.0, BottomLeft.y()-3*Width/4.0), Pnt2s(BottomRight.x()-Width/2.0, BottomRight.y()-3*Width/4.0),Width/2.0,DarkColor, Opacity);
		
		//Right
		drawLine(Pnt2s(BottomRight.x()-Width/4.0, BottomRight.y()), Pnt2s(TopRight.x()-Width/4.0, TopRight.y()), Width/2.0, DarkerColor, Opacity);
		drawLine(Pnt2s(BottomRight.x()-3*Width/4.0, BottomRight.y()-Width/2.0), Pnt2s(TopRight.x()-3*Width/4.0, TopRight.y()+Width/2.0), Width/2.0, DarkColor, Opacity);
	}
	else
	{
		//Bottom
		drawLine(Pnt2s(BottomLeft.x(), BottomLeft.y()-Width/4.0), Pnt2s(BottomRight.x(), BottomRight.y()-Width/4.0), Width/2.0,DarkerColor, Opacity);
		drawLine(Pnt2s(BottomLeft.x() + Width/2.0, BottomLeft.y()-3*Width/4.0), Pnt2s(BottomRight.x()-Width/2.0, BottomRight.y()-3*Width/4.0),Width/2.0,DarkColor, Opacity);
		
		//Right
		drawLine(Pnt2s(BottomRight.x()-Width/4.0, BottomRight.y()), Pnt2s(TopRight.x()-Width/4.0, TopRight.y()), Width/2.0, DarkerColor, Opacity);
		drawLine(Pnt2s(BottomRight.x()-3*Width/4.0, BottomRight.y()-Width/2.0), Pnt2s(TopRight.x()-3*Width/4.0, TopRight.y()+Width/2.0), Width/2.0, DarkColor, Opacity);
	}
}

void Graphics2D::drawText(const Pnt2s& Position, const std::string& Text, const FontPtr TheFont, const Color4f& Color, const Real32& Opacity) const
{
   TextLayoutParam layoutParam;
   layoutParam.spacing = 1.1;
   layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
   layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
 
   TextLayoutResult layoutResult;
   TheFont->layout(Text, layoutParam, layoutResult);

   TheFont->getTexture()->activate(getDrawAction());

   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	
   //Setup the blending equations properly
   glPushAttrib(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

   glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
   glPushMatrix();
   glTranslatef(Position.x(), Position.y(), 0.0);
   glScalef(TheFont->getSize(), TheFont->getSize(), 1);
   drawCharacters(layoutResult, TheFont);
   glPopMatrix();

   TheFont->getTexture()->deactivate(getDrawAction());

	glDisable(GL_BLEND);
   glPopAttrib();
}

Vec2s Graphics2D::getTextBounds(const std::string& Text, const FontPtr TheFont) const
{
   TextLayoutParam layoutParam;
   layoutParam.spacing = 1.1;
   layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
   layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
 
   TextLayoutResult layoutResult;
   TheFont->layout(Text, layoutParam, layoutResult);
   return Vec2s(layoutResult.textBounds.x()*TheFont->getSize(),layoutResult.textBounds.y()*TheFont->getSize());
}

void Graphics2D::drawCharacters( const TextLayoutResult& layoutResult, const FontPtr TheFont) const
{
    glBegin(GL_QUADS);

    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    Real32 width, height;
    for(i = 0; i < numGlyphs; ++i)
    {
        const TextTXFGlyph &glyph = TheFont->getTXFGlyph(layoutResult.indices[i]);
        width = glyph.getWidth();
        height = glyph.getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 posLeft = pos.x();
        Real32 posTop = -pos.y();
        Real32 posRight = pos.x() + width;
        Real32 posBottom = -pos.y() + height;
        Real32 texCoordLeft = glyph.getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop = glyph.getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight = glyph.getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph.getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex2f(posLeft, posBottom);

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex2f(posLeft, posTop);

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex2f(posRight, posTop);

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex2f(posRight, posBottom);


    }

    glEnd();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Graphics2D::Graphics2D(void) :
    Inherited()
{
	setUIDepth(DepthChunk::create());
	getUIDepth()->setReadOnly(true);
}

Graphics2D::Graphics2D(const Graphics2D &source) :
    Inherited(source)
{
}

Graphics2D::~Graphics2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Graphics2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Graphics2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Graphics2D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRAPHICS2DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRAPHICS2DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRAPHICS2DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

