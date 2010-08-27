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

#include "OSGGraphics2D.h"
#include "OSGGL.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextureBaseChunk.h"
#include "OSGDepthChunk.h"
#include "OSGPrimeMaterial.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGraphics2DBase.cpp file.
// To modify it, please change the .fcd file (OSGGraphics2D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Graphics2D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


ColorMaskChunkUnrecPtr Graphics2D::createColorMask(void)
{
    ColorMaskChunkUnrecPtr _ColorMask = ColorMaskChunk::create();
        _ColorMask->setMask(false, false, false,false);
    return _ColorMask;
}

StencilChunkUnrecPtr Graphics2D::createStenciledAreaSetup(void)
{
    StencilChunkUnrecPtr _StenciledAreaSetup = StencilChunk::create();
        _StenciledAreaSetup->setStencilFunc(GL_ALWAYS);
        _StenciledAreaSetup->setStencilOpFail(GL_INCR);
        _StenciledAreaSetup->setStencilOpZFail(GL_INCR);
        _StenciledAreaSetup->setStencilOpZPass(GL_INCR);
        _StenciledAreaSetup->setStencilMask(UInt32(0xFFFFFFFF));
    return _StenciledAreaSetup;
}

StencilChunkUnrecPtr Graphics2D::createStenciledAreaCleanup(void)
{
    StencilChunkUnrecPtr _StenciledAreaCleanup = StencilChunk::create();
        _StenciledAreaCleanup->setStencilFunc(GL_ALWAYS);
        _StenciledAreaCleanup->setStencilOpFail(GL_DECR);
        _StenciledAreaCleanup->setStencilOpZFail(GL_DECR);
        _StenciledAreaCleanup->setStencilOpZPass(GL_DECR);
        _StenciledAreaCleanup->setStencilMask(UInt32(0xFFFFFFFF));
    return _StenciledAreaCleanup;
}

StencilChunkUnrecPtr Graphics2D::createStenciledAreaTest(void)
{
    StencilChunkUnrecPtr _StenciledAreaTest = StencilChunk::create();
        _StenciledAreaTest->setStencilFunc(GL_LEQUAL);
        _StenciledAreaTest->setStencilOpFail(GL_KEEP);
        _StenciledAreaTest->setStencilOpZFail(GL_KEEP);
        _StenciledAreaTest->setStencilOpZPass(GL_KEEP);
        _StenciledAreaTest->setStencilMask(UInt32(0xFFFFFFFF));
    return _StenciledAreaTest;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Real32 Graphics2D::getClipPlaneOffset(void) const
{
    return 0.0f;
}

void Graphics2D::preDraw()
{
    //Reset the Stencil Nesting
    _StencilNesting = 0;

    glPushAttrib(GL_LIGHTING_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

    getUIDepth()->activate(getDrawEnv());

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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glClearStencil(0);
    glClear(GL_STENCIL_BUFFER_BIT);
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

    getUIDepth()->deactivate(getDrawEnv());
    glPopAttrib();
}

void Graphics2D::drawRect(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Color4f& Color, const Real32& Opacity) const
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
    glVertex2fv(TopLeft.getValues());
    glVertex2f(BottomRight.x(), TopLeft.y());
    glVertex2fv(BottomRight.getValues());
    glVertex2f(TopLeft.x(), BottomRight.y());
    glEnd();

    if(Alpha < 1.0 || getEnablePolygonAntiAliasing())
    {
        glDisable(GL_BLEND);
    }
}

void Graphics2D::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
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
    glVertex2fv(p1.getValues());
    glColor4f(c2.red(), c2.green(), c2.blue(), c2.alpha() * Opacity * getOpacity() );
    glVertex2fv(p2.getValues());
    glColor4f(c3.red(), c3.green(), c3.blue(), c3.alpha() * Opacity * getOpacity() );
    glVertex2fv(p3.getValues());
    glColor4f(c4.red(), c4.green(), c4.blue(), c4.alpha() * Opacity * getOpacity() );
    glVertex2fv(p4.getValues());
    glEnd();

    if(MinAlpha < 1.0)
    {
        glDisable(GL_BLEND);
    }
}

void Graphics2D::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
                          const Vec2f& t1, const Vec2f& t2, const Vec2f& t3, const Vec2f& t4,
                          const Color4f& color, const TextureBaseChunkUnrecPtr Texture,
                          const Real32& Opacity) const
{
    Real32 Alpha( Opacity * getOpacity() * color.alpha());
    //if(Alpha < 1.0 ||
       //(Texture-> && Texture->getImage()->hasAlphaChannel()))
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
    glTexCoord2fv(t4.getValues());
    glVertex2fv(p1.getValues());
    glTexCoord2fv(t3.getValues());
    glVertex2fv(p2.getValues());
    glTexCoord2fv(t2.getValues());
    glVertex2fv(p3.getValues());
    glTexCoord2fv(t1.getValues());
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

void Graphics2D::drawQuad(const Pnt2f& p1, const Pnt2f& p2, const Pnt2f& p3, const Pnt2f& p4, 
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

void Graphics2D::drawLine(const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32& Width, const Color4f& Color, const Real32& Opacity) const
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

void Graphics2D::drawPolygon(const MFPnt2f Verticies, const Color4f& Color, const Real32& Opacity) const
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

void Graphics2D::drawDisc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
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
    glVertex2fv(Center.getValues());
    glColor4f(OuterColor.red(), OuterColor.green(), OuterColor.blue(), OuterColor.alpha() * Opacity * getOpacity() );
    for(UInt16 i = 0 ; i<SubDivisions+1 ; ++i)
    {
        glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(Width)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(Height)*osgSin(angleNow));
        angleNow += angleDiff;
    }
    glEnd();

    if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}
void Graphics2D::drawComplexDisc(const Pnt2f& Center, const Real32& InnerRadius, const Real32& OuterRadius, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& CenterColor, const Color4f& OuterColor, const Real32& Opacity) const
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
        glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(OuterRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(OuterRadius)*osgSin(angleNow));
        glColor4f(CenterColor.red(), CenterColor.green(), CenterColor.blue(), CenterColor.alpha());
        glVertex2f(static_cast<Real32>(Center.x()) + static_cast<Real32>(InnerRadius)*osgCos(angleNow), static_cast<Real32>(Center.y()) + static_cast<Real32>(InnerRadius)*osgSin(angleNow));
        angleNow += angleDiff;
    }
    glEnd();
    if(CenterColor.alpha() < 1.0 ||
       OuterColor.alpha() < 1.0)
    {
        glDisable(GL_BLEND);
    }
}

void Graphics2D::drawArc(const Pnt2f& Center, const Real32& Width, const Real32& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color, const Real32& Opacity) const
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
        //glVertex2f(Center.x() + Width*osgcos(angleNow + angleDiff), Center.y() + Height*osgsin(angleNow+angleDiff));
        angleNow += angleDiff;
    }
    glEnd();


    if(Alpha < 1.0)
    {
        glDisable(GL_BLEND);
    }
    glLineWidth(previousLineWidth);
}

void Graphics2D::drawTextUnderline(const Pnt2f& Position, const std::string& Text, UIFont* const TheFont, const Color4f& Color, const Real32& Opacity) const
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

void Graphics2D::drawText(const Pnt2f& Position, const std::string& Text, UIFont* const TheFont, const Color4f& Color, const Real32& Opacity) const
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

void Graphics2D::drawCharacters( const TextLayoutResult& layoutResult, UIFont* const TheFont) const
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

void Graphics2D::incrDrawBounderiesNesting(void)
{
    ++_StencilNesting;
}

void Graphics2D::decrDrawBounderiesNestring(void)
{
    if(_StencilNesting != 0)
    {
        --_StencilNesting;
    }
}

void Graphics2D::initAddDrawBounderies(void)
{
    //Mask the RGBA channels
    getColorMask()->activate(getDrawEnv());

    //Setup to draw to the stencil buffer
    getStenciledAreaSetup()->setStencilValue(_StencilNesting);
    getStenciledAreaSetup()->activate(getDrawEnv());
}

void Graphics2D::uninitAddDrawBounderies(void)
{
    //Unset drawing to the stencil buffer
    getStenciledAreaSetup()->deactivate(getDrawEnv());

    //Unmask the RGBA channels
    getColorMask()->deactivate(getDrawEnv());
}

void Graphics2D::initRemoveDrawBounderies(void)
{
    //Mask the RGBA channels
    getColorMask()->activate(getDrawEnv());

    //Setup to draw to the stencil buffer
    getStenciledAreaCleanup()->setStencilValue(_StencilNesting-1);
    getStenciledAreaCleanup()->activate(getDrawEnv());
}

void Graphics2D::uninitRemoveDrawBounderies(void)
{
    //Unset drawing to the stencil buffer
    getStenciledAreaCleanup()->deactivate(getDrawEnv());

    //Unmask the RGBA channels
    getColorMask()->deactivate(getDrawEnv());
}

void Graphics2D::activateDrawBounderiesTest(void)
{
    //Setup testing against the stencil stencil buffer
    getStenciledAreaTest()->setStencilValue(_StencilNesting);
    getStenciledAreaTest()->activate(getDrawEnv());
}

void Graphics2D::deactivateDrawBounderiesTest(void)
{
    if(_StencilNesting > 0)
    {
        getStenciledAreaTest()->setStencilValue(_StencilNesting);

        //Reset testing against the stencil stencil buffer
        getStenciledAreaTest()->activate(getDrawEnv());
    }
    else
    {
        //Unset testing against the stencil stencil buffer
        getStenciledAreaTest()->deactivate(getDrawEnv());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Graphics2D::Graphics2D(void) :
    Inherited()
{
}

Graphics2D::Graphics2D(const Graphics2D &source) :
    Inherited(source)
{
}

Graphics2D::~Graphics2D(void)
{
}

void Graphics2D::onCreate(const Graphics2D *Id)
{
	Inherited::onCreate(Id);

    //Depth Chunk
    DepthChunkUnrecPtr TheChunk(DepthChunk::create());
    setUIDepth(TheChunk);
    getUIDepth()->setReadOnly(true);

    //ColorMask
    setColorMask(createColorMask());

    //Stencil Chunks
    setStenciledAreaSetup(createStenciledAreaSetup());
    setStenciledAreaCleanup(createStenciledAreaCleanup());
    setStenciledAreaTest(createStenciledAreaTest());
}

void Graphics2D::onDestroy()
{
}

/*----------------------------- class specific ----------------------------*/

void Graphics2D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Graphics2D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Graphics2D NI" << std::endl;
}

OSG_END_NAMESPACE
