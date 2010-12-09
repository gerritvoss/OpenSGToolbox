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

#include "OSGPhysicsCharacteristicsDrawable.h"
#include "OSGRenderAction.h"
#include "OSGPhysicsGeomDrawFuncs.h"
#include "OSGPhysicsBodyDrawFuncs.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGBlendChunk.h"
#include "OSGDepthChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGAction.h"

#include <boost/bind.hpp>


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsCharacteristicsDrawableBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsCharacteristicsDrawable.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MaterialUnrecPtr PhysicsCharacteristicsDrawable::_DefaultMaterial = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsCharacteristicsDrawable::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            PhysicsCharacteristicsDrawable::getClassType(),
            reinterpret_cast<Action::Callback>(
                &PhysicsCharacteristicsDrawable::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            PhysicsCharacteristicsDrawable::getClassType(),
            reinterpret_cast<Action::Callback>(
                &PhysicsCharacteristicsDrawable::renderActionLeaveHandler));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

MaterialUnrecPtr PhysicsCharacteristicsDrawable::getDefaultMaterial(void) const
{
    if(_DefaultMaterial == NULL)
    {
        BlendChunkUnrecPtr TheBlend = BlendChunk::create();
        TheBlend->setSrcFactor(GL_SRC_ALPHA);
        TheBlend->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        PolygonChunkUnrecPtr ThePolyChunk = PolygonChunk::create();
        ThePolyChunk->setCullFace(GL_BACK);
        ThePolyChunk->setOffsetFactor(-1.0f);
        ThePolyChunk->setOffsetBias(2.0f);
        ThePolyChunk->setOffsetFill(true);

        MaterialChunkUnrecPtr TheMaterialChunk = MaterialChunk::create();
        TheMaterialChunk->setAmbient(Color4f(0.2f,0.2f,0.2f,1.0f));
        TheMaterialChunk->setDiffuse(Color4f(0.8f,0.8f,0.8f,1.0f));
        TheMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
        TheMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
        TheMaterialChunk->setLit(true);

        DepthChunkUnrecPtr TheDepthChunk = DepthChunk::create();
        TheDepthChunk->setEnable(true);
        TheDepthChunk->setReadOnly(false);

        _DefaultMaterial = ChunkMaterial::create();
        dynamic_pointer_cast<ChunkMaterial>(_DefaultMaterial)->addChunk(TheBlend);
        dynamic_pointer_cast<ChunkMaterial>(_DefaultMaterial)->addChunk(ThePolyChunk);
        dynamic_pointer_cast<ChunkMaterial>(_DefaultMaterial)->addChunk(TheMaterialChunk);
        dynamic_pointer_cast<ChunkMaterial>(_DefaultMaterial)->addChunk(TheDepthChunk);

    }

    return _DefaultMaterial;
}


Action::ResultE PhysicsCharacteristicsDrawable::renderActionEnterHandler(Action *action)
{
    _DrawAction = static_cast<RenderAction*>(action);

    traverse(getRoot(),
            boost::bind(&PhysicsCharacteristicsDrawable::enter,this, _1));

    if(_DrawAction->pushVisibility())
    {
        if(_DrawAction->selectVisibles() == 0)
        {
            _DrawAction->popVisibility();
            return Action::Skip;
        }
    }
    
    return Action::Continue;
}

Action::ResultE PhysicsCharacteristicsDrawable::renderActionLeaveHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);
    
    a->popVisibility();
    
    return Action::Continue;
}

void PhysicsCharacteristicsDrawable::adjustVolume(Volume & volume)
{
	Inherited::adjustVolume(volume);

	//Extend the volume to infinity
    volume.setInfinite();

}

Action::ResultE PhysicsCharacteristicsDrawable::enter(Node*& node)
{
    if(getDrawGeoms())
    {
        dropPhysicsGeom(_DrawAction, node, getGeomColor(),getDefaultMaterial());
    }
    if(getDrawJoints())
    {
    }
    if(getDrawBodies())
    {
        dropPhysicsBody(_DrawAction, node,getDefaultMaterial());
    }
    if(getDrawSpaces())
    {
    }
    if(getDrawWorlds())
    {
    }
    return Action::Continue;
}

void PhysicsCharacteristicsDrawable::fill(DrawableStatsAttachment *pStat)
{
    if(pStat == NULL)
    {
        FINFO(("PhysicsCharacteristicsDrawable::fill(DrawableStatsAttachment *): "
               "No attachment given.\n"));

        return;
    }

    //pStat->setVertices(vertices);
    //pStat->setPoints(point);
    //pStat->setLines(line);
    //pStat->setTriangles(triangle);
    //pStat->setStoredAttributeBytes(storedAttBytes);
    //pStat->setProcessedAttributeBytes(procAttBytes);
    //pStat->setValid(true);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsCharacteristicsDrawable::PhysicsCharacteristicsDrawable(void) :
    Inherited()
{
}

PhysicsCharacteristicsDrawable::PhysicsCharacteristicsDrawable(const PhysicsCharacteristicsDrawable &source) :
    Inherited(source)
{
}

PhysicsCharacteristicsDrawable::~PhysicsCharacteristicsDrawable(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsCharacteristicsDrawable::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PhysicsCharacteristicsDrawable::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsCharacteristicsDrawable NI" << std::endl;
}

OSG_END_NAMESPACE
