/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#include "OSGSimpleParticleTrailGenerator.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGChunkMaterial.h"
#include "OSGBlendChunk.h"
#include "OSGLineChunk.h"
#include "OSGPointChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGGeometry.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSimpleParticleTrailGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGSimpleParticleTrailGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SimpleParticleTrailGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SimpleParticleTrailGenerator::internalUpdate(ParticleSystemEventDetails* const details)
{	
    static int updates(0);
    static int nonUpdates(0);
    if(updateNeeded)
    {
        switch(getDrawMethod())
        {
            case POINTS:
                updatePoints();
                break;
            case LINES:
                updateLines();
                break;
            default:
                break;
        }

        updateNeeded = false;
    } 

    return;
}

void SimpleParticleTrailGenerator::internalKill(ParticleEventDetails* const details)
{	// since a particle was killed, we need a full update
    updateNeeded = true;
}

void SimpleParticleTrailGenerator::internalGenerated(ParticleEventDetails* const details)
{	// since a particle was generated, we need a full update
    updateNeeded = true;
}

void SimpleParticleTrailGenerator::internalTrailSectGenerated(const TrailSection& ts, const Vec3f& ppVel)
{	// since a particle trail section has been added, we need a full update
    updateNeeded = true;
}

void SimpleParticleTrailGenerator::internalTrailSectKilled(const TrailSection& ts)
{
    // since a particle trail section has been killed, we need a full update
    updateNeeded = true;
}


void SimpleParticleTrailGenerator::updatePoints(void)
{
    GeometryRecPtr geo = dynamic_cast<Geometry*>(getCore());
    
    GeoUInt32PropertyRecPtr types = dynamic_cast<GeoUInt32Property*>(geo->getTypes());
    if(types == NULL)
    {
        types = GeoUInt32Property::create();
        geo->setTypes(types);
    }
    types->clear();
    types->addValue(GL_POINTS);

    GeoPnt3fPropertyRecPtr pos = dynamic_cast<GeoPnt3fProperty*>(geo->getPositions());
    if(pos == NULL)
    {
        pos = GeoPnt3fProperty::create();
        geo->setPositions(pos);
    }
    pos->clear();
    int numPnts(0);
    for(PTMItor it = _mTrails.begin(); it != _mTrails.end(); it++)
    {
        numPnts += (*it).second.size();
        for(ParticleTrail::iterator itor = (*it).second.begin(); itor != (*it).second.end(); ++itor)
        {
            pos->addValue((*itor).pos);
        }
    }

    for(PTMItor it = _mKilledParticleTrails.begin(); it != _mKilledParticleTrails.end(); it++)
    {
        numPnts += (*it).second.size();
        for(ParticleTrail::iterator itor = (*it).second.begin(); itor != (*it).second.end(); ++itor)
        {
            pos->addValue((*itor).pos);
        }
    }


    GeoUInt32PropertyRecPtr lengths = dynamic_cast<GeoUInt32Property*>(geo->getLengths());
    if(lengths == NULL)
    {
        lengths = GeoUInt32Property::create();
        geo->setLengths(lengths);
    }
    lengths->clear();
    lengths->addValue(numPnts);   // # of pts to be drawn

    if(numPnts == 0)
    {
        geo->setTypes(NULL);
        geo->setLengths(NULL);
        geo->setPositions(NULL);
    }
}

void SimpleParticleTrailGenerator::updateLines(void)
{
    GeometryRecPtr geo = dynamic_cast<Geometry*>(getCore());
    
    GeoUInt32PropertyRecPtr types = dynamic_cast<GeoUInt32Property*>(geo->getTypes());
    if(types == NULL)
    {
        types = GeoUInt32Property::create();
        geo->setTypes(types);
    }
    types->clear();

    GeoPnt3fPropertyRecPtr pos = dynamic_cast<GeoPnt3fProperty*>(geo->getPositions());
    if(pos == NULL)
    {
        pos = GeoPnt3fProperty::create();
        geo->setPositions(pos);
    }
    pos->clear();

    GeoUInt32PropertyRecPtr lengths = dynamic_cast<GeoUInt32Property*>(geo->getLengths());
    if(lengths == NULL)
    {
        lengths = GeoUInt32Property::create();
        geo->setLengths(lengths);
    }
    lengths->clear();

    for(PTMItor it = _mTrails.begin(); it != _mTrails.end(); it++)
    {
        if((*it).second.size() > 0)
        {
            types->addValue(GL_LINE_STRIP);
            for(ParticleTrail::iterator itor = (*it).second.begin(); itor != (*it).second.end(); ++itor)
            {
                pos->addValue((*itor).pos);
            }
            lengths->addValue((*it).second.size()); // # of vertices in this line segment
        }
    }

    for(PTMItor it = _mKilledParticleTrails.begin(); it != _mKilledParticleTrails.end(); it++)
    {
        if((*it).second.size() > 0)
        {
            types->addValue(GL_LINE_STRIP);
            for(ParticleTrail::iterator itor = (*it).second.begin(); itor != (*it).second.end(); ++itor)
            {
                pos->addValue((*itor).pos);
            }
            lengths->addValue((*it).second.size()); // # of vertices in this line segment
        }
    }

    if(lengths->size() == 0)
    {
        geo->setTypes(NULL);
        geo->setLengths(NULL);
        geo->setPositions(NULL);
    }
}

Material* SimpleParticleTrailGenerator::getTrailMaterial() const
{
    return dynamic_cast<Geometry*>(getCore())->getMaterial();
}

void SimpleParticleTrailGenerator::setTrailMaterial(Material* const trailMaterial)
{
    dynamic_cast<Geometry*>(getCore())->setMaterial(trailMaterial);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SimpleParticleTrailGenerator::onCreate(const SimpleParticleTrailGenerator *Id)
{
    //assemble a basic material to use for trail
    // Material point chunk, so particles are drawn as points
    PointChunkRecPtr pointChunk = PointChunk::create();
    pointChunk->setSmooth(true);

    BlendChunkRecPtr blendChunk = BlendChunk::create();

    LineChunkRecPtr lineChunk = LineChunk::create();

    //Particle System Material
    MaterialChunkRecPtr materialChunkChunk = MaterialChunk::create();
    materialChunkChunk->setAmbient(Color4f(0.5f,0.5f,0.5f,1.0f));
    materialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    materialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
    materialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    // Assembling materials
    ChunkMaterialRecPtr mat = ChunkMaterial::create();
    mat->addChunk(materialChunkChunk);
    mat->addChunk(pointChunk);
    mat->addChunk(blendChunk);
    mat->addChunk(lineChunk);
    mat->setTransparencyMode(Material::TransparencyForceTransparent);

    // using a geometry as the core and to draw
    GeometryRecPtr geo = Geometry::create();
    geo->setDlistCache(false); // geometry will be changing fequently, so we disable list caches
    geo->setMaterial(mat); // default material we just assembled

    setCore(geo);	

    updateNeeded = true;
}

void SimpleParticleTrailGenerator::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

SimpleParticleTrailGenerator::SimpleParticleTrailGenerator(void) :
    Inherited()
{
}

SimpleParticleTrailGenerator::SimpleParticleTrailGenerator(const SimpleParticleTrailGenerator &source) :
    Inherited(source)
{
}

SimpleParticleTrailGenerator::~SimpleParticleTrailGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SimpleParticleTrailGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SimpleParticleTrailGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SimpleParticleTrailGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
