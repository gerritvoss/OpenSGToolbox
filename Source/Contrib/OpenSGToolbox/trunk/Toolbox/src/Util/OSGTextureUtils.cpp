/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
#include "OSGTextureUtils.h"
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

TextureChunkPtr createTexture(ImagePtr Image)
{
	TextureChunkPtr TexChunk = TextureChunk::create();
	beginEditCP(TexChunk, TextureChunk::ImageFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::EnvModeFieldMask);
		TexChunk->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
		TexChunk->setMagFilter(GL_LINEAR);
		TexChunk->setWrapS(GL_CLAMP);
		TexChunk->setWrapT(GL_CLAMP);
		TexChunk->setEnvMode(GL_MODULATE);
		TexChunk->setImage(Image);
	endEditCP(TexChunk, TextureChunk::ImageFieldMask | TextureChunk::MinFilterFieldMask | TextureChunk::MagFilterFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask | TextureChunk::EnvModeFieldMask);
	return TexChunk;
}

OSG_END_NAMESPACE

