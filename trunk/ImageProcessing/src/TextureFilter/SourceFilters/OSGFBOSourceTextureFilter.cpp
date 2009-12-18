/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#define OSG_COMPILEIMAGEPROCESSINGLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImage.h>

#include "OSGFBOSourceTextureFilter.h"

#include <OpenSG/OSGFBOViewport.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FBOSourceTextureFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FBOSourceTextureFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TextureChunkPtr FBOSourceTextureFilter::pullTexture(UInt8 OutputSlot) const
{
    return getFBO()->getTextures(OutputSlot);
}

std::string FBOSourceTextureFilter::getDescription(void) const
{
    return std::string("");
}

void FBOSourceTextureFilter::internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize)
{
    Vec2f NewFBOSize(getFBOSize());
    ImagePtr TheImage(getFBO()->getTextures(0)->getImage());
    if(getFBOSize().x() < 0.0f)
    {
        NewFBOSize[0] = DrawnSize.x();
    }
    if(getFBOSize().y() < 0.0f)
    {
        NewFBOSize[1] = DrawnSize.y();
    }
    if(Vec2f(TheImage->getWidth(), TheImage->getHeight()) != NewFBOSize)
    {
        //If the size of the FBO Texture has changed then update it
        for( unsigned int nt = 0; nt < getFBO()->getTextures().getSize(); ++ nt )
        {
            osg::TextureChunkPtr tex = getFBO()->getTextures()[nt];
            beginEditCP (tex);
                beginEditCP(tex->getImage());
                    tex->getImage()->set(tex->getImage()->getPixelFormat(),NewFBOSize.x(), NewFBOSize.y() );
                endEditCP(tex->getImage());
            endEditCP (tex);
        }

        beginEditCP(getFBO(), FBOViewport::DirtyFieldMask | FBOViewport::LeftFieldMask | FBOViewport::RightFieldMask | FBOViewport::BottomFieldMask | FBOViewport::TopFieldMask | FBOViewport::StorageHeightFieldMask | FBOViewport::StorageWidthFieldMask);
            getFBO()->setSize(0,0,NewFBOSize.x()-1, NewFBOSize.y()-1);
            
            getFBO()->setStorageWidth(NewFBOSize.x());
            getFBO()->setStorageHeight(NewFBOSize.y());
            getFBO()->setDirty(true);

        endEditCP(getFBO(), FBOViewport::DirtyFieldMask | FBOViewport::LeftFieldMask | FBOViewport::RightFieldMask | FBOViewport::BottomFieldMask | FBOViewport::TopFieldMask | FBOViewport::StorageHeightFieldMask | FBOViewport::StorageWidthFieldMask);
    }

    //Update the parent wintow of the FBO
    WindowPtr ParentWin(action->getWindow());
    if(getFBO()->getParent() != ParentWin)
    {
        beginEditCP(getFBO(), FBOViewport::ParentFieldMask);
            getFBO()->setParent(ParentWin);
        endEditCP(getFBO(), FBOViewport::ParentFieldMask);
    }

    getFBO()->render(action);
}


Int32 FBOSourceTextureFilter::getNumOutputSlots(void) const
{
    //TODO: Implement
    return 1;
}

TextureFilterOutputSlot* FBOSourceTextureFilter::editOutputSlot(UInt32 OutputSlot)
{
    //TODO: Implement
    return NULL;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FBOSourceTextureFilter::FBOSourceTextureFilter(void) :
    Inherited()
{
}

FBOSourceTextureFilter::FBOSourceTextureFilter(const FBOSourceTextureFilter &source) :
    Inherited(source)
{
}

FBOSourceTextureFilter::~FBOSourceTextureFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FBOSourceTextureFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FBOSourceTextureFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FBOSourceTextureFilter NI" << std::endl;
}


OSG_END_NAMESPACE

