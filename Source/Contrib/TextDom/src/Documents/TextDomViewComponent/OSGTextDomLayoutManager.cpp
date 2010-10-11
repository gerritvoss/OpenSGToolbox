/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <cstdlib>
#include <cstdio>

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGGlyphView.h"
#include "OSGTextDomArea.h"
#include "OSGTextDomLayoutManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextDomLayoutManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGTextDomLayoutManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextDomLayoutManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TextDomArea* TextDomLayoutManager::getParentTextDomArea(void) const
{
    return dynamic_cast<TextDomArea*>(_sfParentTextDomArea.getValue());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextDomLayoutManager::TextDomLayoutManager(void) :
    Inherited()
{
}

TextDomLayoutManager::TextDomLayoutManager(const TextDomLayoutManager &source) :
    Inherited(source)
{
}

TextDomLayoutManager::~TextDomLayoutManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextDomLayoutManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextDomLayoutManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextDomLayoutManager NI" << std::endl;
}

OSG_END_NAMESPACE
