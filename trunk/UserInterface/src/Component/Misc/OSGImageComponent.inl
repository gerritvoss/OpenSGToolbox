/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGImageFileHandler.h>

OSG_BEGIN_NAMESPACE

inline
void ImageComponent::setImage(const char *fileName, const char *mimeType)
{
	setImage(ImageFileHandler::the().read(fileName, mimeType));
}

inline
void ImageComponent::setRolloverImage(const char *fileName, const char *mimeType)
{
	setRolloverImage(ImageFileHandler::the().read(fileName, mimeType));
}

inline
void ImageComponent::setDisabledImage(const char *fileName, const char *mimeType)
{
	setDisabledImage(ImageFileHandler::the().read(fileName, mimeType));
}

inline
void ImageComponent::setFocusedImage(const char *fileName, const char *mimeType)
{
	setFocusedImage(ImageFileHandler::the().read(fileName, mimeType));
}

OSG_END_NAMESPACE

#define OSGIMAGECOMPONENT_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

