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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGraphics3DExtrude.h"
#include "OSGGL.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextureBaseChunk.h"
#include "OSGDepthChunk.h"


#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGPrimeMaterial.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGraphics3DExtrudeBase.cpp file.
// To modify it, please change the .fcd file (OSGGraphics3DExtrude.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Graphics3DExtrude::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


MaterialTransitPtr Graphics3DExtrude::createDefaultMaterial(void)
{
	MaterialChunkUnrecPtr TheMaterialChunk = MaterialChunk::create();

	TheMaterialChunk->setAmbient(Color4f(0.4,0.4,0.4,1.0));
	TheMaterialChunk->setDiffuse(Color4f(0.8,0.8,0.8,1.0));
	TheMaterialChunk->setSpecular(Color4f(0.85,0.85,0.85,1.0));
	TheMaterialChunk->setEmission(Color4f(0.0,0.0,0.0,1.0));
	TheMaterialChunk->setShininess(50.0);
	TheMaterialChunk->setLit(true);
	TheMaterialChunk->setColorMaterial(true);
	
	ChunkMaterial* TheMaterial = ChunkMaterial::createEmpty();

    TheMaterial->addChunk(TheMaterialChunk);

	return MaterialTransitPtr(TheMaterial);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 Graphics3DExtrude::getClipPlaneOffset(void) const
{
	return getInternalClipPlaneOffset();
}

void Graphics3DExtrude::preDraw()
{
   glPushAttrib(GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
   
	//getUIDepth()->activate(getDrawEnv());

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT, GL_FILL);

	//_light = glIsEnabled(GL_LIGHTING);

	//glGetIntegerv(GL_POLYGON_MODE, _fill);
	glEnable(GL_LIGHTING);
	if(getMaterial() != NULL)
	{
        getMaterial()->finalize(MaterialMapKey(),getDrawEnv()->getWindow())->getState()->activate(getDrawEnv());
	}

	//_depth = glIsEnabled(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	//_colmat = glIsEnabled(GL_COLOR_MATERIAL);
	//glEnable(GL_COLOR_MATERIAL);


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

void Graphics3DExtrude::postDraw()
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
   
	//getUIDepth()->deactivate(getDrawEnv());
	
	if(getMaterial() != NULL)
	{
        getMaterial()->finalize(MaterialMapKey(),getDrawEnv()->getWindow())->getState()->deactivate(getDrawEnv());
	}
   glPopAttrib();
}

void Graphics3DExtrude::drawRect(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Color4f& Color, const Real32& Opacity) const
{
   Real32 Alpha(Color.alpha() * Opacity * getOpacity());
	if(Alpha < 1.0 || getEnablePolygonAntiAliasing())
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

    glColor4f(Color.red(), Color.green(), Color.blue(), Alpha );
	glBegin(GL_QUADS);
	   //Front
	   glNormal3f(0.0,0.0,1.0);
	   glVertex3f(TopLeft.x(), TopLeft.y(), 0.0);
	   glVertex3f(TopLeft.x(), BottomRight.y(), 0.0);
	   glVertex3f(BottomRight.x(), BottomRight.y(), 0.0);
	   glVertex3f(BottomRight.x(), TopLeft.y(), 0.0);

	   //Back
	   glNormal3f(0.0,0.0,-1.0);
	   glVertex3f(TopLeft.x(), TopLeft.y(), getExtrudeLength());
	   glVertex3f(BottomRight.x(), TopLeft.y(), getExtrudeLength());
	   glVertex3f(BottomRight.x(), BottomRight.y(), getExtrudeLength());
	   glVertex3f(TopLeft.x(), BottomRight.y(), getExtrudeLength());
	   
	   //Top
	   glNormal3f(0.0,-1.0,0.0);
	   glVertex3f(TopLeft.x(), TopLeft.y(), 0.0);
	   glVertex3f(BottomRight.x(), TopLeft.y(), 0.0);
	   glVertex3f(BottomRight.x(), TopLeft.y(), getExtrudeLength());
	   glVertex3f(TopLeft.x(), TopLeft.y(), getExtrudeLength());

	   //Bottom
	   glNormal3f(0.0,1.0,0.0);
	   glVertex3f(TopLeft.x(), BottomRight.y(), 0.0);
	   glVertex3f(TopLeft.x(), BottomRight.y(), getExtrudeLength());
	   glVertex3f(BottomRight.x(), BottomRight.y(), getExtrudeLength());
	   glVertex3f(BottomRight.x(), BottomRight.y(), 0.0);
	   
	   //Right
	   glNormal3f(1.0,0.0,0.0);
	   glVertex3f(BottomRight.x(), TopLeft.y(), 0.0);
	   glVertex3f(BottomRight.x(), BottomRight.y(), 0.0);
	   glVertex3f(BottomRight.x(), BottomRight.y(), getExtrudeLength());
	   glVertex3f(BottomRight.x(), TopLeft.y(), getExtrudeLength());

	   //Left
	   glNormal3f(-1.0,0.0,0.0);
	   glVertex3f(TopLeft.x(), TopLeft.y(), 0.0);
	   glVertex3f(TopLeft.x(), TopLeft.y(), getExtrudeLength());
	   glVertex3f(TopLeft.x(), BottomRight.y(), getExtrudeLength());
	   glVertex3f(TopLeft.x(), BottomRight.y(), 0.0);

	glEnd();
	
	if(Alpha < 1.0 || getEnablePolygonAntiAliasing())
	{
		glDisable(GL_BLEND);
	}
}

void Graphics3DExtrude::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
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

	   
	   //Front
	   glNormal3f(0.0,0.0,1.0);
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex3f(p1.x(), p1.y(), 0.0);
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex3f(p4.x(), p4.y(), 0.0);
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), 0.0);
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), 0.0);

	   //Back
	   glNormal3f(0.0,0.0,-1.0);
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex3f(p1.x(), p1.y(), getExtrudeLength());
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), getExtrudeLength());
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), getExtrudeLength());
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex3f(p4.x(), p4.y(), getExtrudeLength());
	   
	   //Top
	   glNormal3f(0.0,-1.0,0.0);
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex3f(p1.x(), p1.y(), 0.0);
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), 0.0);
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), getExtrudeLength());
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex3f(p1.x(), p1.y(), getExtrudeLength());

	   //Bottom
	   glNormal3f(0.0,1.0,0.0);
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), 0.0);
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex3f(p4.x(), p4.y(), 0.0);
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex3f(p4.x(), p4.y(), getExtrudeLength());
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), getExtrudeLength());
	   
	   //Right
	   glNormal3f(1.0,0.0,0.0);
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), 0.0);
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), 0.0);
	   glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
	   glVertex3f(p3.x(), p3.y(), getExtrudeLength());
	   glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
	   glVertex3f(p2.x(), p2.y(), getExtrudeLength());

	   //Left
	   glNormal3f(-1.0,0.0,0.0);
	   glColor4f(c1.red(), c1.green(), c1.blue(), c1.alpha() * Opacity * getOpacity() );
	   glVertex3f(p1.x(), p1.y(), 0.0);
	   glVertex3f(p1.x(), p1.y(), getExtrudeLength());
	   glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
	   glVertex3f(p4.x(), p4.y(), getExtrudeLength());
	   glVertex3f(p4.x(), p4.y(), 0.0);
	glEnd();

	if(MinAlpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics3DExtrude::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
						const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
						const Color4f& color, const TextureBaseChunkUnrecPtr Texture,
						const Real32& Opacity) const
{
	Real32 Alpha( Opacity * getOpacity() * color.alpha());
	//if(Alpha < 1.0 || Texture->getImage()->hasAlphaChannel())
	//{
        //Setup the Blending equations properly
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
	//}

	if(Texture != NULL)
	{
		Texture->activate(getDrawEnv());
	}
	
	glBegin(GL_QUADS);
	   glColor4f(color.red(), color.green(), color.blue(), Alpha );
	   glTexCoord2fv(t1.getValues());
	   glVertex2fv(p1.getValues());
	   glTexCoord2fv(t2.getValues());
	   glVertex2fv(p2.getValues());
	   glTexCoord2fv(t3.getValues());
	   glVertex2fv(p3.getValues());
	   glTexCoord2fv(t4.getValues());
	   glVertex2fv(p4.getValues());
	glEnd();
	
	if(Texture != NULL)
	{
		Texture->deactivate(getDrawEnv());
	}

	//if(Alpha < 1.0 || Texture->getImage()->hasAlphaChannel())
	//{
        glDisable(GL_BLEND);
	//}
}

void Graphics3DExtrude::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
						const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
						Material* const Material,
						const Real32& Opacity) const
{
	Real32 Alpha( Opacity * getOpacity());
	if(Alpha < 1.0 || Material->isTransparent())
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

    StateUnrecPtr state = NULL;
    if(Material != NULL)
    {
        state = Material->finalize(MaterialMapKey(),getDrawEnv()->getWindow())->getState();

        state->activate(getDrawEnv());
    }
	
	glBegin(GL_QUADS);
	   glColor4f(1.0, 1.0, 1.0, Alpha );
	   glTexCoord2fv(t1.getValues());
	   glVertex2fv(p1.getValues());
	   glTexCoord2fv(t2.getValues());
	   glVertex2fv(p2.getValues());
	   glTexCoord2fv(t3.getValues());
	   glVertex2fv(p3.getValues());
	   glTexCoord2fv(t4.getValues());
	   glVertex2fv(p4.getValues());
	glEnd();
	
	if(state != NULL)
	{
		state->deactivate(getDrawEnv());
	}

	if(Alpha < 1.0 || Material->isTransparent())
	{
		glDisable(GL_BLEND);
	}
}

void Graphics3DExtrude::drawLine(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32& Width, const Color4f& Color, const Real32& Opacity) const
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
		glVertex2fv(TopLeft.getValues());
		glVertex2fv(BottomRight.getValues());
	glEnd();
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
	glLineWidth(previousLineWidth);
}

void Graphics3DExtrude::drawPolygon(const MFPnt2f Verticies, const Color4f& Color, const Real32& Opacity) const
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
	      glVertex2fv(Verticies[i].getValues());
	   }
	glEnd();
	
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics3DExtrude::drawDisc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
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
	
	//Front Disc
	glBegin(GL_TRIANGLE_FAN);
	  glNormal3f(0.0,0.0,1.0);
      glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha() * Opacity * getOpacity() );
      glVertex2fv(Center.getValues());
      glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha() * Opacity * getOpacity() );
      for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
      {
			glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgSin(angleNow));
			angleNow -= angleDiff;
		}
	glEnd();
	
	//Back Disc
	angleNow = StartAngleRad;
	glBegin(GL_TRIANGLE_FAN);
	  glNormal3f(0.0,0.0,-1.0);
      glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha() * Opacity * getOpacity() );
      glVertex3f(Center.x(), Center.y(), getExtrudeLength());
      glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha() * Opacity * getOpacity() );
      for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
      {
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgSin(angleNow), getExtrudeLength());
			angleNow += angleDiff;
		}
	glEnd();

	//Outer Hull
	angleNow = StartAngleRad;
	glBegin(GL_QUAD_STRIP);
      glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha() * Opacity * getOpacity() );

      for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
      {
		glNormal3f(osgCos(angleNow),osgSin(angleNow),0.0);
		glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgSin(angleNow), 0);
		glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgSin(angleNow), getExtrudeLength());
		angleNow -= angleDiff;
	  }
	glEnd();

    if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}
void Graphics3DExtrude::drawComplexDisc(const Pnt2f& Center, const Real32& InnerRadius, const Real32& OuterRadius, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
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
	//Front
	glBegin(GL_QUAD_STRIP);
	   glNormal3f(0.0,0.0,1.0);
		for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
		{
			glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha());
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgSin(angleNow),0.0);
			glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha());
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgSin(angleNow), 0.0);
			angleNow += angleDiff;
		}
	glEnd();
	
	//OuterArc
	angleNow = StartAngleRad;
	glBegin(GL_QUAD_STRIP);
		glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha());
		for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
		{
			glNormal3f(osgCos(angleNow),osgSin(angleNow),0.0);

			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgSin(angleNow),getExtrudeLength());
			
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgSin(angleNow),0.0);
			
			
			angleNow += angleDiff;
		}
	glEnd();

	//InnerArc
	angleNow = StartAngleRad;
	glBegin(GL_QUAD_STRIP);
		glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha());
		for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
		{
			glNormal3f(-osgCos(angleNow),-osgSin(angleNow),0.0);
			
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgSin(angleNow),0.0);
			
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgSin(angleNow),getExtrudeLength());
			
			angleNow += angleDiff;
		}
	glEnd();

	//Back
	angleNow = StartAngleRad;
	glBegin(GL_QUAD_STRIP);
	   glNormal3f(0.0,0.0,-1.0);
		for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
		{
			glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha());
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgSin(angleNow), getExtrudeLength());
			glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha());
			glVertex3f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgSin(angleNow), getExtrudeLength());
			angleNow += angleDiff;
		}
	glEnd();

	if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}

void Graphics3DExtrude::drawArc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const
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
			glVertex2f( static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow ),static_cast<Real32>(Center.y()) +static_cast<Real32>(Height)*osgSin(angleNow));
			//glVertex2f(Center.x() + Width*osgCos(angleNow + angleDiff), Center.y() + Height*osgSin(angleNow+angleDiff));
			angleNow += angleDiff;
		}
	glEnd();

	
	if(Alpha < 1.0)
	{
		glDisable(GL_BLEND);
	}
   glLineWidth(previousLineWidth);
}

void Graphics3DExtrude::drawTextUnderline(const Pnt2f& Position, const std::string& Text, UIFont* const TheFont, const Color4f& Color, const Real32& Opacity) const
{
    Pnt2f TextTopLeft, TextBottomRight;
    TheFont->getBounds(Text, TextTopLeft, TextBottomRight);
    
    Pnt2f CharacterTopLeft, CharacterBottomRight;
    TheFont->getBounds("A", CharacterTopLeft, CharacterBottomRight);
    
    //Line Start Point
    Pnt2f LineStart(Position.x() + TextTopLeft.x(), Position.y() + CharacterBottomRight.y()-1);
    //Line End Point
    Pnt2f LineEnd(LineStart + Vec2f(TextBottomRight.x()-TextTopLeft.x(),1));

    drawRect(LineStart, LineEnd, Color, Opacity);
}

void Graphics3DExtrude::drawText(const Pnt2f& Position, const std::string& Text, UIFont* const TheFont, const Color4f& Color, const Real32& Opacity) const
{
   TextLayoutParam layoutParam;
   layoutParam.spacing = 1.1;
   layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
   layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
 
   TextLayoutResult layoutResult;
   TheFont->layout(Text, layoutParam, layoutResult);

   TheFont->getTexture()->activate(getDrawEnv());

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

   TheFont->getTexture()->deactivate(getDrawEnv());

	glDisable(GL_BLEND);
   glPopAttrib();
}

void Graphics3DExtrude::drawCharacters( const TextLayoutResult& layoutResult, UIFont* const TheFont) const
{
    glBegin(GL_QUADS);

    UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
    Real32 width, height;
    for(i = 0; i < numGlyphs; ++i)
    {
        const TextTXFGlyph *glyph = TheFont->getTXFGlyph(layoutResult.indices[i]);
        width = glyph->getWidth();
        height = glyph->getHeight();
        // No need to draw invisible glyphs
        if ((width <= 0.f) || (height <= 0.f))
            continue;

        // Calculate coordinates
        const Vec2f &pos = layoutResult.positions[i];
        Real32 posLeft = pos.x();
        Real32 posTop = -pos.y();
        Real32 posRight = pos.x() + width;
        Real32 posBottom = -pos.y() + height;
        Real32 texCoordLeft = glyph->getTexCoord(TextTXFGlyph::COORD_LEFT);
        Real32 texCoordTop = glyph->getTexCoord(TextTXFGlyph::COORD_TOP);
        Real32 texCoordRight = glyph->getTexCoord(TextTXFGlyph::COORD_RIGHT);
        Real32 texCoordBottom = glyph->getTexCoord(TextTXFGlyph::COORD_BOTTOM);

        // lower left corner
		Real32 Offset(0.001);
	    glNormal3f(0.0,0.0,1.0);
        glTexCoord2f(texCoordLeft, texCoordBottom);
        glVertex3f(posLeft, posBottom, getTextOffset());

        // lower right corner
        glTexCoord2f(texCoordRight, texCoordBottom);
        glVertex3f(posRight, posBottom, getTextOffset());

        // upper right corner
        glTexCoord2f(texCoordRight, texCoordTop);
        glVertex3f(posRight, posTop, getTextOffset());

        // upper left corner
        glTexCoord2f(texCoordLeft, texCoordTop);
        glVertex3f(posLeft, posTop, getTextOffset());


    }

    glEnd();
}

void Graphics3DExtrude::incrDrawBounderiesNesting(void)
{
}

void Graphics3DExtrude::decrDrawBounderiesNestring(void)
{
}

void Graphics3DExtrude::initAddDrawBounderies(void)
{
}

void Graphics3DExtrude::uninitAddDrawBounderies(void)
{
}

void Graphics3DExtrude::initRemoveDrawBounderies(void)
{
}

void Graphics3DExtrude::uninitRemoveDrawBounderies(void)
{
}

void Graphics3DExtrude::activateDrawBounderiesTest(void)
{
}

void Graphics3DExtrude::deactivateDrawBounderiesTest(void)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Graphics3DExtrude::Graphics3DExtrude(void) :
    Inherited()
{
}

Graphics3DExtrude::Graphics3DExtrude(const Graphics3DExtrude &source) :
    Inherited(source)
{
}

Graphics3DExtrude::~Graphics3DExtrude(void)
{
}
void Graphics3DExtrude::onCreate(const Graphics3DExtrude *Id)
{
	Inherited::onCreate(Id);

    //Depth Chunk
    DepthChunkUnrecPtr TheChunk(DepthChunk::create());
    setUIDepth(TheChunk);
    getUIDepth()->setReadOnly(false);
    getUIDepth()->setEnable(true);
    getUIDepth()->setFunc(GL_LEQUAL);
}

void Graphics3DExtrude::onDestroy()
{
}


/*----------------------------- class specific ----------------------------*/

void Graphics3DExtrude::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Graphics3DExtrude::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Graphics3DExtrude NI" << std::endl;
}

OSG_END_NAMESPACE
