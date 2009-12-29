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

#include <OSGConfig.h>

#include "OSGCgfxMaterial.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCgfxMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGCgfxMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CgfxMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*
PrimeMaterial *CgfxMaterial::finalize(MaterialMapKey oKey)
{

}

void CgfxMaterial::rebuildState(void ) 
{
	
}

State  *CgfxMaterial::getState(UInt32 index = 0)
{
	
	
} 
*/

UInt32  CgfxMaterial::getNPasses(void )
{
	// will be # of cgfx render pass chks
	return 0;
}



/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CgfxMaterial::CgfxMaterial(void) :
    Inherited()
{
}

CgfxMaterial::CgfxMaterial(const CgfxMaterial &source) :
    Inherited(source)
{
}

CgfxMaterial::~CgfxMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CgfxMaterial::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CgfxMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CgfxMaterial NI" << std::endl;
}

OSG_END_NAMESPACE
