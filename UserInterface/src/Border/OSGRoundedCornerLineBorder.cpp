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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGRoundedCornerLineBorder.h"
#include "Graphics/OSGGraphics2d.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RoundedCornerLineBorder
UI Line Border. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
ColorMaskChunkPtr RoundedCornerLineBorder::_ColorMask = NullFC;
StencilChunkPtr RoundedCornerLineBorder::_StenciledAreaSetup = NullFC;
StencilChunkPtr RoundedCornerLineBorder::_StenciledAreaCleanup = NullFC;
StencilChunkPtr RoundedCornerLineBorder::_StenciledAreaTest = NullFC;

ColorMaskChunkPtr RoundedCornerLineBorder::getColorMask(void)
{
    if(_ColorMask == NullFC)
    {
        _ColorMask = ColorMaskChunk::create();
        beginEditCP(_ColorMask, ColorMaskChunk::MaskRFieldMask | ColorMaskChunk::MaskGFieldMask | ColorMaskChunk::MaskBFieldMask | ColorMaskChunk::MaskAFieldMask);
            _ColorMask->setMask(false, false, false,false);
        endEditCP(_ColorMask, ColorMaskChunk::MaskRFieldMask | ColorMaskChunk::MaskGFieldMask | ColorMaskChunk::MaskBFieldMask | ColorMaskChunk::MaskAFieldMask);
    }
    return _ColorMask;
}

StencilChunkPtr RoundedCornerLineBorder::getStenciledAreaSetup(void)
{
    if(_StenciledAreaSetup == NullFC)
    {
        _StenciledAreaSetup = StencilChunk::create();
        beginEditCP(_StenciledAreaSetup, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
            _StenciledAreaSetup->setStencilFunc(GL_ALWAYS);
            _StenciledAreaSetup->setStencilValue(1);
            _StenciledAreaSetup->setStencilMask(UInt32(0xFFFFFFFF));
            _StenciledAreaSetup->setStencilOpFail(GL_REPLACE);
            _StenciledAreaSetup->setStencilOpZFail(GL_REPLACE);
            _StenciledAreaSetup->setStencilOpZPass(GL_REPLACE);
        endEditCP(_StenciledAreaSetup, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
    }
    return _StenciledAreaSetup;
}

StencilChunkPtr RoundedCornerLineBorder::getStenciledAreaCleanup(void)
{
    if(_StenciledAreaCleanup == NullFC)
    {
        _StenciledAreaCleanup = StencilChunk::create();
        beginEditCP(_StenciledAreaCleanup, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
            _StenciledAreaCleanup->setStencilFunc(GL_ALWAYS);
            _StenciledAreaCleanup->setStencilValue(0);
            _StenciledAreaCleanup->setStencilMask(UInt32(0xFFFFFFFF));
            _StenciledAreaCleanup->setStencilOpFail(GL_ZERO);
            _StenciledAreaCleanup->setStencilOpZFail(GL_ZERO);
            _StenciledAreaCleanup->setStencilOpZPass(GL_ZERO);
        endEditCP(_StenciledAreaCleanup, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
    }
    return _StenciledAreaCleanup;
}

StencilChunkPtr RoundedCornerLineBorder::getStenciledAreaTest(void)
{
    if(_StenciledAreaTest == NullFC)
    {
        _StenciledAreaTest = StencilChunk::create();
        beginEditCP(_StenciledAreaTest, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
            _StenciledAreaTest->setStencilFunc(GL_EQUAL);
            _StenciledAreaTest->setStencilValue(1);
            _StenciledAreaTest->setStencilMask(UInt32(0xFFFFFFFF));
            _StenciledAreaTest->setStencilOpFail(GL_KEEP);
            _StenciledAreaTest->setStencilOpZFail(GL_KEEP);
            _StenciledAreaTest->setStencilOpZPass(GL_KEEP);
        endEditCP(_StenciledAreaTest, StencilChunk::StencilFuncFieldMask | StencilChunk::StencilValueFieldMask | StencilChunk::StencilOpFailFieldMask | StencilChunk::StencilOpZFailFieldMask| StencilChunk::StencilOpZPassFieldMask| StencilChunk::StencilMaskFieldMask);
    }
    return _StenciledAreaTest;
}
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RoundedCornerLineBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RoundedCornerLineBorder::draw(const GraphicsPtr g, const Int16 x, const Int16 y , const UInt16 Width, const UInt16 Height, const Real32 Opacity) const
{
	//draw corners
	g->drawComplexDisc(Pnt2s(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 3.14159265, 4.71238898, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2s(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 1.57079633, 3.14159265, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2s(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 0, 1.57079633, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2s(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 4.71238898,6.28318531, 10, getColor(), getColor(), Opacity);

	//draw sides
	g->drawRect(Pnt2s(x, y+getCornerRadius()), Pnt2s(x+getWidth(), y+Height-getCornerRadius()), getColor(), Opacity);
	g->drawRect(Pnt2s(x+getCornerRadius(), y), Pnt2s(x+Width-getCornerRadius(), y+getWidth()), getColor(), Opacity);
	g->drawRect(Pnt2s(x+Width-getWidth(), y+getCornerRadius()), Pnt2s(x+Width, y+Height-getCornerRadius()), getColor(), Opacity);
	g->drawRect(Pnt2s(x+getCornerRadius(), y+Height-getWidth()), Pnt2s(x+Width-getCornerRadius(), y+Height), getColor(), Opacity);
}

void RoundedCornerLineBorder::getInsets(UInt16& Left, UInt16& Right,UInt16& Top,UInt16& Bottom) const
{
	//TODO:Implement
	Left=Right=Top=Bottom = getWidth(); //wrong, but what else are you supposed to do?
}

void RoundedCornerLineBorder::activateInternalDrawConstraints(const GraphicsPtr g, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
{
    //Mask the RGBA channels
    getColorMask()->activate(g->getDrawAction());

    //Setup to draw to the stencil buffer
    getStenciledAreaSetup()->activate(g->getDrawAction());

    glBegin(GL_QUADS);
       glVertex2s(x-1,y+getCornerRadius()-1);
       glVertex2s(x+Width+1,y+getCornerRadius()-1);
       glVertex2s(x+Width+1,y+Height-getCornerRadius()+1);
       glVertex2s(x-1,y+Height-getCornerRadius()+1);
       
       glVertex2s(x+getCornerRadius()-1,y-1);
       glVertex2s(x+Width-getCornerRadius()+1,y-1);
       glVertex2s(x+Width-getCornerRadius()+1,y+Height+1);
       glVertex2s(x+getCornerRadius()-1,y+Height+1);
    glEnd();

    g->drawDisc(Pnt2s(x+getCornerRadius(), y+getCornerRadius()),              getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2s(x+getCornerRadius(), y+Height-getCornerRadius()),       getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2s(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2s(x+Width-getCornerRadius(), y+getCornerRadius()),        getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

    //Unset drawing to the stencil buffer
    getStenciledAreaSetup()->deactivate(g->getDrawAction());

    //Setup to draw to the stencil buffer
    getStenciledAreaCleanup()->activate(g->getDrawAction());

	//draw corners
	g->drawComplexDisc(Pnt2s(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
	g->drawComplexDisc(Pnt2s(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
	g->drawComplexDisc(Pnt2s(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
	g->drawComplexDisc(Pnt2s(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

	//draw sides
	g->drawRect(Pnt2s(x-1, y+getCornerRadius()), Pnt2s(x+getWidth(), y+Height-getCornerRadius()), getColor(), 1.0);
	g->drawRect(Pnt2s(x+getCornerRadius(), y-1), Pnt2s(x+Width-getCornerRadius(), y+getWidth()), getColor(), 1.0);
	g->drawRect(Pnt2s(x+Width-getWidth(), y+getCornerRadius()), Pnt2s(x+Width+1, y+Height-getCornerRadius()), getColor(), 1.0);
	g->drawRect(Pnt2s(x+getCornerRadius(), y+Height-getWidth()), Pnt2s(x+Width-getCornerRadius(), y+Height+1), getColor(), 1.0);

    //Unset drawing to the stencil buffer
    getStenciledAreaCleanup()->deactivate(g->getDrawAction());

    //Unmask the RGBA channels
    getColorMask()->deactivate(g->getDrawAction());
    
    //Setup testing against the stencil stencil buffer
    getStenciledAreaTest()->activate(g->getDrawAction());
}

void RoundedCornerLineBorder::deactivateInternalDrawConstraints(const GraphicsPtr g, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
{
    //Unset testing against the stencil stencil buffer
    getStenciledAreaTest()->deactivate(g->getDrawAction());
    
    //Mask the RGBA channels
    getColorMask()->activate(g->getDrawAction());

    //Setup to draw to the stencil buffer
    getStenciledAreaCleanup()->activate(g->getDrawAction());

    glBegin(GL_QUADS);
       glVertex2s(x-2,y-2);
       glVertex2s(x+Width+2,y-2);
       glVertex2s(x+Width+2,y+Height+2);
       glVertex2s(x-2,y+Height+2);
    glEnd();

    //Unset drawing to the stencil buffer
    getStenciledAreaCleanup()->deactivate(g->getDrawAction());

    //Unmask the RGBA channels
    getColorMask()->deactivate(g->getDrawAction());
}

bool RoundedCornerLineBorder::isContained(const Pnt2s& p, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
{
    bool AreCornersContained(true);
    //TopLeft Corner
    if(p.x() >= x && p.x() <= x+getCornerRadius() &&
            p.y() >= y && p.y() <= y+getCornerRadius())
    {
        Real32 Length = p.dist(Pnt2s(x+getCornerRadius(),y+getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //BottomLeft Corner
    if(p.x() >= x && p.x() <= x+getCornerRadius() &&
            p.y() >= y+Height-getCornerRadius() && p.y() <= y+Height)
    {
        Real32 Length = p.dist(Pnt2s(x+getCornerRadius(),y+Height-getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //TopRight Corner
    if(p.x() >= x+Width-getCornerRadius() && p.x() <= x+Width &&
            p.y() >= y && p.y() <= y+getCornerRadius())
    {
        Real32 Length = p.dist(Pnt2s(x+Width-getCornerRadius(),y+getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //BottomRight Corner
    if(p.x() >= x+Width-getCornerRadius() && p.x() <= x+Width &&
            p.y() >= y+Height-getCornerRadius() && p.y() <= y+Height)
    {
        Real32 Length = p.dist(Pnt2s(x+Width-getCornerRadius(),y+Height-getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    return AreCornersContained &&
           (p.x() >= x && p.x() <= x+Width &&
            p.y() >= y && p.y() <= y+Height);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RoundedCornerLineBorder::RoundedCornerLineBorder(void) :
    Inherited()
{
}

RoundedCornerLineBorder::RoundedCornerLineBorder(const RoundedCornerLineBorder &source) :
    Inherited(source)
{
}

RoundedCornerLineBorder::~RoundedCornerLineBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RoundedCornerLineBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RoundedCornerLineBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RoundedCornerLineBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGROUNDEDCORNERLINEBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGROUNDEDCORNERLINEBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGROUNDEDCORNERLINEBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

