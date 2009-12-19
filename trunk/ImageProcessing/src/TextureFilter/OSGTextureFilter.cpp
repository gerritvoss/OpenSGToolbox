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

#include "OSGTextureFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TextureChunkPtr TextureFilter::pullTexture(UInt8 OutputSlot) const
{
    assert(false && "pullTexture() not defined for this TextureFilterType.");
    return NullFC;
}

void TextureFilter::update(RenderActionBase *action, const Vec2f& DrawnSize)
{
    if(isDirty())
    {
        for(UInt32 i(0) ; i < getNumInputSlots() ; ++i)
        {
            editInputSlot(i)->getSourceFilter()->update(action, DrawnSize);
        }

        internalUpdate(action, DrawnSize);

        setDirty(false);
    }
}

bool TextureFilter::attachSource(TextureFilterPtr OutputSlotSrc, UInt8 OutputSlot, UInt8 InputSlot)
{
    if(!OutputSlotSrc->isSource())
    {
        SWARNING << "TextureFilter::attachSource(): Cannot attach source filter, because the filter is not a Source." << std::endl;
        return false;
    }
    if(!isSink())
    {
        SWARNING << "TextureFilter::attachSource(): Cannot attach filters to this TextureFilter, because this TextureFilter is not a Sink." << std::endl;
        return false;
    }
    if(getNumInputSlots() > 0 && InputSlot >= getNumInputSlots())
    {
        SWARNING << "TextureFilter::attachSource(): Cannot attach filters to slot " << InputSlot << ", becuase there are only " << getNumInputSlots() << " slots." << std::endl;
        return false;
    }

    if(getNumOutputSlots() > 0 && OutputSlot >= getNumOutputSlots())
    {
        SWARNING << "TextureFilter::attachSource(): Cannot attach filter from output slot " << OutputSlot << ", becuase there are only " << getNumOutputSlots() << " slots on that filter." << std::endl;
        return false;
    }

    if(OutputSlotSrc == NullFC)
    {
        SWARNING << "TextureFilter::attachSource(): Attempting to attach a NullFC TextureFilter." << std::endl;
        return false;
    }


    //Check for Cycles
    if(wouldMakeCyclic(OutputSlotSrc))
    {
        SWARNING << "TextureFilter::attachSource(): Failed to add source filter, because doing so would create a cycle in the filter graph." << std::endl;
        return false;
    }
    TextureFilterInputSlot* InputSlotObj(editInputSlot(InputSlot));
    TextureFilterOutputSlot* OutputSlotObj(editOutputSlot(OutputSlot));

    //Check if the Input slot is already attach to something else
    if(InputSlotObj->isAttached())
    {
        SWARNING << "TextureFilter::attachSource(): Failed to attach output slot " << OutputSlot << " of the given source Filter to input slot " << InputSlot << " because that slot is already attached to another TextureFilter." << std::endl;
        return false;
    }

    //Check if the Formats for the slots are compatable
    if((InputSlotObj->getTextureFormatClasses() & OutputSlotObj->getTextureFormatClasses()) == 0 )
    {
        SWARNING << "TextureFilter::attachSource(): Failed to attach output slot " << OutputSlot << " of the given source Filter to input slot " << InputSlot << " because the data format of those two slots are not compatable." << std::endl;
        return false;
    }

    //Check if the Data types for the slots are compatable


    //Attach this given filter to the InputSlot
    InputSlotObj->setSourceFilter(OutputSlotSrc);
    InputSlotObj->setSourceFilterOutputSlot(OutputSlot);

    //Attach this Filter to the Output Slot of the given Filter
    OutputSlotSrc->attachOutputSlot(TextureFilterPtr(this), InputSlot);

    //Flag this filter as dirty
    setDirty(true);
    return true;

}

bool TextureFilter::detachSource(UInt8 InputSlot)
{
    if( getNumInputSlots() < -1 || 
        InputSlot < getNumInputSlots())
    {
        TextureFilterInputSlot* InputSlotObj(editInputSlot(InputSlot));
        if(InputSlotObj->isAttached())
        {
            //Detach this Filter from the OutputSlot of the given Filter
            InputSlotObj->getSourceFilter()->detachOutputSlot(TextureFilterPtr(this), InputSlotObj->getSourceFilterOutputSlot());

            //Detach the filter at this InputSlot 
            InputSlotObj->setSourceFilter(NullFC);

            //Flag this filter as dirty
            setDirty(true);

            return true;
        }
    }
    return false;
}


TextureFilterPtr TextureFilter::getSource(UInt8 InputSlot) const
{
    const TextureFilterInputSlot* InputSlotObj(getInputSlot(InputSlot));
    if(InputSlotObj->isAttached())
    {
        return InputSlotObj->getSourceFilter();
    }
    else
    {
        return NullFC;
    }
}


bool TextureFilter::attachOutputSlot(TextureFilterPtr Sink, UInt8 SinkInputSlot, UInt8 OutputSlot)
{
    if(Sink != NullFC)
    {
        TextureFilterOutputSlot* OutputSlotObj(editOutputSlot(OutputSlot));
        OutputSlotObj->addSinkFilter(Sink, SinkInputSlot);

        return true;
    }
    else
    {
        return false;
    }
}

bool TextureFilter::detachOutputSlot(TextureFilterPtr Sink, UInt8 SinkInputSlot, UInt8 OutputSlot)
{
    if(Sink != NullFC)
    {
        TextureFilterOutputSlot* OutputSlotObj(editOutputSlot(OutputSlot));
        if(OutputSlotObj != NULL )
        {
            OutputSlotObj->removeSinkFilter(Sink, SinkInputSlot);

            return true;
        }
    }
    return false;
}

bool TextureFilter::isDirty(void) const
{
    const TextureFilterInputSlot* InputSlotObj(NULL);
    for(UInt32 i(0) ; i < getNumInputSlots() ; ++i)
    {
        InputSlotObj = getInputSlot(i);
        if(InputSlotObj != NULL && InputSlotObj->getSourceFilter()->isDirty())
        {
            return true;
        }
    }

    return getInternalDirty();
}

void TextureFilter::setDirty(bool dirty)
{
    beginEditCP(TextureFilterPtr(this), TextureFilter::InternalDirtyFieldMask);
        setInternalDirty(dirty);
    endEditCP(TextureFilterPtr(this), TextureFilter::InternalDirtyFieldMask);
}

bool TextureFilter::wouldMakeCyclic(TextureFilterPtr Src)
{
    //Adding this source would make this Filter graph cyclic iff
    //this Filter is one of the downstream nodes

    if(Src == TextureFilterPtr(this))
    {
        return true;
    }

    bool Result(false);
    const TextureFilterInputSlot* InputSlotObj(NULL);
    for(UInt32 i(0) ; i < getNumInputSlots() ; ++i)
    {
        InputSlotObj = getInputSlot(i);
        if(InputSlotObj != NULL && 
			InputSlotObj->getSourceFilter() != NullFC&& 
			InputSlotObj->getSourceFilter()->wouldMakeCyclic(Src))
        {
            return true;
        }
    }

    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureFilter::TextureFilter(void) :
    Inherited()
{
}

TextureFilter::TextureFilter(const TextureFilter &source) :
    Inherited(source)
{
}

TextureFilter::~TextureFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

}

void TextureFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextureFilter NI" << std::endl;
}


OSG_END_NAMESPACE

