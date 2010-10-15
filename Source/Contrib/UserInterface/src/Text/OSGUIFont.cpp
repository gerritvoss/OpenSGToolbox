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

#include "OSGUIFont.h"
#include "OSGTextTXFParam.h"
#include "OSGTextureObjChunk.h"
#include "OSGFilePathAttachment.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIFontBase.cpp file.
// To modify it, please change the .fcd file (OSGUIFont.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIFont::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPre)
    {
        FilePathAttachment::registerHandler(getClassType(), boost::bind(&UIFont::loadFromFileHandler, _1), false);
    }
}

FieldContainerTransitPtr UIFont::createFont( const BoostPath& FilePath )
{
    UIFont* Result = UIFont::createEmpty();
    FilePathAttachment::setFilePath(Result, FilePath);
    return FieldContainerTransitPtr(Result);
}

FieldContainerUnrecPtr UIFont::loadFromFileHandler( const BoostPath& FilePath )
{
    return createFont(FilePath);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIFont::initText(void)
{
    // Create the font

    //Check if I have a FilePathAttachment
    const BoostPath* FilePath(FilePathAttachment::getFilePath(this));
    if(FilePath != NULL)
    {
        //Create the font from a file
        _face = TextTXFFace::createFromFile(FilePath->string().c_str());
    }
    else
    {
        TextTXFParam param;
        param.size = getGlyphPixelSize();
        param.gap = getGap();
        param.textureWidth = getTextureWidth();

        //Use my Family Field to create font texture
        _face = TextTXFFace::create(getFamily(), static_cast<TextFace::Style>(getStyle()), param);
    }


    TextureObjChunkUnrecPtr TheChunk(TextureObjChunk::create());
    setTexture(TheChunk);

    if (_face != NULL)
    {
        ImageRefPtr image = _face->getTexture();
        getTexture()->setImage(image);
        getTexture()->setWrapS(GL_CLAMP);
        getTexture()->setWrapT(GL_CLAMP);
        //if(getAntiAliasing())
        //{
        getTexture()->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
        getTexture()->setMagFilter(GL_LINEAR);
        //}
        //else
        //{
        //getTexture()->setMinFilter(GL_NEAREST);
        //getTexture()->setMagFilter(GL_NEAREST);
        //}
        //getTexture()->setEnvMode(GL_MODULATE);
    }

    // We failed to create the font - fallback to the default font
    //if (_face == NULL)
    //{
    //    _face = getStatisticsDefaultFont();
    //    getTexture() = getStatisticsDefaultFontTexture();
    //}

}

void UIFont::getBounds(const std::string& Text, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    TextLayoutParam layoutParam;
    layoutParam.spacing = 1.1;
    layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
    layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;

    TextLayoutResult layoutResult;
    layout(Text, layoutParam, layoutResult);

    //Vec2f BottomLeft, TopRight;
    Vec2f size = Vec2f(layoutResult.textBounds.x()*getSize(),layoutResult.textBounds.y()*getSize());
    // _face->calculateBoundingBox(layoutResult,BottomLeft, TopRight);

    TopLeft.setValues(0, 0);
    BottomRight.setValue(size);
}

Vec2f UIFont::getBounds(const std::string& Text)
{
    Pnt2f TopLeft, BottomRight;
    getBounds(Text, TopLeft, BottomRight);
    return (BottomRight-TopLeft);
}

void UIFont::layout(const std::string &utf8Text, const TextLayoutParam &param, TextLayoutResult &result)
{
    if (_face == NULL)
    {
        initText();
    }

    if (_face != NULL)
    {
        _face->layout(utf8Text,param,result);
    }
}

const TextTXFGlyph* UIFont::getTXFGlyph(TextGlyph::Index glyphIndex)
{
    if (_face == NULL)
    {
        initText();
    }

    if (_face != NULL)
    {
        return &(_face->getTXFGlyph(glyphIndex));
    }
    else
    {
        return NULL;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIFont::UIFont(void) :
    Inherited(),
    _face(NULL)
{
}

UIFont::UIFont(const UIFont &source) :
    Inherited(source),
    _face(NULL)
{
}

UIFont::~UIFont(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIFont::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(whichField & 
        ( FamilyFieldMask
        | GlyphPixelSizeFieldMask
        | GapFieldMask
        | StyleFieldMask
        | TextureWidthFieldMask 
        | AttachmentsFieldMask) )
    {
        initText();
    }
    if((whichField & AntiAliasingFieldMask) &&
        getTexture() != NULL)
    {
        //if(getAntiAliasing())
        //{
            getTexture()->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
            getTexture()->setMagFilter(GL_LINEAR);
        //}
        //else
        //{
            //getTexture()->setMinFilter(GL_NEAREST);
            //getTexture()->setMagFilter(GL_NEAREST);
        //}
    }
}

void UIFont::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIFont NI" << std::endl;
}

OSG_END_NAMESPACE
