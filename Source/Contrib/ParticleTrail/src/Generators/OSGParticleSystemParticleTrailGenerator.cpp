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

#include "OSGParticleSystemParticleTrailGenerator.h"
#include "OSGChunkMaterial.h"
#include "OSGBlendChunk.h"
#include "OSGLineChunk.h"
#include "OSGPointChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleSystemParticleTrailGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystemParticleTrailGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemParticleTrailGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void ParticleSystemParticleTrailGenerator::internalUpdate(ParticleSystemEventDetails* const details)
{ //nothing to do
}

void ParticleSystemParticleTrailGenerator::internalKill(ParticleEventDetails* const details)
{ // nothing to do
}

void ParticleSystemParticleTrailGenerator::internalGenerated(ParticleEventDetails* const details)
{ // nothing to do
}

void ParticleSystemParticleTrailGenerator::internalTrailSectGenerated(const TrailSection& ts,const Vec3f& ppVel)
{
    Color4f color;
    Real32 transp = 1.0f;
    if(getTransparencyDistribution() != NULL) transp = getTransparencyDistribution()->generate();
    if(getColorDistribution() == NULL)
    {
        color = Color4f(1.0f,1.0f,1.0f,transp);
    }
    else
    {
        Vec3f col = getColorDistribution()->generate();
        color = Color4f(col.x(),col.y(),col.z(),transp);
    }

    Vec3f vel(0.0f,0.0f,0.0f);
    switch(getVelocitySource())
    {
        case PARENT_PARTICLE:
            vel = ppVel;
            break;
        case BLEND:
            if(getVelocityDistribution() != NULL)
            {
                vel = (ppVel + getVelocityDistribution()->generate())*0.5;
            } else vel = ppVel;
            break;
        case DISTRIBUTION:
            if(getVelocityDistribution() != NULL)
            {
                vel = getVelocityDistribution()->generate();
            }
            break;
        case NONE:
        default:
            // no velocity
            break;

    }

    // add particle
    getParticleSystem()->addParticle(ts.pos, // position
                                     (getNormalDistribution() == NULL)?(Vec3f(0.0,1.0,0.0)):(getNormalDistribution()->generate()), // normal
                                     color, // color
                                     (getSizeDistribution() == NULL)?(Vec3f(1.0f,1.0f,1.0f)):(getSizeDistribution()->generate()),	// size
                                     (getTrailResolutionMethod() == TIME_SPACING)?(getTrailLength()):(-1.0f),// lifespan
                                     vel * getVelocityMultiplier(), //velocity
                                     (getAccelerationDistribution() == NULL)?(Vec3f(0.0f,0.0f,0.0f)):(getAccelerationDistribution()->generate())); // acceleration
    // ID will be of the last particle added, whose index will always be numParticles-1
    UInt32 particleID = _mTrailIDtoParticleIDMap[ts.ID];
    _mTrailIDtoParticleIDMap[ts.ID] = getParticleSystem()->getID((getParticleSystem()->getNumParticles())-1);
}	

void ParticleSystemParticleTrailGenerator::internalTrailSectKilled(const TrailSection& ts)
{
    // remove particle
    if(getTrailResolutionMethod() != TIME_SPACING)
    {
        getParticleSystem()->killParticleByID(_mTrailIDtoParticleIDMap[ts.ID]);
    }
    _mTrailIDtoParticleIDMap.erase(ts.ID);
}

Material* ParticleSystemParticleTrailGenerator::getTrailMaterial(void) const
{
    return dynamic_cast<ParticleSystemCore*>(getCore())->getMaterial();
}

void ParticleSystemParticleTrailGenerator::setTrailMaterial(Material* const newMaterial)
{
    dynamic_cast<ParticleSystemCore*>(getCore())->setMaterial(newMaterial);
}

void ParticleSystemParticleTrailGenerator::setTrailDrawer(ParticleSystemDrawer* const drawer)
{
    dynamic_cast<ParticleSystemCore*>(getCore())->setDrawer(drawer);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ParticleSystemParticleTrailGenerator::onCreate(const ParticleTrailGenerator *Id)
{
    // assemble default material
    PointChunkRecPtr pointChunk = PointChunk::create();
    pointChunk->setSmooth(true);

    BlendChunkRecPtr blendChunk = BlendChunk::create();

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

    PointParticleSystemDrawerRecPtr theDrawer = PointParticleSystemDrawer::create();
    theDrawer->setForcePerParticleSizing(true);

    ParticleSystemRecPtr newPS = ParticleSystem::create();
    newPS->setDynamic(true);
    setParticleSystem(newPS);

    ParticleSystemCoreRecPtr newCore = ParticleSystemCore::create();
    newCore->setSystem(newPS);
    newCore->setMaterial(mat);
    newCore->setDrawer(theDrawer);

    setCore(newCore);
}

void ParticleSystemParticleTrailGenerator::onDestroy()
{

}

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemParticleTrailGenerator::ParticleSystemParticleTrailGenerator(void) :
    Inherited()
{
}

ParticleSystemParticleTrailGenerator::ParticleSystemParticleTrailGenerator(const ParticleSystemParticleTrailGenerator &source) :
    Inherited(source)
{
}

ParticleSystemParticleTrailGenerator::~ParticleSystemParticleTrailGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemParticleTrailGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleSystemParticleTrailGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemParticleTrailGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
