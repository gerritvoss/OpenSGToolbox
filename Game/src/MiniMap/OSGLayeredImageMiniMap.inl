/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *					Authors: David Kabala, Eric Langkamp					 *
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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGImageFileHandler.h>

OSG_BEGIN_NAMESPACE

inline
void LayeredImageMiniMap::setLayer(UInt32 index, Real32 DistanceFromPrevious, const char *fileName, const char *mimeType)
{
	setLayer(index, DistanceFromPrevious, ImageFileHandler::the().read(fileName, mimeType));
}
inline
void LayeredImageMiniMap::insertLayer(const char *fileName, Real32 DistanceFromPrevious, const char *mimeType)
{
	insertLayer(ImageFileHandler::the().read(fileName, mimeType), DistanceFromPrevious);
}

inline
void LayeredImageMiniMap::insertLayer(UInt32 index, Real32 DistanceFromPrevious, const char *fileName, const char *mimeType)
{
	insertLayer(index, DistanceFromPrevious, ImageFileHandler::the().read(fileName, mimeType));
}

OSG_END_NAMESPACE

#define OSGLAYEREDIMAGEMINIMAP_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

