/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
#include <OpenSG/OSGTextTXFParam.h>
#include <OpenSG/OSGTextureChunk.h>

#include "OSGFont.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Font
UI Font. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Font::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Font::initText(void)
{
   // Cleanup
   if (_face != NULL)
      subRefP(_face);

   // Create the font
   TextTXFParam param;
   param.size = getSize();
   param.gap = getGap();
   param.textureWidth = getTextureWidth();
   _face = TextTXFFace::create(getFamily(), static_cast<TextFace::Style>(getStyle()), param);
   if (_face != NULL)
   {
      beginEditCP(FontPtr(this), TextureFieldMask);
         setTexture(TextureChunk::create());
      endEditCP(FontPtr(this), TextureFieldMask);

      beginEditCP(getTexture());
      {
            ImagePtr image = _face->getTexture();
			image->setPixelFormat(Image::OSG_A_PF);
            getTexture()->setImage(image);
            getTexture()->setWrapS(GL_CLAMP);
            getTexture()->setWrapT(GL_CLAMP);
            getTexture()->setMinFilter(GL_NEAREST);
            getTexture()->setMagFilter(GL_NEAREST);
            getTexture()->setEnvMode(GL_MODULATE);
            //getTexture()->setEnvMode(GL_BLEND);
      }
      endEditCP(getTexture());
   }

    // We failed to create the font - fallback to the default font
    //if (_face == 0)
    //{
    //    _face = getStatisticsDefaultFont();
    //    getTexture() = getStatisticsDefaultFontTexture();
    //}

    // Increment reference counters
    addRefP(_face);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Font::Font(void) :
    Inherited(),
       _face(NULL)
{
}

Font::Font(const Font &source) :
    Inherited(source),
       _face(NULL)
{
}

Font::~Font(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Font::changed(BitVector whichField, UInt32 origin)
{
   if(whichField & 
        ( FamilyFieldMask
        | GlyphPixelSizeFieldMask
        | GapFieldMask
        | StyleFieldMask
        | TextureWidthFieldMask ) )
   {
      initText();
   }
   Inherited::changed(whichField, origin);
}

void Font::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Font NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFONTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFONTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFONTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

